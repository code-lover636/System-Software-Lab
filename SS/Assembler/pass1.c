#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){
    FILE *inpf = fopen("input.txt", "r");
    FILE *opf = fopen("optab.txt", "r");
    FILE *outf = fopen("output.txt", "w");
    FILE *symf = fopen("symtab.txt", "w");

    int locctr=0, start=0, prev;
    char operand[10], opcode[10], label[10], symbol[10], code[10];

    fscanf(inpf, "%s%s%x", label, opcode, &start);
    if(strcmp(opcode, "START")==0){
        locctr = start;
        fprintf(outf, "**%10s%10s\t%x\n", label, opcode, start);
        fscanf(inpf, "%s%s%s", label, opcode, operand);
    }
    

    while(strcmp(opcode, "END") != 0){
        prev = locctr;
        // label
        if(strcmp(label, "**") != 0){
            fprintf(symf, "%s\t%x\n", label, locctr);
        }

        //opcode
        if(strcmp(opcode,"BYTE")==0){
            locctr++;
        }
        else if(strcmp(opcode,"WORD")==0){
            locctr += 3;
        }
        else if(strcmp(opcode,"RESB")==0){
            locctr += atoi(operand);
        }
        else if(strcmp(opcode,"RESW")==0){
            locctr += atoi(operand) * 3;
        }
        else{
            int flag = 0;
            rewind(opf);
            while(fscanf(opf, "%s%s", symbol, code)!=EOF){
                if(strcmp(symbol, opcode)==0){
                    flag = 1;
                    locctr += 3;
                    break;
                }
            }
            if(!flag){
                printf("Error: Opcode not found\n");
                exit(0);
            }
        }
        fprintf(outf, "%x%10s%10s%10s\n", prev, label, opcode, operand);
        fscanf(inpf, "%s%s%s", label, opcode, operand);
    }
    printf("length: %x\n", locctr-start);
    fprintf(outf, "%x%10s%10s%10s\n", locctr, label, opcode, operand);
    fclose(inpf);
    fclose(outf);
    fclose(symf);
    fclose(opf);
}