from distutils.util import execute
from http.server import executable
from time import sleep

#스테이더스 변수 선언

Type = ["Player", "Dummy","Mob"]
Name = ["Player", "Dummy","슬라임"]
Gold = [0]
Lv, Exp, MaxExp = [1, 1, 1], [0, 1, 5], [5, 1, 10]
MaxHp, Hp = [10, 1000, 3], [10, 1000, 3]
MaxMp, Mp = [10, 1000, 0], [10, 1000, 0]
Atk, Def = [3, 0, 1], [3, 0, 0]

# 던전 몹 관련 변수 선언
# Type는 그냥 Mob으로 추가해주세요.
# 2차원 배열이고, 하나의 차원마다 한 개의 던전이 할당됩니다.
# 즉, 기존 던전에 몹을 추가하고 싶으시면 뒤에 그대로 이어 붙여주세요.
# Type는 아직 신경쓰실 필요 없습니다.
# Name는 몹 이름, Mob_Exp와 Mob_MaxExp는 각각 처치시 얻는 골드, 경험치입니다.

Dungeon_Mob_Type = [["Dummy","Mob","Mob","Mob","Mob","Mob","Mob","Mob","Mob","Mob","Mob"]]
Dungeon_Mob_Name = [["Dummy","슬라임","미들 슬라임","빅 슬라임","스트롱 슬라임","탱 슬라임","락 슬라임","효율 슬라임","엘리트 슬라임","중간보스 슬라임","[BOSS]킹 슬라임"]]
Dungeon_Mob_Lv, Dungeon_Mob_Exp, Dungeon_Mob_MaxExp = [[1, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10]], [[1, 5, 6, 8, 10, 15, 20, 50, 30, 40, 100]], [[1, 10, 15, 20, 25, 30, 40, 100, 60, 80, 200]]
Dungeon_Mob_MaxHp, Dungeon_Mob_Hp = [[1000, 3, 5, 10, 15, 50, 30, 40, 50, 100, 300]], [[1000, 3, 5, 10, 15, 50, 30, 40, 50, 100, 300]]
Dungeon_Mob_MaxMp, Dungeon_Mob_Mp = [[1000, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0]], [[1000, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0]]
Dungeon_Mob_Atk, Dungeon_Mob_Def = [[0, 1, 3, 5, 15, 5, 7, 10, 30, 40, 75]], [[0, 0, 1, 3, 3, 5, 20, 10, 20, 40, 75]]

#기타 변수 선언
Village_Name = ["시작의 마을"]
Village_Lore = ["모든 용사의 일대기가 시작되는 마을.\n각종 시설들이 설치되어 있다.\n"]
Village_Command = [ # 세로 순으로 진행되는 마을.
    ["장비상점", "무기상점", "잡화상점", "던전 입장", "종료"]
]
Village_Run_Command = [
    ["Shop(\"시작의 마을-장비상점\")", "Shop(\"시작의 마을-무기상점\")", "Shop(\"시작의 마을-잡화상점\")", "Entrance_Dungeon(0)", "quit()"]
]

Dungeon_Name = ["시작의 던전"]
Dungeon_Fight_Command = ["공격"]
Dungeon_Fight_Run_Command = ["Dungeon_Fight_Attek(DungeonNum, Floor)"]

Dungeon_Command = [
    ["다음 층으로", "전투", "종료"]
]
Dungeon_Run_Command = [
    ["Dungeon_Next_Floor(DungeonNum, Floor)", "Dungeon_Fight(DungeonNum, Floor)", "quit()"]
]


# 시스템 변수 선언
Command = "None"

# 함수호출

