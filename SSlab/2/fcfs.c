#include<stdio.h>
#include<stdlib.h>

int main()
{
    int n, a[30], total = 0;

    printf("\nEnter position of head: ");
    scanf("%d",&a[0]);

    printf("Enter no of locations: ");
    scanf("%d",&n);

    for(int i=1;i<=n;i++)
        scanf("%d",&a[i]);

    printf("%d --> ",a[0]);
    for(int i=1;i<=n;i++)
    {
        total += abs(a[i] - a[i-1]);
        printf("%d --> ",a[i]);
    }

    printf("\nTotal disk head movement: %d\n\n", total);
}
