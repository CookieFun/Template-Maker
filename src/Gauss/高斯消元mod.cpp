const int MOD= 7;
const int MAXN=400;
int a[MAXN][MAXN];//增广矩阵
int x[MAXN];//解集
bool free_x[MAXN];//标记是否是不确定的变元

inline int gcd(int a,int b)
{
    int t;
    while(b!=0)
    {
        t=b;
        b=a%b;
        a=t;
    }
    return a;
}
inline int lcm(int a,int b)
{
    return a/gcd(a,b)*b;//先除后乘防溢出
}

// 高斯消元法解方程组(Gauss-Jordan elimination).(-2表示有浮点数解，但无整数解，
//-1表示无解，0表示唯一解，大于0表示无穷解，并返回自由变元的个数)
//有equ个方程，var个变元。增广矩阵行数为equ,分别为0到equ-1,列数为var+1,分别为0到var.
int Gauss(int equ,int var)
{
    int i,j,k;
    int max_r;// 当前这列绝对值最大的行.
    int col;//当前处理的列
    int ta,tb;
    int LCM;
    int temp;
    int free_x_num;
    int free_index;

    for(int i=0;i<=var;i++)
    {
        x[i]=0;
        free_x[i]=true;
    }
    col=0; 
    for(k = 0;k < equ && col < var;k++,col++)
    {
        max_r=k;
        for(i=k+1;i<equ;i++)
        	if(abs(a[i][col])>abs(a[max_r][col])) max_r=i;
        if(max_r!=k)
        	for(j=k;j<var+1;j++) swap(a[k][j],a[max_r][j]);
        
        if(a[k][col]==0)
        {
            k--;
            continue;
        }
        for(i=k+1;i<equ;i++)
        {
            if(a[i][col]!=0)
            {
                LCM = lcm(abs(a[i][col]),abs(a[k][col]));
                ta = LCM/abs(a[i][col]);
                tb = LCM/abs(a[k][col]);
                if(a[i][col]*a[k][col]<0)tb=-tb;//异号的情况是相加
                for(j=col;j<var+1;j++)
                {
                    a[i][j] = ((a[i][j]*ta-a[k][j]*tb)%MOD+MOD)%MOD;
                }
            }
        }
    }


    for (i = k; i < equ; i++)
    { 
        if ( a[i][col]  != 0) return -1;//无解
    }
    if (k < var)
    {
        // 首先，自由变元有var - k个，即不确定的变元至少有var - k个.
        for (i = k - 1; i >= 0; i--)
        {
            // 第i行一定不会是(0, 0, ..., 0)的情况，因为这样的行是在第k行到第equ行.
            // 同样，第i行一定不会是(0, 0, ..., a), a != 0的情况，这样的无解的.
            free_x_num = 0; // 用于判断该行中的不确定的变元的个数，如果超过1个，则无法求解，它们仍然为不确定的变元.
            for (j = 0; j < var; j++)
            {
                if (a[i][j] != 0 && free_x[j]) free_x_num++, free_index = j;
            }
            if (free_x_num > 1) continue; // 无法求解出确定的变元.
            // 说明就只有一个不确定的变元free_index，那么可以求解出该变元，且该变元是确定的.
            temp = a[i][var];
            for (j = 0; j < var; j++)
            {
                if (a[i][j] != 0 && j != free_index) temp -= a[i][j] * x[j]%MOD;
                temp=(temp%MOD+MOD)%MOD;
            }
            x[free_index] = (temp / a[i][free_index])%MOD; // 求出该变元.
            free_x[free_index] = 0; // 该变元是确定的.
        }
        return var - k; // 自由变元有var - k个.
    }
    for (i = var - 1; i >= 0; i--)
    {
        temp = a[i][var];
        for (j = i + 1; j < var; j++)
        {
            if (a[i][j] != 0) temp -= a[i][j] * x[j];
            temp=(temp%MOD+MOD)%MOD;
        }
        while (temp % a[i][i] != 0) temp+=MOD;
        x[i] =( temp / a[i][i])%MOD ;
    }
    return 0;
}