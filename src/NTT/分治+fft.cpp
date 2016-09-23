#include <bits/stdc++.h>
#define INF 0x3f3f3f3f
#define EPS 1e-8
#define PI acos(-1.0)
#define LL long long
#define ld double
#define ULL unsigned long long
#define rep(i,a,b) for(int i=a;i<b;i++)
#define PII pair<int,int>
#define PLL pair<LL,LL>
#define MP make_pair
#define sf(x) scanf("%d",&x)
#define sqr(x) ((x)*(x))
template <class T>
inline void rd(T &x) { char c = getchar(); x = 0;while(!isdigit(c)) c = getchar();
while(isdigit(c)) { x = x * 10 + c - '0'; c = getchar(); }}
#define IN freopen("in.txt","r",stdin);
#define OUT freopen("out.txt","w",stdout);
using namespace std;
const int N=1e5+10; 
const int M=313;
struct cpx
{
    ld r,i;
    cpx(){}
    cpx(ld r ,ld i):r(r),i(i) {}
    cpx operator + (const cpx& t) const
    {
        return cpx(r+t.r,i+t.i) ;
    }
    cpx operator - (const cpx& t) const
    {
        return cpx(r-t.r,i-t.i);
    }
    cpx operator * (const cpx& t) const
    {
        return cpx(r*t.r-i*t.i,r*t.i+i*t.r);
    }
};
const double pi=acos(-1.0);
int rev(int x, int n)
{
    int tmp=0;
    for (int i=1;i<n;i<<=1)
    {
        tmp<<=1;
        if (x & i) tmp |=1;
    }
    return tmp;
}

void fft(cpx *a, int n, int flag)// 1 -1
{
    for (int i=0;i<n;i++)
        if (i<rev(i, n))
            swap(a[rev(i, n)], a[i]);
    for (int i=1;i<n;i<<=1)
    {
        cpx wn(cos(pi/i), flag*sin(pi/i));
        for (int j=0;j<n;j+=(i<<1))
        {
            cpx w(1, 0);
            for (int k=0;k<i;k++, w=w*wn)
            {
                cpx x=a[j+k], y=w*a[j+k+i];
                a[j+k]=x+y;
                a[j+k+i]=x-y;
            }
        }
    }
    if (flag==-1) for (int i=0;i<n;i++) a[i].r/=n;
}
cpx x[1<<20],y[1<<20];
int a[N];
LL f[N];
void cdq(int l,int r)
{
	//cout<<l<<" "<<r<<endl;
	if (l==r)
	{
		(f[l]+=a[l])%=M;
		return;
	}
	int mid=l+r>>1;
	cdq(l,mid);
	int L=1;
	while (L<=r-l+1) L<<=1;

	rep(i,0,L) 
	{
		if (l+i<=mid) x[i]=cpx(f[i+l],0);
		else x[i]=cpx(0,0);
		if (i+1+l<=r) y[i]=cpx(a[i+1]%M,0);
		else y[i]=cpx(0,0);
	}

	fft(x,L,1);
	fft(y,L,1);
	rep(i,0,L)
		x[i]=x[i]*y[i];
	fft(x,L,-1);
	rep(i,mid+1,r+1)
	{
		f[i]+=(LL)(x[i-l-1].r+0.5);
		f[i]%=M;
	}
	cdq(mid+1,r);
}
int main()
{

	int n;
	while (~sf(n)&&n)
	{
		memset(f,0,sizeof(LL)*(n+2));
		rep(i,0,n)
		rd(a[i+1]);
		cdq(1,n);
		cout<<f[n]<<endl;
    }
    return 0;
}
/*
2
8 6
*/
