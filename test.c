int mulx(int a,int b)
{
	return a*b;
}
int divx(int c,int d)
{
	return c/d;
}
int addx(int e,int f)
{
	return e+f;
}
int subx(int g,int h)
{
	return g-h;
}
int jiecheng(int n)
{
	if(n<=1)return 1;
	return n*jiecheng(n-1);
}
int main()
{
	int mark=1,x=5,y=2,result;
	if(mark==1)result=mulx(x,y);
	else if(mark==2)result=divx(x,y);
	else if(mark==3)result=addx(x,y);
	else if(mark==4)result=subx(x,y);
	else if(mark==5)result=jiecheng(x);
	dis(result);
	return 0;
}
