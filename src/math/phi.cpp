//欧拉函数
LL calphi(LL n)
{
    LL res = n;
    for(LL i = 2; i*i <= n; i++)
	if(n%i==0)
    {
        res -= res/i;
        while(n%i==0) n/=i;
    }
    if(n > 1)
        res -= res/n;
    return res;
}

//欧拉函数预处理
int phi[maxn];
void getpthi(int n)
{
    memset(phi, 0, sizeof(phi));
    phi[1] = 1;
    for(int i = 2; i <= n; i++)if(!phi[i])
    {
        for(int j = i; j <= n; j+=i)
        {
            if(!phi[j])
                phi[j] = j;
            phi[j] = phi[j]/i*(i-1);
        }
    }
}