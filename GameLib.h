#ifndef GAMELIB_H_INCLUDED
#define GAMELIB_H_INCLUDED

/*******************************************
*�ļ�����GameLib.h
*����������������Ϸ���õ��Ŀ���̨����ϵͳ����
*���ڣ�2019.5.5
*******************************************/

#include <windows.h>
#include <stdio.h>

//���ÿ���̨���ڵı���
void SetTitle(char *title);
//���ÿ���̨����ɫ ǰ��ɫ�ͱ���ɫ
void SetColor(int foreColor, int backColor);
//���ù��λ��
void SetPosition(int x, int y);
//��x��y���꿪ʼ���rowCount��
void Clear(int x, int y, int rowCount);

#endif // GAMELIB_H_INCLUDED