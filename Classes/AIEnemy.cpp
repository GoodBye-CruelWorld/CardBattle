#include "Battle.h"
#include "AIEnemy.h"


CAIEnemy::CAIEnemy(CBattle* b)
{
	bat = b;
	for (int i = 0; i < 5; i++)
		place[i] =true;
	delayTime = 4;
}


CAIEnemy::~CAIEnemy()
{
}

float CAIEnemy::AiTurn(){
	/*bat->runAction(Sequence::create(
		DelayTime::create(2),
		CallFunc::create(CC_CALLBACK_0(CAIEnemy::AiCummom, this)),
		NULL));
	bat->runAction(Sequence::create(
		DelayTime::create(4),
		CallFunc::create(CC_CALLBACK_0(CAIEnemy::AiAttack, this)),
		NULL));*/
	AiCummom();
	AiAttack();
	//delayTime = 5;
	//for (int i = 0; i < bat->_cardPool[POOL_BATTLE].size(); i++)	
	//	delayTime += 1;
	auto dT = bat->_gameboard->getActionQueue()->getDelayTime();/*获取动画序列总延迟时间*/
	return dT;
}

void CAIEnemy::AiCummom(){
	auto c = bat->_cardPool[POOL_HAND];//手牌
	int pts = bat->ActionPoints;//行动点
	int k = c.size();//手牌数量
	vector<int> p,v, n;
	for (int i = 0; i < k; i++){
		p.push_back(c[i].get_cost());
		v.push_back(c[i].get_attack() + c[i].get_health());
	}
	n = dp(p, v, pts, c);//决策出哪张牌
	//delayTime = 10;
	k = 0;
	for (int i = 0; i < n.size(); i++){
		if (!AiCummon(n[i] - k)) break;
		k++;
	}
}
/*
我们认为一个随从的价值是A attack H health S Spell构成
价值点数P CostPoint被召唤消耗C Cost决定
那么根据P=A+H+S=2C+3
一个随从的现有价值就是A+H+S因为目前没有S可以确定 攻击力也不会改变
那么现有价值和现有生命h挂钩 即P=A+h+S=2C+3-失去生命
但是从交换的角度考虑 受伤的随从更有交换价值 -（同样是4/2 但是受伤的雪人比王牌更有交换价值 而却费用有部分算在战吼里
S后来会用spell里的函数来具体确定，所以暂不考虑 P=A+h（以后会算上受伤的价值收益
另一方面可以认为 高攻的随从更有交换价值
4/2比3/3更容易交换 所以这部分价值可以归类到战损里（交换时受伤更多 公式不做调整											——@1

然后根据死后价值收益不确定（尤其之后引入炉石的亡语的要素之后）不采用动态规划（在确定具体交换时使用），直接采用贪心
以每个随从计算交换产生价值 交换随从时 从ai角度考虑
若不能交换 则该随从不会受到ai攻击
若能交换 参考价值收益
ai所有随从产生价值如果不死亡 收益为P-A'('表示ai）若死亡则为P-A'-P'
（引入A'是因为若不交换则产生了攻击英雄的血量收益 不考虑交换时ai随从受到伤害，是参考@1而相抵消
若收益为正 则执行交换
若不为正 则视为不能交换
以下是计算描述中P的函数
*/
//计算随从交换价值
float CAIEnemy::calcValue(int Num1, int Num2){
	if (Num1 == -1) {
		auto t = bat->_enemy->_cardPool[POOL_BATTLE];
		return t[Num2].get_attackBattle() + t[Num2].get_healthBattle();
	}
	else {
		auto t = bat->_cardPool[POOL_BATTLE];
		return t[Num1].get_attackBattle() + t[Num1].get_healthBattle();
	}
}


//一个递归找到局部最优解法的小函数 返回值在atkCard中
void CAIEnemy::find(int Value, int Attack, int HealthRest){
	auto c = bat->_cardPool[POOL_BATTLE];
	if (HealthRest <= 0 && Value > _atkCard[0]){
		_atkCard.clear();
		_atkCard.push_back(Value);
		for (int i = 0; i < 5; i++){
			if (_atkF[i] == -2) _atkCard.push_back(i);
		}
	}
	else{
		for (int i = 0; i < 5; i++){
			if (_atkF[i] == -1){
				_atkF[i] = -2;
				find(Value - (Attack >= c[i].get_healthBattle() ? calcValue(i, -1) : 0) - c[i].get_attackBattle() / 2, Attack, HealthRest - c[i].get_attackBattle());
				_atkF[i] = -1;
			}
		}
	}

}



