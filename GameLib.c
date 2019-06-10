/*******************************************
*�ļ�����GameLib.h
*����������������Ϸ���õ��Ŀ���̨����ϵͳ����
*���ڣ�2019.5.5
*******************************************/

#include "GameLib.h"
#include <stdlib.h>
#include <stdio.h>
#include <windows.h>

//���ÿ���̨����
void SetTitle(char *title)
{
    SetConsoleTitle(title);
}

void SetColor(int foreColor, int backColor)
{
    HANDLE winHandle;   //���
    winHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    //������ɫ
    SetConsoleTextAttribute(winHandle, foreColor + backColor * 0x10);
}

void SetPosition(int x, int y)
{
    //����x y��
    HANDLE winHandle;
    COORD pos = {x, y};
    winHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    //����λ��
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
