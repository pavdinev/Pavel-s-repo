#include<stdio.h>
#include<fcntl.h>
#include<errno.h>
extern int errno;
#include<string.h>
#include<stdlib.h>
#include<stdarg.h>

//int pfprintf (FILE* fp, const char *format)
//{
//    
//    HANDLE hFile; 
//    char DataBuffer[] = "This is some test data to write to the file.";
//    DWORD dwBytesToWrite = (DWORD)strlen(DataBuffer);
//    DWORD dwBytesWritten = 0;
//    BOOL bErrorFlag = FALSE;
//
//    hFile = CreateFile(fp,                     // name of the write
//                       GENERIC_WRITE,          // open for writing
//                       0,                      // do not share
//                       NULL,                   // default security
//                       CREATE_NEW,             // create new file only
//                       FILE_ATTRIBUTE_NORMAL,  // normal file
//                       NULL);                  // no attr. template
//
//    if (hFile == INVALID_HANDLE_VALUE) 
//    { 
//        _tprintf(TEXT("Terminal failure: Unable to open file \"%s\" for write.\n"), fp);
//        exit(1);
//    }
//
//    _tprintf(TEXT("Writing %d bytes to %s.\n"), dwBytesToWrite, fp);
//
//    bErrorFlag = WriteFile( 
//                    hFile,           // open file handle
//                    DataBuffer,      // start of data to write
//                    dwBytesToWrite,  // number of bytes to write
//                    &dwBytesWritten, // number of bytes that were written
//                    NULL);            // no overlapped structure
//
//    if (FALSE == bErrorFlag)
//    {
//        printf("Terminal failure: Unable to write to file.\n");
//        return -1;
//    }
//    else
//    {
//        if (dwBytesWritten != dwBytesToWrite)
//        {
//            // This is an error because a synchronous write that results in
//            // success (WriteFile returns TRUE) should write all data as
//            // requested. This would not necessarily be the case for
//            // asynchronous writes.
//            printf("Error: dwBytesWritten != dwBytesToWrite\n");
//        }
//        else
//        {
//            _tprintf(TEXT("Wrote %d bytes to %s successfully.\n"), dwBytesWritten, fp);
//            return dwBytesWritten;
//        }
//    }
//
//    CloseHandle(hFile);
//}

int pfprintf(FILE* fp,const char* format,...){
    int fd = _fileno(fp);
    int state = 0;
    char buff[strlen(format)];
    printf("11: %d\n",strlen(format));
    int i = 0;
    va_list args;
    va_start(args,format);
    while(*format){

        if(state == 0){
            if(*format == '%'){
                state = 1;
            }
            else{
                buff[i++] = *format;
            }

        }
        else if( state == 1){

            switch(*format){

                case 'c':{
                    buff[i++] = va_arg(args,int);
                    break;
                }

                case 'd':{
                    int num = va_arg(args,int);
                    int calc_dig = num;
                    int num_len = 0;
                    while(calc_dig != 0){
                        calc_dig = calc_dig / 10; 
                        num_len++;
                    }
                    char str[num_len];
                    sprintf(str,"%d",num);
                    
                    while(str[calc_dig] != '\0'){
                        buff[i++] = str[calc_dig++];
                    }
                    printf("i in int: %d\n",i);
                    break;
                }

                case 's':{
                    const char *s = va_arg(args,const char *);
                    while(*s){
                        buff[i++] = *s;
                        s++;
                    }
                    break;
                }
                case 'l':{

                    if(*(format+1) == 'f'){
                        format++;
                        double num = va_arg(args,double);
                        char str[51+1];
                        if(sprintf(str,"%lf",num) > 51){
                            printf("The number you want to include is too big please reduci precision to 51 characters in total\n");
                            exit(1);
                        }
                        else{
                            sprintf(str,"%lf",num);
                        }
                        int j= 0;
                        while(str[j] != '\0'){
                            buff[i++] = str[j++];
                        }
                        
                    }
                    
                    break;
                }
                case 'f':{
                    double num = va_arg(args,double);
                    
                    //sprintf(str,"%f",num);
                    
                    break;
                }
            }
            state = 0;
        }
        format++;
        
    }
    va_end(args);
    write(fd, buff, i);

}
    


int main(){
    FILE* fp;
    fp = fopen("idiot.txt","w");
    int a = 15;
    //fprintf(fp,"adsdsasdasas aagdlkusdliggadsilgasidufasp;idgf;ioasjhcp;iaGFPEI;BAD;JC\nBA;ioef;jednhf;oajbsdgf;iousagfnbfg;s;j\ngnk'sdofghb'lsjnkfg;ljsafkdhsakd gf;jbsadf;bdsvfsdasafspigyafdi;uhsfadpi\ngufdasgiuadfj;an;fdjndcnmzcx.nmzclz;ji;ojhqkja;fadsd;lnndmvvnmvalguh;ajhas;dhfga;sdjf;asdbf;bsad;fihbskd;fihgbs %s\n","fffffffffffffff");
    pfprintf(fp,"gfaaggadaggad %lf an\nd %d",-1536.12431,3344);
    fclose(fp);
    
    return 0;
}
