#include <stdio.h>
int main(void) 

{ 

    unsigned int attendance = 0; 
    unsigned int att_mask = 0;

    int option; 
    int n;
    int exit = 1;
    int check_att;

    while (exit = 1) 

    { 

        printf("1. Set attending person number\n"); 

        printf("2. Clear attending person number\n"); 

        printf("3. Attendance info\n"); 

        printf("4. Change attendance\n"); 

        printf("5. Exit\n"); 

        scanf("%d", &option); 

        if (option == 1) 

        { 

           printf("Please enter the number of the attending person:\n");
           scanf("%d",&n);
           if(n==1){
               n = 0 ;
           att_mask |= 1 << n;
           printf("%u\n",att_mask);
           }
           else if(n==32){
            n = 31;
            att_mask |= 1 << n;
            printf("%u\n",att_mask);
           }
           else if (n >=1 && n <=32)
           {
            att_mask |= 1 <<n-1;
           printf("%u\n",att_mask);   
           }
           else{
           printf("Invalid student number.\nNumber must be between 1 and 32\n");
           }
        } 

        else if (option == 2) 

        { 

           printf("Please enter the number of the absent person:\n");
           scanf("%d",&n);
           if(n==1){
           n = 0 ;
           att_mask &= ~(1 << n);
           printf("%u\n",att_mask);
           }
           else if(n==32){
            n = 31;
            att_mask &= ~(1 << n);
           }
           else if (n >=1 && n <=32)
           {
            att_mask &= ~(1 << n-1);
           printf("%u\n",att_mask);   
           }
           else{
               printf("Invalid student number.\nNumber must be between 1 and 32\n");
           }

        } 

        else if (option == 3) 

        { 

          for (n = 0; n <=31;++n){ 
          
          check_att = att_mask & (1 <<n);
          if (check_att = att_mask & (1 <<n)){
          printf("Attendant number %d is present\n", n+1);
          }
          else{
            printf("Attendant number %d is absent\n", n+1);
          }
          }
        } 

        else if (option == 4) 

        { 

           printf("Please enter the number of the person you want to change status for:\n");
           scanf("%d",&n);
           if(n==1){
                   n = 0 ;
                   att_mask ^= 1 << n;
                   printf("%u\n",att_mask);
           }
           else if(n==32){
                  n = 31;
                  att_mask ^= 1 << n;
           }
           else if (n >=1 && n <=32)
           {
                  att_mask ^= 1 << n-1;
                  printf("%u\n",att_mask); 
           }
           else{
                  printf("Invalid student number.\nNumber must be between 1 and 32\n");
           } 

           } 
           else if (option == 5){ 
                   printf("Exiting the program");
                   break;
           } 
           else{
                   printf("Invalid choice!\nChoice must be between 1 and 5!\n");
           }

    } 
    
  
}