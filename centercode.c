#include"centercode.h"
#include<stdio.h>
#include<string.h>
#include"symbol.h"
#include"symbol.c"
#include <stdlib.h>
int labelnum=0;
int xnum=0;
void tracetree2(struct ast *t)
{
    if(strcmp(t->info.name,"FunDec")==0)
    {
        printf("FUNCTION %s:\n",t->lc->info.name);
        if(strcmp(t->lc->info.name,"main")==0)fprintf(fp,"%s proc far\n        push ds\n        xor  ax, ax\n        push ax\n    mov ax, data\n    mov ds, ax\n",t->lc->info.name);
        else fprintf(fp,"%s proc near\n",t->lc->info.name);
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
        fprintf(fp,"%s endp\n",t->lc->info.name);
    }
    else if(strcmp(t->info.name,"if")==0&&t->rlength==4)
    {
        int start=labelnum;
        labelnum++;
        int end=labelnum;
        labelnum++;
        traceexp(t->rc->rc,0);
        if(t->rc->rc->tfname==0)
        {
            printf("IF _t%d GOTO label%d\n",t->rc->rc->xnum,start);
            fprintf(fp,"    MOV AL,[%d + data1]\n",t->rc->rc->xnum);
            fprintf(fp,"    CMP AL,0\n  JA label%d\n",start);
        }
        else
        {
            printf("IF %s GOTO label%d\n",t->rc->rc->tname,start);
            fprintf(fp,"    MOV AL,[%d + data2]\n",getloc(t->rc->rc->tname));
            fprintf(fp,"    CMP AL,0\n JA label%d\n",start);
        }
        printf("GOTO label%d\n",end);
        fprintf(fp,"    JMP label%d\n",end);
        printf("LABEL label%d :\n",start);
        fprintf(fp,"label%d:\n",start);
        if(t->rc->rc->rc->rc->llength!=0) tracetree2(t->rc->rc->rc->rc->lc);
        printf("LABEL label%d :\n",end);
        fprintf(fp,"label%d:\n",end);
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
        if(t->rc->rc->tfname==0)
        {
            printf("IF _t%d GOTO label%d\n",t->rc->rc->xnum,start);
            fprintf(fp,"    MOV AL,[%d + data1]\n",t->rc->rc->xnum);
            fprintf(fp,"    CMP AL,0\n    JA label%d\n",start);
        }
        else
        {
            printf("IF %s GOTO label%d\n",t->rc->rc->tname,start);
            fprintf(fp,"    MOV AL,[%d + data2]\n",getloc(t->rc->rc->tname));
            fprintf(fp,"    CMP AL,0\n  JA label%d\n",start);
        }
        printf("GOTO label%d\n",center);
        fprintf(fp,"    JMP label%d\n",center);
        printf("LABEL label%d :\n",start);
        fprintf(fp,"label%d:\n",start);
        if(t->rc->rc->rc->rc->llength!=0) tracetree2(t->rc->rc->rc->rc->lc);
        printf("GOTO label%d\n",end);
        fprintf(fp,"    JMP label%d\n",end);
        printf("LABEL label%d :\n",center);
        fprintf(fp,"label%d:\n",center);
        if(t->rc->rc->rc->rc->rc->rc->llength!=0) tracetree2(t->rc->rc->rc->rc->rc->rc->lc);
        printf("LABEL label%d :\n",end);
        fprintf(fp,"label%d:\n",end);
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
        fprintf(fp,"label%d:\n",start);
        traceexp(t->rc->rc,0);
        if(t->rc->rc->tfname==0)
        {
            printf("IF _t%d GOTO label%d\n",t->rc->rc->xnum,center);
            fprintf(fp,"    MOV AL,[%d + data1]\n",t->rc->rc->xnum);
            fprintf(fp,"    CMP AL,0\n    JA label%d\n",center);
        }
        else
        {
            printf("IF %s GOTO label%d\n",t->rc->rc->tname,center);
            fprintf(fp,"    MOV AL,[%d + data2]\n",getloc(t->rc->rc->tname));
            fprintf(fp,"    CMP AL,0\n  JA label%d\n",center);
        }
        printf("GOTO label%d\n",end);
        fprintf(fp,"    JMP label%d\n",end);
        printf("LABEL label%d :\n",center);
        fprintf(fp,"label%d:\n",center);
        if(t->rc->rc->rc->rc->llength!=0) tracetree2(t->rc->rc->rc->rc->lc);
        printf("GOTO label%d\n",start);
        fprintf(fp,"    JMP label%d\n",start);
        printf("LABEL label%d :\n",end);
        fprintf(fp,"label%d:\n",end);
    }
    else if(strcmp(t->info.name,"return")==0)
    {
        traceexp(t->rc,1);
        printf("RETURN ");
        if(t->rc->tfname==0)
        {
            printf("_t%d \n",t->rc->xnum);
            fprintf(fp,"    MOV AH,[%d + data1]\n",t->rc->xnum);
            fprintf(fp,"    ret\n");
        }
        else
        {
            printf("%s \n",t->rc->tname);
            fprintf(fp,"    MOV AH,[%d + data2]\n",getloc(t->rc->tname));
            fprintf(fp,"    ret\n");
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
            fprintf(fp,"    MOV Al,[%d + data1]\n",t->rc->rc->xnum);
            fprintf(fp,"    MOV BX,%d + offset data2\n",getloc(t->tname));
            fprintf(fp,"    MOV [BX],AL\n");
        }
        else
        {
            printf("%s \n",t->rc->rc->tname);
            fprintf(fp,"    MOV Al,[%d + data2]\n",getloc(t->rc->rc->tname));
            fprintf(fp,"    MOV BX,%d + offset data2\n",getloc(t->tname));
            fprintf(fp,"    MOV [BX],AL\n");
        }
    }
    else
    {
        if(t->llength!=0) tracetree2(t->lc);
        if(t->rlength!=0) tracetree2(t->rc);
    }
}
void tracearg(struct ast *t,struct arg *args)
{
    if(strcmp(t->info.name,"Exp")==0&&args!=NULL)
    {
        if(t->tfname==0)
        {
            printf("_t%d ",t->xnum);
            fprintf(fp,"    MOV BX,%d +offset data2\n",getloc(args->name));
            fprintf(fp,"    MOV AX,[BX]\n");
            fprintf(fp,"    PUSH AX\n");
            fprintf(fp,"    MOV BX,%d +offset data1\n",t->xnum);
            fprintf(fp,"    MOV AL,[BX]\n");
            fprintf(fp,"    MOV BX,%d +offset data2\n",getloc(args->name));
            fprintf(fp,"    MOV [BX],AL\n");
            args=args->next;
        }
        else
        {
            printf("%s ",t->tname);
            fprintf(fp,"    MOV BX,%d +offset data2\n",getloc(args->name));
            fprintf(fp,"    MOV AX,[BX]\n");
            fprintf(fp,"    PUSH AX\n");
            fprintf(fp,"    MOV BX,%d +offset data2\n",getloc(t->tname));
            fprintf(fp,"    MOV AL,[BX]\n");
            fprintf(fp,"    MOV BX,%d +offset data2\n",getloc(args->name));
            fprintf(fp,"    MOV [BX],AL\n");
            args=args->next;
        }
    }
    if(t->llength!=0)tracearg(t->lc,args);
    if(t->rlength!=0)tracearg(t->rc,args);
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
        fprintf(fp,"    MOV AL,%d\n",t->lc->info.in);
        fprintf(fp,"    MOV BX,%d + offset data1\n",xnum);
        fprintf(fp,"    MOV [BX],AL\n",xnum);
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
            if(t->lc->tfname==0)
            {
                printf("_t%d ",t->lc->xnum);
                fprintf(fp,"    MOV AL,[%d + data1]\n",t->lc->xnum);
            }
            else
            {
                printf("%s ",t->lc->tname);
                fprintf(fp,"    MOV AL,[%d + data2]\n",getloc(t->lc->tname));
            }
            printf("%s ",t->lc->rc->info.name);
            int loc;
            if(t->lc->rc->rc->tfname==0)
            {
                printf("_t%d ",t->lc->rc->rc->xnum);
                loc=t->lc->rc->rc->xnum+1000;
            }
            else
            {
                printf("%s ",t->lc->rc->rc->tname);
                loc=getloc(t->lc->rc->rc->tname)+1100;
            }
            if(strcmp(t->lc->rc->info.name,"+")==0)
            {
                if(loc>=1100)fprintf(fp,"    ADD AL,[%d + data2]\n",loc-1100);
                else fprintf(fp,"    ADD AL,[%d + data1]\n",loc-1000);
            }
            else if(strcmp(t->lc->rc->info.name,"-")==0)
            {
                if(loc>=1100)fprintf(fp,"    SUB Al,[%d + data2]\n",loc-1100);
                else fprintf(fp,"    SUB AL,[%d + data1]\n",loc-1000);
            }
            else if(strcmp(t->lc->rc->info.name,"*")==0)
            {
                if(loc>=1100)
                {
                    fprintf(fp,"    MOV BL,[%d + data2]\n",loc-1100);
                    fprintf(fp,"    MUL BL\n");
                }
                else
                {
                    fprintf(fp,"    MOV BL,[%d + data1]\n",loc-1000);
                    fprintf(fp,"    MUL BL\n");
                }
            }
            else if(strcmp(t->lc->rc->info.name,"/")==0)
            {
                if(loc>=1100)
                {
                    fprintf(fp,"    MOV BL,[%d + data2]\n",loc-1100);
                    fprintf(fp,"    MOV AH,0\n");
                    fprintf(fp,"    DIV BL\n");
                }
                else
                {
                    fprintf(fp,"    MOV BL,[%d + data1]\n",loc-1000);
                    fprintf(fp,"    DIV BL\n");
                }
            }
            else if(strcmp(t->lc->rc->info.name,"&&")==0)
            {
                if(loc>=1100)fprintf(fp,"    AND Al,[%d + data2]\n",loc-1100);
                else fprintf(fp,"    AND AL,[%d + data1]\n",loc-1000);
            }
            else if(strcmp(t->lc->rc->info.name,"||")==0)
            {
                if(loc>=1100)fprintf(fp,"    OR Al,[%d + data2]\n",loc-1100);
                else fprintf(fp,"    OR AL,[%d + data1]\n",loc-1000);
            }
            else if(strcmp(t->lc->rc->info.name,"==")==0)
            {
                if(loc>=1100)
                {
                    fprintf(fp,"    CMP AL,[%d + data2]\n",loc-1100);
                }
                else
                {
                    fprintf(fp,"    CMP AL,[%d + data1]\n",loc-1000);
                }
                int start,center,end;
                start=asmnum;
                asmnum++;
                center=asmnum;
                asmnum++;
                end=asmnum;
                asmnum++;
                fprintf(fp,"    JNE t%d\n",center);
                fprintf(fp,"t%d:\n",start);
                fprintf(fp,"    MOV AL,1\n");
                fprintf(fp,"    JMP t%d\n",end);
                fprintf(fp,"t%d:\n",center);
                fprintf(fp,"    MOV AL,0\n");
                fprintf(fp,"t%d:\n",end);
                fprintf(fp,"    MOV [%d + data1],AL\n",t->xnum);
            }
            else if(strcmp(t->lc->rc->info.name,">=")==0)
            {
                if(loc>=1100)
                {
                    fprintf(fp,"    CMP AL,[%d + data2]\n",loc-1100);
                }
                else
                {
                    fprintf(fp,"    CMP AL,[%d + data1]\n",loc-1000);
                }
                int start,center,end;
                start=asmnum;
                asmnum++;
                center=asmnum;
                asmnum++;
                end=asmnum;
                asmnum++;
                fprintf(fp,"    JNGE t%d\n",center);
                fprintf(fp,"t%d:\n",start);
                fprintf(fp,"    MOV AL,1\n");
                fprintf(fp,"    JMP t%d\n",end);
                fprintf(fp,"t%d:\n",center);
                fprintf(fp,"    MOV AL,0\n");
                fprintf(fp,"t%d:\n",end);
                fprintf(fp,"    MOV [%d + data1],AL\n",t->xnum);
            }
            else if(strcmp(t->lc->rc->info.name,"<=")==0)
            {
                if(loc>=1100)
                {
                    fprintf(fp,"    CMP AL,[%d + data2]\n",loc-1100);
                }
                else
                {
                    fprintf(fp,"    CMP AL,[%d + data1]\n",loc-1000);
                }
                int start,center,end;
                start=asmnum;
                asmnum++;
                center=asmnum;
                asmnum++;
                end=asmnum;
                asmnum++;
                fprintf(fp,"    JG t%d\n",center);
                fprintf(fp,"t%d:\n",start);
                fprintf(fp,"    MOV AL,1\n");
                fprintf(fp,"    JMP t%d\n",end);
                fprintf(fp,"t%d:\n",center);
                fprintf(fp,"    MOV AL,0\n");
                fprintf(fp,"t%d:\n",end);
                fprintf(fp,"    MOV [%d + data1],AL\n",t->xnum);
            }
            else if(strcmp(t->lc->rc->info.name,">")==0)
            {
                if(loc>=1100)
                {
                    fprintf(fp,"    CMP AL,[%d + data2]\n",loc-1100);
                }
                else
                {
                    fprintf(fp,"    CMP AL,[%d + data1]\n",loc-1000);
                }
                int start,center,end;
                start=asmnum;
                asmnum++;
                center=asmnum;
                asmnum++;
                end=asmnum;
                asmnum++;
                fprintf(fp,"    JNG t%d\n",center);
                fprintf(fp,"t%d:\n",start);
                fprintf(fp,"    MOV AL,1\n");
                fprintf(fp,"    JMP t%d\n",end);
                fprintf(fp,"t%d:\n",center);
                fprintf(fp,"    MOV AL,0\n");
                fprintf(fp,"t%d:\n",end);
                fprintf(fp,"    MOV [%d + data1],AL\n",t->xnum);
            }
            else if(strcmp(t->lc->rc->info.name,"<")==0)
            {
                if(loc>=1100)
                {
                    fprintf(fp,"    CMP AL,[%d + data2]\n",loc-1100);
                }
                else
                {
                    fprintf(fp,"    CMP AL,[%d + data1]\n",loc-1000);
                }
                int start,center,end;
                start=asmnum;
                asmnum++;
                center=asmnum;
                asmnum++;
                end=asmnum;
                asmnum++;
                fprintf(fp,"    JGE t%d\n",center);
                fprintf(fp,"t%d:\n",start);
                fprintf(fp,"    MOV AL,1\n");
                fprintf(fp,"    JMP t%d\n",end);
                fprintf(fp,"t%d:\n",center);
                fprintf(fp,"    MOV AL,0\n");
                fprintf(fp,"t%d:\n",end);
                fprintf(fp,"    MOV [%d + data1],AL\n",t->xnum);
            }
            else if(strcmp(t->lc->rc->info.name,"!=")==0)
            {
                if(loc>=1100)
                {
                    fprintf(fp,"    CMP AL,[%d + data2]\n",loc-1100);
                }
                else
                {
                    fprintf(fp,"    CMP AL,[%d + data1]\n",loc-1000);
                }
                int start,center,end;
                start=asmnum;
                asmnum++;
                center=asmnum;
                asmnum++;
                end=asmnum;
                asmnum++;
                fprintf(fp,"    JE t%d\n",center);
                fprintf(fp,"t%d:\n",start);
                fprintf(fp,"    MOV AL,1\n");
                fprintf(fp,"    JMP t%d\n",end);
                fprintf(fp,"t%d:\n",center);
                fprintf(fp,"    MOV AL,0\n");
                fprintf(fp,"t%d:\n",end);
                fprintf(fp,"    MOV [%d + data1],AL\n",t->xnum);
            }
            if(t->tfname==0)
            {
                fprintf(fp,"    MOV BX,%d + offset data1\n",t->xnum);
                fprintf(fp,"    MOV [BX],AL\n");
            }
            else
            {
                fprintf(fp,"    MOV BX,%d + offset data2\n",getloc(t->tname));
                fprintf(fp,"    MOV [BX],AL\n");
            }
        }

        if(t->lc->rc->type==ASSIGNOP)
        {
            int loc;
            if(t->lc->rc->rc->tfname==0)
            {
                loc=t->lc->rc->rc->xnum+1000;
            }
            else
            {
                loc=getloc(t->lc->rc->rc->tname)+1100;
            }
            if(loc>=1100)fprintf(fp,"    MOV AL,[%d + data2]\n",loc-1100);
            else fprintf(fp,"    MOV AL,[%d + data1]\n",loc-1000);
            if(t->lc->tfname==0)
            {
                loc=t->lc->xnum+1000;
            }
            else
            {
                loc=getloc(t->lc->tname)+1100;
            }
            if(loc>=1100)
            {
                fprintf(fp,"    MOV BX,%d + offset data2\n",loc-1100);
                fprintf(fp,"    MOV [BX],AL\n");
            }
            else
            {
                fprintf(fp,"    MOV BX,%d + offset data1\n",loc-1000);
                fprintf(fp,"    MOV [BX],AL\n");
            }
        }
        if(t->lc->rc->type==ASSIGNOP)
        {
            if(t->lc->tfname==0)
            {
                printf("_t%d ",t->lc->xnum);
            }
            else
            {
                printf("%s ",t->lc->tname);
            }
            printf("= ");
            if(t->lc->rc->rc->tfname==0)
            {
                printf("_t%d ",t->lc->rc->rc->xnum);
            }
            else
            {
                printf("%s ",t->lc->rc->rc->tname);
            }
        }
        printf("\n");
    }
    else if(t->llength==2&&t->lc->type>=NOT)//ÅÐ¶Ï£¡
    {
        printf("_t%d := ",xnum);
        t->xnum=xnum;
        t->tfname=0;
        xnum++;
        if(t->lc->rc->tfname==0)
        {
            printf("!_t%d \n",t->lc->rc->xnum);
            fprintf(fp,"    MOV AL,[%d + data1]\n",t->lc->rc->xnum);
        }
        else
        {
            printf("!%s \n",t->lc->rc->tname);
            fprintf(fp,"    MOV AL,[%d + data2]\n",getloc(t->lc->rc->tname));
        }
        int start,center,end;
        fprintf(fp,"    CMP AL,0\n");
        start=asmnum;
        asmnum++;
        center=asmnum;
        asmnum++;
        end=asmnum;
        asmnum++;
        fprintf(fp,"    JA t%d\n",center);
        fprintf(fp,"t%d:\n",start);
        fprintf(fp,"    MOV AL,1\n");
        fprintf(fp,"    JMP t%d\n",end);
        fprintf(fp,"t%d:\n",center);
        fprintf(fp,"    MOV AL,0\n");
        fprintf(fp,"t%d:\n",end);
        fprintf(fp,"    MOV [%d + data1],AL\n",t->xnum);

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
        struct arg* arg=getfuncargs(t->lc->info.name);
        struct arg* tt=getfuncargs(t->lc->info.name);
        struct namelist* namelist=t->lc->rc->rc->namearg;
        if(namelist!=NULL)printf("ARG ");
        tracearg(t->lc->rc->rc,arg);
        if(t->lc->rc->rc->namearg!=NULL)printf("\n");
        printf("_t%d := ",xnum);
        t->xnum=xnum;
        t->tfname=0;
        xnum++;
        printf("CALL %s\n",t->lc->info.name);
        fprintf(fp,"    CALL %s\n",t->lc->info.name);
        while(tt!=NULL)
        {
            fprintf(fp,"    POP CX\n");
            fprintf(fp,"    MOV data2[%d],CL\n",getloc(tt->name));
            tt=tt->next;
        }
        fprintf(fp,"    MOV BX,%d +offset data1\n",t->xnum);
        fprintf(fp,"    MOV [BX],AH\n");
    }
}

