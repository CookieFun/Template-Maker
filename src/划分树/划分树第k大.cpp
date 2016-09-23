template <class T>
inline void rd(T &x) { char c = getchar(); x = 0;while(!isdigit(c)) c = getchar();
while(isdigit(c)) { x = x * 10 + c - '0'; c = getchar(); }}
using namespace std;
#define N 111111
#define M 22
int f[M][N];
int lef[M][N];
int sorted[N];
int n;
void build(int l=0,int r=n-1,int dep=0)
{
	if (l==r) return;
	int mid=(l+r)>>1;
	int s_same=0;
	int X=sorted[mid];
	int pl=l,pr=mid+1;
	rep(i,l,r+1)
		if (f[dep][i]<X) s_same++;
	s_same=mid-l+1-s_same;
	rep(i,l,r+1)
	{
		if (f[dep][i]<X)
		{
			f[dep+1][pl++]=f[dep][i];
			lef[dep][i]=(i-l?lef[dep][i-1]:0)+1;
		}else if (f[dep][i]==X&&s_same)
		{
			f[dep+1][pl++]=f[dep][i];
			s_same--;
			lef[dep][i]=(i-l?lef[dep][i-1]:0)+1;
		}else
		{
			f[dep+1][pr++]=f[dep][i];
		    lef[dep][i]=(i-l?lef[dep][i-1]:0);
		}
	}
	build(l,mid,dep+1);
	build(mid+1,r,dep+1);
}
int qry(int l,int r,int k,int L=0,int R=n-1,int dep=0)
{
	int mid=(L+R)>>1;

	if (l==r) return f[dep][l];
	int cnt=lef[dep][r]-(l-L?lef[dep][l-1]:0);
	if (k>cnt)
	{
		int nl,nr;
		nl=mid+1+l-L-(l-L?lef[dep][l-1]:0);
		nr=mid+1+r-L-lef[dep][r];
		return qry(nl,nr,k-cnt,mid+1,R,dep+1);
	}else
	{
		int nl,nr;
		nl=L+(l-L?lef[dep][l-1]:0);
		nr=L+lef[dep][r]-1;
		return qry(nl,nr,k,L,mid,dep+1);
	}
}
int main()
{
    	int m;
    	rd(n);rd(m);
    	memset(f,0,sizeof(f));
    	rep(i,0,n)
    	{
    		rd(sorted[i]);
    		f[0][i]=sorted[i];
    	}
    	sort(sorted,sorted+n);
    	build();
    	rep(i,0,m)
    	{
    		int s,t,k;
    		rd(s);rd(t);rd(k);
    		s--,t--;
    		printf("%d\n",qry(s,t,k));
    	}
    return 0;
}   
/*
10 3
1 5 2 7 5 4 3 8 7 7
2 5 3
4 4 1
1 7 3
*/
 
