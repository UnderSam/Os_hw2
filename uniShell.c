#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<stdlib.h>
#include<sys/wait.h>

#define MAX_LINE 80

int main(void){

char *args[MAX_LINE][MAX_LINE/2 + 1];
int should_run = 1;
size_t len = 0;
ssize_t nread;
int round = 0;
char *temp;
char *delim = (char *)" \n";
char *params;
int waitFor;
pid_t pid;
int status;
while(should_run){
	
	
	int token_num=0;
	printf("osh>"); 
	fflush(stdout);
	fflush(stdin);

	nread = getline(&params,&len,stdin);
	//printf("words : %s",params);
	
	waitFor = 0;
	temp = strtok(params,delim);	
	while( temp != NULL){
		
		if (strcmp("&",temp) == 0)
		{
			
			waitFor = 1;
			//printf("&&&");
			temp = strtok(NULL,delim);
			continue;
		}
		else if (strcmp("exit",temp) == 0)
		{
			should_run = 0;
			break;
		}
		//printf("%s\n",temp);
		args[round][token_num] = temp;
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
		execvp(args[round][0],args[round]);
		exit(0);
	}
	if(waitFor == 1){
		sleep(1);
		//printf("wait");
		pid = wait(&status);
		round++;
	}
	else
		round++;
}
if(params)
free(params);
return 0;
}
