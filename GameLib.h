#ifndef GAMELIB_H_INCLUDED
#define GAMELIB_H_INCLUDED

/*******************************************
*文件名：GameLib.h
*描述：用来定义游戏中用到的控制台还有系统操作
*日期：2019.5.5
*******************************************/

#include <windows.h>
#include <stdio.h>

//设置控制台窗口的标题
void SetTitle(char *title);
//设置控制台的颜色 前景色和背景色
void SetColor(int foreColor, int backColor);
//设置光标位置
void SetPosition(int x, int y);
//从x，y坐标开始清除rowCount行
void Clear(int x, int y, int rowCount);

#endif // GAMELIB_H_INCLUDED
