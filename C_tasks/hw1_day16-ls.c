#include <stdio.h>
#include <windows.h>
#include <string.h>
#include <sys/stat.h>
#include <winnt.h>

int main(int argc,char* argv[]){
    WIN32_FIND_DATA FindFileData;
    HANDLE hfind;
    const char* files =   {"-files"};
    const char* hidden =  {"-hidden"};
    const char* folders = {"-folders"};
    const char* help =    {"-help"};

    if ( argv[1] != '\0' && ( argv[1][ strlen(argv[1]) - 1] != '\\') ){
        strcat(argv[1],"\\*");
    }
    else if (argv[1] != '\0'){
        strcat(argv[1],"*");
    }
    
    switch(argc){
        case 1:  
            printf("Too few arguments please first enter path to folder and then option\n");
            exit(1);
        
        case 2:
            hfind = FindFirstFile(argv[1],&FindFileData);
            while(FindNextFile(hfind,&FindFileData)){
                printf("%s\n",FindFileData.cFileName);
            }    
            break;  

        case 3 :
            hfind = FindFirstFile(argv[1],&FindFileData);
            while(FindNextFile(hfind,&FindFileData)){
                if( (FindFileData.dwFileAttributes & FILE_ATTRIBUTE_HIDDEN) && !strcmp(argv[2],hidden)){ 
                    printf("%s\n",FindFileData.cFileName);
                }
                else if( (FindFileData.dwFileAttributes & FILE_ATTRIBUTE_ARCHIVE) && !strcmp(argv[2],files)){ 
                    printf("%s\n",FindFileData.cFileName);
                }
                else if( (FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) && !strcmp(argv[2],folders)){
                    printf("%s\n",FindFileData.cFileName);
                }
                else if( !strcmp(argv[2],help) ){
                    printf("Usage of the program:\n");
                    printf("<prgram name> <path to folder> <argument>\n");
                    printf("<argument> can be:\n");
                    printf("-hidden........prints only hidden files or folders\n");
                    printf("-files.........prints all files\n");
                    printf("-folders.......prints only folders\n");
                    printf("-help..........shows this message\n");
                    printf("no argument...prints all files and folders including hidden\n");
                    break;
                }

            }
            break;

        default :
            printf("Too many or incorrect arguments as an input\n");
            exit(1);
    }
    FindClose(hfind);
    return 0;
}