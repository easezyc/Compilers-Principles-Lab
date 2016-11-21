%{
//	#include"head.h"
	#include"lex.yy.c"	
	#include<string.h>
	#include"symbol.h"
	#include"symbol.c"
	extern yylineno;
	int yylex();
	void yyerror(char *);
	char name[28][10]={"INT","FLOAT","ID","SEMI","COMMA","ASSIGNOP","RELOP","PLUS","MINUS","STAR","DIV","AND","OR","DOT","NOT","TYPE","LP","RP","LB","RB","LC","RC","STRUCT","RETURN","IF","ELSE","WHILE"};
%}
%union{
	struct ast *a;	
}

%token <a>  INT FLOAT ID SEMI COMMA ASSIGNOP RELOP PLUS MINUS STAR DIV AND OR DOT NOT TYPE LP RP LB RB LC RC STRUCT RETURN IF ELSE WHILE

%type <a> Program ExtDefList ExtDef ExtDecList Specifier StructSpecifier OptTag Tag VarDec FunDec VarList ParamDec CompSt StmtList Stmt DefList Def DecList
%type <a> Dec Exp Args

%nonassoc LOWER_THAN_ELSE
%nonassoc ELSE
%right ASSIGNOP
%left OR
%left AND
%left RELOP
%left PLUS MINUS
%left DIV STAR
%right NOT UMINUS
%left DOT LB RB LP RP
%%
Program:	ExtDefList {$$ = newast1(maketext("Program"), $1);
//	tracetree($$, 0);
	freetree($$);
	symbollisttrace();
};
ExtDefList:	ExtDef ExtDefList{
	$$ = newast2(maketext("ExtDefList"), $1,$2);
} 
	| {$$ = newast(maketext("null"));}
	;
ExtDef:		Specifier ExtDecList SEMI {$$ = newast3(maketext("ExtDef"), $1,$2,$3);addsymbol1($1->name,$2->namearg);}
	|Specifier SEMI {$$ = newast2(maketext("ExtDef"), $1,$2);}
	|Specifier FunDec CompSt {$$ = newast3(maketext("ExtDef"), $1,$2,$3);modfunctype($2->name,$1->name);}
	|error SEMI {}	
;
ExtDecList:	VarDec {$$ = newast1(maketext("ExtDecList"), $1);$$->namearg=addnamelist($$,$1->name);}
	|VarDec COMMA ExtDecList {$$ = newast3(maketext("ExtDecList"), $1,$2,$3);$$->namearg=addnamelist($3,$1->name);}
	;

Specifier:	TYPE {$$ = newast1(maketext("Specifier"), $1);strcpy($$->name,$1->info.name);}
	|StructSpecifier {$$ = newast1(maketext("Specifier"), $1);strcpy($$->name,$1->name);}
	;
StructSpecifier:	STRUCT OptTag LC DefList RC {$$ = newast5(maketext("StructSpecifier"), $1,$2,$3,$4,$5);strcpy($$->name,$2->name);}
	|STRUCT Tag {$$ = newast2(maketext("StructSpecifier"), $1,$2);strcpy($$->name,$2->name);}
	;
OptTag:		ID {$$ = newast1(maketext("OptTag"), $1);strcpy($$->name,$1->info.name);}
	| {$$ = newast(maketext("null"));}
	;
Tag:	ID {$$ = newast1(maketext("Tag"), $1);strcpy($$->name,$1->info.name);}

VarDec:		ID {$$ = newast1(maketext("VarDec"), $1);strcpy($$->name,$1->info.name);}
	|VarDec LB INT RB {$$ = newast4(maketext("VarDec"), $1,$2,$3,$4);strcpy($$->name,$1->name);};//    assssssssaaaaaaaaaaaaaaaaaaaa
FunDec:		ID LP VarList RP {$$ = newast4(maketext("FunDec"), $1,$2,$3,$4);addfunc($1->info.name,$3->namearg);strcpy($$->name,$1->info.name);}
	|ID LP RP {$$ = newast3(maketext("FunDec"), $1,$2,$3);addfunc($1->info.name,NULL);strcpy($$->name,$1->info.name);}
VarList:	ParamDec COMMA VarList{$$ = newast3(maketext("VarList"), $1,$2,$3);$$->namearg=addnamelist($3,$1->name);}
	|ParamDec{$$ = newast1(maketext("VarList"), $1);$$->namearg=addnamelist($$,$1->name);}
ParamDec:	Specifier VarDec{$$ = newast2(maketext("ParamDec"), $1,$2);strcpy($$->name,$2->name);$$->namearg=addnamelist($$,$2->name);addsymbol1($1->name,$$->namearg);}

