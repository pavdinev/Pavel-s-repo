#include <stdio.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>

/*Moving average functuon*/
double* movingAverage(double* x_in,size_t len, size_t window ){
    /*Allocate memory for the output array initialized with zeros due to the fact that there may be leftover data inside that particular chunk of memory*/
    double *y_out = (double*) calloc(len, sizeof(double));

    /*Init the first value of the output array*/
    for (int i = 0; i < window; i++){
        y_out[i] = x_in[i];
    }
    
    /*Iterate over the whole input array */
    for (int i =  window; i <= len; i++){
        
        /*Get the current sum value. We start from j = 1 because we want the summing to start from (i - 1)st element*/
        for (int j = 1; j <= window; j++ ){
            y_out[i] = y_out[i] + x_in[i-j];
        }
        /*Divide by the window to get the average*/
        y_out[i] = y_out[i]/window;
    }

    /*Finally return pointer to the allocated array*/
    return y_out;
}
    

/* generate a random floating point number from min to max */
double randfrom(double min, double max) 
{
    double random = ((double) rand())/RAND_MAX;
    double range = (max - min) *random; 
    double number = min + range;
    return number;
}

int main(){
    srand(time(NULL));  

    /*formula for generating random number in a certain range is 
    ( rand() % (upper - lower + 1) + lower;*/
    //size_t len = rand()%(50 - 20 + 1) + 20;;
    //size_t window = rand()%(10 - 5 + 1) + 5;
    //for (int i = 0; i <= len-1; i++){
    //    x_in[i] = randfrom(-1,1);    
    //}
          
    
    size_t len = 24;
    size_t window = 4;
    double x_in[24] = {-1.00,-0.879,-0.802,-0.768,-0.713,-0.675,-0.604,-0.574,-0.513,-0.423,-0.329,-0.257,-0.122,-0.04,0.198,0.267,0.386,0.427,0.513,0.674,0.742,0.822,0.95,1.00};
    double* y_out;
    double* ptr_x = x_in;
    double y_out_check[len];
    
    y_out_check[0] =   x_in[0];
    y_out_check[1] =   x_in[1];
    y_out_check[2] =   x_in[2];
    y_out_check[3] =   x_in[3];
    y_out_check[4] =  (x_in[0] + x_in[1] + x_in[2] + x_in[3])/window;
    y_out_check[5] =  (x_in[1] + x_in[2] + x_in[3] + x_in[4])/window;
    y_out_check[6] =  (x_in[2] + x_in[3] + x_in[4] + x_in[5])/window;
    y_out_check[7] =  (x_in[3] + x_in[4] + x_in[5] + x_in[6])/window;
    y_out_check[8] =  (x_in[4] + x_in[5] + x_in[6] + x_in[7])/window;
    y_out_check[9] =  (x_in[5] + x_in[6] + x_in[7] + x_in[8])/window;
    y_out_check[10] = (x_in[6] + x_in[7] + x_in[8] + x_in[9])/window;
    y_out_check[11] = (x_in[7] + x_in[8] + x_in[9] + x_in[10])/window;
    y_out_check[12] = (x_in[8] + x_in[9] + x_in[10] + x_in[11])/window;
    y_out_check[13] = (x_in[9] + x_in[10] + x_in[11] + x_in[12])/window;
    y_out_check[14] = (x_in[10] + x_in[11] + x_in[12] + x_in[13])/window;
    y_out_check[15] = (x_in[11] + x_in[12] + x_in[13] + x_in[14])/window;
    y_out_check[16] = (x_in[12] + x_in[13] + x_in[14] + x_in[15])/window;
    y_out_check[17] = (x_in[13] + x_in[14] + x_in[15] + x_in[16])/window;
    y_out_check[18] = (x_in[14] + x_in[15] + x_in[16] + x_in[17])/window;
    y_out_check[19] = (x_in[15] + x_in[16] + x_in[17] + x_in[18])/window;
    y_out_check[20] = (x_in[16] + x_in[17] + x_in[18]+ x_in[19])/window;
    y_out_check[21] = (x_in[17]+ x_in[18] + x_in[19] + x_in[20])/window;
    y_out_check[22] = (x_in[18] + x_in[19] + x_in[20] + x_in[21])/window;
    y_out_check[23] = (x_in[19] + x_in[20] + x_in[21] + x_in[22])/window;
    
    
      
 
    
    y_out = movingAverage(ptr_x,len,window);
    
    for (int i = 0; i < len;i++){
        printf("y_out[%d] %lf\n",i,y_out[i]);
        printf("y_out_check[%d] %lf\n",i,y_out_check[i]);
    }

    free(y_out);
    

    return 0;
}