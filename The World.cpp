#include<stdio.h>
#include<windows.h>

//#define Sleep(X); //이 옵션을 사용시 디버그 모드 실행. 모든 지연 제거. 

/*
몹을 추가하고 싶을 때
MapInf,MobName 변수를 찾아주세요.
그러고 층의 설명과 몹 이름을 바뀌주세요.
마지막으로, 맨 밑에 SetMobStat라는 함수가 있습니다.
그곳으 SetMobStatGrade 함수를 추가해 몹의 스탯을 설정해주세요.
몹의 스텟 설정은, 상단의 함수 선언부에 있는
SetMobStatGrade 함수 밑에 설명이 나와있습니다.
그러고 Mob 구조체 배열의 배열양도 늘려주세요. 
*/ 

/*함수 선언부*/



int City();//마을 

int Dungeon(int Grade);//던전 

int Dungeon_Start(int Grade);//던전 플래이어 위치설정 

int Dungeon_Main(int Grade);//던전 메인화면 

int Dungeon_Fight(int Grade);//던전 전튜 

int Fight_Attek(int Grade);//공격 

int CheckMobDied(int Grade);//몹 사망 여부 

int MobAttek(int Grade);//몹공격 

int CheckPlayerDied();//플레이어 사망 여부 

int Shop();//상점 

int ShopExpend();//상점 소모품

int ShopPotion();//상점 물약 

int CheckLvUp();//레벨업 체크 

int LevelUp();//레벨업 

int BuyItem(int ItemNum);//아이템 구메 

int playerRegenTick();//플래이어 채력/마나리젠

int ShowStat();//스텟 보여주기 

int ShowArmor();//장비창 

int ShowInventory();//인벤토리 

int SelectItem();//아이템선택 

int Useitem(int Num);

int HpPotion(int Hp, int Potion);

int PpPotion(int Pp, int Potion);

int SetMobStat();//몹 스텟 초기화

int MobReganTick(int Grade);

int SetMobStatGrade(int Grade,int Exp,int Gold, int MaxHp, int HpGen, int MaxPp, int PpGen, int Atk, int Def, int Speed, int Power);//몹 스텟 초기화 옵션 

//순서대로 몹 출현 층,주는 경험치,주는 골드, 채력,턴마다 리젠되는 채력,마나,턴마다 리젠되는 마나,공격력,방어력,속도,힘 입니다. 

int ColorString(int Color,char String[]);//색깔 코드 바꾸기 함수 

