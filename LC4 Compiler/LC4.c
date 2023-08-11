/*
 * LC4.c: Defines simulator functions for executing instructions
 */

#include "LC4.h"
#include <stdio.h>

/*
 * Reset the machine state as Pennsim would do
 */


#define ISN_OP(I) ((I) >> 12)
#define ISN_15_11(I) ((I) >> 11 & 0x1F)
#define ISN_11_9(I) (((I) >> 9) & 0x7)
#define ISN_8_6(I) (((I) >> 6) & 0x7)
#define ISN_5_3(I) ((I >> 3) & 0x7)
#define ISN_2_0(I) ((I >> 0) & 0x7)
#define ISN_5_5(I) ((I>>5) &0x1)
#define ISN_4_0(I) ((I) & 0x1F)
#define ISN_5_0(I) ((I) & 0x3F)
#define ISN_5_4(I) ((I >> 4) & 0x3)
#define ISN_6_0(I) ((I >> 0) & 0x7F)
#define ISN_8_7(I) ((I >> 7) & 0x3)
#define ISN_3_0(I) ((I>>0) & 0xF)
#define ISN_8_0(I) ((I>>0) & 0x1FF)
#define ISN_15_9(I) ((I>>9) & 0x7F)
#define ISN_10_0(I)((I>>0) & 0x07FF)
#define ISN_7_0(I) ((I>>0) & 0x00FF)

 int isNegativeConvertToPositive (unsigned short int number) {
      if((number & (1<<15)) != 0) {
        return (int) -1 * (int)(~number + 1);
      } else {
        return (int) number;
      }

}


void StoreOP(MachineState* CPU, FILE* output) {
   unsigned short int PSR_OS = (CPU->PSR >>15) & 0x0001;
    unsigned short int instruct = CPU->memory[CPU->PC];
    unsigned short int op_code = ISN_OP(instruct);
    unsigned short int Rt = ISN_11_9(instruct);
    unsigned short int Rs = ISN_8_6(instruct);
    int add  = ISN_5_0(instruct);
    unsigned short int value = 0;
 

 if(add & (1<<5)) {
             add = -(~add +1 &0x3F);
          }

    int location = isNegativeConvertToPositive(CPU->R[Rs]) + add;
    CPU->memory[location] = CPU->R[Rt]; 
     CPU->dmemAddr = (unsigned short int) location;
   CPU->dmemValue = CPU->R[Rt];

    

   
   CPU->rsMux_CTL =  0;
   CPU->rtMux_CTL =  1;
   CPU->rdMux_CTL =  0;
   CPU->regFile_WE =  0;
   CPU->NZP_WE =  0;
   CPU->DATA_WE =  1;
   CPU->regInputVal = 0;
   CPU->dmemAddr = (unsigned short int) location;
   CPU->dmemValue = CPU->R[Rt];
   
  

   if(((CPU->dmemAddr) <= 0xFFFF) && ((CPU->dmemAddr) >= 0x8000) && (PSR_OS == 0)) {
     return;
   } 



 

 SetNZP(CPU, value);
 WriteOut(CPU, output);

 

}


void LoadOP(MachineState* CPU, FILE* output) {
  
    unsigned short int instruct = CPU->memory[CPU->PC];
    unsigned short int op_code = ISN_OP(instruct);
    unsigned short int Rd = ISN_11_9(instruct);
    unsigned short int Rs = ISN_8_6(instruct);
   int add = ISN_5_0(instruct);
    unsigned short int value = 0;


    unsigned short int PSR_OS = (CPU->PSR >>15) & 0x0001;

  

if(add & (1<<5)) {
             add = -(~add +1 &0x3F);
    }

    int location = isNegativeConvertToPositive(CPU->R[Rs]) + add;
    value = CPU->memory[location];
    CPU->dmemAddr = location;
    CPU->dmemValue = value;
     


   
    


   

    CPU->R[Rd] =  CPU->memory[location];
   CPU->rsMux_CTL =  0;
   CPU->rtMux_CTL =  0;
   CPU->rdMux_CTL =  0;
   CPU->regFile_WE =  1;
   CPU->NZP_WE =  1;
   CPU->DATA_WE =  0;
   CPU->regInputVal = value;
   CPU->dmemAddr = location;
   CPU->dmemValue = value;
   
   


   if(((CPU->dmemAddr) <= 0xFFFF) && ((CPU->dmemAddr) >= 0x8000) && (PSR_OS == 0)) {
     return;
  } 
  

 SetNZP(CPU, value);
 WriteOut(CPU, output);

 

}


