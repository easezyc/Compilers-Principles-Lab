#ifndef ERROR_H_INCLUDED
#define ERROR_H_INCLUDED
//分别对应17类错误
void error1(char* name,int line);
void error2(char* name,int line);
void error3(char* name,int line);
void error4(char* name,int line);
void error5(struct ast* ast1,struct ast* ast2,int line);
void error6(int type,int line);
void error7(struct ast* ast1,struct ast* ast2,int line);
void error8(char* name,char* name2,int line);
void error9(char* name,struct namelist* namelist,int line);
void error10(char* name,int line);
void error11(char* typname,int line);
void error12(char* typname,int line);
void error13(int line);
void error14(char* name2,int line);
void error15(char* name,int line);
void error16(char* name,int line);
void error17(char* name,int line);
#endif // ERROR_H_INCLUDED
