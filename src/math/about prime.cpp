const int maxn = 3010020;
bool isprime[maxn];
LL prime[maxn];
int doprime(LL n)
//prime[] 储存质数。1-based index;
{
    int nprime = 0;
    memset(isprime, true, sizeof(isprime));
    isprime[1] = false;
    for(LL i = 2; i <= n; i++)
    {
        if(isprime[i])
        {
            prime[++nprime] = i;
            for(LL j = i*i; j <= N; j+=i)
                isprime[j] = false;
        }
    }
    return nprime;
}
LL slow_mul(LL a, LL b, LL p)
{
    // cout << a << " " << b << endl;
    LL ret = 0;  
    while(b) {  
        if(b & 1) ret = (ret + a) % p;  
        a = (a + a) % p;
        b >>= 1;  
    }  
    return ret % p;  
}  
  
LL pow_mod(LL a, LL b, LL p)
//快速幂   
{
    LL ret = 1;  
    while(b) {  
        if(b & 1) ret = (ret*a)%p;  
        a = (a*a)%p;  
        b >>= 1;  
    }  
    return ret%p;  
}  


//判断Mp = 2^p-1 是否为梅森素数
bool lucas_lehmer(int p)
{
    if(p == 2) return true;
    LL m = (1LL<<p)-1LL, tmp = 4LL;
    for(int i = 0; i < p-2; i++)
    {
        tmp = (slow_mul(tmp, tmp, m) - 2 + m) % m;
    }
    if(tmp == 0LL) return true;
    return false;
}

LL witness(LL a,LL b,LL c)
{
    if(b==0)return 1;
    LL x,y,t=0;
    while((b&1)==0)
        b>>=1,t++;
    y=x=pow_mod(a,b,c);
    //二次探测
    while(t--)
    {
        y=slow_mul(x,x,c);
        if(y==1 && x!=1 && x!=c-1)
            return false;
        x=y;
    }
    return y==1;
}
bool miller_rabin(LL n)
//..质数为true, 非质数为false..
{
    if(n==2)return true;
    if(n<2 || (n&1)==0)return false;
    for(int i=0;i<3;i++)
        if(witness(rand()%(n-2)+2,n-1,n)!=1)
            return false;
    return true;
}
LL ANS = INF;
LL pollard_rho(LL n,LL c)
//..随机返回一个 n 的约数..
{
    if(n%2==0)return 2;
    LL i=1,k=2,x=rand()%n,y=x,d;
    while(1){
        i++;
        x=(slow_mul(x,x,n)+c)%n;
        d=gcd(y-x,n);
        if(d==n)return n;
        if(d!=n && d>1)return d;
        if(i==k) y=x,k<<=1;
    }
}
void calc(LL n,LL c=240)
//寻找最小的约数..
{
    if(n==1)return;
    if(miller_rabin(n)){
        ANS=min(ANS,n);
        return;
    }
    LL k=n;
    while(k==n)k=pollard_rho(n,c--);
    calc(k,c),calc(n/k,c);
}