#include<stdio.h>
#include<windows.h>

//#define Sleep(X); //�� �ɼ��� ���� ����� ��� ����. ��� ���� ����. 

/*
���� �߰��ϰ� ���� ��
MapInf,MobName ������ ã���ּ���.
�׷��� ���� ����� �� �̸��� �ٲ��ּ���.
����������, �� �ؿ� SetMobStat��� �Լ��� �ֽ��ϴ�.
�װ��� SetMobStatGrade �Լ��� �߰��� ���� ������ �������ּ���.
���� ���� ������, ����� �Լ� ����ο� �ִ�
SetMobStatGrade �Լ� �ؿ� ������ �����ֽ��ϴ�.
�׷��� Mob ����ü �迭�� �迭�絵 �÷��ּ���. 
*/ 

/*�Լ� �����*/



int City();//���� 

int Dungeon(int Grade);//���� 

int Dungeon_Start(int Grade);//���� �÷��̾� ��ġ���� 

int Dungeon_Main(int Grade);//���� ����ȭ�� 

int Dungeon_Fight(int Grade);//���� ��Ʃ 

int Fight_Attek(int Grade);//���� 

int CheckMobDied(int Grade);//�� ��� ���� 

int MobAttek(int Grade);//������ 

int CheckPlayerDied();//�÷��̾� ��� ���� 

int Shop();//���� 

int ShopExpend();//���� �Ҹ�ǰ

int ShopPotion();//���� ���� 

int CheckLvUp();//������ üũ 

int LevelUp();//������ 

int BuyItem(int ItemNum);//������ ���� 

int playerRegenTick();//�÷��̾� ä��/��������

int ShowStat();//���� �����ֱ� 

int ShowArmor();//���â 

int ShowInventory();//�κ��丮 

int SelectItem();//�����ۼ��� 

int Useitem(int Num);

int HpPotion(int Hp, int Potion);

int PpPotion(int Pp, int Potion);

int SetMobStat();//�� ���� �ʱ�ȭ

int MobReganTick(int Grade);

int SetMobStatGrade(int Grade,int Exp,int Gold, int MaxHp, int HpGen, int MaxPp, int PpGen, int Atk, int Def, int Speed, int Power);//�� ���� �ʱ�ȭ �ɼ� 

//������� �� ���� ��,�ִ� ����ġ,�ִ� ���, ä��,�ϸ��� �����Ǵ� ä��,����,�ϸ��� �����Ǵ� ����,���ݷ�,����,�ӵ�,�� �Դϴ�. 

int ColorString(int Color,char String[]);//���� �ڵ� �ٲٱ� �Լ� 

int Line()
{
	
	ColorString(8,"������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������\n");
	
}


/*���� �ڵ�ǥ ����

00 ������	08 ȸ�� 
01 �Ķ���	09 ���� �Ķ���	 
02 �ʷϻ�	10 ���� �ʷϻ� 
03 ����	    11 ���� ���� 
04 ������	12 ���� ������ 
05 ���ֻ�	13 ���� ���ֻ� 
06 �����	14 ���� ����� 
07 ��� 	15 ���� ��� 
*/


/*-----���� �����-----*/ 

struct stat
{
	
		/*-----���� �����-----*/ 
	
	//���� 
	int Lv;
	int Exp,MaxExp;//����,����ġ ���� 
	int Hp,MaxHp,HpGen;//hp���� 
	int Pp,MaxPp,PpGen;//pp���� 
	int Atk;//���ݰ��� 
	int Def;//��� 
	int Speed;//�ӵ�
	int Power;//�� 
	char Name[50];
	
	int x,y;//��ǥ 
	
	//�й轺��
	
	int SP = 0;//���� ����Ʈ 
	
	int STR;//��(����, ���� ����)	 
	int INT;//����(����,���������,�ӵ��� ����) 
	int SPD;//�ӵ�(�ӵ��� ũ�� ����) 
	int REG;//�����(ä�� �����, ���� �����, ������ ����)
	int BOD;//��Ŀ(ä��,����,���� ����) 
	
	//���
	
	int Hat = 19;
	int Body = 19;
	int Leggings = 19;
	int Shose = 19;
	int Wepon = 19;
	int Shiled = 19;
	
