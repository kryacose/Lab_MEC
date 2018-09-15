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

int main()
{   
    int mutex = 1, buffer = 0, n = 5 , tnum;
    omp_set_num_threads(2);
    srand(time(0));
    #pragma omp parallel private(tnum)
    {
        tnum = omp_get_thread_num();
        int rnd;

        procon:

        rnd = rand();
        rnd %= 2;
        

        if(rnd == 1 && (tnum*n != buffer))
        {
            if(wait(&mutex))
            {
                buffer += (2*tnum - 1);
            }
            release(&mutex);
            #pragma omp crtical
            {

            for(int i=0;i<buffer;i++) printf("#");
            for(int i=0;i<n-buffer;i++) printf("_");
            (tnum == 1)? printf("   Produce\n") : printf("   Consume\n");

            }
        }
       
        sleep(1);
        goto procon;
    }
}
