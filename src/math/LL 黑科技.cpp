LL mult( LL A, LL B, LL Mo )
{
    LL temp = ( ( LL ) ( ( db ) A*B/Mo+1e-6 ) * Mo );
    return A*B - temp;
}