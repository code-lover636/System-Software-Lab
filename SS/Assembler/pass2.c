#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(){
    FILE * inpF = fopen("output.txt", "r");
    FILE * optab = fopen("optab.txt", "r");
    FILE * symtab = fopen("symtab.txt", "r");
    FILE * objF = fopen("object.txt", "w");
    FILE * outF = fopen("finaloutput.txt", "w");

    char label[10], opcode[10], operand[10], loc[10], code[10], symbol[10];
    int prevaddr, finaddr, length,start;

    fscanf(inpF, "%s%s%s%s", loc, label, opcode, operand);
    while(strcmp(opcode, "END")!=0){
        prevaddr = atoi(loc);
        fscanf(inpF, "%s%s%s%s", loc, label, opcode, operand);
    }
    finaddr = atoi(loc);
    fclose(inpF);

    inpF = fopen("output.txt", "r");
    fscanf(inpF, "%s%s%s%s", loc, label, opcode, operand);
    if(strcmp(opcode, "START")==0){
        start = atoi(operand);
        fprintf(outF, "%s\t%10s%10s%10s\t%s\n", loc, label, opcode, operand, "**");
        printf("%s\n", loc);
        fprintf(objF, "H^%s^%06d^%06X\n", label, atoi(operand), finaddr - atoi(operand));
        fprintf(objF, "T^%06d^%X", atoi(operand), prevaddr - atoi(operand));
        fscanf(inpF, "%s%s%s%s", loc, label, opcode, operand);
    }

    while(strcmp(opcode, "END")!=0){

        if(strcmp(opcode,"BYTE")==0){
            fprintf(outF, "%s%10s%10s%10s\t", loc, label, opcode, operand);
            fprintf(objF, "^");
            length = strlen(operand) - 3;

            for(int i = 2; i<length+2; i++){
                fprintf(outF, "%X", operand[i]);
                fprintf(objF, "%X", operand[i]);
            }
            fprintf(outF, "\n");

        }
        else if(strcmp(opcode,"WORD")==0){
            fprintf(outF, "%s%10s%10s%10s\t%06d\n", loc, label, opcode, operand, atoi(operand));
            fprintf(objF, "^%06d", atoi(operand));
        }
        else if(strcmp(opcode,"RESB")==0 || strcmp(opcode,"RESW")==0){
            fprintf(outF, "%s%10s%10s%10s\n", loc, label, opcode, operand);
        }
        else{
            fprintf(outF, "%s%10s%10s%10s\t", loc, label, opcode, operand);
            if(strcmp(opcode, "END") != 0){
                rewind(optab);
                fscanf(optab, "%s%s", symbol, code);
                while(strcmp(symbol, opcode)!=0){
                    fscanf(optab, "%s%s", symbol, code);
                }
                fprintf(outF, "%s", code);
                fprintf(objF, "^%s", code);

                rewind(symtab);
                fscanf(symtab, "%s%s", symbol, code);
                while(strcmp(symbol, operand)!=0){
                    fscanf(symtab, "%s%s", symbol, code);
                }
                  
                fprintf(outF, "%s\n", code);
                fprintf(objF, "%s", code);
            }

        }
        fscanf(inpF, "%s%s%s%s", loc, label, opcode, operand);
    }
    fprintf(outF, "%s%10s%10s%10s\n", loc, label, opcode, operand);
    fprintf(objF, "\nE^%06d\n", start);
}