def Reset_Dungeon(): # 던전 리셋
    global Dungeon_Mob_Type,Dungeon_Mob_Name,Dungeon_Mob_Lv, Dungeon_Mob_Exp, Dungeon_Mob_MaxExp,Dungeon_Mob_MaxHp, Dungeon_Mob_Hp,Dungeon_Mob_MaxMp, Dungeon_Mob_Mp,Dungeon_Mob_Atk, Dungeon_Mob_Def
    Dungeon_Mob_Type = [["Dummy","Mob","Mob","Mob","Mob","Mob","Mob","Mob","Mob","Mob","Mob"]]
    Dungeon_Mob_Name = [["Dummy","슬라임","미들 슬라임","빅 슬라임","스트롱 슬라임","탱 슬라임","락 슬라임","효율 슬라임","엘리트 슬라임","중간보스 슬라임","[BOSS]킹 슬라임"]]
    Dungeon_Mob_Lv, Dungeon_Mob_Exp, Dungeon_Mob_MaxExp = [[1, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10]], [[1, 5, 6, 8, 10, 15, 20, 50, 30, 40, 100]], [[1, 10, 15, 20, 25, 30, 40, 100, 60, 80, 200]]
    Dungeon_Mob_MaxHp, Dungeon_Mob_Hp = [[1000, 3, 5, 10, 15, 50, 30, 40, 50, 100, 300]], [[1000, 3, 5, 10, 15, 50, 30, 40, 50, 100, 300]]
    Dungeon_Mob_MaxMp, Dungeon_Mob_Mp = [[1000, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0]], [[1000, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0]]
    Dungeon_Mob_Atk, Dungeon_Mob_Def = [[0, 1, 3, 5, 15, 5, 7, 10, 30, 40, 75]], [[0, 0, 1, 3, 3, 5, 20, 10, 20, 40, 75]]

def Dungeon_Mob_Attek(DungeonNum, Floor): # 몹 공격
    print("%s의 공격!" % Dungeon_Mob_Name[DungeonNum][Floor])
    sleep(0.3)
    Hp[0] -= Dungeon_Mob_Atk[DungeonNum][Floor] - Def[0]
    print("%s은(는) %d의 데미지를 입었다!" % (Name[0], Dungeon_Mob_Atk[DungeonNum][Floor] - Def[0]))
    sleep(0.3)
    if Hp[0] > MaxHp[0]:
        Hp[0] = MaxHp[0]
    print("%s의 남은 HP:%d/%d" % (Name[0], MaxHp[0], Hp[0]))
    sleep(0.3)
    Dungeon_Check_Player_Dead(DungeonNum,Floor)

def Dungeon_Check_Player_Dead(DungeonNum,Floor): # 플레이어 사망 체크
    if Hp[0] <= 0:
        print("전투에서 패배하였습니다!")
        sleep(0.3)
        print("운명하셨습니다.")
        sleep(0.3)
        Hp[0] = 1
        Village(0)
    else:
        Dungeon_Player_Turn(DungeonNum, Floor)

def Dungeon_Mob_Turn(DungeonNum, Floor): # 던전 몹 턴
    Dungeon_Mob_Attek(DungeonNum, Floor)

def Dungeon_Check_Mob_Dead(DungeonNum,Floor): # 몹 사망 체크
    if Dungeon_Mob_Hp[DungeonNum][Floor] <= 0:
        print("전투에서 승리하였습니다!")
        sleep(0.3)
        Exp[0] += Dungeon_Mob_MaxExp[DungeonNum][Floor]
        Gold[0] += Dungeon_Mob_Exp[DungeonNum][Floor]
        print("경험치 %d, 골드 %d만큼 획득하였습니다." % (Dungeon_Mob_MaxExp[DungeonNum][Floor], Dungeon_Mob_Exp[DungeonNum][Floor]))
        sleep(0.3)
        Check_Player_Levelup()
        Dungeon(DungeonNum,Floor)
    else:
        Dungeon_Mob_Turn(DungeonNum, Floor)

def Check_Player_Levelup(): # 플레이어 레벨업
    if Exp[0] >= MaxExp[0]:
        Exp[0] -= MaxExp[0]
        Lv[0] += 1
        print("레벨 업![Lv %d]" % Lv[0])
        sleep(0.3)
        MaxHp[0] += Lv[0]
        Hp[0] += Lv[0]
        MaxMp[0] += Lv[0] // 3
        Mp[0] += Lv[0] // 3
        Atk[0] += Lv[0] // 10
        Def[0] += Lv[0] // 30
        MaxExp[0] *= 1 + (1 / Lv[0])
        MaxExp[0] = int(MaxExp[0])
        Check_Player_Levelup()
        Show_Status(0)

def Dungeon_Player_Turn(DungeonNum, Floor): # 플레이어 턴
    print("당신은 %s 중 하나의 행동을 하실 수 있습니다." % Dungeon_Fight_Command)
    sleep(0.3)
    running = True
    while(running):
        Command = input("할 행동을 입력해 주세요:")
        for i in range(len(Dungeon_Fight_Command)):
            if Command == Dungeon_Fight_Command[i]:
                exec(Dungeon_Fight_Run_Command[i])
                running = False
                break
            elif i == len(Dungeon_Fight_Command) - 1:
                print("다시 입력해 주세요")

