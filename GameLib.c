/*******************************************
*文件名：GameLib.h
*描述：用来定义游戏中用到的控制台还有系统操作
*日期：2019.5.5
*******************************************/

#include "GameLib.h"
#include <stdlib.h>
#include <stdio.h>
#include <windows.h>

//设置控制台窗口
void SetTitle(char *title)
{
    SetConsoleTitle(title);
}

void SetColor(int foreColor, int backColor)
{
    HANDLE winHandle;   //句柄
    winHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    //设置颜色
    SetConsoleTextAttribute(winHandle, foreColor + backColor * 0x10);
}

void SetPosition(int x, int y)
{
    //传入x y轴
    HANDLE winHandle;
    COORD pos = {x, y};
    winHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    //设置位置
    SetConsoleCursorPosition(winHandle, pos);

}

void Clear(int x, int y, int rowCount)
{
    //SetPosition(x, y);
    int i, j;
    for(i = 0; i < rowCount; i++)
        {
            SetPosition(x, y + i);
            for(j = 0; j < 76; j++)
            {
                printf(" ");
            }
        }
}
