#include <stdio.h>
#include <stdlib.h>
#include "Game.h"
#include "GameLib.h"
#include <conio.h>

#include<windows.h>
#include<mmsystem.h>
#pragma comment(lib, "winmm.lib")

extern int X, Y;

//�û���ȫ�ֱ�������

int main()
{

    char key;   //���յ����û�����
    PlaySound("xxx.wav",NULL,SND_FILENAME|SND_ASYNC |SND_LOOP);
    //���ÿ���̨����
    SetTitle("Game of Thrones");
    //����������ɫ
    SetColor(10, 0);
    Load();
    Init();
    Start();
    ShowWelcome();
    ShowMapNC();
    ShowInfo();
    ShowWarn();
    if(getch())
    {
        ShowMap();
        ShowInfo();
        ShowSquare();
        showMainMenu();
        while(1)
            {
                //������뻺����
                fflush(stdin);
                key = getch();
                fflush(stdin);
                if(key != 37 && key != 38 && key != 39 && key != 40 && key != 72 && key != 75 && key != 77 && key != 80)
                {
                    //printf("��Ϸ�˵�");
                    ProcessMainMenu(key);
                    continue;
                }
                else if(key == 38 || key == 72)
                {
                    Y--;//��
                }
                else if(key == 39 || key == 77)
                {
                    X++;//��
                }
                else if(key == 40 || key == 80)
                {
                    Y++;//��
                }
                else if(key == 37 || key == 75)
                {
                    X--;//��
                }

            if(X > 7) X = 0;
            if(X < 0) X = 7;
            if(Y > 7) Y = 0;
            if(Y < 0) Y = 7;
            ShowMap();
        }
    }
    return 0;
}
