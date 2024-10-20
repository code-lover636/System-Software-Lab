#include <stdio.h>

int main() {
    char name[10][30]; 
    int start[10], length[10], num, count = 0;

    printf("Enter the number of files to be allocated: ");
    scanf("%d", &num);

    for (int i = 0; i < num; i++) {
        printf("Enter the name of the file %d: ", i + 1);
        scanf("%s", name[i]);
        printf("Enter the start block of the file %d: ", i + 1);
        scanf("%d", &start[i]);
        printf("Enter the length of the file %d: ", i + 1);
        scanf("%d", &length[i]);

        for (int j = 0; j < i; j++) {
            if ((start[i] >= start[j] && start[i] < start[j] + length[j]) || 
                (start[i] + length[i] > start[j] && start[i] < start[j])) {
                count = 1;
                break;
            }
        }

        if (count == 1) {
            printf("%s cannot be allocated disk space due to overlap\n", name[i]);
            count = 0; 
        }
    }

    printf("\nFile Allocation Table\n");
    printf("%-20s %-20s %-20s\n", "File Name", "Start Block", "Length");
 
    for (int i = 0; i < num; i++) {
        printf("%-20s %-20d %-20d\n", name[i], start[i], length[i]);
    }

    return 0;
}
