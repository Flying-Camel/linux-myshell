#include<stdio.h>
#include<stdlib.h>
#include<string.h>


int myhead(char *command){

    char *option1;   //filename
    char *option2;   //number
    char c;
    int line;

    option1 = strtok_r(command," ",&option2);

    //option check
    if(strstr(option2," ") || !strcmp(command,"")){
        printf("Wtong Option\n");
        return -1;
    }

    if(option1[strlen(option1) -1]=='\n')
        option1[strlen(option1) - 1] = '\0';
    option2[strlen(option2) -1]='\0';

    FILE *fp=fopen(option1,"r");

    if(fp==NULL){
        printf("ERROR : no exit file\n");
        return -1;
    }
    else{
        if(!strcmp(option2,"")){

            //print line 5
            int count=0;
            while((c = fgetc(fp))!=EOF){
                printf("%c",c);
                if(c=='\n')
                    count++;
                if(count==5)
                    break;
            }
        }
        else{

            //string to int
            line = atoi(option2);
            if(strcmp(option2,"0")&& line==0){
                printf("Wtong Option\n");
                return -1;
            }

            //print until line and EOF
            int count=0;
            while((c = fgetc(fp)) != EOF){
                printf("%c",c);
                if(c=='\n')
                    count++;
                if((count==line))
                    break;
            }

            printf("\n");
        }
    }

    fclose(fp);

    return 0;

}