int Line()
{
	
	ColorString(8,"━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
	
}


/*색깔 코드표 정리

00 검정색	08 회색 
01 파란색	09 연한 파란색	 
02 초록색	10 연한 초록색 
03 옥색	    11 연한 옥색 
04 빨간색	12 연한 빨간색 
05 자주색	13 연한 자주색 
06 노란색	14 연한 노란색 
07 흰색 	15 진한 흰색 
*/


/*-----변수 선언부-----*/ 

struct stat
{
	
		/*-----변수 선언부-----*/ 
	
	//스텟 
	int Lv;
	int Exp,MaxExp;//레벨,경험치 관련 
	int Hp,MaxHp,HpGen;//hp관련 
	int Pp,MaxPp,PpGen;//pp관련 
	int Atk;//공격관련 
	int Def;//방어 
	int Speed;//속도
	int Power;//힘 
	char Name[50];
	
	int x,y;//좌표 
	
	//분배스텟
	
	int SP = 0;//스텟 포인트 
	
	int STR;//힘(공격, 힘에 영향)	 
	int INT;//지능(마나,마나재생력,속도에 영향) 
	int SPD;//속도(속도에 크게 영향) 
	int REG;//재생성(채력 재생력, 마나 재생력, 마나에 영향)
	int BOD;//탱커(채력,방어력,힘에 영향) 
	
	//장비
	
	int Hat = 19;
	int Body = 19;
	int Leggings = 19;
	int Shose = 19;
	int Wepon = 19;
	int Shiled = 19;
	
	//아이템 소지
		
	int Item[32][2];//1차는 아이템코드, 2차는 보유 갯수 
	
		
}; 

struct stat p;

struct stat Mob[21];//이것도 늘려주세요.

/*
0:없음
1~4:갑옷 세트
5:목검
6:활
7:지팡이
8:방패 
9:로브 
*/
/*
1:투구
2:갑옷
3:바지
4:신발
5:무기
6:방패 
*/
int EStat[10][11] = //6개중 옵션/장비 번호/채/마/공/방/속/힘
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

//아이템 

/*
1:귀환석
2~5:채력물약
6~9:마나물약
10~18:(초보자의)검,활,지팡이,방패,투구,갑옷,바지,신발,로브 
19:없음 
*/

int HpPotionHeal[4] = {5,8,15,25};

int Item[19] = {5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

int ItemPrize[19] = {10,5,10,20,40,5,10,20,40,50,50,50,60,30,100,70,20,150,0};

char ItemName[19][50] = {"귀환석\n기절시 마을로 귀환시켜줍니다.",
"채력 물약(소)\nHp를 5 회복합니다.",
"채력 물약(중)\nHp를 8 회복합니다.",
"채력 물약(대)\nHp를 15 회복합니다.",
"채력 물약(특대)\nHp를 25 회복합니다.",
"마나 물약(소)\nPp를 5 회복합니다.",
"마나 물약(중)\nPp를 8 회복합니다.",
"마나 물약(대)\nPp를 15 회복합니다.",
"마나 물약(특대)\nPp를 25 회복합니다.",
"초보자의 목검",
"초보자의 나무 활",
"참나무 지팡이",
"초보자의 방패",
"토끼 가죽 투구",
"토끼 가죽 갑옷",
"토끼 가죽 바지",
"토끼 가죽 신발",
"토끼 가죽 로브",
"없음",
};

int Money = 0;//돈 

char MAPINF[21][1000] =
{
	{"1층부터 10층의 던전에는 약한 마물들이 살고 있다.\n그 중 1층은 마을과도 연결되어 있는 곳.\n저 멀리 슬라임이 보인다.\n"},
	{"저 멀리 워터 슬라임이 보인다.\n"},
	{"저 멀리 파이어 슬라임이 보인다.\n"},
	{"저 멀리 포이즌 슬라임이 보인다.\n"},
	{"저 멀리 일렉트릭 슬라임이 보인다.\n"},
	{"저 멀리 아이스 슬라임이 보인다.\n"},
	{"저 멀리 스톤 슬라임이 보인다.\n"},
	{"저 멀리 에너지 슬라임이 보인다.\n"},
	{"저 멀리 엘리트 슬라임이 보인다.\n"},
	{"보스가 있는 최상층이다.\n저 멀리 슬라임 킹이 보인다.\n"},
	{"2층부터 20층의 던전에는 초보자가 잡을 수 없는 마물들이 살고 있다.\n저 멀리 스켈레톤이 보인다.\n"},
	{"저 멀리 스켈레톤 병사가 보인다.\n"},
	{"저 멀리 올드 스켈레톤이 보인다.\n"},
	{"저 멀리 올드 스켈레톤 병사가 보인다.\n"},
	{"저 멀리 스켈레톤 아처가 보인다.\n"},
	{"저 멀리 언데드 스켈레톤이 보인다.\n"},
	{"저 멀리 스켈레톤 군주가 보인다.\n"},
	{"저 멀리 언데드 스켈레톤 군주가 보인다.\n"},
	{"저 멀리 The Skeleton이 보인다.\n"},
	{"보스가 있는 최상층이다.\n저 멀리 스켈레톤 킹이 보인다.\n"},
	{"최종 보스가 있는 곳이다.\n저 멀리 코끼리 똥구멍이 보인다.\n"}
	
};
char MobName[21][100] = 
{
	{"슬라임"},
	{"워터 슬라임"},
	{"파이어 슬라임"},
	{"포이즌 슬라임"},
	{"일렉트릭 슬라임"},
	{"아이스 슬라임"},
	{"스톤 슬라임"},
	{"에너지 슬라임"},
	{"엘리트 슬라임"},
	{"슬라임 킹"},
	{"스켈레톤"},
	{"스켈레톤 병사"},
	{"올드 스켈레톤"},
	{"고대 스켈레톤 병사"},
	{"스켈레톤 아처"},
	{"언데드 스켈레톤"},
	{"스켈레톤 군주"},
	{"언데드 스켈레톤 군주"},
	{"The Skeleton"},
	{"스켈레톤 킹"},
	{"[최종보스]코끼리 똥구멍"},
};

int main()//메인함수 
{
	
	/*-----변수 초기화-----*/
	
	//플레이어 스텟	
	p.Lv = 1, p.Exp = 100, p.MaxExp = 20;//레벨 
	p.MaxHp = 10, p.Hp = p.MaxHp, p.HpGen = 0;//채력 
	p.MaxPp = 8, p.Pp = p.MaxPp, p.PpGen = 0;//마나 
	p.Atk = 3, p.Def = 0;//공격력, 방어력
	p.Speed = 10, p.Power = 1;//속도, 힘 

	//플래이어 분배스텟
	p.STR = 0, p.INT = 0, p.SPD = 0, p.REG = 0, p.BOD = 0;//분배스텟

	City();

}

int City()//마을 
{
	
	SetMobStat();
	
	//힐 
	
	p.Hp = p.MaxHp;
	
	p.Pp = p.MaxPp;
	
	playerRegenTick();
	
	int Select = 0;
	
	
	
	Line();
	ColorString(9,"-던전의 마을-\n");
	
	Line();
	ColorString(15,"유명한 던전이 있는 마을이다.\n");
	
	B1://B1
	
	Line();
	ColorString(10,"[메뉴와 호환되는 숫자를 입력하세요.]\n");
	ColorString(7,"1:던전 입장\n");
	ColorString(7,"2:잡화상점 입장\n");
	ColorString(7,"3:스테이더스 확인\n");
	ColorString(7,"4:정비\n");
	
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

int Dungeon(int Grade)//던전 
{	

	Dungeon_Start(Grade);
	
	Dungeon_Main(Grade);

}

int Dungeon_Start(int Grade)//던전 입장 
{
	
	
	
	playerRegenTick();
	Line();
	ColorString(3, "-던전에 입장하였습니다!-\n");
	Sleep(2000);
	Line();
	ColorString(4, "-기절시 귀환석이 없으면 사망하니 주의해주세요.\n");
	Sleep(2000);
	
}

int Dungeon_Main(int Grade)//던전 선택창 
{
	
	playerRegenTick();
	
	int Select = 0;
	
	Line();
	ColorString(3,"");
	printf("-던전 %d층-\n", Grade+1);
	
	Line();
	ColorString(9,"");
	printf("%s", MAPINF[Grade]);
	
	A1://A1
	
	Line();
	ColorString(10,"[메뉴와 호환되는 숫자를 입력하세요.]\n");
	ColorString(7,"1:전투\n");
	ColorString(7,"2:스탯 확인\n");
	ColorString(7,"3:정비\n");
	
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

int Dungeon_Fight(int Grade)//전투 
{
	
	playerRegenTick();
	
	Line();
	ColorString(4,"");
	printf("[%s이(가) 튀어나왔다!]\n", MobName[Grade]);
	Sleep(1000);	
	
	int Select = 0;
	
	E1:
	
	Line();
	ColorString(2,"[무엇을 하시겠습니까?]\n");	
	
	C1:
	
	Line();
	ColorString(10,"[메뉴와 호환되는 숫자를 입력하세요.]\n");
	ColorString(7,"1:공격\n");
	//ColorString(7,"2:방어\n");
	ColorString(7,"3:아이템 사용\n");
	//ColorString(7,"4:스킬\n");
	
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

int Fight_Attek(int Grade)//공격 
{
	
	if(p.Atk - Mob[Grade].Def < 0){
		
		Line();
		ColorString(15,"");
		printf("%s에게 0의 피해를 입혔습니다!\n",MobName[Grade]);
		Sleep(800);
		
	}
	else{
		
		Line();
		ColorString(15,"");
		printf("%s에게 %d의 피해를 입혔습니다!\n",MobName[Grade], p.Atk - Mob[Grade].Def);
		Sleep(800);
		
		Mob[Grade].Hp -= p.Atk - Mob[Grade].Def;	
		
	}
	
	if(Mob[Grade].Hp < 0){
		
		Mob[Grade].Hp = 0;
		
	}
	
	Line();
	ColorString(15,"");
	printf("%s 남은 채력:%d/%d\n",MobName[Grade], Mob[Grade].MaxHp, Mob[Grade].Hp);
	Sleep(800);
	
}

int CheckMobDied(int Grade)//몹 사망여부 
{
	
	if(Mob[Grade].Hp<1)
	{
		
		Line();
		ColorString(1,"");
		printf("%s이(가) 죽었습니다!\n", MobName[Grade]);
		Sleep(800);
		
		p.Exp += Mob[Grade].Exp;
		Line();
		ColorString(2,"");
		printf("경험치를 %d 획득하였습니다!\n",Mob[Grade].Exp);
		Sleep(800);
		
		Money += Mob[Grade].MaxExp;
		Line();
		ColorString(6,"");
		printf("%d골드를 획득하였습니다!\n",Mob[Grade].MaxExp);
		Sleep(800);
		
		CheckLvUp();
		
		Dungeon(Grade+1);
		
	}
	
}

int MobAttek(int Grade)//몹 공격 
{
	
	Line();
	ColorString(5,"");
	printf("%s의 공격!\n",MobName[Grade]);
	Sleep(800);
	
	if(Mob[Grade].Atk - p.Def < 0){
		
		Line();
		ColorString(4,"");
		printf("0의 피해를 입었습니다!\n");
		Sleep(800);
		
	} 
	else{
		
		p.Hp -= Mob[Grade].Atk - p.Def;
	
		Line();
		ColorString(4,"");
		printf("%d의 피해를 입었습니다!\n", Mob[Grade].Atk - p.Def);
		Sleep(800);
		
	}
	
	if(p.Hp < 0){
		
		p.Hp = 0;
		
	}
	
	Line();
	ColorString(2,"");
	printf("남은 채력 %d/%d\n",p.MaxHp,p.Hp);
	Sleep(800);

	
}

int CheckPlayerDied()//플래이어 사망여부 
{
	
	if(p.Hp < 1){
		
		Line();
		ColorString(4,"기절하셨습니다.\n");
		Sleep(800);
		
		if(Item[0] > 0){
			
			Line();
			ColorString(4,"귀환석이 남아 있어 사망하지 않고 마을로 귀환합니다.\n");
			Sleep(800);
			Line();
			ColorString(4,"기절하여 경험치가 0으로 초기화되며, 요구되는 경험치량이 2배 증가합니다..\n");
			Sleep(800);
			p.Exp = 0;
			p.MaxExp *= 2;
			p.Hp = 1;
			Item[0] -= 1;
			City();
			
		}
		else{
			
			Line();
			ColorString(4,"귀환석이 남아 있지 않습니다.\n당신은 사망하였습니다.\n");
			Sleep(800);
			Line();
			ColorString(4,"게임을 처음부터 다시 시작합니다.\n");
			Sleep(800);
			main();
			
		}
		
	}
	
}

int Shop()//상점 
{
	
	
	
	playerRegenTick();
	
	int Select = 0;
	
	Line();
	ColorString(3,"-잡화상점-\n");
	Line();
	ColorString(9,"-여러 가지 물품을 판매하고 있다.\n");
	
	F1:
	
	Line();
	ColorString(10,"[메뉴와 호환되는 숫자를 입력하세요.]");
	printf("소지금 %dG\n",Money);
	ColorString(7,"1:소모품\n");
	//ColorString(7,"2:장비\n");
	//ColorString(7,"3:판매\n");
	ColorString(7,"4:탈주\n");
	
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

int ShopExpend()//소모품 
{
	
	
	
	int Select;
	
	Line();
	ColorString(3,"-소모품-\n");
	
	G1:
	
	Line();
	ColorString(10,"[메뉴와 호환되는 숫자를 입력하세요.]");
	printf("소지금 %dG\n",Money);
	ColorString(7,"1:물약\n");
	ColorString(7,"2:[10골드]귀환석\n");
	ColorString(7,"3:탈주\n");
	
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

int ShopPotion()//물약 
{
	
	
	
	int Select = 0; 
	
	Line();
	ColorString(3,"-물약-\n");
	
	H1:
	
	Line();
	ColorString(10,"[메뉴와 호환되는 숫자를 입력하세요.]");
	printf("소지금 %dG\n",Money);
	ColorString(7,"1:[5골드]채력 물약(소)[Hp 5 회복]\n");
	ColorString(7,"2:[10골드]채력 물약(중)[Hp 8 회복]\n");
	ColorString(7,"3:[20골드]채력 물약(대)[Hp 15 회복]\n");
	ColorString(7,"4:[40골드]채력 물약(특대)[Hp 25 회복]\n");
	ColorString(7,"5:[5골드]마나 물약(소)[Pp 5 회복]\n");
	ColorString(7,"6:[10골드]마나 물약(중)[Pp 8 회복]\n");
	ColorString(7,"7:[20골드]마나 물약(대)[Pp 15 회복]\n");
	ColorString(7,"8:[40골드]마나 물약(특대)[Pp 25 회복]\n");
	ColorString(7,"9:탈주\n");
	
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

int CheckLvUp()//레벨업 확인 
{
	
	if(p.Exp > p.MaxExp-1){
		
		LevelUp();
		
	}
	
}

int LevelUp()//레벨업 
{
	
	Sleep(1000);
	
	int Stat[6];
	
	int DX;
	
	Line();
	ColorString(6,"레벨이 올랐습니다!\n");
	
	p.SP += 5+p.Lv/20;
	
	MXS:
	
	Line();
	ColorString(1,"스텟 분배를 해 주세요.");
	printf("[스텟 포인트:%d]\n",p.SP);
	
	Line();
	ColorString(4,"STR:힘 스텟\n");
	ColorString(1,"INT:마법력 스텟\n");
	ColorString(2,"SPD:속도 스텟\n");
	ColorString(6,"REG:재생력 스텟\n");
	ColorString(5,"BOD:맷집 스텟\n");
	
	ColorString(15,"STR INT SPD REG BOD에 각각 부여할 스텟 수치를 순서대로 입력해 주세요.\n");
	
	scanf("%d %d %d %d %d", &Stat[0], &Stat[1], &Stat[2], &Stat[3], &Stat[4]);
	Stat[5] = Stat[0]+Stat[1]+Stat[2]+Stat[3]+Stat[4];
	
	if(Stat[5]>p.SP){
		
		Line();
		ColorString(4,"보유하고 있는 스텟 포인트보다 사용량이 많습니다!\n");
		
		goto MXS;
		
	}
	if(Stat[5]<0){
		
		Line();
		ColorString(4,"음수는 입력 불가합니다!\n"); 
		
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
	
	ColorString(6,"스텟 분배가 완료되었습니다!\n");
	
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

int BuyItem(int ItemNum)//아이템 구매 
{
	
	if(Money > ItemPrize[ItemNum]-1){
		
		Item[ItemNum] += 1;
		Money -= ItemPrize[ItemNum];
		
		Line();
		ColorString(6,"");
		printf("%s을(를)구매하였습니다!\n",ItemName[ItemNum]);
		
	}
	else{
		
		Line();
		ColorString(4,"");
		printf("골드가 모자랍니다!\n");
		
	}
	
	Shop();
	
}  

int playerRegenTick()//회복 
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

int ShowStat()//스텟창 
{
	
	Line();
	ColorString(1,"-스테이더스-\n");
	Line();
	ColorString(15,"");
	printf("LV:%-20d Exp:%-10d/%-10d\n",p.Lv,p.MaxExp,p.Exp);
	printf("Hp:%-10d/%-10d HpGen:%-20d\n",p.MaxHp,p.Hp,p.HpGen);
	printf("Pp:%-10d/%-10d PpGen:%-20d\n",p.MaxPp,p.Pp,p.PpGen); 
	printf("Atk:%-20d Def:%-20d\n",p.Atk,p.Def);
	printf("Speed:%-18d Power:%-20d\n",p.Speed,p.Power);
	
}

int ShowArmor()//장비창
{
	
	Line();
	ColorString(1,"-장비-\n");
	
	Line();	
	ColorString(15,"");
	printf("모자:%s\n",ItemName[p.Hat-1]);
	printf("갑옷:%s\n",ItemName[p.Body-1]);
	printf("바지:%s\n",ItemName[p.Leggings-1]);
	printf("신발:%s\n",ItemName[p.Shose-1]);
	printf("무기:%s\n",ItemName[p.Wepon-1]);
	printf("방패:%s\n",ItemName[p.Shiled-1]);
	
} 

int ShowInventory()//인벤토리
{
	
	
	
	Line();
	
	ColorString(1,"-인벤토리-\n");	
	
} 

int SelectItem()
{
	
	int Select = 0;
	
	int i = 0;

	Line();
	ColorString(10,"[메뉴와 호환되는 숫자를 입력하세요.]\n");
	
	while(i < 19){
		
		if(Item[i] > 0){
			
			Line();
			
			ColorString(15,"");
			
			printf("%d:%s[%d개]\n",i+1,ItemName[i],Item[i]);
			
			
			
		}
		i += 1;
		
	}
	Line();
	ColorString(15,"없는 번호:쓸모없는 턴 소비\n"); 
	
	scanf("%d", &Select);
	
	Select -= 1;
	
	if(Item[Select] > 0){
		
		Useitem(Select);
		
	}
	else{
		
		Line();
		ColorString(5,"아이템이 존재하지 않거나 갯수가 부족합니다!\n");
		
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
				ColorString(4,"마을로 귀환합니다.\n");
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
				ColorString(5,"아이템이 존재하지 않거나 갯수가 부족합니다!\n");
				SelectItem();
				
		
		}
		
	}
	
}

int HpPotion(int Hp, int Potion)
{
	
	Line();
	ColorString(1,"체력 물약을 사용하였습니다!\n");
	Sleep(800);
	
	p.Hp += Hp;
	if(p.Hp > p.MaxHp)
		p.Hp = p.MaxHp;
	
	Item[Potion+1] -= 1;
	
}

int PpPotion(int Pp, int Potion)
{
	
	Line();
	ColorString(1,"마나 물약을 사용하였습니다!\n");
	Sleep(800);
	
	p.Pp += Pp;
	if(p.Pp > p.MaxPp)
		p.Pp = p.MaxPp;
	
	Item[Potion+1] -= 1;
	
}

int ColorString(int Color,char String[])//색깔 택스트 출력 
{
		
	SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE ),Color);
	
	printf("%s",String);
		
	return 0;
		
}

int SetMobStat()//몹 스텟 초기화 
{
	
	//층수/경치/돈/피/젠/마나/젠/공/방/속/힘 
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
	Mob[Grade].MaxHp = MaxHp, Mob[Grade].Hp = Mob[Grade].MaxHp, Mob[Grade].HpGen = HpGen;//채력 
	Mob[Grade].MaxPp = MaxPp, Mob[Grade].Pp = Mob[Grade].MaxPp, Mob[Grade].PpGen = PpGen;//마나 
	Mob[Grade].Atk = Atk, Mob[Grade].Def = Def;//공격력, 방어력 
	Mob[Grade].Speed = Speed, Mob[Grade].Power = Power;//속도, 힘 
	
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

/*베타 0.1
기본 프로그램 구현
*베타 0.11
포션 아이템 추가
*베타 0.12
기절시 경험치 0으로 초기화와 요구 경험치 2배 증가 
*베타 0.13
11~20층 몹 추가 및 벨런스 패치 
*/
