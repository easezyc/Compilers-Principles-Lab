#include"centercode.h"
#include<stdio.h>
#include<string.h>
#include"symbol.h"
#include"symbol.c"
int labelnum=0;
int xnum=0;
void tracetree2(struct ast *t)
{
    if(strcmp(t->info.name,"FunDec")==0)
    {
        printf("FUNCTION %s:\n",t->lc->info.name);
        struct namelist* namelist=t->lc->rc->rc->namearg;
        if(namelist!=NULL)printf("PARAM ");
        while(namelist!=NULL)
        {
            printf("%s ",namelist->name);
            namelist=namelist->next;
        }
        if(t->lc->rc->rc->namearg!=NULL)printf("\n");
        if(t->llength!=0) tracetree2(t->lc);
        if(t->rlength!=0) tracetree2(t->rc);
    }
    else if(strcmp(t->info.name,"if")==0&&t->rlength==4)
    {
        int start=labelnum;
        labelnum++;
        int end=labelnum;
        labelnum++;
        traceexp(t->rc->rc,0);
        if(t->rc->rc->tfname==0)printf("IF _t%d GOTO label%d\n",t->rc->rc->xnum,start);
        else printf("IF %s GOTO label%d\n",t->rc->rc->tname,start);
        printf("GOTO label%d\n",end);
        printf("LABEL label%d :\n",start);
        if(t->rc->rc->rc->rc->llength!=0) tracetree2(t->rc->rc->rc->rc->lc);
        printf("LABEL label%d :\n",end);
    }
    else if(strcmp(t->info.name,"if")==0&&t->rlength==6)
    {
        int start=labelnum;
        labelnum++;
        int center=labelnum;
        labelnum++;
        int end=labelnum;
        labelnum++;
        traceexp(t->rc->rc,0);
        if(t->rc->rc->tfname==0)printf("IF _t%d GOTO label%d\n",t->rc->rc->xnum,start);
        else printf("IF %s GOTO label%d\n",t->rc->rc->tname,start);
        printf("GOTO label%d\n",center);
        printf("LABEL label%d :\n",start);
        if(t->rc->rc->rc->rc->llength!=0) tracetree2(t->rc->rc->rc->rc->lc);
        printf("GOTO label%d\n",end);
        printf("LABEL label%d :\n",center);
        if(t->rc->rc->rc->rc->rc->rc->llength!=0) tracetree2(t->rc->rc->rc->rc->rc->rc->lc);
        printf("LABEL label%d :\n",end);
    }
    else if(strcmp(t->info.name,"while")==0)
    {
        int start=labelnum;
        labelnum++;
        int center=labelnum;
        labelnum++;
        int end=labelnum;
        labelnum++;
        printf("LABEL label%d :\n",start);
        traceexp(t->rc->rc,0);
        if(t->rc->rc->tfname==0)printf("IF _t%d GOTO label%d\n",t->rc->rc->xnum,center);
        else printf("IF %s GOTO label%d\n",t->rc->rc->tname,center);
        printf("GOTO label%d\n",end);
        printf("LABEL label%d :\n",center);
        if(t->rc->rc->rc->rc->llength!=0) tracetree2(t->rc->rc->rc->rc->lc);
        printf("GOTO label%d\n",start);
        printf("LABEL label%d :\n",end);
    }
    else if(strcmp(t->info.name,"return")==0)
    {
        traceexp(t->rc,1);
        printf("RETURN ");
        if(t->rc->tfname==0)
        {
            printf("_t%d \n",t->rc->xnum);
        }
        else
        {
            printf("%s \n",t->rc->tname);
        }
    }
    else if(strcmp(t->info.name,"Exp")==0)
    {
        traceexp(t,1);
    }
    else if(strcmp(t->info.name,"VarDec")==0&&t->rlength==2&&strcmp(t->rc->rc->info.name,"Exp")==0)
    {
        traceexp(t->rc->rc,1);
        printf("%s = ",t->tname);
        if(t->rc->rc->tfname==0)
        {
            printf("_t%d \n",t->rc->rc->xnum);
        }
        else
        {
            printf("%s \n",t->rc->rc->tname);
        }
    }
    else
    {
        if(t->llength!=0) tracetree2(t->lc);
        if(t->rlength!=0) tracetree2(t->rc);
    }
}
void traceexp(struct ast *t,int mark)
{
    if(t->llength!=0) traceexp(t->lc,1);
    if(t->rlength!=0)
    {
        if(mark==0) {}
        else traceexp(t->rc,1);
    }
    if(t->lc!=NULL&&t->lc->type==INT)
    {
        printf("_t%d := #%d\n",xnum,t->lc->info.in);
        t->xnum=xnum;
        t->tfname=0;
        xnum++;
    }
    else if(t->lc!=NULL&&t->lc->type==ID)
    {
        t->tfname=1;
        strcpy(t->tname,t->lc->info.name);
    }
    if(t->llength==3&&t->lc->rc->type>=263&&t->lc->rc->type<=272)
    {
        if(t->lc->rc->type!=ASSIGNOP)
        {
            printf("_t%d := ",xnum);
            t->xnum=xnum;
            t->tfname=0;
            xnum++;
        }
		else printf("%s ",t->tname);
        if(t->lc->tfname==0)
        {
            printf("_t%d ",t->lc->xnum);
        }
        else
        {
            printf("%s ",t->lc->tname);
        }
        printf("%s ",t->lc->rc->info.name);
        if(t->lc->rc->rc->tfname==0)
        {
            printf("_t%d ",t->lc->rc->rc->xnum);
        }
        else
        {
            printf("%s ",t->lc->rc->rc->tname);
        }
        printf("\n");
    }
    else if(t->llength==3&&strcmp(t->lc->rc->info.name,"Exp")==0)
    {
        if(t->lc->tfname==0)
        {
            t->xnum=t->lc->rc->xnum;
            t->tfname=0;
        }
        else
        {
            strcpy(t->tname,t->lc->rc->tname);
            t->tfname=1;
        }
    }
    else if(strcmp(t->info.name,"Exp")==0&&t->llength>=2&&t->lc->type==ID&&t->lc->rc->type==LP)
    {
        struct namelist* namelist=t->lc->rc->rc->namearg;
        if(namelist!=NULL)printf("ARG ");
        tracearg(t->lc->rc->rc);
        if(t->lc->rc->rc->namearg!=NULL)printf("\n");
        printf("_t%d := ",xnum);
        t->xnum=xnum;
        t->tfname=0;
        xnum++;
        printf("CALL %s\n",t->lc->info.name);
    }
}
void tracearg(struct ast *t)
{
    if(strcmp(t->info.name,"Exp")==0)
    {
        if(t->tfname==0)
        {
            printf("_t%d ",t->xnum);
        }
        else
        {
            printf("%s ",t->tname);
        }
    }
    if(t->llength!=0)tracearg(t->lc);
    if(t->rlength!=0)tracearg(t->rc);
}
