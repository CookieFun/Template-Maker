
using namespace std;
#define N 1111111
#define M 8111111
const int MaxM = 1111;
const int MaxN = 1111;
const int maxnode = MaxN * MaxM;
int flag;
struct DLX
{
    int n,m,size;
    int U[maxnode],D[maxnode],R[maxnode],L[maxnode],Row[maxnode],Col[maxnode];
    int H[MaxN],S[MaxM];
    int ansd;
    void init(int _n,int _m)
    {
        n = _n;
        m = _m;
        for(int i = 0;i <= m;i++)
        {
            S[i] = 0;
            U[i] = D[i] = i;
            L[i] = i-1;
            R[i] = i+1;
        }
        R[m] = 0; L[0] = m;
        size = m;
        for(int i = 1;i <= n;i++)H[i] = -1;
    }
    void Link(int r,int c)
    {
        ++S[Col[++size]=c];
        Row[size] = r;
        D[size] = D[c];
        U[D[c]] = size;
        U[size] = c;
        D[c] = size;
        if(H[r] < 0)H[r] = L[size] = R[size] = size;
        else
        {
            R[size] = R[H[r]];
            L[R[H[r]]] = size;
            L[size] = H[r];
            R[H[r]] = size;
        }
    }
    void remove(int c)
    {
        L[R[c]] = L[c]; R[L[c]] = R[c];
        for(int i = D[c];i != c;i = D[i])
            for(int j = R[i];j != i;j = R[j])
            {
                U[D[j]] = U[j];
                D[U[j]] = D[j];
                --S[Col[j]];
            }
    }
    void resume(int c)
    {
        for(int i = U[c];i != c;i = U[i])
            for(int j = L[i];j != i;j = L[j])
                ++S[Col[U[D[j]]=D[U[j]]=j]];
        L[R[c]] = R[L[c]] = c;
    }
    int ans[MaxN];
    void Dance(int d)
    {
        if (flag) return;
        if(R[0] == 0)
        {
            flag=1;
            printf("%d ",d);
            rep(i,0,d)
            printf("%d%c",ans[i],i==d-1?'\n':' ');
            return;
        }
        int c = R[0];
        for(int i = R[0];i != 0;i = R[i])
            if(S[i] < S[c])
                c = i;
        remove(c);
        for(int i = D[c];i != c;i = D[i])
        {
            for(int j = R[i];j != i;j = R[j]) remove(Col[j]);
            ans[d]=Row[i];
            Dance(d+1);
            for(int j = L[i];j != i;j = L[j]) resume(Col[j]);
        }
        resume(c);
    }
}dlx;
int main()
{
	int n,m;
	while (~scanf("%d%d",&n,&m))
	{
		dlx.init(n,m);
		rep(i,0,n)
		{
			int k,x;
			scan(&k);
			rep(j,0,k)
			{
				scan(&x);
				dlx.Link(i+1,x);
			}
		}
		flag=0;
		dlx.Dance(0);
		if (!flag) puts("NO");
	}
    return 0;
}
/*
6 5
1 2
2 3
3 4
4 5
3 5
2 4 5 6
*/
