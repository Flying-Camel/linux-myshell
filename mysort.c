#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
int counting(char *);
int cmp(const void *,const void *);
int cmpr(const void *,const void *);
int cmpb(const void *,const void *);


int mysort(char *command){

    char *option1,*fileName;
    char *pwd;
    FILE *fp;
    int count=0;

    if(!strcmp(command,"")){
        printf("ERROR : Enter File\n");
        return -1;
    }

    command[strlen(command) -1] = '\0';

    if(strstr(command," ")){
        option1 = strtok_r(command," ",&fileName);
    }
    else{  
        //no option
        fileName=command;

        //counting \n
	if((count = counting(fileName)) == -1)
		return -1;

        fp = fopen(fileName,"r");
        if(fp==NULL){
            printf("ERROR : No such file\n");
            return -1;
        }

        char str[count][10000];   //2D array for sort
        int i=0;

        //read file .. escape \n
        while(fgets(str[i++],10000,fp));

        //sort
        qsort(str,count,sizeof(str[0]),cmp);

        for(i=0;i<count;i++)
            printf("%s",str[i]);

        fclose(fp);

        return 0;
    }


    if(!strcmp(option1,"-r")){

        //counting \n
	if((count = counting(fileName)) == -1)
		return -1;

        fp = fopen(fileName,"r");
        if(fp==NULL){
            printf("ERROR : No such file\n");
            return -1;
        }

        char str[count][10000];   //2D array for sort
        int i=0;

        //read file .. escape \n
        while(fgets(str[i++],10000,fp));

        //sort
        qsort(str,count,sizeof(str[0]),cmpr);

        for(i=0;i<count;i++)
            printf("%s",str[i]);

        fclose(fp);

    }
    else if(!strcmp(option1,"-b")){
        
        //counting \n
	if((count = counting(fileName)) == -1)
		return -1;

        fp = fopen(fileName,"r");
        if(fp==NULL){
            printf("ERROR : No such file\n");
            return -1;
        }

        char str[count][10000];   //2D array for sort
        int i=0;

        while(fgets(str[i++],10000,fp));

        qsort(str,count,sizeof(str[0]),cmpb);

        for(i=0;i<count;i++)
            printf("%s",str[i]);

        fclose(fp);
    }
    else{
        printf("ERROR : Wrong Option\n");
        return -1;
    }

    return 0;
}

int counting(char fileName[]){

    int count=0;
    char c;

    FILE *p = fopen(fileName,"r");
    if(p==NULL){
        printf("ERROR : No such file\n");
        return -1;
    }

    while((c=fgetc(p)) != EOF){
        if(c=='\n')
            count++;
    }
    fclose(p);
    return count;
}
//sotring without space
int cmpb(const void*a, const void*b){

    //compare without ' ' 
    while( *(char *)a == ' ') a++;
    while( *(char *)b == ' ') b++;

    return (strcmp( (char *)a, (char *)b) );
}
//sorting reverse
int cmpr(const void*a, const void*b){
    return (strcmp( (char *)b, (char *)a) );
}
//sorting
int cmp(const void*a, const void*b){
    return (strcmp( (char *)a, (char *)b) );
}

