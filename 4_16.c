#include<stdio.h>
#include<unistd.h>
#include<pthread.h>
#include<string.h>
#include<stdlib.h>
#include<limits.h>
struct compute_number_struct{
    int numbers[100];
    int size;
} ;

struct compute_number_struct args;
void Average(void){
    
    int sum,i;
    for(i=0;i<args.size;i++)
	sum+=args.numbers[i];
    printf("average is %f.\n",(double)sum/args.size);
    return ;
}
void Maximum(void){
    
    int i,max = INT_MIN;
    for(i=0;i<args.size;i++)
	if(args.numbers[i] > max)
	    max = args.numbers[i];	
    printf("Maximum is %d.\n",max);
    return ;
}
void Minimum(void){
   
    int i,min = INT_MAX;
    for(i=0;i<args.size;i++)
	if(args.numbers[i] < min)
	    min = args.numbers[i];
    printf("Minimum is %d.\n",min);
    return ;
}
int main(int argc,char* argv[])
{
	
	
	pthread_t ave_t,max_t,min_t;
	
	int i;
	
	for(int i=0;i<argc-1;i++)
	{
	    args.numbers[i] = atoi(*++argv);
	    //printf("%d\n",args.numbers[i]);
	    args.size++;
	}
	
	
	pthread_create(&ave_t,NULL,(void *)Average,NULL);
	pthread_create(&max_t,NULL,(void *)Maximum,NULL);
	pthread_create(&min_t,NULL,(void *)Minimum,NULL);
		
	
	if ( pthread_join(ave_t,NULL) !=0)
	    fprintf(stderr,"Thread join error");
	if ( pthread_join(min_t,NULL) !=0)
	    fprintf(stderr,"Thread join error");
	if ( pthread_join(max_t,NULL) !=0)
	    fprintf(stderr,"Thread join error");
	//puts("parent");
	return 0;
}

