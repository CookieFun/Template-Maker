using namespace std;
struct nod
{
	int y,id;
}a[N];
int n;
bool cmp(nod a,nod b)
{
	if (a.y!=b.y) return a.y>b.y;
	return a.id<b.id;
}
int b[N][N];
int linker[N],ma[N];
bool use[N];
bool dfs(int u)
{
	rep(i,1,n+1)
	if (b[u][i]&&!use[i])
	{
		use[i]=true;
		if (linker[i]==-1||dfs(linker[i]))
		{
			linker[i]=u;
			ma[u]=i;
			return true;
		}
	}
	return false;
}
void hungary()
{
	int u;
	memset(linker,-1,sizeof(linker));
	rep(i,0,n)
	{
		memset(use,0,sizeof(use));
		if (!dfs(a[i].id)) ma[a[i].id]=0;
	}
	rep(i,1,n+1)
	printf("%d%c",ma[i],i==n?'\n':' ');
}
int main()
{
	scan(&n);
	rep(i,0,n)
	{
		scan(&a[i].y);
		a[i].id=i+1;
	}
	sort(a,a+n,cmp);
	rep(i,1,n+1)
	{
		int m;
		scan(&m);
		rep(j,0,m)
		{
			int x;
			scan(&x);
			b[i][x]=1;
		}
	}
	hungary();	
	return 0;
}