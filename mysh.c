#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<signal.h>

#define MAX_PATH    100
#define MAX_COMMAND 50

void handler(int signo){
    if(signo==SIGINT)
        printf("\nSIGINT\n");
}

void setenvironment(){
    char *pwd = (char *)malloc(100);
    char *envi;

    //get current path
    getcwd(pwd,100);
    envi=getenv("PATH");
    //add path
    sprintf(envi,"%s:%s",envi,pwd);

    //set path
    setenv("PATH",envi,1);
}

void help(char str[]){

    if(!strcmp(str,"myset")){
        printf("|====================================================|\n");
        printf("|This Command is for set environment                 |\n");
        printf("|myset PATH [option] [path]                          | \n");
        printf("|-n option : overwrite path                          |\n");
        printf("|-a option : add new path at the end of PATH         |\n");
        printf("|path is string                                      |\n");
        printf("|====================================================|\n");
    }
    else if(!strcmp(str,"myenv")){
        printf("|====================================================|\n");
        printf("|This Command is for get environment                 |\n");
        printf("|myenv [STRING]                                      | \n");
        printf("|get env using STRING                                |\n");
        printf("|====================================================|\n");

    }
    else if(!strcmp(str,"myps")){
        printf("|====================================================|\n");
        printf("|This Command is Show Current Process                |\n");
        printf("|<UID> <PID> <PPID> <PGID> <SID> <STIME> <TIME> <CMD>| \n");
        printf("|====================================================|\n");

    }
    else if(!strcmp(str,"myjobs")){
        printf("|====================================================|\n");
        printf("|This Command is for Print Background Process        |\n");
        printf("|[order] [process state] [CMD]                       | \n");
        printf("|====================================================|\n");
    }
    else if(!strcmp(str,"mycd")){
        printf("|====================================================|\n");
        printf("|This Command is for Change Directory                |\n");
        printf("|mycd [FILENAME]                                     | \n");
        printf("|change directory to FILENAME                        |\n");
        printf("|if no FILENAME or ~, go to home directory           |\n");
        printf("|====================================================|\n");

    }
    else if(!strcmp(str,"mypwd")){

        printf("|====================================================|\n");
        printf("|This Command is for Print current Path              |\n");
        printf("|====================================================|\n");
    }
    else if(!strcmp(str,"myls")){
        printf("|====================================================|\n");
        printf("|This Command is for print list of files/directories |\n");
        printf("|myls [option]  [FILENAME]                                     | \n");
        printf("|list FILENAME                                       |\n");
        printf("|-a option : print hidden file                       |\n");
        printf("|====================================================|\n");
    }
    else if(!strcmp(str,"mycat")){
        printf("|====================================================|\n");
        printf("|This Command is for print file                      |\n");
        printf("|mycat [FILENAME] [number]                           | \n");
        printf("|number can be skip                                  |\n");
        printf("|print file at number byte                           |\n");
        printf("|====================================================|\n");
    }
    else if(!strcmp(str,"myhead")){
        printf("|====================================================|\n");
        printf("|This Command is for print first 5line               |\n");
        printf("|myhead [FILENAME] [number]                          | \n");
        printf("|print [number]line at first                         |\n");
        printf("|====================================================|\n");
    }
    else if(!strcmp(str,"mytail")){
        printf("|====================================================|\n");
        printf("|This Command is for print last 5line                |\n");
        printf("|mytail [FILENAME] [number]                          | \n");
        printf("|print last [number] line                            |\n");
        printf("|====================================================|\n");
    }
    else if(!strcmp(str,"mysort")){
        printf("|====================================================|\n");
        printf("|This Command is for sotring file content by line    |\n");
        printf("|mysort [FILENAME]                                   | \n");
        printf("|-b option is ignore space                           |\n");
        printf("|-r option is sotring reverse                        |\n");
        printf("|====================================================|\n");
    }
    else if(!strcmp(str,"mycp")){
        printf("|====================================================|\n");
        printf("|This Command is for Copy File                       |\n");
        printf("|mycp [SOURCE] [DEST]                                | \n");
        printf("|copy file from [SOURCE] at [DEST]                   |\n");
        printf("|if already exist at DEST, It's fail                 |\n");
        printf("|====================================================|\n");
    }
    else if(!strcmp(str,"mymkdir")){
        printf("|====================================================|\n");
        printf("|This Command is for Make Directory                  |\n");
        printf("|mymkdir [DIRECTORY]                                 | \n");
        printf("|mymkdir -p [PATH]                                   |\n");
        printf("|-p option : make all directory for path             |\n");
        printf("|====================================================|\n");
    }
    else if(!strcmp(str,"myrm")){
        printf("|====================================================|\n");
        printf("|This Command is for remove file or directory        |\n");
        printf("|myrm [FILENAME]                                     | \n");
        printf("|myrm -rf [FILENAME]                                 |\n");
        printf("|remove file. it will be fail remove directory       |\n");
        printf("|-rf option : can remove directory if it has files   |\n");
        printf("|====================================================|\n");
    }



}

