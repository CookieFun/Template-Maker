int equ,var;
int a[110][110];
int x[110];
int free_x[110];
int free_num;

//返回值为-1表示无解，为0是唯一解，否则返回自由变元个数
int Gauss()
{
    int max_r, col, k;
    free_num = 0;
    for(k = 0, col = 0; k < equ && col < var; k++, col++)
    {
        max_r = k;
        for(int i = k+1 ; i < equ; i++)
            if(abs(a[i][col]) > abs(a[max_r][col]))
                max_r = i;
        if(a[max_r][col] == 0)
        {
            k--;
            free_x[free_num++] = col; //自由变元
            continue;
        }
        if(max_r != k)
        {
            for(int j = col; j < var+1; j++)
                swap(a[k][j],a[max_r][j]);
        }
        for(int i = k+1; i < equ;i++)
            if(a[i][col] != 0)
                for(int j = col; j < var+1;j++)
                    a[i][j] ^= a[k][j];
    }
    for(int i = k;i < equ;i++)
        if(a[i][col] != 0)
            return -1;
    if(k < var)
    {//多解求最小1个数
            int ans = INF;
            int t=var-k;
            int tot = (1<<t);
            for(int i = 0;i < tot;i++)
            {
                int cnt = 0;
                for(int j = 0;j < t;j++)
                {
                    if(i&(1<<j))
                    {
                        x[free_x[j]] = 1;
                        cnt++;
                    }
                    else x[free_x[j]] = 0;
                }
                for(int j = var-t-1;j >= 0;j--)
                {
                    int idx;
                    for(idx = j;idx < var;idx++)
                        if(a[j][idx])
                            break;
                    x[idx] = a[j][var];
                    for(int l = idx+1;l < var;l++)
                        if(a[j][l])
                            x[idx] ^= x[l];
                    cnt += x[idx];
                }
                ans = min(ans,cnt);
            }
            printf("%d\n",ans);

        return var-k;
    }
    for(int i = var-1; i >= 0;i--)
    {
        x[i] = a[i][var];
        for(int j = i+1; j < var;j++)
            x[i] ^= (a[i][j] && x[j]);
    }
    return 0;
}