/***************************************************************************
 * file name   : assembler.c                                               *
 * author      : tjf & you                                                 *
 * description : This program will assemble a .ASM file into a .OBJ file   *
 *               This program will use the "asm_parser" library to achieve *
 *			     its functionality.										   * 
 *                                                                         *
 ***************************************************************************
 *
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "asm_parser.h"

int main(int argc, char** argv) {

	char* filename = NULL ;					// name of ASM file
	char  program [ROWS][COLS] ; 			// ASM file line-by-line
	char  program_bin_str [ROWS][17] ; 		// instructions converted to a binary string
	unsigned short int program_bin [ROWS] ; // instructions in binary (HEX)

if(argc != 2){
	 printf("error1: usage: ./assembler <assembly_file.asm>\n");
   return 1;
 }

if(strncmp(argv[0], "./assembler",11) != 0) {
	printf("error1: usage: ./assembler <assembly_file.asm>\n");
  return 1;
}

filename = argv[1];

read_asm_file(filename, program);
 


for(int i = 0; i <ROWS; i++) {
	if(program[i][0] == '\0') {
		break;
	}

	 parse_instruction(program[i], program_bin_str[i]);
	 
	 program_bin[i] = str_to_bin(program_bin_str[i]);
	
}

write_obj_file(filename, program_bin);
return 0;

}



