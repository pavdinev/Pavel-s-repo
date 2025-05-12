#include <stdio.h>
#include <stdlib.h>
int main(int argc, char *argv[]){
    
    if ( argc !=2){
        printf("Please provide only filename as parameter\n");
        exit(1);
    }
    else{
        FILE* in_file;
        char symb;
        in_file = fopen(argv[1],"r");
        int line_count = 0;
        if (in_file != NULL){
            while ( ((symb = fgetc(in_file)) != EOF) && line_count < 10){
                if (symb == '\r' || symb == '\n'){
                    line_count++;
                }
                printf("%c",symb);
                

            }
            fclose(in_file);
        }
        else{
            printf("Error opening file\n");
        }

    }

    return 0;
}