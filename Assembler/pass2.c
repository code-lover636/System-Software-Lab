#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void itoa(int n, char s[], int base) {
    sprintf(s, "%X", n); // Convert integer to hexadecimal string
}

int main() {
    char a[10], ad[10], label[10], opcode[10], operand[10], symbol[10], ch;
    int st, diff, i, address = 0, add, len, actual_len, finaddr, prevaddr = 0, j;
    char mnemonic[15][15] = {"LDA", "STA", "LDCH", "STCH"};
    char code[15][15] = {"33", "44", "53", "57"};
    FILE *fp1, *fp2, *fp3, *fp4;

    fp1 = fopen("ASSMLIST.DAT", "w");
    fp2 = fopen("SYMTAB.DAT", "r");
    fp3 = fopen("INTERMED.DAT", "r");
    fp4 = fopen("OBJCODE.DAT", "w");

    if (!fp1 || !fp2 || !fp3 || !fp4) {
        printf("Error opening file!\n");
        return 1;
    }

    fscanf(fp3, "%s%s%s", label, opcode, operand);
    while (strcmp(opcode, "END") != 0) {
        prevaddr = address;
        fscanf(fp3, "%d%s%s%s", &address, label, opcode, operand);
    }

    finaddr = address;
    fclose(fp3);
    fp3 = fopen("INTERMED.DAT", "r");

    fscanf(fp3, "%s%s%s", label, opcode, operand);
    if (strcmp(opcode, "START") == 0) {
        fprintf(fp1, "\t%s\t%s\t%s\n", label, opcode, operand);
        fprintf(fp4, "H^%s^00%s^00%d\n", label, operand, finaddr);
        fscanf(fp3, "%d%s%s%s", &address, label, opcode, operand);
        st = address;
        diff = prevaddr - st;
        fprintf(fp4, "T^00%d^%d", address, diff);
    }

    while (strcmp(opcode, "END") != 0) {
        if (strcmp(opcode, "BYTE") == 0) {
            fprintf(fp1, "%d\t%s\t%s\t%s\t", address, label, opcode, operand);
            len = strlen(operand);
            actual_len = len - 3;
            fprintf(fp4, "^");
            for (i = 2; i < (actual_len + 2); i++) {
                itoa(operand[i], ad, 16);
                fprintf(fp1, "%s", ad);
                fprintf(fp4, "%s", ad);
            }
            fprintf(fp1, "\n");
        } else if (strcmp(opcode, "WORD") == 0) {
            len = strlen(operand);
            itoa(atoi(operand), a, 10);
            fprintf(fp1, "%d\t%s\t%s\t%s\t00000%s\n", address, label, opcode, operand, a);
            fprintf(fp4, "^00000%s", a);
        } else if ((strcmp(opcode, "RESB") == 0) || (strcmp(opcode, "RESW") == 0)) {
            fprintf(fp1, "%d\t%s\t%s\t%s\n", address, label, opcode, operand);
        } else {
            j = 0;  // Initialize j before using it
            while (j < 4 && strcmp(opcode, mnemonic[j]) != 0) j++;  // Prevent endless loop
            if (j >= 4) {
                printf("Error: Unknown opcode '%s'\n", opcode);
                return 1;
            }

            if (strcmp(operand, "COPY") == 0)
                fprintf(fp1, "%d\t%s\t%s\t%s\t%s0000\n", address, label, opcode, operand, code[j]);
            else {
                rewind(fp2);
                fscanf(fp2, "%s%d", symbol, &add);
                while (strcmp(operand, symbol) != 0)
                    fscanf(fp2, "%s%d", symbol, &add);
                fprintf(fp1, "%d\t%s\t%s\t%s\t%s%d\n", address, label, opcode, operand, code[j], add);
                fprintf(fp4, "^%s%d", code[j], add);
            }
        }
        fscanf(fp3, "%d%s%s%s", &address, label, opcode, operand);
    }

    fprintf(fp1, "%d\t%s\t%s\t%s\n", address, label, opcode, operand);
    fprintf(fp4, "\nE^00%d", st);
    printf("\nIntermediate file is converted into object code");

    fclose(fp1);
    fclose(fp2);
    fclose(fp3);
    fclose(fp4);

    // Display the contents of the files
    printf("\n\nThe contents of Intermediate file:\n\n");
    fp3 = fopen("INTERMED.DAT", "r");
    ch = fgetc(fp3);
    while (ch != EOF) {
        printf("%c", ch);
        ch = fgetc(fp3);
    }
    fclose(fp3);

    printf("\n\nThe contents of Symbol Table:\n\n");
    fp2 = fopen("SYMTAB.DAT", "r");
    ch = fgetc(fp2);
    while (ch != EOF) {
        printf("%c", ch);
        ch = fgetc(fp2);
    }
    fclose(fp2);

    printf("\n\nThe contents of Output file:\n\n");
    fp1 = fopen("ASSMLIST.DAT", "r");
    ch = fgetc(fp1);
    while (ch != EOF) {
        printf("%c", ch);
        ch = fgetc(fp1);
    }
    fclose(fp1);

    printf("\n\nThe contents of Object code file:\n\n");
    fp4 = fopen("OBJCODE.DAT", "r");
    ch = fgetc(fp4);
    while (ch != EOF) {
        printf("%c", ch);
        ch = fgetc(fp4);
    }
    fclose(fp4);

    return 0;
}
