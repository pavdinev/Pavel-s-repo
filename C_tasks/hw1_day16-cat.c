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
        if (in_file != NULL){
            while ( (symb = fgetc(in_file)) != EOF ){
                
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