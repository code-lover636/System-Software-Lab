#include <stdio.h>
#include <stdlib.h>
#include <string.h>

FILE *argtab, *namtab, *deftab, *output, *input;
char opcode[10], operand[10], label[10], parameter[10];
int EXPANDING = 0;
int POSITIONAL_VALUE = 1;

int set_up_arguments_in_argtab();
int substitute_arguments();
int substitute_positional_notation();
int PROCESSLINE();
int DEFINE();
int EXPAND();
int GETLINE();


int main(){

    argtab = fopen("argtab.txt", "w");
    output = fopen("expanded_file.txt", "w");
    input = fopen("input.txt", "r");

    fscanf(input, "%s %s %s", label, opcode, operand);
    while(strcmp(opcode, "END") != 0){
        PROCESSLINE();
        GETLINE();
    }

    fclose(argtab);
    fclose(output);
    fclose(input);
}


int PROCESSLINE(){
    
    //Searching NAMTAB for OPCODE
    namtab = fopen("namtab.txt", "r");
    char name[10];
    while(fscanf(namtab, "%s", name) != EOF){
        if(strcmp(name, opcode) == 0){
            fclose(namtab);
            EXPAND();
            return 0;
        }
    }

    //If opcode is not found in NAMTAB
    if(strcmp(opcode, "MACRO") == 0){
        DEFINE();
    } 
    else
        fprintf(output, "%s\t%s\t%s\n", label, opcode, operand);
    
}

int substitute_arguments(){
    
    char arg[100][10];
    int i = 0, j = 0;

    //Reading arguments from argtab.txt to array arg
    argtab = fopen("argtab.txt", "r");
    while(fscanf(argtab, "%s", arg[i]) != EOF) i++;
    fclose(argtab);  
 
    //positional notation - 1 will be the index of the corresponding argument in arg[]
    parameter[0] = '\0';  
    for(int i=0; i<strlen(operand); i++) {
        if(operand[i] == '?'){
            i++;
            j = operand[i] - '1';
            strcat(parameter, arg[j]);
        } 
        else 
            strncat(parameter, &operand[i], 1);  
    }

    //Copying the substituted arguments to operand
    strcpy(operand, parameter);
}

int GETLINE(){
    if(EXPANDING){
        fscanf(deftab, "%s%s%s", label, opcode, operand);
        substitute_arguments();
    } else {
        fscanf(input, "%s %s %s", label, opcode, operand);
    }
}

int set_up_arguments_in_argtab(){
    argtab = fopen("argtab.txt", "a");
    char arg[10];
    int j = 0;

    //For each argument in operand(of the invocation statment), write it to argtab.txt
    for(int i=0; i<strlen(operand); i++){
        if(operand[i] == ','){
            arg[j] = '\0';
            fprintf(argtab, "%s\n", arg);
            j = 0;
        } 
        else 
            arg[j++] = operand[i];
        
    }
    fprintf(argtab, "%s\n", arg);
    fclose(argtab);
}

int EXPAND(){
    EXPANDING = 1;
    deftab = fopen("deftab.txt", "r");

    set_up_arguments_in_argtab();  
    fprintf(output, ".\t%s\t%s\t%s\n", label, opcode, operand);

    //Skip the first line of the macro (macro heading)
    fscanf(deftab, "%s%s%s", label, opcode, operand);

    while(strcmp(opcode, "MEND") != 0){
        GETLINE();
        PROCESSLINE();
    }

    EXPANDING = 0;
    fclose(deftab);
    return 0;
}

int substitute_positional_notation(){
    char arg[10];
    int i = 0;
    
    //Positional notation - ?1, ?2, ?3, ...
    while(operand[i] != '\0'){
        if(operand[i] == '&'){      
            sprintf(parameter, "?%d\0", POSITIONAL_VALUE++);
        }
        i++;
    }
    
}

int DEFINE(){
    namtab = fopen("namtab.txt", "a");  
    deftab = fopen("deftab.txt", "a");  

    fprintf(namtab, "%s\n", label);
    fprintf(deftab, "%s\t%s\t%s\n", label, opcode, operand);
    
    int LEVEL = 1;
    while(LEVEL > 0) {
        GETLINE();
        
        //If not a comment line (comment line starts with '.')
        if(label[0] != '.'){
            if(strcmp(opcode, "MACRO") == 0){
                LEVEL++;
            }
            else if(strcmp(opcode, "MEND") == 0){
                fprintf(deftab, "**\tMEND\t**\n");
                LEVEL--;
            }
            else {
                substitute_positional_notation();
                fprintf(deftab, "%s\t%s\t%s\n", label, opcode, parameter);
            }
        }
    }

    fclose(namtab);
    fclose(deftab);
}

