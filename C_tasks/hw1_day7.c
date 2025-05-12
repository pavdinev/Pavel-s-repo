#include <stdio.h>
int secondMax(const int* arr, unsigned int size,int* sm){
    int i = 0;
    int max = arr[0];
    int arr_count = 0;
    for(i=0;i<=size;i++){
    if( arr[i] == 0){
    arr_count++;
    }     
    else if(arr_count == size && arr_count != 1){
           printf("The array is empty!");
    }
    else if(size == 1){
        printf("The array has only one element");
    }
    else{
            for (i=1;i<=size;i++) {
               if (max <= arr[i]) {
                max = arr[i];
                }
            }
            *sm = 0;
            i = 0;    
            while(i<=size) {
                if(*sm <= arr[i] && arr[i] != max) {
                       *sm = arr[i];                     
                }
                i++;  
            }
            printf("Second max number is: %d\n",*sm);
    }
    }        
}
int main(){
    int size = 5;
    int sm;
    int arr[]= {0,12, 34, 5, 70, 46};
    secondMax(arr,size,&sm);
    return 0;
}