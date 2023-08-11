/*
 * trace.c: location of main() to start the simulator
 */

#include "loader.h"

// Global variable defining the current state of the machine
MachineState* CPU;

int main(int argc, char** argv)
{
    
    if(argc < 2) {
        printf("Not enough input files to run the code\n");
        return -1;

    }
    FILE* final = fopen(argv[1], "w");
    if(!final){

        printf("error: File could not be opened for writing\n");
        return -1;
    }



    CPU = malloc(sizeof(MachineState));
    memset(CPU -> memory, 0, sizeof(unsigned short)*65536);
    Reset(CPU);
    for(int j = 2; j < argc; j++) {
        int x = ReadObjectFile(argv[j], CPU);
       
        if(x!= 0) {
            printf("%s\n", argv[j]);
            printf("Error Reading File Obj File \n");
            fclose(final); 
            return -1; 
        }
    }

              
        for(int i = 0; i< 65536; i++) {
           if((*CPU).memory[i]!=0) {
             
              //fprintf(final, "%04X, %04X\n", i, (*CPU).memory[i]);
             // fflush(final);
           
           }
        }


  UpdateMachineState(CPU, final);
   free(CPU);
   fclose(final);
    return 0;
}