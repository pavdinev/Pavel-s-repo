#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
#include <libgen.h>
#include <string.h>


int isFile(const char *path)
{
    struct stat path_stat;
    stat(path, &path_stat);
    return S_ISREG(path_stat.st_mode);
}

int isDir(const char *path) {
   struct stat statbuf;
   if (stat(path, &statbuf) != 0)
       return 0;
   return S_ISDIR(statbuf.st_mode);
}

int main(int argc, char *argv[]){
    //if (argc != 1){
    //    printf("Please input destion and source for copy\n");
    //    exit(0);
    //}

    FILE* source;
    FILE* destination;
    source = fopen(argv[1],"r");

    if (source == NULL){
        printf("Error opening source\n");
        exit(0);
    }

    if (isDir(argv[2]) == 0){
        mkdir(argv[2]);
    }
    destination = fopen(strcat(argv[2],basename(argv[1])),"w");
    if (destination == NULL){
        printf("Error opening destination\n");
        exit(0);
    }
    

    fseek(source,0,SEEK_END);
    int source_length = ftell(source);
    char buffer[source_length];
    fseek(source,0,SEEK_SET);
    int in;
    while(in = fread(buffer,1,256,source) ){
        fwrite(buffer,1,in,destination);
    }
    fclose(source);
    fclose(destination);
    remove(argv[1]);
    return 0;
}