void CAIEnemy::AiAttack()
{
	auto c = bat->_cardPool[POOL_BATTLE];
	int k = c.size();
	float t = 0;
	
	for (int i = 0; i < 5; i++)
	{
		//表示攻击英雄
		if (i < k) 
			_atkF[i] = -1;
		else 
			_atkF[i] = -3;
	}

	auto ce = bat->_enemy->_cardPool[POOL_BATTLE];
	/*
	*/
	for (int i = 0; i < ce.size(); i++){
		_atkCard.clear();
		_atkCard.push_back(-3);
		find(calcValue(-1, i), ce[i].get_attackBattle(), ce[i].get_healthBattle());
		for (int j = 1; j < _atkCard.size(); j++)
			_atkF[_atkCard[j]] = i;
	}
	CCard *a[5], *b[5];
	for (int i = 0; i < k; i++){
		a[i] = &(bat->_cardPool[POOL_BATTLE][i]);
		b[i] = nullptr;
		if (_atkF[i] >= 0) 
			b[i] = &bat->_enemy->_cardPool[POOL_BATTLE].at(_atkF[i]);
	}
	//每个随从轮流打脸
	int s1 = c.size(), s2 = ce.size();
	/*for (int i = 0; i < k; i++){
		bat->runAction(Sequence::create(
			DelayTime::create(t++),
			CallFunc::create(CC_CALLBACK_0(CAIEnemy::AiAttackTo, this, i, _atkF[i], s1, s2)),
			NULL));
	}*/
	for (int i = 0; i < k; i++){
		AiAttackTo(i, _atkF[i], s1, s2);
	}
}

void CAIEnemy::AiAttackTo(int num1, int num2, int s1, int s2)
{
	num1 -= s1 - bat->_cardPool[POOL_BATTLE].size();
	if (num2 >= 0) num2 -= s2 - bat->_enemy->_cardPool[POOL_BATTLE].size();
	if (num2 < 0){
		bat->CardAttack(num1);
	}
	else
	{
		bat->cardAttack(num1,bat->_camp, num2,!bat->_camp);
	}
	
}

bool CAIEnemy::AiCummon(int num){
	//bat->ActionPoints;
	//bat->_cardPool[POOL_HAND][0].flagNum=1;
	int t = setPlace();
	if (t == -1) return false;
	bat->CardCummon(bat->_cardPool[POOL_HAND], bat->_cardPool[POOL_BATTLE], num, 0,t);

	//bat->_gameboard->getCard(bat->_cardPool[POOL_BATTLE][0].flagNum)->transFromHandToBattle(t,1);
	//bat->_gameboard->cardTransfer(POOL_HAND,POOL_BATTLE,0,1,1,)
	place[t] = false;
	//bat->_cardPool[POOL_HAND][0].flagNum = ;
	return true;
	
}

/*
void CAIEnemy::Turning(){
	vector<CCard> VCVcard = Value_Cost();//检测使用卡牌最优解
	AICardUse(VCVcard);//使用卡牌
	AICheckAttack();//随从攻击
	TurnOver();
}


bool CAIEnemy::AICardUse(vector<CCard>&card){
	//使用每张卡牌
}


void CAIEnemy::AICheckAttack(){
	vector<CCard> &Ecard = Enemy->_cardPool[POOL_BATTLE];//敌人的卡牌引用
	int k, v;
	vector<CCard> cardAtt, cardTemp;//攻击随从的数组和临时随从的数组
	CCard cardT;
	do{
		k = Ecard.size;//随从交换决策 再议
		v = -10000;
		for (int i = 0; i < k; i++){
			int v_e = Value_EXMin(Ecard[i], cardTemp);
			if (v_e > v){
				v = v_e;
				cardT = Ecard[i];//cardT为被攻击随从
				cardAtt = cardTemp;//cardTemp为攻击随从-数组
			}
		}
		//调用攻击
		AICardAttack(cardTemp, cardT);
	} while (v >= 0);//若检测下来发下不能获得正价值 则结束
}


void CAIEnemy::AICardAttack(vector<CCard>&card, CCard &beAttCard){
	int k = card.size;
	for (int i = 0; i < k; i++){
		if (beAttCard.Pos == 2){
			CardAttack(card[i], beAttCard);
		}
		else
			return;
	}
}
double CAIEnemy::Value(CCard &card){
	return card.GetAttack() + card.GetHealth() + Value_Spell(card);
} 

double CAIEnemy::Value_Spell(CCard &card){
	//计算卡牌异能的价值
}
double CAIEnemy::Value_EXMin(CCard &card,vector<CCard>&cardT){
	//动态规划算法计算换取最小值
}

vector<CCard> CAIEnemy::Value_Cost(){
	vector<CCard> Vcard;

}

bool CAIEnemy::KO(){
	KO(this);
}

bool CAIEnemy::KO(CBattle *player){
	int health_hero;//=英雄血量
	vector<CCard> &cib = player->Enemy->_cardPool[POOL_BATTLE];
	int k = cib.size, s = 0;//计算场功
	for (int i = 0; i < k; i++){
		s += cib[i].GetAttack();
	}
	if (s >= health_hero) return true;
	return false;
}
*/

vector<int> CAIEnemy::dp(vector<int>&p, vector<int>&v, int m, vector<CCard> &card){
	int n = p.size();
	int f[100] = {};
	vector<int> cardN[100];
	for (int i = 0; i < n; i++){
		for (int j = m; j >= p[i]; j--){
			if (f[j - p[i]] + v[i] > f[j]){
				f[j] = f[j - p[i]] + v[i];
				cardN[j] = cardN[j - p[i]];
				cardN[j].push_back(i);
			}
		}
	}
	return cardN[m];
}

int CAIEnemy::setPlace(){
	int p[5] = { 2, 1, 3, 0,-1 };
	//int p[5] = { 3,2, 1,  0, -1 };
	int i = 0;
	while (!place[p[i]]) i++;
	return p[i];
}