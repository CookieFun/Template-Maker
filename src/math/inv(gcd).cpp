void EXT_GCD(LL a, LL b, LL &d, LL &x, LL &y)
//a , b 任意
{
    if(!b) {d = a, x = 1, y = 0;}
    else {EXT_GCD(b, a % b, d, y, x), y -= x * (a / b);}
}

//递归求逆元
//p, x 互质
LL inv(LL a, LL c)
// 用扩展欧几里得求逆元
// 要求 a, c 互质
// 如果没有逆元返回 -1
{
	LL d, x, y;
	EXT_GCD(a, c, d, x, y);
	return d == 1 ? (x + c) % c : -1;
}