	//������ ����
		
	int Item[32][2];//1���� �������ڵ�, 2���� ���� ���� 
	
		
}; 

struct stat p;

struct stat Mob[21];//�̰͵� �÷��ּ���.

/*
0:����
1~4:���� ��Ʈ
5:���
6:Ȱ
7:������
8:���� 
9:�κ� 
*/
/*
1:����
2:����
3:����
4:�Ź�
5:����
6:���� 
*/
int EStat[10][11] = //6���� �ɼ�/��� ��ȣ/ä/��/��/��/��/��
{
{1,1,0,0,0,0,0,0,10,0,6},
{2,2,0,0,0,0,0,0,20,0,12},
{3,3,0,0,0,0,0,0,15,0,9},
{4,4,0,0,0,0,0,0,5,0,3},
{5,5,0,0,0,0,0,20,0,0,5},
{5,6,0,0,0,0,0,20,0,50,3},
{5,7,0,0,30,5,0,0,0,30,4},
{6,8,0,0,0,0,0,0,30,0,7},
{2,9,0,3,20,3,0,0,0,20,1}
};

//������ 

/*
1:��ȯ��
2~5:ä�¹���
6~9:��������
10~18:(�ʺ�����)��,Ȱ,������,����,����,����,����,�Ź�,�κ� 
19:���� 
*/

int HpPotionHeal[4] = {5,8,15,25};

