#include<stdio.h>

void sort(int n, int a[])
{
    int t;

    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n-i-1;j++)
            if(a[j]>a[j+1])
            {
                t = a[j];
                a[j] = a[j+1];
                a[j+1] = t;
            }
    }
}

int main()
{
    int a[5] = {5,9,6,11,3};

    sort(5,a);

    for(int i=0;i<5;i++)
        printf("%d ",a[i]);
}