CompSt:		LC DefList StmtList RC{$$ = newast4(maketext("CompSt"), $1,$2,$3,$4);};
StmtList:	Stmt StmtList{$$ = newast2(maketext("StmtList"), $1,$2);}
	| {$$ = newast(maketext("null"));}
	;
Stmt:		Exp SEMI{$$ = newast2(maketext("Stmt"), $1,$2);}
	|CompSt{$$ = newast1(maketext("Program"), $1);}
	|RETURN Exp SEMI{$$ = newast3(maketext("Stmt"), $1,$2,$3);}
	|IF LP Exp RP Stmt %prec LOWER_THAN_ELSE{$$ = newast5(maketext("Stmt"), $1,$2,$3,$4,$5);}
	|IF LP Exp RP Stmt ELSE Stmt{$$ = newast7(maketext("Stmt"), $1,$2,$3,$4,$5,$6,$7);}
	|WHILE LP Exp RP Stmt {$$ = newast5(maketext("Stmt"), $1,$2,$3,$4,$5);}
	;
DefList:	Def DefList {$$ = newast2(maketext("DefList"), $1,$2);}
	| {$$ = newast(maketext("null"));;}
	;
Def:	Specifier DecList SEMI {$$ = newast3(maketext("Def"), $1,$2,$3);addsymbol1($1->name,$2->namearg);}
;
DecList:	Dec {$$ = newast1(maketext("DecList"), $1);$$->namearg=addnamelist($$,$1->name);}
	|Dec COMMA DecList {$$ = newast3(maketext("DecList"), $1,$2,$3);$$->namearg=addnamelist($3,$1->name);}
	;
Dec:	VarDec ASSIGNOP Exp {$$ = newast3(maketext("Dec"), $1,$2,$3);strcpy($$->name,$1->name);}
	|VarDec {$$ = newast1(maketext("Dec"), $1);strcpy($$->name,$1->name);}
	;

Exp:	Exp ASSIGNOP Exp {$$ = newast3(maketext("Exp"), $1,$2,$3);}
	|Exp AND Exp {$$ = newast3(maketext("Exp"), $1,$2,$3);}
	|Exp OR Exp {$$ = newast3(maketext("Exp"), $1,$2,$3);}
	|Exp RELOP Exp {$$ = newast3(maketext("Exp"), $1,$2,$3);}
	|Exp PLUS Exp {$$ = newast3(maketext("Exp"), $1,$2,$3);}
	|Exp MINUS Exp {$$ = newast3(maketext("Exp"), $1,$2,$3);}
	|Exp STAR Exp {$$ = newast3(maketext("Exp"), $1,$2,$3);}
	|Exp DIV Exp {$$ = newast3(maketext("Exp"), $1,$2,$3);}
	|LP Exp RP {$$ = newast3(maketext("Exp"), $1,$2,$3);}
	|MINUS Exp {$$ = newast2(maketext("Exp"), $1,$2);}
	|NOT Exp {$$ = newast2(maketext("Exp"), $1,$2);}
	|ID LP Args RP {$$ = newast4(maketext("Exp"), $1,$2,$3,$4);}
	|ID LP RP {$$ = newast3(maketext("Exp"), $1,$2,$3);}
	|Exp LB Exp RB {$$ = newast4(maketext("Exp"), $1,$2,$3,$4);}
	|Exp DOT ID {$$ = newast3(maketext("Exp"), $1,$2,$3);}
	|ID {$$ = newast1(maketext("Exp"), $1);}
	|INT {$$ = newast1(maketext("Exp"), $1);}
	|FLOAT {$$ = newast1(maketext("Exp"), $1);}	
	;
Args:	Exp COMMA Args {$$ = newast3(maketext("Args"), $1,$2,$3);}
	|Exp {$$ = newast1(maketext("Args"), $1);}
	;
