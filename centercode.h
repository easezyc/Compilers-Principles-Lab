#ifndef INTERMEDIATE_CODE_H_INCLUDED
#define INTERMEDIATE_CODE_H_INCLUDED
#include"symbol.h"
FILE *fp;//�����ļ���ָ�룬���ڴ�д�������ļ�
int num;//�Լ�����ı�������
int asmnum;//�����label����
char* common[50];//�洢�Լ�����ı���������
void tracetree2(struct ast *t);//�����﷨���������м�����Ŀ�����
void traceexp(struct ast *t,int mark);//����EXP�ڵ�
void tracearg(struct ast *t,struct arg *args);//����Arg�ڵ�
void openfile();//���ļ�����ʼ��
int getloc(char* name);//��ñ����������ڴ��ַ
void symbollisttrace2();//�������ű�
void closefile();//�ر��ļ�
#endif // INTERMEDIATE_CODE_H_INCLUDED
