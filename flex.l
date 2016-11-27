%option yylineno
%option noyywrap
%{
	#include <stdio.h>
	#include"head.h"
	#include"bison.tab.h"
	#include<math.h>	
	extern union YYSTYPE yylval;
	enum num{
		A=10,
		a=10,
		B=11,
		b=11,
		C=12,
		c=12,
		D=13,
		d=13,
		E=14,
		e=14,
		F=15,
		f=15
	};
%}

%x COMMENT

OCT 0[0-7]*?
HEX 0[Xx][0-9a-fA-F]+?
FLOAT [0-9]*[.]?[0-9]+([eE][+-]?[0-9]*|[0])?f?
INT [1-9][0-9]*|[0]
TYPE (int)|(float)
ID (_|[A-Za-z])([A-Za-z]|[0-9]|_)*
SEMI [;]
COMMA [,]
ASSIGNOP [=]
RELOP [>]|[<]|[>][=]|[<][=]|"=="|[!][=](^[=])
PLUS [+]
MINUS [-]
STAR [*]
DIV [/]
AND [&][&]
OR [|][|]
DOT [.]
NOT [!]
LP \(
RP \)
LB \[
RB \]
LC \{
RC \}
STRUCT struct
RETURN return
IF if
ELSE else 
WHILE while

%%
 /* comments */
"/*" { BEGIN(COMMENT); }
<COMMENT>"*/" { BEGIN(INITIAL); }
<COMMENT>([^*]|\n)+|.
<COMMENT><<EOF>> {
    fprintf(stderr, "Error type A at line %d: Untermintated comment.\n", yylineno);
}
"//".*\n { }
{SEMI} { 
	yylval.a=newastinit(maketext(yytext),SEMI,yylineno);
	return SEMI; 
}
{COMMA} { 
	yylval.a=newastinit(maketext(yytext),COMMA,yylineno);
	return COMMA; 
}
{TYPE} { 
	yylval.a=newastinit(maketext(yytext),TYPE,yylineno);
	return TYPE; 
}
{ASSIGNOP} { 
	yylval.a=newastinit(maketext(yytext),ASSIGNOP,yylineno);
	return ASSIGNOP;
}
{OCT} {
	int j;
	j=strlen(yytext);
	int i,k=0,w=0;
	j=j-1;
	int l;
	l=j;
	for(i=0;i<l;i++)
	{
		k=(yytext[i+1]-48)*(pow(8,--j));
    		w+=k;
	}
	yylval.a=newastinit(makeint(w),INT,yylineno);
	return INT;
}
{HEX} {
  	  int j;
          j=strlen(yytext);
          int i,k=0,w=0;
          j=j-2;
          int l;
          l=j;
          for(i=0;i<l;i++)
          {
		int t;	
                if(yytext[i+2]>90)t=yytext[i+2]-97+10;
		else if(yytext[i+2]>64)t=yytext[i+2]-65+10;
		else t=yytext[i+2]-48;
		k=t*((int)pow(16,--j));
        	 w+=k;
          }
	yylval.a=newastinit(makeint(w),INT,yylineno);
	return INT;
}
{INT} { 
	yylval.a=newastinit(makeint(atoi(yytext)),INT,yylineno);
	return INT;
}
{FLOAT} { 
	yylval.a=newastinit(makefloat(atof(yytext)),FLOAT,yylineno);
	return FLOAT; 
}
{PLUS} { 
	yylval.a=newastinit(maketext(yytext),PLUS,yylineno);
	return PLUS; 
}
{MINUS} { 
	yylval.a=newastinit(maketext(yytext),MINUS,yylineno);
	return MINUS; 
}
{DIV} { 
	yylval.a=newastinit(maketext(yytext),DIV,yylineno);
	return DIV; 
}
{STAR} { 
	yylval.a=newastinit(maketext(yytext),STAR,yylineno);
	return STAR; 
}
{RELOP} { 
	yylval.a=newastinit(maketext(yytext),RELOP,yylineno);
	return RELOP; 
}
{AND} { 
	yylval.a=newastinit(maketext(yytext),AND,yylineno);
	return AND; 
}
{OR} { 
	yylval.a=newastinit(maketext(yytext),OR,yylineno);
	return OR;
}
{STRUCT} {
	yylval.a=newastinit(maketext(yytext),STRUCT,yylineno);
	return STRUCT; 
}

{RETURN} {
	yylval.a=newastinit(maketext(yytext),RETURN,yylineno);
	return RETURN; 
}

{IF}  {
	yylval.a=newastinit(maketext(yytext),IF,yylineno);
	return IF; 
}

{ELSE}	{
	yylval.a=newastinit(maketext(yytext),ELSE,yylineno);
	return ELSE; 
}
 
{WHILE} {
	yylval.a=newastinit(maketext(yytext),WHILE,yylineno);
	return WHILE; 
}
{NOT} { 
	yylval.a=newastinit(maketext(yytext),NOT,yylineno);
	return NOT; 
}
{DOT} { 
	yylval.a=newastinit(maketext(yytext),DOT,yylineno);
	return DOT; 
}
{LP} { 
	yylval.a=newastinit(maketext(yytext),LP,yylineno);
	return LP; 
}
{RP} { 
	yylval.a=newastinit(maketext(yytext),RP,yylineno);
	return RP; 
}
{LB} { 
	yylval.a=newastinit(maketext(yytext),LB,yylineno);
	return LB; 
}
{RB} { 
	yylval.a=newastinit(maketext(yytext),RB,yylineno);
	return RB; 
}
{LC} { 
	yylval.a=newastinit(maketext(yytext),LC,yylineno);
	return LC; 
}
{RC} { 
	yylval.a=newastinit(maketext(yytext),RC,yylineno);
	return RC; 
}
{ID} { 
	yylval.a=newastinit(maketext(yytext),ID,yylineno);
	return ID; 
}
\n {}
\t {}
" " {}
.               {
    fprintf(stderr, "Error at Line %d: %s\n", yylineno, yytext); 
}
%%
