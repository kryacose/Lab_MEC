#include<stdio.h>
#include<stdlib.h>

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
    int n, a[30], h, total = 0, max, pos = 0, i, dir;

    printf("\nMax positions: ");
    scanf("%d",&max);

    printf("Enter position of head: ");
    scanf("%d",&a[0]);
    h = a[0];

    printf("Enter no of locations: ");
    scanf("%d",&n);

    printf("Enter locations: ");
    for(int i=1;i<=n;i++)
        scanf("%d",&a[i]);

    sort(n+1,a);


    printf("Disk Head Movement:\n");
    while(a[pos] != h) pos++;

    if(pos == 0) dir = 1;
    else if(pos == n) dir = -1;
    else dir = (a[pos+1]-a[pos])<=(a[pos]-a[pos-1]) ? 1 : -1;
    
    for(i=pos;i<=n && i>=0 ;i+=dir)
        printf("%d --> ",a[i]);
    

    if(dir==1 && a[i-1] != max-1)
        printf("%d --> ",max-1);

    if(dir==-1 && a[0] != 0)
        printf("%d --> ",0);

    if(h!=0 && h!=max-1)
        printf("%d --> ",dir==1?0:max-1);


    total += abs((dir==1?max-1:0) - h);

    for(i=dir==1?0:n; i!=pos ; i+=dir)
        printf("%d --> ",a[i]);

    if(h!=0 && h!=max-1)
        total += abs((dir==1?0:max-1) - a[pos-dir]);


    printf("\nTotal disk head movement: %d\n\n", total);
}
