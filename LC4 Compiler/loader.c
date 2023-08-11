/*
 * loader.c : Defines loader functions for opening and loading object files
 */

#include "loader.h"

// memory array location
unsigned short memoryAddress;

/*
 * Read an object file and modify the e machine state as described in the writeup
 */
int ReadObjectFile(char* filename, MachineState* CPU) {

FILE* obj_file = fopen(filename, "rb");
if(obj_file == NULL) {
  printf("file error: file could not be opened for reading\n");
  return -1; 
}

unsigned short int code; 

while(fread(&code, sizeof(unsigned short int), 1, obj_file)) {
   
   code = (code << 8) | (code >> 8);
   
   
   switch(code) {
     case 0xCADE: {
       unsigned short int location;
       unsigned short int number;
       fread(&location, sizeof(unsigned short int),1, obj_file);
       fread(&number, sizeof(unsigned short int),1, obj_file);
       location =  (location << 8) | (location >> 8);
       number =  (number << 8) | (number >> 8);

       for(int i = 0; i < number; i++){
         fread(&(CPU->memory[location+i]), sizeof(unsigned short int),1, obj_file);
         CPU->memory[location+i] =  (CPU->memory[location+i] << 8) |
         (CPU->memory[location+i] >> 8);
       }
       break;

     } case 0xDADA: {
       unsigned short int location;
       unsigned short int number;
       fread(&location, sizeof(unsigned short int),1, obj_file);
       fread(&number, sizeof(unsigned short int),1, obj_file);
       location =  (location << 8) | (location >> 8);
       number =  (number << 8) | (number >> 8);

       for(int i = 0; i < number; i++){
         fread(&(CPU->memory[location+i]), sizeof(unsigned short int ),1, obj_file);
         CPU->memory[location+i] =  
         ((CPU->memory[location+i]) << 8) 
         |  ((CPU->memory[location+i]) >> 8);
       }
       break;

     } case 0xC3B7: {
       unsigned short int location;
       unsigned short int number;
       fread(&location, sizeof(unsigned short int),1, obj_file);
       fread(&number, sizeof(unsigned short int),1, obj_file);
       
       fseek(obj_file, number, SEEK_CUR);
       break;

     } case 0xF17E: {
       unsigned short int number;
       fread(&number, sizeof(unsigned short int),1, obj_file);
       
       fseek(obj_file, number, SEEK_CUR);
       break;


     } case 0x715E: {
       unsigned short int location;
       unsigned short int line;
       unsigned short int file_index;
       fread(&location, sizeof(unsigned short int),1, obj_file);
       fread(&line, sizeof(unsigned short int),1, obj_file);
       fread(&file_index, sizeof(unsigned short int),1, obj_file);
       
  
       break;


     } default:
     printf("file reading error: code in File not found to be a valid code\n");
     return -1;

   




   
   
   
   }



}

  fclose(obj_file);
  return 0;



}