int Item[19] = {5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

int ItemPrize[19] = {10,5,10,20,40,5,10,20,40,50,50,50,60,30,100,70,20,150,0};

char ItemName[19][50] = {"��ȯ��\n������ ������ ��ȯ�����ݴϴ�.",
"ä�� ����(��)\nHp�� 5 ȸ���մϴ�.",
"ä�� ����(��)\nHp�� 8 ȸ���մϴ�.",
"ä�� ����(��)\nHp�� 15 ȸ���մϴ�.",
"ä�� ����(Ư��)\nHp�� 25 ȸ���մϴ�.",
"���� ����(��)\nPp�� 5 ȸ���մϴ�.",
"���� ����(��)\nPp�� 8 ȸ���մϴ�.",
"���� ����(��)\nPp�� 15 ȸ���մϴ�.",
"���� ����(Ư��)\nPp�� 25 ȸ���մϴ�.",
"�ʺ����� ���",
"�ʺ����� ���� Ȱ",
"������ ������",
"�ʺ����� ����",
"�䳢 ���� ����",
"�䳢 ���� ����",
"�䳢 ���� ����",
"�䳢 ���� �Ź�",
"�䳢 ���� �κ�",
"����",
};

int Money = 0;//�� 

char MAPINF[21][1000] =
{
	{"1������ 10���� �������� ���� �������� ��� �ִ�.\n�� �� 1���� �������� ����Ǿ� �ִ� ��.\n�� �ָ� �������� ���δ�.\n"},
	{"�� �ָ� ���� �������� ���δ�.\n"},
	{"�� �ָ� ���̾� �������� ���δ�.\n"},
	{"�� �ָ� ������ �������� ���δ�.\n"},
	{"�� �ָ� �Ϸ�Ʈ�� �������� ���δ�.\n"},
	{"�� �ָ� ���̽� �������� ���δ�.\n"},
	{"�� �ָ� ���� �������� ���δ�.\n"},
	{"�� �ָ� ������ �������� ���δ�.\n"},
	{"�� �ָ� ����Ʈ �������� ���δ�.\n"},
	{"������ �ִ� �ֻ����̴�.\n�� �ָ� ������ ŷ�� ���δ�.\n"},
	{"2������ 20���� �������� �ʺ��ڰ� ���� �� ���� �������� ��� �ִ�.\n�� �ָ� ���̷����� ���δ�.\n"},
	{"�� �ָ� ���̷��� ���簡 ���δ�.\n"},
	{"�� �ָ� �õ� ���̷����� ���δ�.\n"},
	{"�� �ָ� �õ� ���̷��� ���簡 ���δ�.\n"},
	{"�� �ָ� ���̷��� ��ó�� ���δ�.\n"},
	{"�� �ָ� �𵥵� ���̷����� ���δ�.\n"},
	{"�� �ָ� ���̷��� ���ְ� ���δ�.\n"},
	{"�� �ָ� �𵥵� ���̷��� ���ְ� ���δ�.\n"},
	{"�� �ָ� The Skeleton�� ���δ�.\n"},
	{"������ �ִ� �ֻ����̴�.\n�� �ָ� ���̷��� ŷ�� ���δ�.\n"},
	{"���� ������ �ִ� ���̴�.\n�� �ָ� �ڳ��� �˱����� ���δ�.\n"}
	
};
char MobName[21][100] = 
{
	{"������"},
	{"���� ������"},
	{"���̾� ������"},
	{"������ ������"},
	{"�Ϸ�Ʈ�� ������"},
	{"���̽� ������"},
	{"���� ������"},
	{"������ ������"},
	{"����Ʈ ������"},
	{"������ ŷ"},
	{"���̷���"},
	{"���̷��� ����"},
	{"�õ� ���̷���"},
	{"��� ���̷��� ����"},
	{"���̷��� ��ó"},
	{"�𵥵� ���̷���"},
	{"���̷��� ����"},
	{"�𵥵� ���̷��� ����"},
	{"The Skeleton"},
	{"���̷��� ŷ"},
	{"[��������]�ڳ��� �˱���"},
};

int main()//�����Լ� 
{
	
	/*-----���� �ʱ�ȭ-----*/
	
	//�÷��̾� ����	
	p.Lv = 1, p.Exp = 100, p.MaxExp = 20;//���� 
	p.MaxHp = 10, p.Hp = p.MaxHp, p.HpGen = 0;//ä�� 
	p.MaxPp = 8, p.Pp = p.MaxPp, p.PpGen = 0;//���� 
	p.Atk = 3, p.Def = 0;//���ݷ�, ����
	p.Speed = 10, p.Power = 1;//�ӵ�, �� 

	//�÷��̾� �й轺��
	p.STR = 0, p.INT = 0, p.SPD = 0, p.REG = 0, p.BOD = 0;//�й轺��

	City();

}

int City()//���� 
{
	
	SetMobStat();
	
	//�� 
	
	p.Hp = p.MaxHp;
	
	p.Pp = p.MaxPp;
	
	playerRegenTick();
	
	int Select = 0;
	
	
	
	Line();
	ColorString(9,"-������ ����-\n");
	
	Line();
	ColorString(15,"������ ������ �ִ� �����̴�.\n");
	
	B1://B1
	
	Line();
	ColorString(10,"[�޴��� ȣȯ�Ǵ� ���ڸ� �Է��ϼ���.]\n");
	ColorString(7,"1:���� ����\n");
	ColorString(7,"2:��ȭ���� ����\n");
	ColorString(7,"3:�����̴��� Ȯ��\n");
	ColorString(7,"4:����\n");
	
	scanf("%d",&Select);
	
	switch(Select)
	{
		
		case 1:
			Dungeon(0);
			break;
		
		case 2:
			Shop();
			break;
			
		case 3:
			ShowStat();
			goto B1;
			break;
			
		case 4:
			ShowArmor();
			ShowInventory();
			SelectItem();
			goto B1;
			break;
			
		default:
			goto B1;//B1
		
	}
	
	
}

int Dungeon(int Grade)//���� 
{	

	Dungeon_Start(Grade);
	
	Dungeon_Main(Grade);

}

int Dungeon_Start(int Grade)//���� ���� 
{
	
	
	
	playerRegenTick();
	Line();
	ColorString(3, "-������ �����Ͽ����ϴ�!-\n");
	Sleep(2000);
	Line();
	ColorString(4, "-������ ��ȯ���� ������ ����ϴ� �������ּ���.\n");
	Sleep(2000);
	
}

int Dungeon_Main(int Grade)//���� ����â 
{
	
	playerRegenTick();
	
	int Select = 0;
	
	Line();
	ColorString(3,"");
	printf("-���� %d��-\n", Grade+1);
	
	Line();
	ColorString(9,"");
	printf("%s", MAPINF[Grade]);
	
	A1://A1
	
	Line();
	ColorString(10,"[�޴��� ȣȯ�Ǵ� ���ڸ� �Է��ϼ���.]\n");
	ColorString(7,"1:����\n");
	ColorString(7,"2:���� Ȯ��\n");
	ColorString(7,"3:����\n");
	
	scanf("%d", &Select);
	
	switch(Select)
	{
		
		case 1:
			Dungeon_Fight(Grade);
			break;
			
		case 2:
			ShowStat();
			Dungeon_Main(Grade);
			break;
			
		case 3:
			ShowArmor();
			ShowInventory();
			SelectItem();
			break;
			
		default:
			goto A1; //A1
		
	}
	
}

int Dungeon_Fight(int Grade)//���� 
{
	
	playerRegenTick();
	
	Line();
	ColorString(4,"");
	printf("[%s��(��) Ƣ��Դ�!]\n", MobName[Grade]);
	Sleep(1000);	
	
	int Select = 0;
	
	E1:
	
	Line();
	ColorString(2,"[������ �Ͻðڽ��ϱ�?]\n");	
	
	C1:
	
	Line();
	ColorString(10,"[�޴��� ȣȯ�Ǵ� ���ڸ� �Է��ϼ���.]\n");
	ColorString(7,"1:����\n");
	//ColorString(7,"2:���\n");
	ColorString(7,"3:������ ���\n");
	//ColorString(7,"4:��ų\n");
	
	scanf("%d", &Select);
	
	switch(Select)
	{
		
		case 1:
			Fight_Attek(Grade);
			break;
			
		case 3:
			ShowInventory();
			SelectItem();
			break;
			
		default:
			goto C1;//C1
			break;
		
	}
	
	CheckMobDied(Grade);
	
	MobReganTick(Grade);
	
	MobAttek(Grade);
	
	CheckPlayerDied();	
	
	goto E1;
	
}

int Fight_Attek(int Grade)//���� 
{
	
	if(p.Atk - Mob[Grade].Def < 0){
		
		Line();
		ColorString(15,"");
		printf("%s���� 0�� ���ظ� �������ϴ�!\n",MobName[Grade]);
		Sleep(800);
		
	}
	else{
		
		Line();
		ColorString(15,"");
		printf("%s���� %d�� ���ظ� �������ϴ�!\n",MobName[Grade], p.Atk - Mob[Grade].Def);
		Sleep(800);
		
		Mob[Grade].Hp -= p.Atk - Mob[Grade].Def;	
		
	}
	
	if(Mob[Grade].Hp < 0){
		
		Mob[Grade].Hp = 0;
		
	}
	
	Line();
	ColorString(15,"");
	printf("%s ���� ä��:%d/%d\n",MobName[Grade], Mob[Grade].MaxHp, Mob[Grade].Hp);
	Sleep(800);
	
}

int CheckMobDied(int Grade)//�� ������� 
{
	
	if(Mob[Grade].Hp<1)
	{
		
		Line();
		ColorString(1,"");
		printf("%s��(��) �׾����ϴ�!\n", MobName[Grade]);
		Sleep(800);
		
		p.Exp += Mob[Grade].Exp;
		Line();
		ColorString(2,"");
		printf("����ġ�� %d ȹ���Ͽ����ϴ�!\n",Mob[Grade].Exp);
		Sleep(800);
		
		Money += Mob[Grade].MaxExp;
		Line();
		ColorString(6,"");
		printf("%d��带 ȹ���Ͽ����ϴ�!\n",Mob[Grade].MaxExp);
		Sleep(800);
		
		CheckLvUp();
		
		Dungeon(Grade+1);
		
	}
	
}

int MobAttek(int Grade)//�� ���� 
{
	
	Line();
	ColorString(5,"");
	printf("%s�� ����!\n",MobName[Grade]);
	Sleep(800);
	
	if(Mob[Grade].Atk - p.Def < 0){
		
		Line();
		ColorString(4,"");
		printf("0�� ���ظ� �Ծ����ϴ�!\n");
		Sleep(800);
		
	} 
	else{
		
		p.Hp -= Mob[Grade].Atk - p.Def;
	
		Line();
		ColorString(4,"");
		printf("%d�� ���ظ� �Ծ����ϴ�!\n", Mob[Grade].Atk - p.Def);
		Sleep(800);
		
	}
	
	if(p.Hp < 0){
		
		p.Hp = 0;
		
	}
	
	Line();
	ColorString(2,"");
	printf("���� ä�� %d/%d\n",p.MaxHp,p.Hp);
	Sleep(800);

	
}

int CheckPlayerDied()//�÷��̾� ������� 
{
	
	if(p.Hp < 1){
		
		Line();
		ColorString(4,"�����ϼ̽��ϴ�.\n");
		Sleep(800);
		
		if(Item[0] > 0){
			
			Line();
			ColorString(4,"��ȯ���� ���� �־� ������� �ʰ� ������ ��ȯ�մϴ�.\n");
			Sleep(800);
			Line();
			ColorString(4,"�����Ͽ� ����ġ�� 0���� �ʱ�ȭ�Ǹ�, �䱸�Ǵ� ����ġ���� 2�� �����մϴ�..\n");
			Sleep(800);
			p.Exp = 0;
			p.MaxExp *= 2;
			p.Hp = 1;
			Item[0] -= 1;
			City();
			
		}
		else{
			
			Line();
			ColorString(4,"��ȯ���� ���� ���� �ʽ��ϴ�.\n����� ����Ͽ����ϴ�.\n");
			Sleep(800);
			Line();
			ColorString(4,"������ ó������ �ٽ� �����մϴ�.\n");
			Sleep(800);
			main();
			
		}
		
	}
	
}

int Shop()//���� 
{
	
	
	
	playerRegenTick();
	
	int Select = 0;
	
	Line();
	ColorString(3,"-��ȭ����-\n");
	Line();
	ColorString(9,"-���� ���� ��ǰ�� �Ǹ��ϰ� �ִ�.\n");
	
	F1:
	
	Line();
	ColorString(10,"[�޴��� ȣȯ�Ǵ� ���ڸ� �Է��ϼ���.]");
	printf("������ %dG\n",Money);
	ColorString(7,"1:�Ҹ�ǰ\n");
	//ColorString(7,"2:���\n");
	//ColorString(7,"3:�Ǹ�\n");
	ColorString(7,"4:Ż��\n");
	
	scanf("%d", &Select);
	
	switch(Select)
	{
		
		case 1:
			ShopExpend();
			break;
			
		//case 2:
			break;
			
		//case 3:
			break;
			
		case 4:
			City();
			break;
			
		default:
			goto F1;
		
	}
	
	
}

int ShopExpend()//�Ҹ�ǰ 
{
	
	
	
	int Select;
	
	Line();
	ColorString(3,"-�Ҹ�ǰ-\n");
	
	G1:
	
	Line();
	ColorString(10,"[�޴��� ȣȯ�Ǵ� ���ڸ� �Է��ϼ���.]");
	printf("������ %dG\n",Money);
	ColorString(7,"1:����\n");
	ColorString(7,"2:[10���]��ȯ��\n");
	ColorString(7,"3:Ż��\n");
	
	scanf("%d", &Select);
	
	switch(Select)
	{
		
		case 1:
			ShopPotion();
			break;
			
		case 2:
			BuyItem(0);
			break;
			
		case 3:
			City();
			break;
			
		default:
			goto G1;
		
	}
	
}

int ShopPotion()//���� 
{
	
	
	
	int Select = 0; 
	
	Line();
	ColorString(3,"-����-\n");
	
	H1:
	
	Line();
	ColorString(10,"[�޴��� ȣȯ�Ǵ� ���ڸ� �Է��ϼ���.]");
	printf("������ %dG\n",Money);
	ColorString(7,"1:[5���]ä�� ����(��)[Hp 5 ȸ��]\n");
	ColorString(7,"2:[10���]ä�� ����(��)[Hp 8 ȸ��]\n");
	ColorString(7,"3:[20���]ä�� ����(��)[Hp 15 ȸ��]\n");
	ColorString(7,"4:[40���]ä�� ����(Ư��)[Hp 25 ȸ��]\n");
	ColorString(7,"5:[5���]���� ����(��)[Pp 5 ȸ��]\n");
	ColorString(7,"6:[10���]���� ����(��)[Pp 8 ȸ��]\n");
	ColorString(7,"7:[20���]���� ����(��)[Pp 15 ȸ��]\n");
	ColorString(7,"8:[40���]���� ����(Ư��)[Pp 25 ȸ��]\n");
	ColorString(7,"9:Ż��\n");
	
	scanf("%d", &Select);
	
	if(0 < Select){
		
		if(Select<9){
			
			BuyItem(Select);
			
		}
		else if(Select = 9){
			
			City();
			
		}
		
	}
	
		goto H1;
	
}

int CheckLvUp()//������ Ȯ�� 
{
	
	if(p.Exp > p.MaxExp-1){
		
		LevelUp();
		
	}
	
}

int LevelUp()//������ 
{
	
	Sleep(1000);
	
	int Stat[6];
	
	int DX;
	
	Line();
	ColorString(6,"������ �ö����ϴ�!\n");
	
	p.SP += 5+p.Lv/20;
	
	MXS:
	
	Line();
	ColorString(1,"���� �й踦 �� �ּ���.");
	printf("[���� ����Ʈ:%d]\n",p.SP);
	
	Line();
	ColorString(4,"STR:�� ����\n");
	ColorString(1,"INT:������ ����\n");
	ColorString(2,"SPD:�ӵ� ����\n");
	ColorString(6,"REG:����� ����\n");
	ColorString(5,"BOD:���� ����\n");
	
	ColorString(15,"STR INT SPD REG BOD�� ���� �ο��� ���� ��ġ�� ������� �Է��� �ּ���.\n");
	
	scanf("%d %d %d %d %d", &Stat[0], &Stat[1], &Stat[2], &Stat[3], &Stat[4]);
	Stat[5] = Stat[0]+Stat[1]+Stat[2]+Stat[3]+Stat[4];
	
	if(Stat[5]>p.SP){
		
		Line();
		ColorString(4,"�����ϰ� �ִ� ���� ����Ʈ���� ��뷮�� �����ϴ�!\n");
		
		goto MXS;
		
	}
	if(Stat[5]<0){
		
		Line();
		ColorString(4,"������ �Է� �Ұ��մϴ�!\n"); 
		
		goto MXS;
		
	}
	
	p.SP -= Stat[5];
	
	p.STR += Stat[0];
	p.INT += Stat[1];
	p.SPD += Stat[2];
	p.REG += Stat[3];
	p.BOD += Stat[4];
	
	p.MaxExp += p.MaxExp/95 + 1;
	p.Exp -= p.MaxExp;
	
	p.Lv += 1;
	
	DX = 0;
	
	while(DX<p.STR)
	{
		
		DX += 1;
		
		p.Power += 1;
		
		if(DX % 5 == 0){
			
			p.Atk += DX/5;
			
		}
			
	}
	
	DX = 0;
	
	while(DX<p.INT)
	{
		
		DX += 1;
		
		p.MaxPp += DX/3;
		
		if(DX % 5 == 0){
			
			p.Speed += DX/10;
			
		}
			
	}
	
	DX = 0;
	
	while(DX<p.SPD)
	{
		
		DX += 1;
		
		if(DX % 4 == 0){
			
			p.Speed += DX/8;
			
		}
				
	}
	p.Power += DX/6;
	
	DX = 0;
	
	while(DX<p.REG)
	{
		
		DX += 1;
		
		p.HpGen += DX/40;
		
		p.PpGen += DX/30;
			
	}
	
	DX = 0;
	
	while(DX<p.BOD)
	{
		
		DX += 1;
		
		p.MaxHp += DX/4;
			
	}
	p.Def += DX/15;
	
	p.Hp = p.MaxHp;
	p.Pp = p.MaxPp;
	
	ColorString(6,"���� �й谡 �Ϸ�Ǿ����ϴ�!\n");
	
	Line();
	ColorString(4,"");
	printf("STR:%d\n",p.STR);
	ColorString(1,"");
	printf("INT:%d\n",p.INT);
	ColorString(2,"");
	printf("SPD:%d\n",p.SPD);
	ColorString(6,"");
	printf("REG:%d\n",p.REG);
	ColorString(5,"");
	printf("BOD:%d\n",p.BOD);
	
	ShowStat();	
	CheckLvUp();
	
}

int BuyItem(int ItemNum)//������ ���� 
{
	
	if(Money > ItemPrize[ItemNum]-1){
		
		Item[ItemNum] += 1;
		Money -= ItemPrize[ItemNum];
		
		Line();
		ColorString(6,"");
		printf("%s��(��)�����Ͽ����ϴ�!\n",ItemName[ItemNum]);
		
	}
	else{
		
		Line();
		ColorString(4,"");
		printf("��尡 ���ڶ��ϴ�!\n");
		
	}
	
	Shop();
	
}  

int playerRegenTick()//ȸ�� 
{
	
	p.Hp += p.HpGen;
	p.Pp += p.PpGen;
	if(p.Hp > p.MaxHp){
		
		p.Hp = p.MaxHp;
		
	}
	if(p.Pp > p.MaxPp){
		
		p.Pp = p.MaxPp;
		
	}
	
}

int ShowStat()//����â 
{
	
	Line();
	ColorString(1,"-�����̴���-\n");
	Line();
	ColorString(15,"");
	printf("LV:%-20d Exp:%-10d/%-10d\n",p.Lv,p.MaxExp,p.Exp);
	printf("Hp:%-10d/%-10d HpGen:%-20d\n",p.MaxHp,p.Hp,p.HpGen);
	printf("Pp:%-10d/%-10d PpGen:%-20d\n",p.MaxPp,p.Pp,p.PpGen); 
	printf("Atk:%-20d Def:%-20d\n",p.Atk,p.Def);
	printf("Speed:%-18d Power:%-20d\n",p.Speed,p.Power);
	
}

int ShowArmor()//���â
{
	
	Line();
	ColorString(1,"-���-\n");
	
	Line();	
	ColorString(15,"");
	printf("����:%s\n",ItemName[p.Hat-1]);
	printf("����:%s\n",ItemName[p.Body-1]);
	printf("����:%s\n",ItemName[p.Leggings-1]);
	printf("�Ź�:%s\n",ItemName[p.Shose-1]);
	printf("����:%s\n",ItemName[p.Wepon-1]);
	printf("����:%s\n",ItemName[p.Shiled-1]);
	
} 

int ShowInventory()//�κ��丮
{
	
	
	
	Line();
	
	ColorString(1,"-�κ��丮-\n");	
	
} 

int SelectItem()
{
	
	int Select = 0;
	
	int i = 0;

	Line();
	ColorString(10,"[�޴��� ȣȯ�Ǵ� ���ڸ� �Է��ϼ���.]\n");
	
	while(i < 19){
		
		if(Item[i] > 0){
			
			Line();
			
			ColorString(15,"");
			
			printf("%d:%s[%d��]\n",i+1,ItemName[i],Item[i]);
			
			
			
		}
		i += 1;
		
	}
	Line();
	ColorString(15,"���� ��ȣ:������� �� �Һ�\n"); 
	
	scanf("%d", &Select);
	
	Select -= 1;
	
	if(Item[Select] > 0){
		
		Useitem(Select);
		
	}
	else{
		
		Line();
		ColorString(5,"�������� �������� �ʰų� ������ �����մϴ�!\n");
		
	}
		
}

int Useitem(int Num)
{

	if(Item[Num] > -1){
		
		if(Num > 0 && Num<5)
			HpPotion(HpPotionHeal[Num-1],Num-1);
			
		if(Num > 4 && Num<9)
			PpPotion(HpPotionHeal[Num-1],Num-1);
		
		switch(Num){
		
			case 0:
				Line();
				ColorString(4,"������ ��ȯ�մϴ�.\n");
				Sleep(800);
				Item[0] -= 1;
				City();
				break;
			
			case 1:
				break;
				
			case 2:
				break;
				
			case 3:
				break;

			case 4:
				break;
				
			case 5:
				break;
				
			case 6:
				break;
				
			case 7:
				break;
				
			case 8:
				break;
				
			default:
				Line();
				ColorString(5,"�������� �������� �ʰų� ������ �����մϴ�!\n");
				SelectItem();
				
		
		}
		
	}
	
}

int HpPotion(int Hp, int Potion)
{
	
	Line();
	ColorString(1,"ü�� ������ ����Ͽ����ϴ�!\n");
	Sleep(800);
	
	p.Hp += Hp;
	if(p.Hp > p.MaxHp)
		p.Hp = p.MaxHp;
	
	Item[Potion+1] -= 1;
	
}

int PpPotion(int Pp, int Potion)
{
	
	Line();
	ColorString(1,"���� ������ ����Ͽ����ϴ�!\n");
	Sleep(800);
	
	p.Pp += Pp;
	if(p.Pp > p.MaxPp)
		p.Pp = p.MaxPp;
	
	Item[Potion+1] -= 1;
	
}

int ColorString(int Color,char String[])//���� �ý�Ʈ ��� 
{
		
	SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE ),Color);
	
	printf("%s",String);
		
	return 0;
		
}