def Dungeon_Fight_Attek(DungeonNum, Floor): # 플레이어 공격
    print("플레이어 %s의 공격!" % Name[0])
    sleep(0.3)
    Dungeon_Mob_Hp[DungeonNum][Floor] -= Atk[0] - Dungeon_Mob_Def[DungeonNum][Floor]   
    print("%s은(는) %d의 데미지를 입었다!" % (Dungeon_Mob_Name[DungeonNum][Floor], Atk[0] - Dungeon_Mob_Def[DungeonNum][Floor]))
    sleep(0.3)
    if Dungeon_Mob_Hp[DungeonNum][Floor] > Dungeon_Mob_MaxHp[DungeonNum][Floor]:
        Dungeon_Mob_Hp[DungeonNum][Floor] = Dungeon_Mob_MaxHp[DungeonNum][Floor]
    print("%s의 남은 HP:%d/%d" % (Dungeon_Mob_Name[DungeonNum][Floor], Dungeon_Mob_MaxHp[DungeonNum][Floor], Dungeon_Mob_Hp[DungeonNum][Floor]))
    sleep(0.3)
    Dungeon_Check_Mob_Dead(DungeonNum, Floor)

def Dungeon_Fight(DungeonNum, Floor): # 던전 전투
    print("전투 시작!")
    sleep(1)
    while Hp[0] > 0 or Dungeon_Mob_Hp[DungeonNum][Floor] > 0: 
        Dungeon_Player_Turn(DungeonNum, Floor)

def Dungeon_Next_Floor(DungeonNum, Floor): # 다음 층으로 전진
    print("다음 층으로 올라갑니다..")
    sleep(1)
    Dungeon(DungeonNum,Floor+1)

def Dungeon(DungeonNum,Floor): # 던전 루프
    Reset_Dungeon()
    while True:
        print("지금 당신은 %d층에 있습니다." % Floor)
        sleep(0.3)
        print("저 앞에 %s이(가) 보이는군요." % Dungeon_Mob_Name[DungeonNum][Floor])
        sleep(0.3)
        print("당신은 %s 중 하나의 행동을 하실 수 있습니다." % Dungeon_Command[DungeonNum])
        Command = input("할 행동을 입력해 주세요:")
        for i in range(len(Dungeon_Command[DungeonNum])):
            if Command == Dungeon_Command[DungeonNum][i]:
                exec(Dungeon_Run_Command[DungeonNum][i])
                break
            elif i == len(Dungeon_Command[DungeonNum]) - 1:
                print("다시 입력해 주세요.")

def Entrance_Dungeon(DungeonNum): # 던전 입장
    Floor = 0
    print("%s에 입장했습니다!(고유번호 %d)" % (Dungeon_Name[DungeonNum], DungeonNum))
    sleep(0.3)
    Dungeon(DungeonNum,Floor)

def Shop(Name): # 상점 열기
    print("%s" % (Name))

def Show_Status(Num): # 스테이더스 보여주기
    print("이름:%s          종류:%s         " % (Name[Num], Type[Num]))
    print("Lv:%d            Exp:%d/%d       " % (Lv[0], MaxExp[0], Exp[0]))
    print("Hp:%d/%d         Mp:%d/%d        " % (MaxHp[Num], Hp[Num], MaxMp[Num], Mp[Num]))
    print("Atk:%d           Def:%d          " % (Atk[Num], Def[Num]))

def Create_Charactor(): # 캐릭터 생성
    print("The World에 오신 것을 환영합니다.")
    Name[0] = input("당신의 이름을 말해주세요:")
    print("당신의 이름은 [%s]입니다." % (Name[0]))
    print("다음은 현제 당신의 스테이더스입니다.")
    Show_Status(0)
    print("이제 탑이 존재하는 세계로 들어갑니다. 즐거운 게임 되십시오.")

def Village(Num): # 마을
    print("-%s-" % (Village_Name[Num]))
    print("%s" % (Village_Lore[Num]))
    print("당신은 %s 중 하나의 행동을 하실 수 있습니다." % (Village_Command[Num]))
    Command = input("할 행동을 입력해 주세요:")
    Num2 = len(Village_Command[Num])
    for i in range(Num2):
        if Command == Village_Command[Num][i]:
            exec(Village_Run_Command[Num][i])
            break
        elif i == Num2 - 1:
            print("다시 입력해 주세요.")

# 소스 코드

Create_Charactor()
while True:
    Village(0)