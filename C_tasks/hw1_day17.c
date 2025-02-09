#include <stdio.h>
#include <windows.h>
#include <string.h>
    void main(int argc, char* argv[]){


        char buff_path[FILENAME_MAX];
        GetCurrentDirectory(FILENAME_MAX,buff_path);
        char* print_path = {"\\print.exe"};
        //if( argc != 2 ){
        //        printf("Usage: %s N of processes\n", argv[0]);
        //        return;
        //}
        strcat(buff_path,print_path);
        

        for (int i = 0; i < 3; i++){
            STARTUPINFO si;
            PROCESS_INFORMATION pi;
            ZeroMemory( &si, sizeof(si) );
            si.cb = sizeof(si);
            ZeroMemory( &pi, sizeof(pi) );
            // Start the child process. 
            printf("%d: ",i+1);
            if( !CreateProcess( buff_path,   // No module name (use command line)
                NULL,        // Command line
                NULL,           // Process handle not inheritable
                NULL,           // Thread handle not inheritable
                FALSE,          // Set handle inheritance to FALSE
                0,              // No creation flags
                NULL,           // Use parent's environment block
                NULL,           // Use parent's starting directory 
                &si,            // Pointer to STARTUPINFO structure
                &pi )           // Pointer to PROCESS_INFORMATION structure
            ){
                printf( "CreateProcess failed (%d).\n", GetLastError() );
                exit(0);
            }

            
            // Wait until child process exits.
            if( WaitForSingleObject( pi.hProcess, INFINITE ) != 0){
                printf("Object could not be put into signaled state. Error (%d).\n",GetLastError());
            }
            else{
                // Close process and thread handles. 
                CloseHandle( pi.hProcess );
                CloseHandle( pi.hThread );
                
                printf("Thred %d stopped.\n",i+1);
                Sleep(1000);
            }
            
        
        }
        

}