int SetMobStat()//�� ���� �ʱ�ȭ 
{
	
	//����/��ġ/��/��/��/����/��/��/��/��/�� 
	SetMobStatGrade(0,5,5,5,0,0,0,1,0,4,1);
	SetMobStatGrade(1,8,6,10,0,0,0,2,0,4,1);
	SetMobStatGrade(2,15,8,20,0,0,0,3,0,5,1);
	SetMobStatGrade(3,20,15,50,0,0,0,1,1,5,1);
	SetMobStatGrade(4,30,15,40,0,0,0,3,0,6,1);
	SetMobStatGrade(5,40,20,60,0,0,0,4,0,6,1);
	SetMobStatGrade(6,52,25,70,0,0,0,5,0,7,1);
	SetMobStatGrade(7,65,25,80,0,0,0,5,0,7,1);
	SetMobStatGrade(8,80,30,100,0,0,0,7,0,8,1);
	SetMobStatGrade(9,150,50,250,0,0,0,15,0,10,2);
	SetMobStatGrade(20,2147483100,2147483100,2147483100,2147483100,2147483100,2147483100,2147483100,2147483100,2147483100,2147483100);
    
}

int MobReganTick(int Grade)
{
	
	Mob[Grade].Hp += Mob[Grade].HpGen;
	Mob[Grade].Pp += Mob[Grade].PpGen;
	
	if(Mob[Grade].Hp > Mob[Grade].MaxHp){
		
		Mob[Grade].Hp = Mob[Grade].MaxHp;
		
	}
	if(Mob[Grade].Pp > Mob[Grade].MaxPp){
		
		Mob[Grade].Pp = Mob[Grade].MaxPp;
		
	}
	
}

