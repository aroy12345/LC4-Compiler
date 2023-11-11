

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "asm_parser.h"

int read_asm_file 	(char* filename, char program [ROWS][COLS] ) {
  FILE *file = fopen(filename, "r");
  
  if(file == NULL) {
    printf("error2: read_asm_file() failed\n");
    return 2;
  }

  char nextLine[COLS] ;
  for(int i = 0; i<ROWS; i++) {
    if(fgets(nextLine, COLS, file) == NULL) {
      break;
    }

    if(strlen(nextLine)>0 ) {
     
    nextLine[strlen(nextLine)-1] = '\0';
    
    
  }
    strcpy(program[i],nextLine);
    

  }

     fclose(file);
     return 0;

}


int parse_instruction (char* instr, char* instr_bin_str) {
char* delim = " ,";
char *token = strtok(instr, delim);

if(token == NULL) {
  printf("error3: parse_instruction() failed.\n");
  return 3;
}

  if(strcmp(token, "ADD") == 0) {
    return parse_add(instr, instr_bin_str);
  }

   if(strcmp(token, "MUL") == 0) {
    return parse_mul(instr, instr_bin_str);
  }

   if(strcmp(token, "SUB") == 0) {
    return parse_sub(instr, instr_bin_str);
  }

   if(strcmp(token, "DIV") == 0) {
    return parse_div(instr, instr_bin_str);
  }


 if(strcmp(token, "OR") == 0) {
    return parse_or(instr, instr_bin_str);
  }

 if(strcmp(token, "AND") == 0) {
    return parse_and(instr, instr_bin_str);
  }

  if(strcmp(token, "XOR") == 0) {
    return parse_xor(instr, instr_bin_str);
  }
 
printf("error3: parse_instruction() failed.\n");
  return 3;
}

int parse_add (char* instr, char* instr_bin_str) { 
        strncpy(instr_bin_str, "0001", 4);
        
        char* token = strtok(NULL, " ,");
        if(token == NULL) {
         printf("error4: parse_add() failed.\n");
        return 4;
         }
        if(strlen(token) >1 ) {
        char Rd = token[1]; 
        parse_reg(Rd, &instr_bin_str[4]);
        } else {
           printf("error4: parse_add() failed.\n");
        return 4;
        }




        token = strtok(NULL, " ,");
        if(token == NULL) {
        printf("error4: parse_add() failed.\n");
        return 4;
         }
        if(strlen(token) >1 ) {
        char Rs = token[1]; 
        parse_reg(Rs, &instr_bin_str[7]);
        } else {
           printf("error4: parse_add() failed.\n");
        return 4;
        }
        
        strncpy(&instr_bin_str[10], "000", 3);

        token = strtok(NULL, " ,");
        if(token == NULL) {
        printf("error4: parse_add() failed.\n");
        return 4;
         }
       if(strlen(token) >1 ) {
        char Rt = token[1]; 
        parse_reg(Rt, &instr_bin_str[13]);
        } else {
           printf("error4: parse_add() failed.\n");
        return 4;
        }


  return 0;

}


int parse_mul (char* instr, char* instr_bin_str) { 
        strncpy(instr_bin_str, "0001", 4);
        
        char* token = strtok(NULL, " ,");
        if(token == NULL) {
         printf("error4: parse_mul() failed.\n");
        return 4;
         }
        if(strlen(token) >1 ) {
        char Rd = token[1]; 
        parse_reg(Rd, &instr_bin_str[4]);
        } else {
           printf("error4: parse_mul() failed.\n");
        return 4;
        }




        token = strtok(NULL, " ,");
        if(token == NULL) {
        printf("error4: parse_mul() failed.\n");
        return 4;
         }
        if(strlen(token) >1 ) {
        char Rs = token[1]; 
        parse_reg(Rs, &instr_bin_str[7]);
        } else {
           printf("error4: parse_mul() failed.\n");
        return 4;
        }
        
        strncpy(&instr_bin_str[10], "001", 3);

        token = strtok(NULL, " ,");
        if(token == NULL) {
        printf("error4: parse_mul() failed.\n");
        return 4;
         }
       if(strlen(token) >1 ) {
        char Rt = token[1]; 
        parse_reg(Rt, &instr_bin_str[13]);
        } else {
           printf("error4: parse_mul() failed.\n");
        return 4;
        }


  return 0;

}


