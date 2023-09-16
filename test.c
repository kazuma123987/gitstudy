#include <stdio.h>
void num()
{
    float a, b, c;
    a = 0.112;
    b = 0.231;
    c = a + b;
    if (c == 0.343) // float c精度为小数点后7位，与精度为小数点后15位的(double)（0.343）相比，很大概率不相等
        printf("相等,a=%.8f,b=%.8f,c=%.8f\n", a, b, c);
    else
        printf("不相等,a=%.8f,b=%.8f,c=%.8f\n", a, b, c);
    if (c == (float)0.343) // 将0.343强制转化为float类型两边则相等
        printf("相等,a=%.8f,b=%.8f,c=%.8f\n", a, b, c);
    else
        printf("不相等,a=%.8f,b=%.8f,c=%.8f\n", a, b, c);
    double x, y, z;
    x = 0.112;
    y = 0.231;
    z = x + y;
    if (z == 0.343) // 等式两边都是double类型(精度为小数点后15位)，其值相等
        printf("相等,x=%.20f,y=%.20f,z=%.20f,0.343=%.20f\n", x, y, z, 0.343);
    else
        printf("不相等,x=%.20f,y=%.20f,z=%.20f,0.343=%.16f\n", x, y, z, 0.343);
}
int main()
{
    num();
    return 0;
}