void RTIOP(MachineState* CPU, FILE* output) {


    unsigned short int value = 0;
  
   CPU->PSR = CPU->PSR &= 0x7FFF;


 
   CPU->rsMux_CTL =  1;
   CPU->rtMux_CTL =  0;
   CPU->rdMux_CTL =  0;
   CPU->regFile_WE =  0;
   CPU->NZP_WE =  0;
   CPU->DATA_WE =  0;
   CPU->regInputVal = 0;
   CPU->dmemAddr = 0;
   CPU->dmemValue = 0;

    

 SetNZP(CPU, value);
 WriteOut(CPU, output);

  CPU->PC = CPU->R[7];

}




void ConstantOP(MachineState* CPU, FILE* output) {

    unsigned short int instruct = CPU->memory[CPU->PC];
    unsigned short int op_code = ISN_OP(instruct);
    unsigned short int Rd = ISN_11_9(instruct);
   int add = ISN_8_0(instruct);

    if(add & (1<<8)) {
             add = -(~add +1 &0x1FF);
          }
    
     
     unsigned short int value = add;
    CPU->R[Rd] = value;
   CPU->rsMux_CTL =  0;
   CPU->rtMux_CTL =  0;
   CPU->rdMux_CTL =  0;
   CPU->regFile_WE =  1;
   CPU->NZP_WE =  1;
   CPU->DATA_WE =  0;
   CPU->regInputVal = value;
   CPU->dmemAddr = 0;
   CPU->dmemValue = 0;

    

 SetNZP(CPU, value);
 WriteOut(CPU, output);

 

}



void HiConstantOP(MachineState* CPU, FILE* output) {

    unsigned short int instruct = CPU->memory[CPU->PC];
    unsigned short int op_code = ISN_OP(instruct);
    unsigned short int Rd = ISN_11_9(instruct);
    unsigned short int operation = ISN_7_0(instruct);
    unsigned short int value =  (CPU->R[Rd] & 0xFF) | (operation << 8); 

     
   CPU->R[Rd] = value;
   CPU->rsMux_CTL =  2;
   CPU->rtMux_CTL =  0;
   CPU->rdMux_CTL =  0;
   CPU->regFile_WE =  1;
   CPU->NZP_WE =  1;
   CPU->DATA_WE =  0;
   CPU->regInputVal = value;
   CPU->dmemAddr = 0;
   CPU->dmemValue = 0;

    

 SetNZP(CPU, value);
 WriteOut(CPU, output);

 

}

void TrapOP(MachineState* CPU, FILE* output) {

    unsigned short int instruct = CPU->memory[CPU->PC];
    unsigned short int op_code = ISN_OP(instruct);
    unsigned short int operation = ISN_7_0(instruct);
  
  
   unsigned short int value = CPU->PC + 1;
     CPU->PSR = CPU -> PSR |= (1<<15);
   CPU->R[7] = value;
   CPU->rsMux_CTL =  0;
   CPU->rtMux_CTL =  0;
   CPU->rdMux_CTL =  1;
   CPU->regFile_WE =  1;
   CPU->NZP_WE =  1;
   CPU->DATA_WE =  0;
   CPU->regInputVal = value;
   CPU->dmemAddr = 0;
   CPU->dmemValue = 0;

    

 SetNZP(CPU, value);
 WriteOut(CPU, output);

 
  CPU->PC = (0x8000 | operation);
   





 

}



