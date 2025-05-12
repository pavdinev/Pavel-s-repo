#include <stdio.h>
#include <stdint.h>
#include <string.h>
void reverse(char s[],int len){
    int i,j;
    char tmp;
    for (i = 0,  j = len-1; i<j ; i++, j--){
    tmp = s[i];
    s[i] = s[j];
    s[j] = tmp;   
    }
}
void Conv(int sValue,char *pBuffer){
    int neg_flag = 0;
    if (sValue < 0){
        neg_flag = 1;
        sValue = -sValue;
    }
    int i = 0;
    while(sValue != 0){
        pBuffer[i++] = sValue%10 + '0';
        sValue /= 10;            
    }
    if(neg_flag){
    pBuffer[i++] = '-';
    }
    pBuffer[i] = '\0';
    reverse(pBuffer,strlen(pBuffer));
    printf("%s\n",pBuffer);
}
int main(){
    int16_t sValue =-1425;
    char pBuffer[15];
    Conv(sValue,pBuffer);
    return 0;
}