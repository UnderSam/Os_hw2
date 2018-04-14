#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<stdlib.h>
#include<sys/wait.h>

#define MAX_LINE 80
char *args[MAX_LINE/2 + 1];
char history[MAX_LINE][MAX_LINE/2 + 1];

void Show_history(int round){
	
	
	int flag = 1;
	int i,j;
	for(i = 0;i<round;i++){
	   
		printf("%d : ",i+1);
		printf("%s",history[i]);   
		
		flag = 0;
	}
	if(flag)printf("no commands in history\n");
	return;
}

int main(void){

int should_run = 1;
size_t len = 0;
ssize_t nread;
int round = 0;
char *temp;
char *delim = (char *)" \n";
char *params = (char *) malloc(100);
int waitFor;
pid_t pid;
int status;
long unsigned hist_exec;
while(should_run){
	
	
	int token_num=0;
	printf("osh>"); 
	fflush(stdout);
	fflush(stdin);

	nread = getline(&params,&len,stdin);
	//printf("count : %ld words : %s",nread,params);
	if(nread == 1)
	    continue;
	if(nread >= 3 && strcmp("!!\n",params) != 0 && strstr(params, "!")!=NULL)
	{
	    params[0] = '0';
	    params[strlen(params) - 1] = '\0';
	    printf("locate : %d\n",atoi(params));
	    hist_exec = atoi(params);
	    if(hist_exec > 50)hist_exec = 50;
	    else if(strlen(history[hist_exec-1]) == 0){
		printf("No such command in history.\n");
		continue;   	    
	    }
	    else{
		params = history[hist_exec-1];
		}	
	}	
	if (strcmp("history\n",params) != 0)
	{
		strcpy(history[round],params);
	}
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
		else if (strcmp("history",temp) == 0)
		{
			Show_history(round);
			round--;
			break;
		}
		else if (strcmp("!!",temp) == 0)
		{
			char* oldParam = (char *)history[round--];
			//printf("params  = %s",oldParam);
			temp = strtok(oldParam,delim);
			continue;
		}
		else if (strcmp("",temp) == 0)
		{
			continue;
		}
		
		args[token_num] = temp;
		
		//printf("args[%d][%d] = %s\n",round,token_num,args[round][token_num]);
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
