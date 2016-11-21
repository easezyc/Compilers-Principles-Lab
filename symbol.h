#ifndef SYMBOL_H_INCLUDED
#define SYMBOL_H_INCLUDED
struct arg{
    char* typname;
    char* name;
    int functype;   //0��ʾ��ͨ������1��ʾ�ṹ�������2��ʾ�������
    struct arg* next;
};
struct symbol{
    struct symbol* next;
    char* name;
    char* typname;
    int functype;   //0��ʾ��ͨ������1��ʾ�ṹ�������3��ʾ��������,2��ʾ����
    struct arg* arg;
}*symbollist;
void insertsym2(char* name,char* typname,int functype,struct arg* arg);
int lookup(char* name);
void symbollisttrace();
void addsymbol1(char* name,struct namelist* namelist);
void initsymbolist();
void modfunctype(char* name,char* typname);
struct arg* getarg(struct namelist* namelist);
void addfunc(char* name,struct namelist* namelist);
int getfunctype(char* name);
char* gettype(char* name);
#endif // SYMBOL_H_INCLUDED