void openfile()
{
    fp = fopen("./out.asm","w");
    asmnum=0;
    char* p="stack   segment para stack 'stack'\ndb      1024 dup (?)\nstack   ends\ndata    segment para 'data'\n      data1     db 100 dup(?)\n    data2     db 50 dup(?)\ndata           ends\n      code    segment para 'code'\nassume cs:code, ds:data, es:data, ss:stack\n     call FAR PTR main\n";
    fprintf(fp,"%s",p);
    char* insert="dis proc near\n        push cx\n        mov  bl, data2[0]\n        mov  dl, bl\n        mov  cl, 4\n        rol  dl, cl\n        and  dl, 0fh\n        call disp4\n        mov  dl, bl\n        and  dl, 0fh\n        call disp4\n        pop  cx\n        ret\ndis endp\ndisp4   proc near\n        add  dl, 30h\n        cmp  dl, 3ah\n        jb   ddd\n        add  dl, 27h\nddd:    mov  ah, 02h\n        int  21h\n        ret\n    disp4   endp\n";
    fprintf(fp,"%s",insert);
    symbollisttrace2();
    /*int i=0;
    for(i=0;i<num;i++)
    {
        printf("%s\n",common[i]);
    }*/
}
void closefile()
{
    char* p="code    ends\nend main\n";
    fprintf(fp,"%s",p);
    fclose(fp);
}
void symbollisttrace2()
{
    struct symbol* tsym=symbollist;
    tsym=tsym->next;
    int n=0;
    while(tsym!=NULL)
    {
        if(tsym->functype==0)
        {
            common[n]=(char*)malloc(sizeof(char));
            strcpy(common[n],tsym->name);
            n++;
        }
        tsym=tsym->next;
    }
    num=n;
}
int getloc(char* name)
{
    int i;
    for(i=0; i<num; i++)
    {
        if(strcmp(common[i],name)==0)break;
    }
    return i;
}