void Reset(MachineState* CPU)
{
  CPU->PC = 0x8200;
  CPU->PSR = 0x8002;
   for (int i = 0; i<65536; i++) {
     CPU->memory[i] = 0;
   }

   for(int i = 0; i<8; i++){
     CPU->R[i] = 0;
   }

    ClearSignals(CPU);
}


/*
 * Clear all of the control signals (set to 0)
 */
void ClearSignals(MachineState* CPU)
{
     CPU->rsMux_CTL =  0;
     CPU->rdMux_CTL =  0;
     CPU->rtMux_CTL =  0;
     CPU->regFile_WE =  0;
     CPU->NZP_WE =  0;
     CPU->DATA_WE =  0;
     CPU->regInputVal = 0;
     CPU->NZPVal = 0;
     CPU->dmemAddr = 0;
     CPU->dmemValue = 0;


}
          
char* toBinary(unsigned short int num, char*binary, int size) {
  binary[size-1] = '\0';
  for(int start = size -2; start>=0; start--) {
    binary[start] = (num & 1) ? '1' : '0';
    num >>=1;
  }
  return binary;
}

/*
 * This function should write out the current state of the CPU to the file output.
 */
void WriteOut(MachineState* CPU, FILE* output)
{
  unsigned short int reg = 0;
 
if(CPU->regFile_WE ==  (1) && CPU->rdMux_CTL== 0 ) {
    //printf("henwn");
    reg =ISN_11_9(CPU->memory[CPU->PC]);
    //printf("%hu\n\n", reg);
} else if (CPU->regFile_WE ==  (1) && CPU->rdMux_CTL== 1 ) {
     reg = 7;
} else {
    reg = 0;
}

unsigned short int instruct = CPU->memory[CPU->PC];
   unsigned short int op_code = ISN_OP(instruct);
   


 char binary[17];
   fprintf(output, "%04X %s %hhu %d %04X %hhu %d %hhu %04X %04X\n",
   CPU->PC,
   toBinary(CPU->memory[CPU->PC], binary, 17),
   CPU->regFile_WE, 
    reg,
   CPU->regInputVal,
   CPU->NZP_WE,
   CPU->NZPVal, 
   CPU->DATA_WE,
   CPU->dmemAddr,
   CPU->dmemValue);
fflush(output);

//printf("%04X %s %hhu %d %04X %hhu %d %hhu %04X %04X\n",
  // CPU->PC,
   //toBinary(CPU->memory[CPU->PC], binary, 17),
   //CPU->regFile_WE, 
    //reg,
   //CPU->regInputVal,
   //CPU->NZP_WE,
   //CPU->NZPVal, 
   //CPU->DATA_WE,
   //CPU->dmemAddr,
   //CPU->dmemValue);

    
   

   



}


/*
 * This function should execute one LC4 datapath cycle.
 */
int UpdateMachineState(MachineState* CPU, FILE* output)
{

    CPU -> PC = 0x8200;
    
  while(CPU->PC != 0x80FF) {



   unsigned short int instruct = CPU->memory[CPU->PC];
   unsigned short int op_code = ISN_OP(instruct);
   
   unsigned short int PSR_OS = (CPU->PSR >>15) & 0x0001;

  


   if(((CPU-> PC) <= 0xFFFF) && ((CPU-> PC) >= 0x8000) && (PSR_OS == 0)) {
     break;
   } 


   int x = 0; 



   switch(op_code) {
  
     case(0x0000):
       BranchOp(CPU, output);
       break;
     case(0x0001):
       ArithmeticOp(CPU, output);
       CPU->PC = CPU->PC +1;
       break;
    case(0x0002):
       ComparativeOp(CPU, output);
       CPU->PC = CPU->PC +1;
       break;
    case(0x0005):
       LogicalOp(CPU, output);
       CPU->PC = CPU->PC +1;
       break;
   case(0x000C):
       JumpOp(CPU, output);
       break;
   case(0x0004):
       JSROp(CPU, output);
       break;
   case(10):
       ShiftModOp(CPU, output);
       CPU->PC = CPU->PC +1;
       break;
    case(6):
      LoadOP(CPU, output);
      CPU->PC = CPU->PC +1;
      x = 1;
      break;
    case(7):
      StoreOP(CPU, output);
      CPU->PC = CPU->PC +1;
      x =1;
      break;
    case(8):
      RTIOP(CPU, output);
      break;
    case(9):
       ConstantOP(CPU, output);
       CPU->PC = CPU->PC +1;
      break;
    case(13):
      HiConstantOP(CPU, output);
      CPU->PC = CPU->PC +1;
      break;
    case(15):
      TrapOP(CPU, output);
      break;

    default: 
    break;
     

    
   }

   


   if((x==1) && ((CPU->dmemAddr) <= 0xFFFF) && ((CPU->dmemAddr) >= 0x8000) && (PSR_OS == 0)) {
     break;
   } 


    ClearSignals(CPU);
    

    


  }




    return 0;
}