%%
void show(struct namelist* list)
{
	while(list!=NULL)
	{
		printf("%s\n",list->name);
		list=list->next;
	}
}
struct namelist* addnamelist(struct ast* ast1,char* name)
{
	if(ast1->namearg==NULL)
	{
		ast1->namearg=(struct namelist*)malloc(sizeof(struct namelist));
		ast1->namearg->next=NULL;
		ast1->namearg->name=(char*)malloc(sizeof(char));
		strcpy(ast1->namearg->name,name);
	}
	else{
		struct namelist* t=ast1->namearg;
		while(t->next!=NULL)
		{
			t=t->next;
		}
		struct namelist* tt=(struct namelist*)malloc(sizeof(struct namelist));
		tt->next=NULL;
		tt->name=(char*)malloc(sizeof(char));
		strcpy(tt->name,name);
		t->next=tt;
	}
	return ast1->namearg;
}
struct ast* newast(union Info v)
{
	struct ast *ast=(struct ast*)malloc(sizeof(struct ast));
	if(!ast)
	{
		printf("error type C at line %d",yylineno);
	}
	ast->info=v;
	ast->name=(char*)malloc(sizeof(char));
	return ast;		
}
struct ast* newastinit(union Info info,int type,int line)
{
	struct ast *ast=newast(info);
	ast->line=line;
	ast->type=type;
	return ast;
}
union Info makeint(int n)
{
	union Info info;
	info.in=n;
	return info;	
}
union Info makefloat(float f)
{
	union Info info;
	info.fl=f;
	return info;
}
union Info maketext(const char *s)
{
	union Info info;
	strcpy(info.name,s);
	return info;	
}
struct ast *newast1(union Info info, struct ast *a)
{
    struct ast *ast = newast(info);
    ast->line=a->line;
    ast->lc = a;
    ast->llength=1;
    a->rlength=0;
    return ast;
}
struct ast *newast2(union Info info, struct ast *a,struct ast *b)
{
        struct ast *ast = newast(info);
	ast->line=a->line; 
       ast->lc = a;
	a->rc=b;
	ast->llength=2;
	a->rlength=1;
	b->rlength=0;
        return ast;
}
struct ast *newast3(union Info info, struct ast *a,struct ast *b,struct ast *c)
{
        struct ast *ast = newast(info);
	ast->line=a->line; 
       ast->lc = a;
	a->rc=b;
	ast->llength=3;
	a->rlength=2;
	b->rlength=1;
	b->rc=c;
	c->rlength=0;
        return ast;
}
struct ast *newast4(union Info info, struct ast *a,struct ast *b,struct ast *c,struct ast *d)
{
        struct ast *ast = newast(info);
	ast->line=a->line;
        ast->lc = a;
	a->rc=b;
	ast->llength=4;
	a->rlength=3;
	b->rlength=2;
	b->rc=c;
	c->rlength=1;
	c->rc=d;
	d->rlength=0;
        return ast;
}
struct ast *newast5(union Info info, struct ast *a,struct ast *b,struct ast *c,struct ast *d,struct ast *e)
{
    struct ast *ast = newast(info);
	ast->line=a->line;
    ast->lc = a;
	a->rc=b;
	ast->llength=5;
	a->rlength=4;
	b->rlength=3;
	b->rc=c;
	c->rlength=2;
	c->rc=d;
	d->rlength=1;
	d->rc=e;
	e->rlength=0;
        return ast;
}
struct ast *newast7(union Info info, struct ast *a,struct ast *b,struct ast *c,struct ast *d,struct ast *e,struct ast *f,struct ast *g)
{
    struct ast *ast = newast(info);
	ast->line=a->line; 
    ast->lc = a;
	a->rc=b;
	ast->llength=7;
	a->rlength=6;
	b->rlength=5;
	b->rc=c;
	c->rlength=4;
	c->rc=d;
	d->rlength=3;
	d->rc=e;
	e->rlength=2;
	e->rc=f;
	f->rc=g;
	f->rlength=1;
	g->rlength=0;
        return ast;
}
void freetree(struct ast *t) {
    if(t->llength!=0)freetree(t->lc);
    if(t->rlength!=0)freetree(t->rc);
    free(t);
}
void tracetree(struct ast *t,int l) {
    int i;
	if(strcmp(t->info.name,"null")!=0){	
	for (i = 0; i < l; ++i) {
        printf("  ");
    	}
	}
    if (t == NULL) {
        printf("null\n");
        return;
    }
    if (t->type == INT) {
        printf("INT:%d\n", t->info.in);
    } else if (t->type == FLOAT) {
        printf("FLOAT:%f\n", t->info.fl);
    } else if(t->type==ID){
	printf("ID:%s\n",t->info.name);
    }  else if(t->type==TYPE){
	printf("TYPE:%s\n",t->info.name);
	} else if(t->type!=0){
	printf("%s\n",name[t->type-258]);
    } else if(strcmp(t->info.name,"null")==0){}
    else {
        printf("%s(%d)\n", t->info.name,t->line);
    }
    if(t->llength!=0) tracetree(t->lc, l + 1);
    if(t->rlength!=0) tracetree(t->rc,l);
/*    if (n == 0 && t->type == -1) {
        tracetree(NULL, l + 1);
    }*/
}
int main(int argc,char** argv) {
    initsymbollist();
	if(argc<=1)return 1;
	FILE* f=fopen(argv[1],"r");
	if(!f)
	{
	perror(argv[1]);
	return 1;
	}
	yyrestart(f);
	yyparse();
	return 0;
}

void yyerror(char *msg) {
    fprintf(stderr,"Error Type B at line %d: %s\n", yylineno, msg);
}
