#include<stdio.h>
#include<stdlib.h>
#include<omp.h>
#include<time.h>
#include<unistd.h>

int wait(int *mutex)
{   
    while(*mutex == 0);
    *mutex = 0;
    return 1;
}

void release(int *mutex)
{
    (*mutex)++;
}



void printres(int tnum, int chopstick[], int phil[])
{
    for(int i=0;i<5;i++)
    printf("  %c  %s", chopstick[i] == 1 ? '|' : '_', phil[i] == 1 ? "eat  " : "think");
    printf("  %c", chopstick[0] == 1 ? '|' : '_');

    printf("\n");

}


int main()
{
    omp_set_num_threads(5);
    srand(time(0));
    int phil[5] = {0,0,0,0,0}, chopstick[5] = {1,1,1,1,1}, tnum;

    printf("     ");

    for(int i=0;i<5;i++)
    {
        printf("Phil%d     ",i+1);
    }

    printf("\n");

    #pragma omp parallel private(tnum)
    {
        tnum = omp_get_thread_num();
        int rnd;

        again:


        rnd = rand();
        rnd %= 2;



        if(rnd == 1)//Eat
        {  
            if(tnum == 0)
            {
                wait(&chopstick[(tnum+1)%5]);
                wait(&chopstick[tnum]);
            }
            else
            {
                wait(&chopstick[tnum]);
                wait(&chopstick[(tnum+1)%5]);
            }

            phil[tnum] = 1;

            #pragma omp critical
                printres(tnum, chopstick, phil);

            sleep(2);

            phil[tnum] = 0;

            release(&chopstick[tnum]);
            release(&chopstick[(tnum+1)%5]);

        }

        else //Continue Thinking
        {
            sleep(2);
            #pragma omp critical
                printres(tnum, chopstick, phil);

        }

        goto again;

    }
}