//////////////// PARSING HELPER FUNCTIONS ///////////////////////////



/*
 * Parses rest of branch operation and updates state of machine.
 */




void BranchOp(MachineState* CPU, FILE* output)
{
    unsigned short int instruct = CPU->memory[CPU->PC];
    unsigned short int op_code = ISN_OP(instruct);
    unsigned short int value = 0;

    unsigned short int operation = ISN_15_9(instruct);
    unsigned short int last3 = ISN_2_0(CPU->PSR);

    
  int add = 0;
    
   


   
   CPU->rsMux_CTL =  0;
   CPU->rtMux_CTL =  0;
   CPU->rdMux_CTL =  0;
   CPU->regFile_WE =  0;
   CPU->NZP_WE =  0;
   CPU->DATA_WE =  0;
   CPU->regInputVal = value;
   CPU->dmemAddr = 0;
   CPU->dmemValue = 0;

   SetNZP(CPU, value);
 WriteOut(CPU, output);




 switch (operation) {
      case(0x000):
          CPU->PC = CPU->PC +1;
           break;
      case (0x0004):
         if(last3 == 4) {
          add = ISN_8_0(instruct);
           if(add & (1<<8)) {
             add = -(~add +1 &0x1FF);
          }
         CPU->PC = (int) CPU->PC +(int) 1 + add;
         } else{
            CPU->PC = CPU->PC +1;
         }
        break;
      case (0x0006):
     
         if(last3 == 4 || last3 == 2) {
         add = ISN_8_0(instruct);
           if(add & (1<<8)) {
             add = -(~add +1 &0x1FF);
          }
         CPU->PC = (int) CPU->PC +(int) 1 + add;;
         } else{
            CPU->PC = CPU->PC +1;
         }
         break;
      case (0x0005):
        if(last3 == 4 || last3 == 1) {
        add = ISN_8_0(instruct);
           if(add & (1<<8)) {
             add = -(~add +1 &0x1FF);
          }
         CPU->PC = (int) CPU->PC +(int) 1 + add;
         } else{
            CPU->PC = CPU->PC +1;
         }
         break;
       case (0x0002):
       if(last3 == 2) {
         add = ISN_8_0(instruct);
           if(add & (1<<8)) {
             add = -(~add +1 &0x1FF);
          }
         CPU->PC = (int) CPU->PC +(int) 1 + add;
         } else{
            CPU->PC = CPU->PC +1;
         }
         break;
      case (0x0003):
     
         if(last3 == 2 || last3 ==1 ) {
         add = ISN_8_0(instruct);
           if(add & (1<<8)) {
             add = -(~add +1 &0x1FF);
          }
         CPU->PC = (int) CPU->PC +(int) 1 + add;
         } else{
            CPU->PC = CPU->PC +1;
         }
         break;
      case (0x0001):
        

         if(last3 ==1 ) {
          
           
         add = ISN_8_0(instruct);
           if(add & (1<<8)) {
             add = -(~add +1 &0x1FF);
          }
         CPU->PC = (int) CPU->PC +(int) 1 + add;
         } else{
            CPU->PC = CPU->PC +1;
         }
         break;
      case (0x0007):
          if(last3 ==1 || last3 ==4 || last3 == 2 ) {
         add = ISN_8_0(instruct);
           if(add & (1<<8)) {
             add = -(~add +1 &0x1FF);
          }
         CPU->PC = (int) CPU->PC +(int) 1 + add;
         } else {
            CPU->PC = CPU->PC +1;
         }
         break;
      default:
         CPU->PC = CPU->PC +1;
         break;

    }


}

