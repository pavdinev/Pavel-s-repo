#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void SPRINTF(char* szBuffer, char *szPattern, char** args){
    char* search_str = "%s";
    int i = 0;
    while(*szPattern != '\0'){
        if((*szPattern == *search_str) && (*szPattern+1 == *search_str+1) ){
            *szPattern++;
            for (int j = 0 ; j <= strlen(args[i])-1 ;j++){
                *szBuffer= *(args[i]+j);
                szBuffer++;
            }
            szPattern++;
            i++;
        }
        else{
            *szBuffer = *szPattern;
            szBuffer++;
            szPattern++;
        }      
    }    
}
    
int main(){
    
    char* args[ ] = {"2563","Kaput"};
    char szPattern [] = "This function takes %s and %s as arguments\n";
    char szBuffer[48];
    SPRINTF(szBuffer,szPattern,args);
    printf("%s",szBuffer);           
    return 0;
}