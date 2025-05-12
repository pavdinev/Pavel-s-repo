#include <stdio.h>
#include <stdlib.h>

struct Node{  
    struct Node* prev;
    int data;  
    struct Node* next;  
};  


void add_front(struct Node** curr_node, int new_data){
    struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));
    if (new_node == NULL){
        printf("Error allocating memory\n");
        exit(0);
    }

    new_node->data = new_data;

    new_node->next = *curr_node;
    new_node->prev = NULL;

    if((*curr_node) != NULL){
        (*curr_node)->prev = new_node;
    }

    (*curr_node) = new_node;
}

void add_back(struct Node** curr_node, int new_data){
    struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));

    if (new_node == NULL){
        printf("Error allocating memory\n");
        exit(0);
    }

    struct Node* last = *curr_node;
    new_node->data = new_data;

    
    new_node->next = NULL;

    if((*curr_node) == NULL){
        new_node->prev = NULL;
        *curr_node = new_node;
        return;
    }
    while(last->next != NULL){
        last = last->next;
    }
    last->next = new_node;
    new_node->prev = last;
    return;
}

void free_list(struct Node* head){
    struct Node* tmp;
    while( head!= NULL){
        tmp = head;
        head = head->next;
        free(tmp);
    }
}

void del_node(struct Node** first_node,struct Node* node){
    
    if(node->prev == NULL){
        (*first_node)= node->next;
    }

    if (node->next == NULL){
        node->prev->next = NULL;
    }

    if( (node->prev != NULL) && (node->next != NULL)){
        node->prev->next = node->next;
        node->next->prev = node->prev;
    }
    free(node);       
}

void printList(struct Node* node)
{
    
    while (node != NULL) {
        printf("Data is: %d\n", node->data);
        node = node->next;
    }
}

int main(){
    struct Node* something = NULL;
    add_front(&something,13);
    add_back(&something,5);
    add_back(&something,10);
    //printList(something);
    //printf("%d",something->next->next->data);
    
    del_node(&something,something->next);
    printList(something);
    free_list(something);
    return 0;
}