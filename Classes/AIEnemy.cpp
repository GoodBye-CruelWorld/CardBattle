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
	auto dT = bat->_gameboard->getActionQueue()->getDelayTime();/*��ȡ�����������ӳ�ʱ��*/
	return dT;
}

void CAIEnemy::AiCummom(){
	auto c = bat->_cardPool[POOL_HAND];//����
	int pts = bat->ActionPoints;//�ж���
	int k = c.size();//��������
	vector<int> p,v, n;
	for (int i = 0; i < k; i++){
		p.push_back(c[i].get_cost());
		v.push_back(c[i].get_attack() + c[i].get_health());
	}
	n = dp(p, v, pts, c);//���߳�������
	//delayTime = 10;
	k = 0;
	for (int i = 0; i < n.size(); i++){
		if (!AiCummon(n[i] - k)) break;
		k++;
	}
}
/*
������Ϊһ����ӵļ�ֵ��A attack H health S Spell����
��ֵ����P CostPoint���ٻ�����C Cost����
��ô����P=A+H+S=2C+3
һ����ӵ����м�ֵ����A+H+S��ΪĿǰû��S����ȷ�� ������Ҳ����ı�
��ô���м�ֵ����������h�ҹ� ��P=A+h+S=2C+3-ʧȥ����
���Ǵӽ����ĽǶȿ��� ���˵���Ӹ��н�����ֵ -��ͬ����4/2 �������˵�ѩ�˱����Ƹ��н�����ֵ ��ȴ�����в�������ս����
S��������spell��ĺ���������ȷ���������ݲ����� P=A+h���Ժ���������˵ļ�ֵ����
��һ���������Ϊ �߹�����Ӹ��н�����ֵ
4/2��3/3�����׽��� �����ⲿ�ּ�ֵ���Թ��ൽս�������ʱ���˸��� ��ʽ��������											����@1

Ȼ����������ֵ���治ȷ��������֮������¯ʯ�������Ҫ��֮�󣩲����ö�̬�滮����ȷ�����彻��ʱʹ�ã���ֱ�Ӳ���̰��
��ÿ����Ӽ��㽻��������ֵ �������ʱ ��ai�Ƕȿ���
�����ܽ��� �����Ӳ����ܵ�ai����
���ܽ��� �ο���ֵ����
ai������Ӳ�����ֵ��������� ����ΪP-A'('��ʾai����������ΪP-A'-P'
������A'����Ϊ��������������˹���Ӣ�۵�Ѫ������ �����ǽ���ʱai����ܵ��˺����ǲο�@1�������
������Ϊ�� ��ִ�н���
����Ϊ�� ����Ϊ���ܽ���
�����Ǽ���������P�ĺ���
*/
//������ӽ�����ֵ
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


//һ���ݹ��ҵ��ֲ����Žⷨ��С���� ����ֵ��atkCard��
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
		//��ʾ����Ӣ��
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
	//ÿ�������������
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
	vector<CCard> VCVcard = Value_Cost();//���ʹ�ÿ������Ž�
	AICardUse(VCVcard);//ʹ�ÿ���
	AICheckAttack();//��ӹ���
	TurnOver();
}


bool CAIEnemy::AICardUse(vector<CCard>&card){
	//ʹ��ÿ�ſ���
}


void CAIEnemy::AICheckAttack(){
	vector<CCard> &Ecard = Enemy->_cardPool[POOL_BATTLE];//���˵Ŀ�������
	int k, v;
	vector<CCard> cardAtt, cardTemp;//������ӵ��������ʱ��ӵ�����
	CCard cardT;
	do{
		k = Ecard.size;//��ӽ������� ����
		v = -10000;
		for (int i = 0; i < k; i++){
			int v_e = Value_EXMin(Ecard[i], cardTemp);
			if (v_e > v){
				v = v_e;
				cardT = Ecard[i];//cardTΪ���������
				cardAtt = cardTemp;//cardTempΪ�������-����
			}
		}
		//���ù���
		AICardAttack(cardTemp, cardT);
	} while (v >= 0);//������������²��ܻ������ֵ �����
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
	//���㿨�����ܵļ�ֵ
}
double CAIEnemy::Value_EXMin(CCard &card,vector<CCard>&cardT){
	//��̬�滮�㷨���㻻ȡ��Сֵ
}

vector<CCard> CAIEnemy::Value_Cost(){
	vector<CCard> Vcard;

}

bool CAIEnemy::KO(){
	KO(this);
}

bool CAIEnemy::KO(CBattle *player){
	int health_hero;//=Ӣ��Ѫ��
	vector<CCard> &cib = player->Enemy->_cardPool[POOL_BATTLE];
	int k = cib.size, s = 0;//���㳡��
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