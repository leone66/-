#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

/*******************************************
*文件名：Game.h
*描述：用来定义游戏的一些核心结构和函数
*日期：2019.5.10
*******************************************/

#include <stdio.h>
#include <string.h>
#include <windows.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <conio.h>

/**************游戏的结构类型**************/

//地图
typedef struct _map {
    int id;
    char name[50];
    int minLevel;
    COORD coord;    //坐标结构
    char desc[500];
}Map;

//游戏道具类型枚举
typedef enum _proptype {
    Weapon, Armor, Con
}PropType;

//装备
typedef struct _prop {
    int id;
    char name[50];
    int level;
    int stock;
    int price;
    PropType type;
    union {             //联合机构 多选一
        int minAttack;
        int minDefence;
        int minPower;
    };
    union {
        int maxAttack;
        int maxDefence;
        int maxPower;
    };
    char desc[200];
}Prop;

//门派
typedef struct _martial {
    int id;
    char name[50];
    COORD hqCoord;
    int isOpen;
    char desc[1000];
}Martial;

//角色
typedef struct _player {
    int id;
    char name[50];
    char password[20];
    int level;
    int exp;
    int hp;
    int gold;
    int propCount;
    int propMax;
    Martial martial;
    Prop weapon;
    Prop armor;
}Player;

//怪物
typedef struct _monster {
    int id;
    char name[50];
    int level;
    int hp;
    int att;        //攻击力
    int deff;       //防御力
    int minMoney;   //杀死怪物后掉落的最少金币
    int maxMoney;   //杀死怪物后掉落的最多金币
    int exp;        //经验值
    int state;      //怪物当的状态 0:怪物已死 非0表示怪物存活
    COORD coord;    //怪物的坐标
}Monster;

/**************游戏的测试函数**************/
void Init();
void Show();

/**************游戏的函数**************/
void Start();                   //开始界面
void ShowWelcome();             //欢迎信息
void ShowMap();                 //游戏地图
void ShowMapNC();               //纯地图
void ShowInfo();                //游戏内部信息
void showMainMenu();            //游戏的进入菜单
void ShowMapInfo();             //游戏地图的信息(信息界面中)
void ProcessMainMenu(char key); //处理游戏的主菜单
void ShowSquare();              //显示边框
void ShowWarn();                //显示警告
void Save();                    //存档
void Load();                    //读取
void Register();                //注册
void Login();                   //登陆
void StartMenu();               //起始菜单
void StartSquare();             //起始方框
char * Star(char *);            //密码星号输入
/**************主菜单函数**************/
void ShowPlayerInfo();          //信息界面显示玩家的个人资料
void ShowMonsters();            //在信息界面显示当前地图的怪物
void Fight(int monsterId);      //与怪物进行对战
void Move(int x, int y);        //回到总舵，给你坐标帮你移动
void Trade();                   //购买装备
void SwitchH();                 //切换角色
void DeleteH();                 //删除角色
void SwitchE();                 //切换装备
void Rename();                  //改名
void Repassword();              //修改密码
#endif // GAME_H_INCLUDED

