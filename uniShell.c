#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<stdlib.h>
#include<sys/wait.h>

#define MAX_LINE 80

int main(void){

char *args[MAX_LINE/2 + 1];
int should_run = 1;
size_t len = 0;
ssize_t nread;
int round = 0;
char *temp;
char *delim = (char *)" \n";
char *params;
int waitFor;
pid_t pid;
while(should_run){
	waitFor = 0;
	
	int token_num=0;
	printf("osh>"); 
	fflush(stdout);
	fflush(stdin);

	nread = getline(&params,&len,stdin);
	//printf("words : %s",params);
	
	
	temp = strtok(params,delim);	
	while( temp != NULL){
		
		if (strcmp("&",temp) == 0)
		{
			waitFor = 1;
			temp = strtok(NULL,delim);
			token_num++;
			continue;
		}
		else if (strcmp("exit",temp) == 0)
		{
			should_run = 0;
			break;
		}
		//printf("%s\n",temp);
		args[token_num] = temp;
		temp = strtok(NULL,delim);
		token_num++;
		}
	pid = fork();
	if( pid < 0 ){
		fprintf(stderr,"Fork Failed");
		exit(-1);
	}
	else if( pid ==0 ){
		//printf("%s ????",args[0]);
		execvp(args[0],args);
	}
	

	if(waitFor == 1)
		wait(NULL);
}
if(params)
free(params);
return 0;
}
