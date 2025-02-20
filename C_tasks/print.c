#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

char* rand_string(char* rand_str,int max_letters)
{
    /*
    formula for generating random number in a certain range is 
    ( rand() % (upper - lower + 1)) + lower;
    */

    /*static constant for the whole English alphabet*/
    static const char letters[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";

    /*Initialize array with length max_letters+1 for the \0 */
    rand_str[max_letters+1];

    /*Random index between 0 and 25 pointing only to upprcase letters.*/
    int random_index = rand() % (25 - 0 + 1) + 0;

    /*Initialize the first element from rand_str to be uppercase letter*/
    rand_str[0] = letters[random_index];

    /*Iterate the whole rand_str starting from 1 (rand_str[0] is already uppercase) to max_letters and fill with random lowercase letters*/
    for (int i = 1; i <= max_letters ;i++){
        random_index = rand() % (51 - 26 + 1) + 26;
        rand_str[i] = letters[random_index];
    }

    /*Terminate rand_str with \0*/
    rand_str[max_letters+1] = '\0';
    
    /*return pointer to rand_str*/
    return rand_str;
}

int main(){
    srand(time(NULL));
    int max_letters = 15;
    char ptr1[max_letters];
    rand_string(ptr1, max_letters);
    printf("%s\n",ptr1);
    return 0;
}