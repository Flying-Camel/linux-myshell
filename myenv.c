#include<stdio.h>
#include<string.h>
#include<stdlib.h>

extern char **environ;

int myenv(char *command){
    int i=0;

    command[strlen(command) -1] = '\0';

    if(!strcmp(command,"")){
	
	for(i=0;environ[i] != NULL ; i++)
	    printf("%s\n",environ[i]);

    }
    else if(strstr(command," ")){
	printf("ERROR : Wrong command\n");
	return -1;
    }
    else{
	char *tmp = getenv(command);
	if(tmp != NULL)
	    printf("%s\n",tmp);
    }

    return 0;
}
