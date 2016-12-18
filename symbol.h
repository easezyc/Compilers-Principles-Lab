#ifndef SYMBOL_H_INCLUDED
#define SYMBOL_H_INCLUDED
struct arg{
    char* typname;
    char* name;
    int functype;   //0表示普通变量，1表示结构体变量，2表示数组变量
    struct arg* next;
};
struct symbol{
    struct symbol* next;
    char* name;
    char* typname;
    int functype;   //0表示普通变量，1表示结构体变量，3表示函数变量,2表示数组
    struct arg* arg;
}*symbollist;
void insertsym2(char* name,char* typname,int functype,struct arg* arg); //插入函数和结构体
int lookup(char* name);   //查询符号是否在符号表
void symbollisttrace();   //遍历符号表，并输出
void addsymbol1(char* name,struct namelist* namelist,int line);    //插入普通变量组
void initsymbolist();    //初始化符号表
void modfunctype(char* name,char* typname);     //修改函数和结构体的functype
struct arg* getarg(struct namelist* namelist);   //将head.h中的namelist转换为arg
void addfunc(char* name,struct namelist* namelist,int mark,int line);   //添加函数
int getfunctype(char* name);   //获得符号的functype
char* gettype(char* name);    //获得符号的type名字
void freesymlist();    //清空符号表
struct arg* getfuncargs(char* name);   //获取参数表
#endif // SYMBOL_H_INCLUDED
