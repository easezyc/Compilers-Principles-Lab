#ifndef INTERMEDIATE_CODE_H_INCLUDED
#define INTERMEDIATE_CODE_H_INCLUDED
#include"symbol.h"
FILE *fp;//定义文件流指针，用于打开写操作的文件
int num;//自己定义的变量数量
int asmnum;//汇编中label计数
char* common[50];//存储自己定义的变量的名字
void tracetree2(struct ast *t);//遍历语法树，生成中间代码和目标代码
void traceexp(struct ast *t,int mark);//遍历EXP节点
void tracearg(struct ast *t,struct arg *args);//遍历Arg节点
void openfile();//打开文件并初始化
int getloc(char* name);//获得变量的物理内存地址
void symbollisttrace2();//遍历符号表
void closefile();//关闭文件
#endif // INTERMEDIATE_CODE_H_INCLUDED
