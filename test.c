#include <stdio.h>

void frac_simplify()
{
    int remainder,numerator,denominator;
    printf("请输入分子和分母的值：\n");
    scanf("%d/%d",&numerator,&denominator);
    int num=numerator,den=denominator;
    while(denominator!=0)
    {
        remainder=numerator%denominator;
        numerator=denominator;
        denominator=remainder;
    }
    num/=numerator;
    den/=numerator;
    if(num%den==0)printf("%d",num/den);
    else printf("%d/%d\n",num,den);
}

int main()
{
    frac_simplify();
    return 0;
}