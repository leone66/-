#include <stdio.h>
#include <stdlib.h>
#include "Game.h"
#include "GameLib.h"
#include <conio.h>

#include<windows.h>
#include<mmsystem.h>
#pragma comment(lib, "winmm.lib")

extern int X, Y;

//用户的全局变量坐标

int main()
{

    char key;   //接收到的用户按键
    PlaySound("xxx.wav",NULL,SND_FILENAME|SND_ASYNC |SND_LOOP);
    //设置控制台名称
    SetTitle("Game of Thrones");
    //更改字体颜色
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
                //清空输入缓冲区
                fflush(stdin);
                key = getch();
                fflush(stdin);
                if(key != 37 && key != 38 && key != 39 && key != 40 && key != 72 && key != 75 && key != 77 && key != 80)
                {
                    //printf("游戏菜单");
                    ProcessMainMenu(key);
                    continue;
                }
                else if(key == 38 || key == 72)
                {
                    Y--;//上
                }
                else if(key == 39 || key == 77)
                {
                    X++;//右
                }
                else if(key == 40 || key == 80)
                {
                    Y++;//下
                }
                else if(key == 37 || key == 75)
                {
                    X--;//左
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
