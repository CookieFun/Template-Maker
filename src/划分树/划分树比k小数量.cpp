#define N 111111
#define M 22
int sorted[N];
int lef[22][N],f[22][N];
int n;
void build(int L=1,int R=n,int p=0)
{
    if (L==R) return;
    int mid=L+R>>1;
    int same=mid-L+1;
    int X=sorted[mid];
    rep(i,L,R+1)
        if (f[p][i]<X) same--;
    int lp=L,rp=mid+1;
    rep(i,L,R+1)
    {
        if (f[p][i]<X) f[p+1][lp++]=f[p][i];
        else if (f[p][i]==X&&same) f[p+1][lp++]=f[p][i],same--;
        else f[p+1][rp++]=f[p][i];
        lef[p][i]=lef[p][L-1]+lp-L;
    }
    build(L,mid,p+1);
    build(mid+1,R,p+1);
}
int qry(int l,int r,int k,int L=1,int R=n,int dep=0)
{
    if (l>r) return 0;
    if (l==r) return f[dep][l]<=k;
    int cnt=lef[dep][r]-lef[dep][l-1];
    int mid=L+R>>1;
    if (sorted[mid]<=k)
    {
        int nr=r+lef[dep][R]-lef[dep][r];
        int nl=nr-(r-l-cnt);
        return cnt+qry(nl,nr,k,mid+1,R,dep+1);
    }else{
        int nl=L+lef[dep][l-1]-lef[dep][L-1];
        int nr=cnt+nl-1;
        return qry(nl,nr,k,L,mid,dep+1);
    }
}
int main()
{
    int T,m,Case=0;
    scanf("%d",&T);
    while (T--)
    {
        memset(lef,0,sizeof(lef));
        scanf("%d%d",&n,&m);
        rep(i,1,n+1)
        {
            scanf("%d",&f[0][i]);
            sorted[i]=f[0][i];
        }
        sort(sorted+1,sorted+1+n);
        build();
        printf("Case %d:\n",++Case);
        rep(i,0,m)
        {
            int x,y,z;
            scanf("%d%d%d",&x,&y,&z);
            x++,y++;
            printf("%d\n",qry(x,y,z));
        }
    }
}
/*
1 
10 20
1 4 2 3 5 6 7 8 9 0 
1 3 2 
1
10 1
1 5 2 3 6 4 7 3 0 0
3 9 2
*/
 
