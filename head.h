union Info{
	char name[100];
	int in;
	float fl;
};
struct namelist{
	char* name;
	struct namelist* next;
};
struct ast{
	int line;	
	union Info info;
	int type;
	int rlength;
	int llength;
	char* name;//综合属性变量名
	struct namelist* namearg;
	struct ast *lc;
	struct ast *rc;
};
struct namelist* addnamelist(struct ast* ast1,char* name);
struct ast* newast(union Info v);
struct ast* newastinit(union Info info,int type,int line);
union Info makeint(int n);
union Info makefloat(float f);
union Info maketext(const char *s);
struct ast *newast1(union Info info, struct ast *a);
struct ast *newast2(union Info info, struct ast *a,struct ast *b);
struct ast *newast3(union Info info, struct ast *a,struct ast *b,struct ast *c);
struct ast *newast4(union Info info, struct ast *a,struct ast *b,struct ast *c,struct ast *d);
struct ast *newast5(union Info info, struct ast *a,struct ast *b,struct ast *c,struct ast *d,struct ast *e);
struct ast *newast7(union Info info, struct ast *a,struct ast *b,struct ast *c,struct ast *d,struct ast *e,struct ast *f,struct ast *g);
void freetree(struct ast *t);
void tracetree(struct ast *t,int l);
struct namelist* linknamelist(struct namelist* list1,struct namelist* list2);
void show(struct namelist* list);
