#include<stdio.h>
#include<string.h>
#include"error.h"
void error1(char* name,int line)
{
    int mark=lookup(name);
    if(mark==0)
    {
        printf("Error type 1 at Line %d: Undefined variable \"%s\"\n",line,name);
    }
}
void error2(char* name,int line)
{
    int mark=lookup(name);
    if(mark==0)
    {
        printf("Error type 2 at Line %d: Undefined function \"%s\"\n",line,name);
    }
}
void error3(char* name,int line)
{
    printf("Error type 3 at Line %d: Redefined variable \"%s\"\n",line,name);
}
void error4(char* name,int line)
{
    printf("Error type 4 at Line %d: Redefined function \"%s\"\n",line,name);
}
void error5(struct ast* ast1,struct ast* ast2,int line)
{
    if(strcmp(ast1->typname,ast2->typname)!=0||ast1->arraymark!=ast2->arraymark)
    {
        printf("%s    %s  aaa\n",ast1->typname,ast2->typname);
        printf("Error type 5 at Line %d: Type mismatched for assignment\n",line);
    }
}
void error6(int type,int line)
{
    if(type==0)
    {
        printf("Error type 6 at Line %d: The left-hand side of an assignment must be avariable \n",line);
    }
}
void error7(struct ast* ast1,struct ast* ast2,int line)
{
    if(strcmp(ast1->typname,ast2->typname)!=0||ast1->arraymark!=ast2->arraymark)
    {
        printf("Error type 7 at Line %d: Type mismatched for operands\n",line);
    }
}
void error8(char* name,char* name2,int line)
{
    if(strcmp(name,name2)!=0)
    {
        printf("Error type 8 at Line %d: Type mismatched for return\n",line);
    }
}
void error9(char* name,struct namelist* namelist,int line)
{
    if(getfunctype(name)==3)
    {
        if(checkargs(name,namelist)==0)
        {
            printf("Error type 9 at Line %d: Function is not applicable for arguments\n",line);
        }
    }
}
void error10(char* name,int line)
{
	if(getfunctype(name)!=2)
    {
        printf("Error type 10 at Line %d: \"%s\" is not an array\n",line,name);
    }
}
void error11(char* name,int line)
{
    if(getfunctype(name)!=3&&getfunctype(name)>=0)
    {
        printf("Error type 11 at Line %d: \"%s\" is not a function\n",line,name);
    }
}
void error12(char* typname,int line)
{
    if(strcmp(typname,"int")!=0)
    {
        printf("Error type 12 at Line %d: Type is not an integer\n",line);
    }
}
void error13(int line)
{
    printf("Error type 13 at Line %d: Illegal use of \".\"\n",line);
}
void error14(char* name2,int line)
{
    printf("Error type 14 at Line %d: Non-existent field \"%s\"\n",line,name2);
}
void error15(char* name,int line)
{
    if(strcmp(name,"no")==0)
    {
        printf("Error type 15 at Line %d: Redefined field\n",line);
    }
}
void error16(char* name,int line)
{
    printf("Error type 16 at Line %d: Redefined struct \"%s\"\n",line,name);
}
void error17(char* name,int line)
{
    if(getfunctype(name)!=1)
    {
        printf("Error type 17 at Line %d: Undefined structure \"%s\"\n",line,name);
    }
}