/*
 * Parses rest of arithmetic operation and prints out.
 */
void ArithmeticOp(MachineState* CPU, FILE* output)
{
   unsigned short int instruct = CPU->memory[CPU->PC];
   unsigned short int op_code = ISN_OP(instruct);
    unsigned short int value = 0;
   unsigned short int Rd = 0;
     unsigned short int Rs = 0;
     unsigned short int Rt = 0;
     unsigned short int operation = 0;
    int add = 0;

     if(ISN_5_5(instruct) == 0) {
     Rd = ISN_11_9(instruct);

     Rs = ISN_8_6(instruct);
     Rt = ISN_2_0(instruct);
     operation = ISN_5_3(instruct);
     value = 0;

     switch(operation) {
       case (0x0000):
         value = isNegativeConvertToPositive(CPU->R[Rs])+isNegativeConvertToPositive(CPU->R[Rt]);
         break;
      case (0x0001):
         value = isNegativeConvertToPositive(CPU->R[Rs])*isNegativeConvertToPositive(CPU->R[Rt]);
         break;
      case (0x0002):
         value = isNegativeConvertToPositive(CPU->R[Rs])-isNegativeConvertToPositive(CPU->R[Rt]);
         break;
       case (0x0003):
         value = isNegativeConvertToPositive(CPU->R[Rs])/isNegativeConvertToPositive(CPU->R[Rt]);
         break;
       

     }


     } else {
      Rd = ISN_11_9(instruct);
      Rs = ISN_8_6(instruct);
       add = ISN_4_0(instruct);
      
       if(add & (1<<4)) {
         add = -(~add +1 &0x1F);
       }

       value = isNegativeConvertToPositive(CPU->R[Rs])+ add;
      

     }
    

  


   CPU->R[Rd] = value;
   CPU->rsMux_CTL =  0;
   CPU->rtMux_CTL =  0;
   CPU->rdMux_CTL =  0;
   CPU->regFile_WE =  1;
   CPU->NZP_WE =  1;
   CPU->DATA_WE =  0;
   CPU->regInputVal = value;
   CPU->dmemAddr = 0;
   CPU->dmemValue = 0;
   
  

 

 SetNZP(CPU, value);
 WriteOut(CPU, output);

    
}

/*
 * Parses rest of comparative operation and prints out.
 */
void ComparativeOp(MachineState* CPU, FILE* output)
{

  CPU->NZP_WE =  1;
   unsigned short int instruct = CPU->memory[CPU->PC];
   unsigned short int op_code = ISN_OP(instruct);
   

   unsigned short int Rs = ISN_11_9(instruct);
   unsigned short int operation = ISN_8_7(instruct); 
unsigned short int value = 0;
unsigned short int Rt = 0;
 int add = 0;

     switch(operation) {
       case (0x0000): 
         
          Rt = ISN_2_0(instruct);
         value = isNegativeConvertToPositive(CPU->R[Rs]) - isNegativeConvertToPositive(CPU->R[Rt]);
          SetNZP(CPU, value);
         break;
      case (0x0001): 
         
          Rt = ISN_2_0(instruct);
         value = CPU->R[Rs] - CPU->R[Rt];
          SetNZP(CPU, value);
         break;
      case (0x0002): 
        
        add = ISN_6_0(instruct);
 
          
           if(add & (1<<6)) {
         add = -(~add +1 &0x7F);
       }

      value = isNegativeConvertToPositive(CPU->R[Rs]) - add;
       SetNZP(CPU, value);
         break;
       case (0x0003): 
        
          add = ISN_6_0(instruct);
         value = CPU->R[Rs] - add;
        SetNZP(CPU, value);
         break;
       

     }
   

   
  
   CPU->rsMux_CTL =  1;
   CPU->rtMux_CTL =  0;
   CPU->rdMux_CTL = 0;
   CPU->regFile_WE =  0;
   CPU->NZP_WE =  1;
   CPU->DATA_WE =  0;
   CPU->regInputVal = 0;
   CPU->dmemAddr = 0;
   CPU->dmemValue = 0;




 WriteOut(CPU, output);



}

