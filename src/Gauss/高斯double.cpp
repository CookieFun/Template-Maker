///高斯消元模板
const double eps = 1e-10;    ///精度
double Aug[N][N]; ///增广矩阵
bool free_x[N];         ///判断是否是不确定的变元
double x[N];            ///解集

int sign(double x){ return (x>eps) - (x<-eps);}
int Gauss(int n,int m)//n 变元数量，m 方程数目
{
    memset(x,0,sizeof(x));
    memset(free_x,1,sizeof(free_x));
    int row,col,max_r;
    for(row=0,col=0; row<m&&col<n; row++,col++)
    {
        max_r = row;
        for(int i = row+1; i < m; i++)
        {///找到当前列所有行中的最大值(做除法时减小误差)
            if(sign(fabs(Aug[i][col]) - fabs(Aug[max_r][col])) > 0)
                max_r = i;
        }
        if(max_r != row){///将该行与当前行交换
            for(int j = row; j < n+1; j++)
                swap(Aug[max_r][j],Aug[row][j]);
        }
        if(sign(Aug[row][col])==0)
        {///当前列row行以下全为0(包括row行)
            row--;
            continue;
        }
        for(int i = row+1; i < m; i++)
        {
            if(sign(Aug[i][col])==0)
                continue;
            double ta = Aug[i][col]/Aug[row][col];
            for(int j = col; j < n+1; j++)
                Aug[i][j] -= Aug[row][j]*ta;
        }
    }
    ///无解或者多个解的情况
    for(int i = row; i < m; i++)
    {
        if(sign(Aug[i][col]))
            return -1;///col=n存在0...0,a的情况,无解
    }
    if(row < n)
    {
        for(int i = row-1; i >=0; i--)
        {
            int free_num = 0;   ///自由变元的个数
            int free_index;     ///自由变元的序号
            for(int j = 0; j < n; j++)
            {
                if(sign(Aug[i][j])!=0 && free_x[j])
                    free_num++,free_index=j;
            }
            if(free_num > 1) continue;  ///该行中的不确定的变元的个数超过1个,无法求解,它们仍然为不确定的变元
            ///只有一个不确定的变元free_index,可以求解出该变元,且该变元是确定的
            double tmp = Aug[i][n];
            for(int j = 0; j < n; j++)
            {
                if(sign(Aug[i][j])!=0 && j!=free_index)
                    tmp -= Aug[i][j]*x[j];
            }
            x[free_index] = tmp/Aug[i][free_index];
            free_x[free_index] = false;
        }
        return n-row;///存在0...0,0的情况,有多个解,自由变元个数为n-row个
    }
    ///无解或者多个解的情况
    for(int i = n-1; i >= 0; i--)
    {
        double tmp = Aug[i][n];
        for(int j = i+1; j < n; j++)
            if(sign(Aug[i][j])!=0)
                tmp -= Aug[i][j]*x[j];
        x[i] = tmp/Aug[i][i];
    }
    return 0;///有且仅有一个解,严格的上三角矩阵(n==m)
}