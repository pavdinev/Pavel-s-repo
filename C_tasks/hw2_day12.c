#include <stdio.h>

void swap(char* idx1,char* idx2){
    char tmp = *idx1;
    *idx1 = *idx2;
    *idx2 = tmp;
}
void Reverse(char* ptr){
    int count_size = 0;
    while(*ptr != '\0'){
        count_size++;
        ptr++;
    }
    ptr = ptr-count_size;
    for(int j = 0;j <= (count_size/2)+1;j++){
    swap(ptr+j,(ptr+count_size-1)-j);
    //printf("%d\n",ptr);  
    }
    while(*ptr != '\0'){
        printf("%c\n",*ptr);
        ptr++;
    }
}   
int main(){
    char test_str [] = {"This is a test"};
    Reverse(test_str);
    return 0;
}