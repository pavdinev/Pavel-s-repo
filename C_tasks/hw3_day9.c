#include <stdio.h>


void swap(int *arr,int idx1,int idx2,int size){
    int tmp;
    tmp = arr[idx1];
    arr[idx1] = arr[idx2];
    arr[idx2] = tmp;
    /*for (int i = 0;i<=size;i++){
        printf("%d\n",arr[i]);
    }*/   
}

void quickSort(int *arr,int stat,int end,int size){
    int pivot_idx = end;
    for (int i =0 ;i<= size-1;i++){
        if(arr[pivot_idx] <= arr[i]){
            //printf("%d %d\n",arr[pivot_idx],arr[i]);
            swap(arr,pivot_idx,i,10);
            //pivot_idx = i;
        }
        /*else if(arr[pivot_idx] >= arr[i]){
            swap(arr,pivot_idx,i,10);
            //pivot_idx = i;
        }*/
    }
}
int main(){
    int arr [] = {123,331,1,2,5,7672,1662,317,75,34,872};
    //swap (arr,2,5,10);
    quickSort(arr,0,10,10);
    for (int i = 0;i<=10;i++){
        printf("%d\n",arr[i]);
    }
    return 0;
}