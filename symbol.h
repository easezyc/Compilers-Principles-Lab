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
void insertsym2(char* name,char* typname,int functype,struct arg* arg); //���뺯���ͽṹ��
int lookup(char* name);   //��ѯ�����Ƿ��ڷ��ű�
void symbollisttrace();   //�������ű������
void addsymbol1(char* name,struct namelist* namelist,int line);    //������ͨ������
void initsymbolist();    //��ʼ�����ű�
void modfunctype(char* name,char* typname);     //�޸ĺ����ͽṹ���functype
struct arg* getarg(struct namelist* namelist);   //��head.h�е�namelistת��Ϊarg
void addfunc(char* name,struct namelist* namelist,int mark,int line);   //��Ӻ���
int getfunctype(char* name);   //��÷��ŵ�functype
char* gettype(char* name);    //��÷��ŵ�type����
void freesymlist();    //��շ��ű�
struct arg* getfuncargs(char* name);   //��ȡ������
#endif // SYMBOL_H_INCLUDED
