
LL quick_mod(LL a, LL b, LL m)
{
    LL ans = 1;
    a %= m;
    while(b)
    {
        if(b & 1) ans = ans * a % m;
        b >>= 1;
        a = a * a % m;
    }
    return ans;
}
namespace ntt{
    const int N = (1 << 19)+20;
    const int P = 998244353;
    const int G = 3;
    const int NUM = 25;

    LL  wn[NUM];
    LL  a[N], b[N];
    LL mul(LL x,LL y)
    {
        return (x*y-(LL)(x/(long double)P*y+1e-3)*P+P)%P;
    }

    void GetWn()
    {
        for(int i = 0; i < NUM; i++)
        {
            int t = 1 << i;
            wn[i] = quick_mod(G, (P - 1) / t, P);
        }
    }


    void Rader(LL a[], int len)
    {
        int j = len >> 1;
        for(int i = 1; i < len - 1; i++)
        {
            if(i < j) swap(a[i], a[j]);
            int k = len >> 1;
            while(j >= k)
            {
                j -= k;
                k >>= 1;
            }
            if(j < k) j += k;
        }
    }

    void NTT(LL a[], int len, int on)
    {
        Rader(a, len);
        int id = 0;
        for(int h = 2; h <= len; h <<= 1)
        {
            id++;
            for(int j = 0; j < len; j += h)
            {
                LL w = 1;
                for(int k = j; k < j + h / 2; k++)
                {
                    LL u = a[k] % P;
                    LL t = w * a[k + h / 2] % P;
                    a[k] = (u + t) % P;
                    a[k + h / 2] = (u - t + P) % P;
                    w = w * wn[id] % P;
                }
            }
        }
        if(on == -1)
        {
            for(int i = 1; i < len / 2; i++)
                swap(a[i], a[len - i]);
            LL inv = quick_mod(len, P - 2, P);
            for(int i = 0; i < len; i++)
                a[i] = a[i] * inv % P;
        }
    }

    void Conv(LL a[], LL b[], int n)
    {
        NTT(a, n, 1);
        NTT(b, n, 1);
        for(int i = 0; i < n; i++)
            a[i] = a[i] * b[i] % P;
        NTT(a, n, -1);
    }
    void workNTT(LL a[], LL b[],int L1,int L2,int &len)
    {
        GetWn();
        len = 1;
        while(len < 2 * L1 || len <2 * L2) len <<= 1;
        rep(i,L1,len) a[i] = 0;
        rep(i,L2,len) b[i] = 0;
        Conv(a, b, len);
    }
    ///////////////////////找关于P的G(原根)//////////////////
    void deal()
    {
        int a[100]={0};
        int n=P-1;
        int x=sqrt(n)+1;
        a[0]=1;
        rep(i,2,x)
        {
            while (n%i==0) a[a[0]]=i,n/=i;
            if (a[a[0]]) a[0]++;
        }
        if (n!=1) a[a[0]++]=n;
        n=P;
        int t=1;
        while (t++)
        {
            int flag=0;
            rep(i,1,a[0])
            if (quick_mod(t,(n-1)/a[i],n)==1) flag=1;
            if (!flag) break;
        }
        cout<<t<<endl;
    }
    ////////////////////////////////////////////////////////////////
}