/*
 * Parses rest of logical operation and prints out.
 */
void LogicalOp(MachineState* CPU, FILE* output)
{
   unsigned short int instruct = CPU->memory[CPU->PC];
   unsigned short int op_code = ISN_OP(instruct);
   unsigned short int value = 0;

unsigned short int Rd = 0;
     unsigned short int Rs = 0;
     unsigned short int Rt = 0;
     unsigned short int operation = 0;
     int add = 0;

   if(ISN_5_5(instruct) == 0) {
      Rd = ISN_11_9(instruct);
      Rs = ISN_8_6(instruct);
     Rt = ISN_2_0(instruct);
     operation = ISN_5_3(instruct);
     value = 0;

     switch(operation) {
       case (0x0000): //AND
         value = CPU->R[Rs] & CPU->R[Rt];
         break;
      case (0x0001): //Not
         value = ~CPU->R[Rs];
         break;
      case (0x0002): //OR
         value = CPU->R[Rs] | CPU->R[Rt];
         break;
       case (0x0003): //XOR
         value = CPU->R[Rs] ^ CPU->R[Rt];
         break;
       

     }


     } else {
     Rd = ISN_11_9(instruct);
    Rs = ISN_8_6(instruct);
     add = ISN_4_0(instruct);
       if(add & (1<<4)) {
         add = -(~add +1 &0x1F);
       }
       unsigned short int add2 = add;
       value = CPU->R[Rs] & add2;
     }
    


    CPU->R[Rd] = value;
   CPU->rsMux_CTL =  0;
   CPU->rtMux_CTL =  0;
   CPU->rdMux_CTL =  0;
   CPU->regFile_WE =  1;
   CPU->NZP_WE =  1;
   CPU->DATA_WE =  0;
   CPU->regInputVal = value;
   CPU->dmemAddr = 0;
   CPU->dmemValue = 0;

  
 SetNZP(CPU, value);
 WriteOut(CPU, output);
    
}

/*
 * Parses rest of jump operation and prints out.
 */
void JumpOp(MachineState* CPU, FILE* output)
{
  
   unsigned short int instruct = CPU->memory[CPU->PC];
   unsigned short int op_code = ISN_OP(instruct);
   unsigned short int value = 0;

  unsigned short int operation = ISN_15_11(instruct);

  
    


 
   CPU->rsMux_CTL =  0;
   CPU->rtMux_CTL =  0;
   CPU->rdMux_CTL =  0;
   CPU->regFile_WE =  0;
   CPU->NZP_WE =  0;
   CPU->DATA_WE =  0;
   CPU->regInputVal = 0;
   CPU->dmemAddr = 0;
   CPU->dmemValue = 0;


SetNZP(CPU, value);
 WriteOut(CPU, output);

  if(operation == 25) {
     int add = ISN_10_0(instruct);
    if(add & (1<<10)) {
         add = -(~add +1 &0x7FF);
       }

    CPU->PC =  (int) CPU->PC + (int) 1 + add;
  } else {
     unsigned short int Rs = ISN_8_6(instruct);
     
    CPU->PC = CPU->R[Rs];
  }
}

