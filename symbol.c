#include<stdio.h>
#include<string.h>
#include"symbol.h"
#include"error.c"
void initsymbollist()
{
    symbollist=(struct symbol*)malloc(sizeof(struct symbol));
    symbollist->next=NULL;
    symbollist->name=(char*)malloc(sizeof(char));
    symbollist->typname=(char*)malloc(sizeof(char));
}
void insertsym1(char* name,char* typname,int arraytype)
{
    struct symbol* sym=(struct symbol*)malloc(sizeof(struct symbol));
    sym->name=(char*)malloc(sizeof(char));
    strcpy(sym->name,name);
    sym->typname=(char*)malloc(sizeof(char));
    strcpy(sym->typname,typname);
    if(arraytype==1)sym->functype=2;
	else sym->functype=0;
    sym->next=NULL;
    struct symbol* tsym=symbollist;
    while(tsym->next!=NULL)
    {
        tsym=tsym->next;
    }
    tsym->next=sym;
}
void insertsym2(char* name,char* typname,int functype,struct arg* arg)
{
    struct symbol* sym=(struct symbol*)malloc(sizeof(struct symbol));
    sym->name=(char*)malloc(sizeof(char));
    strcpy(sym->name,name);
    sym->typname=(char*)malloc(sizeof(char));
    strcpy(sym->typname,typname);
    sym->functype=functype;
    sym->arg=arg;
    sym->next=NULL;
    struct symbol* tsym=symbollist;
    while(tsym->next!=NULL)
    {
        tsym=tsym->next;
    }
    tsym->next=sym;
}
char* gettype(char* name)
{
    int mark=0;
    char* typname;
	typname=(char*)malloc(sizeof(char));
    struct symbol* sym=symbollist;
    sym=sym->next;
    while(sym!=NULL)
    {
        if(strcmp(name,sym->name)==0)
        {
            mark=1;
            strcpy(typname,sym->typname);
        }
        if(mark==1)break;
        sym=sym->next;
    }
    return typname;
}
int getfunctype(char* name)
{
    int mark=0;
    int type=-1;
    struct symbol* sym=symbollist;
    sym=sym->next;
    while(sym!=NULL)
    {
        if(strcmp(name,sym->name)==0)
        {
            mark=1;
            type=sym->functype;
        }
        if(mark==1)break;
        sym=sym->next;
    }
    return type;
}
int lookup(char* name)
{
    int mark=0;
    struct symbol* sym=symbollist;
    sym=sym->next;
    while(sym!=NULL)
    {
        if(strcmp(name,sym->name)==0)
        {
            mark=1;
        }
        if(mark==1)break;
        sym=sym->next;
    }
    return mark;
}
char* judgestruct(char* name,char* name2,int line)
{
    int mark=0,mark2=0;
    struct symbol* sym=symbollist;
    sym=sym->next;
    char* result="INT";
    while(sym!=NULL)
    {
        if(strcmp(name,sym->name)==0&&sym->functype==1)
        {
            mark=1;
            struct arg* arg=sym->arg;
            while(arg!=NULL)
            {
                if(strcmp(arg->name,name2)==0){
                    mark2=1;
                    strcpy(result,arg->typname);
                }
                arg=arg->next;
                if(mark2==1)break;
            }
        }
        if(mark==1)break;
        sym=sym->next;
    }
    if(mark==0)error13(line);
    else if(mark2==0)error14(name2,line);
    return result;
}
void symbollisttrace()
{
    struct symbol* tsym=symbollist;
    tsym=tsym->next;
    while(tsym!=NULL)
    {
        if(tsym->functype==3){
            printf("func:  name%s  type:%s  functype:%d\n",tsym->name,tsym->typname,tsym->functype);
            struct arg* arg=tsym->arg;
            while(arg!=NULL)
            {
                printf("name:%s  type:%s\n",arg->name,arg->typname);
                arg=arg->next;
            }
			printf("\n");
        }
		else if(tsym->functype==1){
             printf("struct:  name%s  type:%s  functype:%d\n",tsym->name,tsym->typname,tsym->functype);
             struct arg* arg=tsym->arg;
             while(arg!=NULL)
             {
                 printf("name:%s  type:%s\n",arg->name,arg->typname);
                 arg=arg->next;
             }
             printf("\n");
         }
        else printf("name%s  type:%s  functype:%d\n",tsym->name,tsym->typname,tsym->functype);
        tsym=tsym->next;
    }
}
void addsymbol1(char* name,struct namelist* namelist,int line)
{
    struct namelist* t=namelist;
    while(t!=NULL)
    {
        if(lookup(t->name)==0)
        {
            insertsym1(t->name,name,t->arraymark);
        }
        else error3(t->name,line);
        t=t->next;
    }
}
void addfunc(char* name,struct namelist* namelist,int mark,int line)
{
    if(lookup(name)==0)
    {
        char* tname="int";
        insertsym2(name,tname,mark,getarg(namelist));
    }
    else error4(name,line);
}
void addstruct(char* name,struct namelist* namelist,int mark,int line)
{
    if(lookup(name)==0)
    {
        char* tname="int";
        insertsym2(name,tname,mark,getarg(namelist));
    }
    else error16(name,line);
}
struct arg* getarg(struct namelist* namelist)
{
    struct arg* arg=(struct arg*)malloc(sizeof(struct arg));
    struct arg* ttt=arg;
    struct namelist* t=namelist;
    while(t!=NULL)
    {
        struct arg* tt=(struct arg*)malloc(sizeof(struct arg));
        tt->name=(char*)malloc(sizeof(char));
        strcpy(tt->name,t->name);
        tt->typname=(char*)malloc(sizeof(char));
        strcpy(tt->typname,gettype(t->name));
        tt->functype=getfunctype(t->name);
        t=t->next;
        ttt->next=tt;
		ttt=ttt->next;
    }
    return arg->next;
}
void modfunctype(char* name,char* typname)
{
    int mark=0;
    struct symbol* sym=symbollist;
    sym=sym->next;
    while(sym!=NULL)
    {
        if(strcmp(name,sym->name)==0)
        {
            mark=1;
            strcpy(sym->typname,typname);
        }
        if(mark==1)break;
        sym=sym->next;
    }
}
int checkargs(char* name,struct namelist* namelist)
{
    int mark=0;
    int result=1;
    struct symbol* sym=symbollist;
    sym=sym->next;
    while(sym!=NULL)
    {
        if(strcmp(name,sym->name)==0)
        {
            mark=1;
            struct arg* arg=sym->arg;
            struct namelist* t=namelist;
            while(arg!=NULL&&t!=NULL)
            {
                if(strcmp(arg->typname,t->name)!=0)result=0;
                if(result==0)break;
                arg=arg->next;
                t=t->next;
            }
            if(t!=NULL||arg!=NULL)result=0;
        }
        if(mark==1)break;
        sym=sym->next;
    }
    return result;
}
