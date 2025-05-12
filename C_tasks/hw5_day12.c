#include <stdio.h>
#include <stdint.h>


const int MAX_SIZE = 500;
int arr[500];
int top = 0;
int bottom = 0;

int isEmpty(){
    if(top == 0){
        printf("The array is empty\n");
        return 0;
    }
    else{
        return 1;
    }
}
int isFull(){
    if(bottom == MAX_SIZE){
        printf("The array is full\n");
        return 0;
    }
    else{
        return 1;
    }

}
void Push(int NewValue){
    if(isFull){
        arr[top]= NewValue;
        printf("Element N%d is %d pushed\n",top,NewValue);
        top++;
    }

}

int Pop(){
    if(isEmpty){
        printf("Element N%d is %d popped\n",bottom,arr[bottom]);
        bottom--;
    }
    
}
int main(){
    isEmpty();
    Push(2);
    //Push(3);
    isEmpty();
    Pop();
    

    return 0;
}