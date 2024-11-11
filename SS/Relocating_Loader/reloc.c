#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char bit[13] = {0};

int convert(char h[12]) {
    strcpy(bit, "");

    for (int i = 0; i < strlen(h); i++) {
        switch (h[i]){
            case '0':
                strcat(bit, "0000");
                break;
            case '1':
                strcat(bit, "0001");
                break;
            case '2':
                strcat(bit, "0010");
                break;
            case '3':
                strcat(bit, "0011");
                break;
            case '4':
                strcat(bit, "0100");
                break;
            case '5':
                strcat(bit, "0101");
                break;
            case '6':
                strcat(bit, "0110");
                break;
            case '7':
                strcat(bit, "0111");
                break;
            case '8':
                strcat(bit, "1000");
                break;
            case '9':
                strcat(bit, "1001");
                break;
            case 'A':
                strcat(bit, "1010");
                break;
            case 'B':
                strcat(bit, "1011");
                break;
            case 'C':
                strcat(bit, "1100");
                break;
            case 'D':
                strcat(bit, "1101");
                break;
            case 'E':
                strcat(bit, "1110");
                break;
            case 'F':
                strcat(bit, "1111");
                break;
        }
    }
}

int main(){
    FILE *input, *output;
    char line[100], *bitmask, *token, *pgname, *start_addr, *length, *tlen;
    int PROGADDR, start;

    input = fopen("input.dat", "r");
    output = fopen("output.dat", "w");

    printf("Enter the actual starting address : ");
    scanf("%x", &PROGADDR);

    fscanf(input, "%s", line);
    token = strtok(line, "^");
    if(strcmp(token, "H") == 0){
        pgname = strtok(NULL, "^");
        start_addr = strtok(NULL, "^");
        length = strtok(NULL, "^");
    }

    while(line[0] != 'E'){
        fscanf(input, "%s", line);
        token = strtok(line, "^");

        if(strcmp(token, "T")==0){
            token = strtok(NULL, "^");
            start = strtol(token, NULL, 16);
            tlen = strtok(NULL, "^");
            bitmask = strtok(NULL, "^");

            convert(bitmask);
            for(int i=0; i<strlen(bit); i++){
                token = strtok(NULL, "^");
                if(token == NULL) break;
                int addr = strtol(token, NULL, 16);
                if(bit[i] == '1'){
                    addr += PROGADDR;
                    
                }
                fprintf(output, "%06x\t%06x\n", start, addr);
                start += 3;
            }
        }
    }
    fclose(input);
    fclose(output);
}