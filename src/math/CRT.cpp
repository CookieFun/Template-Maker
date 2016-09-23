vector<LL> linear_mod_equation(LL a, LL b, LL n)
//线性方程求解
//ax = b (mod n)
{
    LL x, y, d;
    vector<LL> sol;
    sol.clear();
    EXT_GCD(a, n, d, x, y);
    if( b%d ) d = 0;
    else
    {
        sol.push_back(x * (b/d) % n);
        for (int i = 1; i < d; i++)
            sol.push_back((sol[i-1] + n/d + n) % n);
    }
    return sol;
}
LL mega_mod(int n)
//解 n 个一元线性同于方程组
//x ≡ r (mod a)
//求x
{
    LL a1, a2, r1, r2, d, c, x, y, x0,s;
    bool flag = true;
    scanf("%lld%lld", &a1, &r1);
    for(int i = 1; i < n; i++)
    {
        scanf("%lld%lld", &a2, &r2);
        if(!flag) continue;
        c = r2 - r1;
        EXT_GCD(a1, a2, d, x, y);
        if(c%d!=0)
        {
            flag = false;
            continue;
        }
        x0 = x*c/d;
        s = a2/d;
        x0 = (x0%s+s)%s;
        r1=r1+x0*a1;
        a1=a1*a2/d;
    }
    if(flag) return r1;
    else return -1LL;
}

LL CRT(LL *a, LL *m, int n)
//中国剩余定理
//x ≡ a[i] (mod m[i])
//m[i] is coprime
{
    LL MM = 1, Mi, x0, y0, d, ret = 0;
    for(int i = 0; i < n; i++)
        MM *= m[i];
    for(int i = 0; i < n; i++)
    {
        Mi = MM/m[i];
        EXT_GCD(Mi, m[i], d, x0, y0);
        ret = (ret+Mi*x0*a[i]) % MM;
    }
    if(ret < 0)
        ret += MM;
    return ret;
}