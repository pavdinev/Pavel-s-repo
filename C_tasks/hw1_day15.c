#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define COUNT 9

/*Declare struct of type book*/
struct book{  
    char title[150];
    char author[100];
    int pages;  
    float price;
    struct book* next;
};  

/*Random string function will always start from capital letter and continie on with small letters*/
void rand_string(char* ptr,int max_letters)
{
    /*
    formula for generating random number in a certain range is 
    ( rand() % (upper - lower + 1)) + lower;
    */
    static const char letters[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
    char rand_str[max_letters];
    int random_index = rand() % (25 - 0 + 1) + 0;
    rand_str[0] = letters[random_index];
    if(rand_str == NULL){
        printf("Error allocating memory.\n");
        exit(0);
    }
    for (int i = 1; i < max_letters ;i++){
        random_index = rand() % (51 - 26 + 1) + 26;
        rand_str[i] = letters[random_index];
    }
    rand_str[max_letters] = '\0';
    strcpy(ptr,rand_str);
}





int main(){

    /*Declare variables*/
    struct book store[COUNT];
    int title_size = rand()%(20-10+1)+10;
    int pages;
    float price; 

    
    /*Fill up the array of structs of type book with numbers*/
    for (int i = 1; i <= COUNT; i++ ){      
        rand_string(store[i-1].title,title_size);
        rand_string(store[i-1].author,title_size);
        store[i-1].pages = (rand() % (2000 - 5 + 1)) + 5;
        store[i-1].price = (1000.00 - 1.00) * ((float)rand() / RAND_MAX) + 1.00;  
    }

    /*Declare pointer for opening a file for writting and creating a variable with user input for file name*/
    FILE *file_ptr_bin;
    FILE *file_ptr_txt;
    char fname[50];
    printf("Please enter filename it must end with .bin\n");
    scanf("%s",fname);
    file_ptr_bin = fopen(fname,"wb");
    file_ptr_txt = fopen("store.txt","w");

    /*Writing the store array and closing the file*/
    for (int i = 0; i < COUNT;i++){
    fprintf(file_ptr_txt,"Title: %s\n",store[i].title);
    fprintf(file_ptr_txt,"Author: %s\n",store[i].author);        
    fprintf(file_ptr_txt,"Pages count: %d\n",store[i].pages);
    fprintf(file_ptr_txt,"Price: %lf\n",store[i].price);
    fprintf(file_ptr_txt,"\n");
    fwrite(&store[i],sizeof(struct book),1,file_ptr_bin);
    
    }
    //fwrite(&store,sizeof(store),1,file_ptr_bin);
    /*Close bin and txt files*/
    fclose(file_ptr_txt);
    fclose(file_ptr_bin);
    return 0;
}