int parse_sub (char* instr, char* instr_bin_str) { 
        strncpy(instr_bin_str, "0001", 4);
        
        char* token = strtok(NULL, " ,");
        if(token == NULL) {
         printf("error4: parse_sub() failed.\n");
        return 4;
         }
        if(strlen(token) >1 ) {
        char Rd = token[1]; 
        parse_reg(Rd, &instr_bin_str[4]);
        } else {
           printf("error4: parse_sub() failed.\n");
        return 4;
        }




        token = strtok(NULL, " ,");
        if(token == NULL) {
        printf("error4: parse_sub() failed.\n");
        return 4;
         }
        if(strlen(token) >1 ) {
        char Rs = token[1]; 
        parse_reg(Rs, &instr_bin_str[7]);
        } else {
           printf("error4: parse_sub() failed.\n");
        return 4;
        }
        
        strncpy(&instr_bin_str[10], "010", 3);

        token = strtok(NULL, " ,");
        if(token == NULL) {
        printf("error4: parse_sub() failed.\n");
        return 4;
         }
       if(strlen(token) >1 ) {
        char Rt = token[1]; 
        parse_reg(Rt, &instr_bin_str[13]);
        } else {
           printf("error4: parse_sub() failed.\n");
        return 4;
        }


  return 0;

}


int parse_div (char* instr, char* instr_bin_str) { 
        strncpy(instr_bin_str, "0001", 4);
        
        char* token = strtok(NULL, " ,");
        if(token == NULL) {
         printf("error4: parse_div() failed.\n");
        return 4;
         }
        if(strlen(token) >1 ) {
        char Rd = token[1]; 
        parse_reg(Rd, &instr_bin_str[4]);
        } else {
           printf("error4: parse_div() failed.\n");
        return 4;
        }




        token = strtok(NULL, " ,");
        if(token == NULL) {
        printf("error4: parse_div() failed.\n");
        return 4;
         }
        if(strlen(token) >1 ) {
        char Rs = token[1]; 
        parse_reg(Rs, &instr_bin_str[7]);
        } else {
           printf("error4: parse_div() failed.\n");
        return 4;
        }
        
        strncpy(&instr_bin_str[10], "011", 3);

        token = strtok(NULL, " ,");
        if(token == NULL) {
        printf("error4: parse_div() failed.\n");
        return 4;
         }
       if(strlen(token) >1 ) {
        char Rt = token[1]; 
        parse_reg(Rt, &instr_bin_str[13]);
        } else {
           printf("error4: parse_div() failed.\n");
        return 4;
        }


  return 0;

}


int parse_and (char* instr, char* instr_bin_str) { 
        strncpy(instr_bin_str, "0101", 4);
        
        char* token = strtok(NULL, " ,");
        if(token == NULL) {
         printf("error4: parse_and() failed.\n");
        return 4;
         }
        if(strlen(token) >1 ) {
        char Rd = token[1]; 
        parse_reg(Rd, &instr_bin_str[4]);
        } else {
           printf("error4: parse_and() failed.\n");
        return 4;
        }




        token = strtok(NULL, " ,");
        if(token == NULL) {
        printf("error4: parse_and() failed.\n");
        return 4;
         }
        if(strlen(token) >1 ) {
        char Rs = token[1]; 
        parse_reg(Rs, &instr_bin_str[7]);
        } else {
           printf("error4: parse_and() failed.\n");
        return 4;
        }
        
        strncpy(&instr_bin_str[10], "000", 3);

        token = strtok(NULL, " ,");
        if(token == NULL) {
        printf("error4: parse_and() failed.\n");
        return 4;
         }
       if(strlen(token) >1 ) {
        char Rt = token[1]; 
        parse_reg(Rt, &instr_bin_str[13]);
        } else {
           printf("error4: parse_and() failed.\n");
        return 4;
        }


  return 0;

}

int parse_or (char* instr, char* instr_bin_str) { 
        strncpy(instr_bin_str, "0101", 4);
        
        char* token = strtok(NULL, " ,");
        if(token == NULL) {
         printf("error4: parse_or() failed.\n");
        return 4;
         }
        if(strlen(token) >1 ) {
        char Rd = token[1]; 
        parse_reg(Rd, &instr_bin_str[4]);
        } else {
           printf("error4: parse_or() failed.\n");
        return 4;
        }




        token = strtok(NULL, " ,");
        if(token == NULL) {
        printf("error4: parse_or() failed.\n");
        return 4;
         }
        if(strlen(token) >1 ) {
        char Rs = token[1]; 
        parse_reg(Rs, &instr_bin_str[7]);
        } else {
           printf("error4: parse_or() failed.\n");
        return 4;
        }
        
        strncpy(&instr_bin_str[10], "010", 3);

        token = strtok(NULL, " ,");
        if(token == NULL) {
        printf("error4: parse_or() failed.\n");
        return 4;
         }
       if(strlen(token) >1 ) {
        char Rt = token[1]; 
        parse_reg(Rt, &instr_bin_str[13]);
        } else {
           printf("error4: parse_or() failed.\n");
        return 4;
        }


  return 0;

}


