#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define COUNT 9

struct book{  
    char title[150];
    char author[100];
    int pages;  
    float price;
    struct book* next;  
};  

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

void push(struct book** head_ref,char* title,char* author,int pages,float price)
{
    struct book* new_book = (struct book*)malloc(sizeof(struct book));  
    strcpy(new_book->title,title);
    strcpy(new_book->author,author);
    new_book->pages = pages;
    new_book->price = price;
    

    new_book->next = (*head_ref);
    
    
 
    (*head_ref) = new_book;
}

      
void free_list(struct book* head){
    struct book* tmp;
    while( head!= NULL){
        tmp = head;
        head = head->next;
        free(tmp);
    }
}


int main(){
    srand(time(NULL));  
    int title_size = rand()%(20-10+1)+10;
    char title [COUNT][title_size];
    char author[COUNT][title_size];     
    struct book* a = NULL;

    /*formula for generating random number in a certain range is 
    ( rand() % (upper - lower + 1)) + lower;*/
    for (int i = 0; i <= COUNT; i++ ){       
        rand_string(title[i],title_size);
        rand_string(author[i],title_size);
        int pages = (rand() % (2000 - 5 + 1)) + 5;
        float price = (1000.00 - 1.00) * ((float)rand() / RAND_MAX) + 1.00;       
        push(&a,title[i],author[i],pages,price); 
    }

    //printf("\nUnsorted Linked List after is: \n\n");
    //printList(a);
    MergeSort(&a);
    //printf("\nSorted Linked List is: \n\n");
    //printList(a);
    printList(a);
    free_list(a);
    return 0;
}
