#ifndef INTERMEDIATE_CODE_H_INCLUDED
#define INTERMEDIATE_CODE_H_INCLUDED
void tracetree2(struct ast *t);//遍历树
void traceexp(struct ast *t,int mark);//遍历EXP
void tracearg(struct ast *t);//遍历参数
#endif // INTERMEDIATE_CODE_H_INCLUDED