int parse_xor (char* instr, char* instr_bin_str) {
       strncpy(instr_bin_str, "0101", 4);
      
       char* token = strtok(NULL, " ,");
       if(token == NULL) {
        printf("error4: parse_xor() failed.\n");
       return 4;
        }
       if(strlen(token) >1 ) {
       char Rd = token[1];
       parse_reg(Rd, &instr_bin_str[4]);
       } else {
          printf("error4: parse_xor() failed.\n");
       return 4;
       }








       token = strtok(NULL, " ,");
       if(token == NULL) {
       printf("error4: parse_xor() failed.\n");
       return 4;
        }
       if(strlen(token) >1 ) {
       char Rs = token[1];
       parse_reg(Rs, &instr_bin_str[7]);
       } else {
          printf("error4: parse_xor() failed.\n");
       return 4;
       }
      
       strncpy(&instr_bin_str[10], "011", 3);


       token = strtok(NULL, " ,");
       if(token == NULL) {
       printf("error4: parse_xor() failed.\n");
       return 4;
        }
      if(strlen(token) >1 ) {
       char Rt = token[1];
       parse_reg(Rt, &instr_bin_str[13]);
       } else {
          printf("error4: parse_xor() failed.\n");
       return 4;
       }




 return 0;
}




int parse_reg (char reg_num, char* instr_bin_str){ 
        
    switch(reg_num) {
      case '0' :
         strncpy(instr_bin_str, "000",3);
         break;
     case '1' :
         strncpy(instr_bin_str, "001",3);
         break;
     case '2' :
         strncpy(instr_bin_str, "010",3);
         break;
     case '3' :
         strncpy(instr_bin_str, "011",3);
         break;
    case '4' :
         strncpy(instr_bin_str, "100",3);
         break;
     case '5' :
         strncpy(instr_bin_str, "101",3);
         break;
     case '6' :
         strncpy(instr_bin_str, "110",3);
         break;
     case '7' :
         strncpy(instr_bin_str, "111",3);
         break;
    default :
        printf("error5: parse_reg() failed.\n");
        
         return 0;
   }

    return 0;
}


 unsigned short int str_to_bin (char* instr_bin_str) {
   char *ptr;
   long ret;
   ret = strtol(instr_bin_str, &ptr, 2);
   if(ret == 0){
     printf("error6: int str_to_bin() failed.\n");
     return 6;
   }

  unsigned short int ret2 =  (unsigned short int) ret;
  return ret2;

  
 }


unsigned short int convert(unsigned short int num){
  return((num<<8)&0xFF00) |
        ((num>>8)&0x00FF) ;



}


int write_obj_file  (char* filename, unsigned short int program_bin[ROWS] ) {
 char obj_file [strlen(filename)+1];
 strcpy(obj_file, filename);
 obj_file[strlen(filename)-1] = 'j';
 obj_file[strlen(filename)-2] = 'b';
 obj_file[strlen(filename)-3] = 'o';
 
 
 

 FILE* output = fopen(obj_file, "wb");
 if(output == NULL) {
	 printf("error7: write_obj_file() failed.\n");
   return 7;
 }
   
  unsigned short int input = convert(0xCADE);
  fwrite(&input, sizeof(unsigned short int), 1, output);
  input = convert(0x0000); 
  fwrite(&input, sizeof(unsigned short int), 1, output);


   unsigned short int rows = 0;
   for(int i = 0; i < ROWS; i++) {
    if(program_bin[i] == 0){
      break;
    } else {
      rows = rows+1;
    }
   }

   input = convert(rows);

   fwrite(&input, sizeof(unsigned short int), 1, output);
   for(int i = 0; i<rows; i++) {
     unsigned short int val = convert(program_bin[i]);
     fwrite(&val, sizeof(unsigned short int),1, output);
   }
  
   fclose(output);

   return 0;


}




