#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct book{  
    char title[150];
    char author[100];
    int pages;  
    float price;
    struct book* next;  
};  

struct book* SortedMerge(struct book* a, struct book* b);
void FrontBackSplit(struct book* source,
                    struct book** frontRef, struct book** backRef);
 

void MergeSort(struct book** headRef)
{ 
    
    struct book* head = *headRef;
    struct book* first_sublist;
    struct book* second_sublist;

    if ((head == NULL) || (head->next == NULL)) {
        return;
    }
    
    

    FrontBackSplit(head, &first_sublist, &second_sublist);
    

    MergeSort(&first_sublist);
    MergeSort(&second_sublist);
    

    *headRef = SortedMerge(first_sublist, second_sublist);
    
}


void FrontBackSplit(struct book* source,
                    struct book** frontRef, struct book** backRef)
{
    struct book* fast;
    struct book* slow;

    slow = source;
    fast = source->next;
    
    

    while (fast != NULL) {
        
        fast = fast->next;
        if (fast != NULL) {
            slow = slow->next;
            fast = fast->next;
        } 
    }

    *frontRef = source;
    *backRef = slow->next;
    slow->next = NULL;
}
 

struct book* SortedMerge(struct book* a, struct book* b)
{
    struct book* result = NULL;

    if (a == NULL)
        return (b);
    else if (b == NULL)
        return (a);
    

    if (a->title[0] <=  b->title[0]) {
        result = a;
        result->next = SortedMerge(a->next, b);
    }
        
    else {
        result = b;
        result->next = SortedMerge(a, b->next);
    }    
    
    return (result); 
    
}


/*Function to print a linked list*/
void printList(struct book* node)
{
    
    while (node != NULL) {
        printf("Title: %s\n", node->title);
        printf("Author: %s\n", node->author);
        printf("Total pages: %d\n", node->pages);
        printf("Price: %f\n\n", node->price);
        node = node->next;
    }
}

/*Function to free taken memory for a linked list*/
void free_list(struct book* head){
    struct book* tmp;
    while( head!= NULL){
        tmp = head;
        head = head->next;
        free(tmp);
    }
}

/*Push function for a linked list of books*/
void push(struct book** head_ref,char* title,char* author,int pages,float price)
{
    /*Allocate memory*/
    struct book* new_book = (struct book*)malloc(sizeof(struct book));  
    strcpy(new_book->title,title);
    strcpy(new_book->author,author);
    new_book->pages = pages;
    new_book->price = price;
    
    
    new_book->next = *head_ref;
    
    
 
    *head_ref = new_book;
    
}



int main(){
    FILE *fptr;
    struct book curr_book;
    struct book* head_ref = NULL;
    char fname[50];
    
    printf("Please enter filename to open\n");
    if(sizeof(fname) > 50){
        printf("Error! File name must be below 50 symbols");
       // Program exits if the file name is above 50 symbols.
        exit(0);
    }

    scanf("%s",fname);
    fptr = fopen(fname,"rb");
    if (fptr == NULL){
       printf("Error! opening file");

       // Program exits if the file pointer returns NULL.
       exit(0);
    }


    while( fread(&curr_book,sizeof(struct book),1,fptr) ){
 
        struct book* new_book = (struct book*)malloc(sizeof(struct book));  
        strcpy(new_book->title,curr_book.title);
        strcpy(new_book->author,curr_book.author);
        new_book->pages = curr_book.pages;
        new_book->price = curr_book.price;


        new_book->next = head_ref;


    
        head_ref = new_book;

    }
  
    fclose(fptr);
    MergeSort(&head_ref);
    

    FILE* fptr_out;
    printf("Please enter filename of the output file it must end with .bin\n");
    scanf("%s",fname);

    fptr_out = fopen(fname,"wb");
    
    if (fptr_out == NULL){
       printf("Error! opening file");

       // Program exits if the file pointer returns NULL.
       exit(2);
    }

    while( head_ref != NULL ){

        fwrite(head_ref,sizeof(struct book),1,fptr_out);
        head_ref = head_ref->next;
    }
    
    fclose(fptr_out); 
    free_list(head_ref);

    return 0;
}