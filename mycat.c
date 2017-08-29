#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int mycat(char *command){

    char *option1;
    char *option2;
    char c;
    int byte;

    //torkernize command option1 and option2
    //option1 has file name and option2 has byte
    option1 = strtok_r(command," ",&option2);

    if(strstr(option2," ") || !strcmp(command,"")){
        printf("Wtong Option\n");
        return -1;
    }

    if(option1[strlen(option1) -1]=='\n')
        option1[strlen(option1) - 1] = '\0';
    option2[strlen(option2) -1]='\0';

    //file open
    FILE *fp=fopen(option1,"r");

    if(fp==NULL){
        printf("ERROR : no exit file\n");
        return -1;
    }
    else{
        if(!strcmp(option2,""))
            while((c = fgetc(fp)) != EOF)
                printf("%c",c);

        else{
	        //get byte
            byte = atoi(option2);

	        //print while byte
            if(strcmp(option2,"0")&& byte==0){
                printf("Wtong Option\n");
                return -1;
            }

            int i;
            for(i=0;i<byte;i++){
                if((c = fgetc(fp)) != EOF)
                    printf("%c",c);
            }
            printf("\n");
        }
    }

    fclose(fp);

    return 0;

}
