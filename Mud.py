#스테이더스 변수 선언
from distutils.util import execute
from http.server import executable


Type = ["Player", "Dummy","Mob"]
Name = ["Player", "Dummy","슬라임"]
Lv, Exp, MaxExp = [1, 1, 1], [5, 1, 5], [0, 1, 10]
MaxHp, Hp = [10, 1000, 3], [10, 1000, 3]
MaxMp, Mp = [10, 1000, 0], [10, 1000, 0]
Atk, Def = [3, 0, 1], [3, 0, 0]

Dungeon_Mob_Type = ["Dummy","Mob"]
Dungeon_Mob_Name = ["Dummy","슬라임"]
Dungeon_Mob_Lv, Dungeon_Mob_Exp, Dungeon_Mob_MaxExp = [1, 1], [1, 5], [1, 10]
Dungeon_Mob_MaxHp, Dungeon_Mob_Hp = [1000, 3], [1000, 3]
Dungeon_Mob_MaxMp, Dungeon_Mob_Mp = [1000, 0], [1000, 0]
Dungeon_Mob_Atk, Dungeon_Mob_Def = [0, 1], [0, 0]

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

def Dungeon_Fight_Attek(DungeonNum, Floor): # 공격
    print("플레이어 %s의 공격!" % Name)
    # Dungeon_Mob_Hp -= Atk // Dungeon_Mob_Def 왜 오류가 나는것이지..
    print("%s은(는) %d의 데미지를 입었다!" % (Dungeon_Mob_Name, Atk // Dungeon_Mob_Def))

def Dungeon_Fight(DungeonNum, Floor): # 던전 전투
    while Hp > 0 or Dungeon_Mob_Hp > 0: 
        print("전투 시작!")
        print("당신은 %s 중 하나의 행동을 하실 수 있습니다." % Dungeon_Fight_Command)
        Command = input("할 행동을 입력해 주세요:")
        for i in range(len(Dungeon_Fight_Command)):
            if Command == Dungeon_Fight_Command[i]:
                exec(Dungeon_Fight_Run_Command[i])
                break
            elif i == len(Dungeon_Fight_Command) - 1:
                print("다시 입력해 주세요")



def Dungeon_Next_Floor(DungeonNum, Floor): # 다음 층으로 전진
    print("다음 층으로 올라갑니다..")
    Dungeon(DungeonNum,Floor+1)

def Dungeon(DungeonNum,Floor): # 던전 루프
    while True:
        print("지금 당신은 %d층에 있습니다." % Floor)
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
    Dungeon(DungeonNum,Floor)


def Shop(Name): # 상점 열기
    print("%s" % (Name))

def Show_Status(Num): # 스테이더스 보여주기
    print("이름:%s          종류:%s         " % (Name[Num], Type[Num]))
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