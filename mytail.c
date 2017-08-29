#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int mytail(char *command){

    char *option1;   //filename
    char *option2;   //number
    char c;
    int line; //print line count
    int lineCount=0; //total line count

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

    //count total line
    while((c = fgetc(fp))!=EOF){
        if(c=='\n')
            lineCount++;
    }
    fclose(fp);


    fp=fopen(option1,"r");

    if(!strcmp(option2,"")){

        //print last line 5
        while((c = fgetc(fp))!=EOF){
            if(lineCount<6)
                printf("%c",c);
            if(c=='\n')
                lineCount--;
        }
    }
    else{

        //string to int
        line = atoi(option2);
        if(strcmp(option2,"0")&& line==0){
            printf("Wtong Option\n");
            return -1;
        }

        //print until last line and EOF
        while((c = fgetc(fp))!=EOF){
             if(lineCount<line+1)
                printf("%c",c);
            if(c=='\n')
                lineCount--;
        }
     
    }

    fclose(fp);
    return 0;

}
