#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<pthread.h>

long long int Fib[10000];

void *Thread(void* args)
{
    int true_value = *((int *) args);
    int i;
    printf("Argument is %d , waiting for Answer...\n",true_value);
    Fib[0]=0;Fib[1]=1;
    for(i=2;i<true_value;i++)
	Fib[i] = Fib[i-1]+Fib[i-2];
}

int main(int argc,char* argv[])
{
    pthread_t fib;
    int i;
    int *Data = malloc(sizeof(*Data));
    if(argc<2){
	fprintf(stderr,"must have 1 arguments\n");
	exit(1);
    }    
    
    *Data = atoi(argv[1]);
    if(*Data>10000) 
        *Data=10000;
    //printf("Argument is %d , waiting for Answer...\n",*Data);
    int ret;
    ret = pthread_create(&fib,NULL,(void*)Thread,Data);
    if(ret!=0)
    {
	fprintf(stderr,"create thread error");
	exit(1);
    }
    pthread_join(fib,NULL);
    printf("answer of Fibonacci %d is: ",*Data);
    for(i=0;i<*Data;i++){
	if(i==0)
	  printf("%lld",Fib[i]);
	else 
	  printf(", %lld",Fib[i]);
    }
    puts("\n");
    free(Data);
    return 0;
}