/*
 * Parses rest of JSR operation and prints out.
 */
void JSROp(MachineState* CPU, FILE* output)
{

   unsigned short int instruct = CPU->memory[CPU->PC];
   unsigned short int op_code = ISN_OP(instruct);
   unsigned short int value = CPU->PC + 1;

    unsigned short int operation = ISN_15_11(instruct);

     

    
   CPU->rsMux_CTL =  0;
   CPU->rtMux_CTL =  0;
   CPU->rdMux_CTL =  1;
   CPU->regFile_WE =  1;
   CPU->NZP_WE =  1;
   CPU->DATA_WE =  0;
   CPU->regInputVal = CPU->PC + 1;
   CPU->dmemAddr = 0;
   CPU->dmemValue = 0;


SetNZP(CPU, value);
 WriteOut(CPU, output);
 

  if(operation == 9) {
     
      int add = ISN_10_0(instruct);
       if(add & (1<<10)) {
         add = -(~add +1 &0x7FF);
       }

      unsigned short int add2 = add;
       
      CPU->R[7]= CPU->PC + 1;
      CPU->PC = (CPU->PC & 0x8000) | (add2 << 4);
     

    } else {

    unsigned short int Rs = ISN_8_6(instruct);

    if(Rs==7) {
      unsigned short int store = CPU->R[7];
       CPU->R[7]= CPU->PC + 1;
       CPU->PC = store;
    } else {
 
    CPU->R[7]= CPU->PC + 1;
    CPU->PC = CPU->R[Rs];
    }

    }




}

/*
 * Parses rest of shift/mod operations and prints out.
 */
void ShiftModOp(MachineState* CPU, FILE* output)
{

  unsigned short int instruct = (*CPU).memory[(*CPU).PC];
  unsigned short int op_code = ISN_OP(instruct);
  unsigned short int value = 0;
  unsigned short int Rd = ISN_11_9(instruct);
  unsigned short int Rs = ISN_8_6(instruct);

  unsigned short int operation = ISN_5_4(instruct);
  unsigned short int add = 0;
  unsigned short int Rt = 0;

  switch(operation) {
       case (0x0000): //SLL
          add = ISN_3_0(instruct);
         value = CPU->R[Rs] << add;
         break;
      case (0x0001): //SRA
         add = ISN_3_0(instruct);
         value = (unsigned short) ((signed short) CPU->R[Rs] >> add);
         break;
      case (0x0002): //SRL
         add = ISN_3_0(instruct);
         value = CPU->R[Rs] >> add;
         break;
       case (0x0003): //MOD
         Rt = ISN_2_0(instruct);
         value = isNegativeConvertToPositive(CPU->R[Rs]) % isNegativeConvertToPositive(CPU->R[Rt]);
         break;
       

     }
    

   CPU->R[Rd] = value;
   CPU->rsMux_CTL =  0;
   CPU->rtMux_CTL =  0;
   CPU->rdMux_CTL =  0;
   CPU->regFile_WE =  1;
   CPU->NZP_WE =  1;
   CPU->DATA_WE =  0;
   CPU->regInputVal = value;
   CPU->dmemAddr = 0;
   CPU->dmemValue = 0;

  


  SetNZP(CPU, value);
 WriteOut(CPU, output);


}

/*
 * Set the NZP bits in the PSR.
 */
void SetNZP(MachineState* CPU, short result)
{

  if(CPU->NZP_WE ==  1) {
    if((result & (1<<15)) != 0){
   CPU->NZPVal = 4;
   CPU->PSR &= 0xFFF8;
    CPU->PSR |= 0x0004;
     
   }  else if(result == 0) {
    CPU->NZPVal = 2;
     CPU->PSR &= 0xFFF8; 
      CPU->PSR |= 0x0002;
   } else {
      CPU->NZPVal = 1;
       CPU->PSR &= 0xFFF8;
    CPU->PSR |= 0x0001;
   }

  }  else {
     CPU->NZPVal = 0;
  }

}
