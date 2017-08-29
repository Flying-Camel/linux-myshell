#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int myset(char *command){

    char *path = {"PATH\0"};
    char *option;
    char *list;
    char *tmp;

    //remove \n
    command[strlen(command) -1] = '\0';

    if(strstr(command," ")){
	tmp = strtok_r(command," ",&option);

	//torkernize command
	if(strcmp(path,tmp)){
	    printf("ERROR : arg1 is not PATH\n");
	    return -1;
	}

	if(!strstr(option," ")){
	    printf("ERROR : Wrong Option\n");
	    return -1;
	}
	else
	    option = strtok_r(option," ",&list);

    }
    else{
	printf("ERROR : No Path\n");
	return -1;
    }

    //option -n
    if(!strcmp(option,"-n")){

	if(setenv(path,list,1)){
	    printf("ERROR : set evnvy error\n");
	    return -1;
	}
    }
    //option -a
    else if(!strcmp(option,"-a")){

	//tmp for env
	char *tmp = getenv(command);
	char *addList = (char *)malloc(100);

	strcat(addList,tmp);
	strcat(addList,":");
	strcat(addList,list);

	if(setenv(path,addList,1)){
	    printf("ERROR : set evnvy error\n");
	    return -1;
	}

	free(addList);
    }
    else{
	printf("ERROR : Wrong Option\n");
	return -1;
    }

    return 0;

}