int SetMobStatGrade(int Grade,int Exp,int Gold, int MaxHp, int HpGen, int MaxPp, int PpGen, int Atk, int Def, int Speed, int Power)
{
	
	Mob[Grade].Exp = Exp,Mob[Grade].MaxExp = Gold;
	Mob[Grade].MaxHp = MaxHp, Mob[Grade].Hp = Mob[Grade].MaxHp, Mob[Grade].HpGen = HpGen;//ä�� 
	Mob[Grade].MaxPp = MaxPp, Mob[Grade].Pp = Mob[Grade].MaxPp, Mob[Grade].PpGen = PpGen;//���� 
	Mob[Grade].Atk = Atk, Mob[Grade].Def = Def;//���ݷ�, ���� 
	Mob[Grade].Speed = Speed, Mob[Grade].Power = Power;//�ӵ�, �� 
	
}

int EqupArmor(int What, int Num,  int Hp, int HpGen, int Pp, int PpGen, int Atk, int Def,int Speed, int Power, int Kg)
{
	
	switch(What)
	{
		
		case 1:
			break;
		
		case 2:
			break;
			
		case 3:
			break;
			
		case 4:
			break;
				
	}
	
}

/*��Ÿ 0.1
�⺻ ���α׷� ����
*��Ÿ 0.11
���� ������ �߰�
*��Ÿ 0.12
������ ����ġ 0���� �ʱ�ȭ�� �䱸 ����ġ 2�� ���� 
*��Ÿ 0.13
11~20�� �� �߰� �� ������ ��ġ 
*/
