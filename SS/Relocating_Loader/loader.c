#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char bitmask[12];
char bit[12] = {0};

FILE *inputF, *outputF;
char progname[10], starting_address[10], length[10], input[10];
int PROGADDR;


int convert(char h[12]) {
    strcpy(bit, "");

    for (int i = 0; i < strlen(h); i++) {
        switch (h[i]){
            case '0':
                strcat(bit, "0");
                break;
            case '1':
                strcat(bit, "1");
                break;
            case '2':
                strcat(bit, "10");
                break;
            case '3':
                strcat(bit, "11");
                break;
            case '4':
                strcat(bit, "100");
                break;
            case '5':
                strcat(bit, "101");
                break;
            case '6':
                strcat(bit, "110");
                break;
            case '7':
                strcat(bit, "111");
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


int main() {
    inputF = fopen("input.txt", "r");
    outputF = fopen("output.txt", "w");

    printf("Enter the actual starting address : ");
    scanf("%x", &PROGADDR);

    fscanf(inputF, "%s", input);
    fprintf(outputF, "---------------------------\n");
    fprintf(outputF, " ADDRESS\tCONTENT\n");
    fprintf(outputF, "---------------------------\n");
    while (strcmp(input, "E") != 0) {
        
        //Read Header Record
        if (strcmp(input, "H") == 0) {
            fscanf(inputF, "%s", progname);
            fscanf(inputF, "%x", starting_address);
            fscanf(inputF, "%x", length);
            fscanf(inputF, "%s", input);
        }

        //Read Text Record
        int address, tlen, opcode, addr, actualadd;
        char relocbit;

        if (strcmp(input, "T") == 0) {
            fscanf(inputF, "%x", &address);
            fscanf(inputF, "%x", &tlen);
            fscanf(inputF, "%s", bitmask);
            address += PROGADDR;
            convert(bitmask);

            for (int i = 0; i < strlen(bit); i++) {
                fscanf(inputF, "%x", &opcode);
                fscanf(inputF, "%x", &addr);
                relocbit = bit[i];
                if (relocbit == '0')
                    actualadd = addr;
                else
                    actualadd = addr + PROGADDR;
                fprintf(outputF, "\n %x\t\t%x%x\n", address, opcode, actualadd);
                address += 3;
            }
            fscanf(inputF, "%s", input);
        }
    }

    fclose(inputF);
    fclose(outputF);
}