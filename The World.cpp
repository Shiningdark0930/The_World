#include<stdio.h>
#include<windows.h>

#define Sleep(X); //�� �ɼ��� ���� ����� ��� ����. ��� ���� ����. 

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
	int Lv,Exp,MaxExp;//����,����ġ ���� 
	int Hp,MaxHp,HpGen;//hp���� 
	int Pp,MaxPp,PpGen;//pp���� 
	int Atk;//���ݰ��� 
	int Def;//��� 
	int Speed;//�ӵ�
	int Power;//�� 
	char Name[50];
	
	int x,y;//��ǥ 
	
	//�й轺��
	
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

struct stat Mob[2];

//������ 

/*
1:��ȯ��
2~5:ä�¹���
6~9:��������
10~18:(�ʺ�����)��,Ȱ,������,����,����,����,����,�Ź�,�κ� 
19:���� 
*/

int Item[19] = {5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

int ItemPrize[19] = {10,50,1000,10000,100000,50,1000,10000,100000,50,50,50,70,30,100,70,20,150,0};

char ItemName[19][50] = {"��ȯ��\n������ ������ ��ȯ�����ݴϴ�.",
"ä�� ����(��)\nHp�� 50 ȸ���մϴ�.",
"ä�� ����(��)\nHp�� 750 ȸ���մϴ�.",
"ä�� ����(��)\nHp�� 5,000 ȸ���մϴ�.",
"ä�� ����(Ư��)\nHp�� 30,000 ȸ���մϴ�.",
"���� ����(��)\nPp�� 50 ȸ���մϴ�.",
"���� ����(��)\nPp�� 750 ȸ���մϴ�.",
"���� ����(��)\nPp�� 5,000 ȸ���մϴ�.",
"���� ����(Ư��)\nPp�� 30,000 ȸ���մϴ�.",
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

int Money = 100;//�� 

char MAPINF[2][1000] =
{
	{"1������ 10���� �������� ���� �������� ��� �ִ�.\n�� �� 1���� �������� ����Ǿ� �ִ� ��.\�� �ָ� �������� ���δ�.\n"},
	{"�� �������\n"}
	
};
char MobName[2][100] = 
{
	{"������"},
	{"���� ��������. �ʴ� �������"},
};

int main()//�����Լ� 
{
	
	/*-----���� �ʱ�ȭ-----*/
	
	//�÷��̾� ����	
	p.Lv = 1, p.Exp = 1000000, p.MaxExp = 10;//���� 
	p.MaxHp = 100, p.Hp = p.MaxHp, p.HpGen = 0;//ä�� 
	p.MaxPp = 50, p.Pp = p.MaxPp, p.PpGen = 1;//���� 
	p.Atk = 5, p.Def = 0;//���ݷ�, ���� 
	p.Speed = 100, p.Power = 10;//�ӵ�, �� 

	//�÷��̾� �й轺��
	p.STR = 0, p.INT = 0, p.SPD = 0, p.REG = 0, p.BOD = 0;//�й轺��

	City();

}

int City()//���� 
{
	
	//�� ���� �ʱ�ȭ 
	
	//1��  
	Mob[0].Exp = 10,Mob[0].MaxExp = 5;
	Mob[0].MaxHp = 30, Mob[0].Hp = Mob[0].MaxHp, Mob[0].HpGen = 0;//ä�� 
	Mob[0].MaxPp = 10, Mob[0].Pp = Mob[0].MaxPp, Mob[0].PpGen = 1;//���� 
	Mob[0].Atk = 3, Mob[0].Def = 0;//���ݷ�, ���� 
	Mob[0].Speed = 40, Mob[0].Power = 3;//�ӵ�, ��
	
	//2��
	Mob[1].Exp = 0,Mob[1].MaxExp = 0;
	Mob[1].MaxHp = 10000, Mob[1].Hp = Mob[1].MaxHp, Mob[1].HpGen = 100;//ä�� 
	Mob[1].MaxPp = 10000, Mob[1].Pp = Mob[1].MaxPp, Mob[1].PpGen = 100;//���� 
	Mob[1].Atk = 1000, Mob[1].Def = 1000;//���ݷ�, ���� 
	Mob[1].Speed = 100000, Mob[1].Power = 300;//�ӵ�, �� 
	
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
	//ColorString(7,"3:�κ��丮\n");
	
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
			
		//case 3:
			//break;
			
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
	//ColorString(7,"3:������ ���\n");
	//ColorString(7,"4:��ų\n");
	
	scanf("%d", &Select);
	
	switch(Select)
	{
		
		case 1:
			Fight_Attek(Grade);
			break;
			
		default:
			goto C1;//C1
			break;
		
	}
	
	CheckMobDied(Grade);
	
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
	ColorString(10,"[�޴��� ȣȯ�Ǵ� ���ڸ� �Է��ϼ���.]\n");
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
	ColorString(10,"[�޴��� ȣȯ�Ǵ� ���ڸ� �Է��ϼ���.]\n");
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
	ColorString(10,"[�޴��� ȣȯ�Ǵ� ���ڸ� �Է��ϼ���.]\n");
	ColorString(7,"1:[50���]ä�� ����(��)[Hp 50 ȸ��]\n");
	ColorString(7,"2:[1,000���]ä�� ����(��)[Hp 750 ȸ��]\n");
	ColorString(7,"3:[10,000���]ä�� ����(��)[Hp 5,000 ȸ��]\n");
	ColorString(7,"4:[100,000���]ä�� ����(Ư��)[Hp 30,000 ȸ��]\n");
	ColorString(7,"5:[50���]���� ����(��)[Pp 50 ȸ��]\n");
	ColorString(7,"6:[1,000���]���� ����(��)[Pp 750 ȸ��]\n");
	ColorString(7,"7:[10,000���]���� ����(��)[Pp 5,000 ȸ��]\n");
	ColorString(7,"8:[100,000���]���� ����(Ư��)[Pp 30,000 ȸ��]\n");
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
	
	Line();
	ColorString(6,"������ �ö����ϴ�!\n");
	
	p.Lv += 1; 
	p.Exp -= p.MaxExp;
	p.Hp = p.MaxHp;
	p.Pp = p.MaxPp;
	p.MaxExp *= 1.1;
	p.MaxHp *= 1.04;
	p.MaxPp *= 1.041;
	p.HpGen += p.Lv/5;
	p.PpGen += p.Lv/3;
	p.Atk += p.Lv/10;
	p.Def += p.Lv/35;
	p.Speed += p.Lv/100;
	p.Power += p.Lv/20;
	
	CheckLvUp();
	
}

int BuyItem(int ItemNum)//������ ���� 
{
	
	if(Money > ItemPrize[ItemNum]){
		
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
	printf("Hp:%-10d/%-10dHpGen:%-20d\n",p.MaxHp,p.Hp,p.HpGen);
	printf("Pp:%-10d/%-10dPpGen:%-20d\n",p.MaxPp,p.Pp,p.PpGen); 
	printf("Atk:%-20dDef:%-20d\n",p.Atk,p.Def);
	printf("Speed:%-18dPower:%-20d\n",p.Speed,p.Power);
	
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
			
			printf("%d:%s\n",i+1,ItemName[i]);
			
			i += 1;
			
		}
		
	}
	
	scanf("%d", &Select);
	
	if(Item[Select-1] > 0){
		
		Useitem(Select-1);
		
	}
	else{
		
		Line();
		ColorString(5,"�������� �������� �ʰų� ������ �����մϴ�!\n");
		
	}
		
}

int Useitem(int Num)
{

	if(Item[Num] > 0){
		
		switch(Item[Num]){
		
			case 0:
				Line();
				ColorString(4,"������ ��ȯ�մϴ�.\n");
				Sleep(800);
				Item[0] -= 1;
				City();
				break;
				
			case 1:
				Line();
		
		}
		
	}
	
}

int ColorString(int Color,char String[])//���� �ý�Ʈ ��� 
{
		
	SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE ),Color);
	
	printf("%s",String);
		
	return 0;
		
}
