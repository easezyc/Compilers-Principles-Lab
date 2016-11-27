union Info{
	char name[100];
	int in;
	float fl;
};
struct namelist{
	char* name;
	int arraymark;
	struct namelist* next;
};
struct ast{
	int arraymark;
	int line;
	union Info info;
	int type;
	int rlmark;//0表示左值，1表示右值
	char* typname;
	char* up;
	int rlength;
	int llength;
	int tfname;
	char* tname;
	int xnum;
	char* name;//综合属性变量名
	struct namelist* namearg;
	struct ast *lc;
	struct ast *rc;
};
void setarrtype(struct ast* ast,char* name,int mark,int rlmark);   //标记是否是数组以及是否是左值
struct namelist* addnamelist(struct ast* ast1,char* name,int arraymark);   //添加需要成为参数的变量名字
struct ast* newast(union Info v);   //新建语法节点
struct ast* newastinit(union Info info,int type,int line);    //初始化词法单元
union Info makeint(int n);   //初始化int的词法单元
union Info makefloat(float f);   //初始化float的词法单元
union Info maketext(const char *s);    //初始化其他词法单元
struct ast *newast1(union Info info, struct ast *a);     //建树
struct ast *newast2(union Info info, struct ast *a,struct ast *b);
struct ast *newast3(union Info info, struct ast *a,struct ast *b,struct ast *c);
struct ast *newast4(union Info info, struct ast *a,struct ast *b,struct ast *c,struct ast *d);
struct ast *newast5(union Info info, struct ast *a,struct ast *b,struct ast *c,struct ast *d,struct ast *e);
struct ast *newast7(union Info info, struct ast *a,struct ast *b,struct ast *c,struct ast *d,struct ast *e,struct ast *f,struct ast *g);
void freetree(struct ast *t);   //释放语法树
void tracetree(struct ast *t,int l);    //遍历语法树
struct namelist* linknamelist(struct namelist* list1,struct namelist* list2);    //连接两个namelist
void show(struct namelist* list);   //测试时用于显示namelist
