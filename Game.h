#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

/*******************************************
*�ļ�����Game.h
*����������������Ϸ��һЩ���Ľṹ�ͺ���
*���ڣ�2019.5.10
*******************************************/

#include <stdio.h>
#include <string.h>
#include <windows.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <conio.h>

/**************��Ϸ�Ľṹ����**************/

//��ͼ
typedef struct _map {
    int id;
    char name[50];
    int minLevel;
    COORD coord;    //����ṹ
    char desc[500];
}Map;

//��Ϸ��������ö��
typedef enum _proptype {
    Weapon, Armor, Con
}PropType;

//װ��
typedef struct _prop {
    int id;
    char name[50];
    int level;
    int stock;
    int price;
    PropType type;
    union {             //���ϻ��� ��ѡһ
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

//����
typedef struct _martial {
    int id;
    char name[50];
    COORD hqCoord;
    int isOpen;
    char desc[1000];
}Martial;

//��ɫ
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

//����
typedef struct _monster {
    int id;
    char name[50];
    int level;
    int hp;
    int att;        //������
    int deff;       //������
    int minMoney;   //ɱ��������������ٽ��
    int maxMoney;   //ɱ����������������
    int exp;        //����ֵ
    int state;      //���ﵱ��״̬ 0:�������� ��0��ʾ������
    COORD coord;    //���������
}Monster;

/**************��Ϸ�Ĳ��Ժ���**************/
void Init();
void Show();

/**************��Ϸ�ĺ���**************/
void Start();                   //��ʼ����
void ShowWelcome();             //��ӭ��Ϣ
void ShowMap();                 //��Ϸ��ͼ
void ShowMapNC();               //����ͼ
void ShowInfo();                //��Ϸ�ڲ���Ϣ
void showMainMenu();            //��Ϸ�Ľ���˵�
void ShowMapInfo();             //��Ϸ��ͼ����Ϣ(��Ϣ������)
void ProcessMainMenu(char key); //������Ϸ�����˵�
void ShowSquare();              //��ʾ�߿�
void ShowWarn();                //��ʾ����
void Save();                    //�浵
void Load();                    //��ȡ
void Register();                //ע��
void Login();                   //��½
void StartMenu();               //��ʼ�˵�
void StartSquare();             //��ʼ����
char * Star(char *);            //�����Ǻ�����
/**************���˵�����**************/
void ShowPlayerInfo();          //��Ϣ������ʾ��ҵĸ�������
void ShowMonsters();            //����Ϣ������ʾ��ǰ��ͼ�Ĺ���
void Fight(int monsterId);      //�������ж�ս
void Move(int x, int y);        //�ص��ܶ棬������������ƶ�
void Trade();                   //����װ��
void SwitchH();                 //�л���ɫ
void DeleteH();                 //ɾ����ɫ
void SwitchE();                 //�л�װ��
void Rename();                  //����
void Repassword();              //�޸�����
#endif // GAME_H_INCLUDED

