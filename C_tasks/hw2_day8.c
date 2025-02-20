#include <stdio.h>
#include <stdlib.h>

void recursion(int *arr,int size,int start_point){
    static int count = 0;
    int check_arr[size];
    int tmp_digit;
    tmp_digit = arr[start_point];
    int stored_sum = 0;
    check_arr[count] = start_point;
    while(tmp_digit){
        stored_sum = stored_sum + tmp_digit %10;
        tmp_digit /=10;
    }
    if(stored_sum % 2 == 0){    
        if( (start_point +3) > 0 && (start_point + 3 < size)){
            start_point = start_point + 3;
            printf("1: %d %d\n",check_arr[count],start_point); 
            for (int i = 0; i <= count ;i++){
                printf("1i is :%d\n",i);
                if(check_arr[i] == start_point){
                printf("kaput2 %d %d\n",check_arr[i],start_point);              
                }
            }
            count++;
            recursion(arr,size,start_point);
            return;
        }
    }
        else{
            if((start_point-2 > 0) && (start_point-2 < size)){
                start_point = start_point - 2;
                //printf("2: %d %d\n",check_arr[count],start_point);
                for (int i = 0; i <= count ;i++){
                    //printf("2i is: %d\n",i);
                    if(check_arr[i] == start_point){
                    //printf("kaput2 %d %d\n",check_arr[i],start_point);              
                    }
                }
                count++;
                recursion(arr,size,start_point);  
                return;
            }
        }            
printf("Exit after %d iterations\n",count);
}

int main(){

    int arr [] = {71,14,90,26,11,63,81,52};

    recursion(arr,8,0);

   

    return 0;

}