int main()
{

    char *shell = (char *)malloc(MAX_PATH); 
    char *tmp = (char *)malloc(MAX_PATH);
    char *command = (char *)malloc(MAX_COMMAND);
    char *command2;
    int parentId = getpid();

    signal(SIGINT, (void *)handler);

    //set environment
    setenvironment();

    printf("\n|-----------------<COMMAND>-----------------|\n");
    printf("|myset(O)   myenv(O)   myps(O)   myjobs(O)  |\n");   
    printf("|mypwd(O)   myls(O)    mycat(O)  myhead(O)  |\n");   
    printf("|mytail(O)  mysort(O)  mycp(O)   mymkdir(O) |\n");   
    printf("|myrm(O)    mycd(O)                         |\n");   
    printf("|-------------------------------------------|\n\n");

    while(1){       

        getcwd (shell, MAX_PATH); 

        tmp=strtok(shell,"/");
        while(tmp=strtok(NULL,"/"))
            strcpy(shell,tmp);

        if(shell != 0)
            printf("[20122382 %s]$ ",shell);

        fgets(command,MAX_COMMAND,stdin);
        if(command[0] == ' '){
            printf("ERROR : Wrong Command\n");
            continue;
        }

        //if command is exit or EOF
        if(!strcmp(command,"exit\n") || feof(stdin)){
            printf("SHELL CLOSE\n");
            return 0;
        }

        //sigint
        if(!strcmp(command,"")){
            strcpy(command,"");
            continue;
        }

        //user do not nothing
        if(!strcmp(command,"\n"))
            continue;
        char *bs;
        if(bs=strstr(command,"&")){
            if(2!=strlen(bs)){
                printf("ERROR : Wrong usagse '&'");
                continue;
            }

        }

        fflush(stdin);

        command = strtok_r(command," |\n",&command2);

        int pid=-1,pid2=-1,pid3=-1;
        pid = fork();

        if(pid == -1){
            printf("ERROR : Fork Error");
            return -1;
        }
        else if(pid ==0){

            //background processing
            if(strstr(command2,"&")){
                pid2=fork();

                if(pid2 > 0){
                    exit(0);
                }
                else if(pid2 == 0){
                    pid3 = fork();

                    if(pid3<0)
                        exit(0);

                    else if(pid3 == 0){
                        printf("background processing...\n");
                        char *c = strstr(command2,"&");
                        //delete character &
                        strcpy(c,c+1);
                        c[strlen(c)-1]='\0';
                    }
                    else{
                        wait(NULL);
                        printf("\n%d is complete",pid3);
                        exit(0);
                    }
                }
                else{
                    printf("ERROR : Fork Error");
                    exit(0);
                }

            }

            if(!strcmp(command,"mycat")){
                if(strstr(command2,"--help")){
                    help(command);
                    continue;
                }
                mycat(command2);

            }
            else if(!strcmp(command,"myps")){
                if(strstr(command2,"--help")){
                    help(command);
                    continue;
                }

                myps(command2);
            }
            else if(!strcmp(command,"mypwd")){
                if(strstr(command2,"--help")){
                    help(command);
                    continue;
                }

                mypwd(command2);
            }
            else if(!strcmp(command,"mycp")){
                if(strstr(command2,"--help")){
                    help(command);
                    continue;
                }

                mycp(command2);
            }
            else if(!strcmp(command,"mymkdir")){
                if(strstr(command2,"--help")){
                    help(command);
                    continue;
                }

                mymkdir(command2);
            }
            else if(!strcmp(command,"myls")){
                if(strstr(command2,"--help")){
                    help(command);
                    continue;
                }

                myls(command2);
            }
            else if(!strcmp(command,"myhead")){
                if(strstr(command2,"--help")){
                    help(command);
                    continue;
                }

                myhead(command2);
            }
            else if(!strcmp(command,"mytail")){
                if(strstr(command2,"--help")){
                    help(command);
                    continue;
                }

                mytail(command2);
            }
            else if(!strcmp(command,"myrm")){
                if(strstr(command2,"--help")){
                    help(command);
                    continue;
                }

                myrm(command2);
            }
            else if(!strcmp(command,"mysort")){
                if(strstr(command2,"--help")){
                    help(command);
                    continue;
                }

                mysort(command2);
            }
            else if(!strcmp(command,"myenv")){
                if(strstr(command2,"--help")){
                    help(command);
                    continue;
                }

                myenv(command2);
            }
            else if(!strcmp(command,"myjobs")){
                if(strstr(command2,"--help")){
                    help(command);
                    continue;
                }
                myjobs(command2,parentId);
            }
            else{
                if(strcmp(command,"mycd") && strcmp(command,"myset"))
                    printf("Wrong Command\n");
            }

            if(pid3==0){
                //confirm background
                sleep(30);
                exit(0);
            }

            strcpy(command,"");
            return 0;
        }
        else if(pid>0){

            if(!strcmp(command,"mycd")){
                if(strstr(command2,"--help")){
                    help(command);
                    continue;
                }
                mycd(command2);
            }
            else if(!strcmp(command,"myset")){
                if(strstr(command2,"--help")){
                    help(command);
                    continue;
                }

                myset(command2);
            }

            wait();
        }

    }

    free(tmp);
    free(command);
    free(shell);

    return 0;
}

