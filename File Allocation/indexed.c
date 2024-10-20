#include <stdio.h>
#include <stdlib.h>

struct File {
    int start, length, num, *blocks;
};

int main() {
    int n;
    printf("Enter number of files to be added: ");
    scanf("%d", &n);
    struct File files[n];
    for (int i = 0; i < n; ++i) {
        printf("Enter start address, length, and number of blocks: ");
        scanf("%d %d %d", &files[i].start, &files[i].length, &files[i].num);
        files[i].blocks = malloc(files[i].num * sizeof(int));
        printf("Enter blocks: ");
        for (int j = 0; j < files[i].num; ++j) {
            scanf("%d", files[i].blocks + j);
        }
    }
    
    printf("\nAllocation table:\n");
    printf("%-8s %-15s %-10s %-15s\n", "File No", "No of Blocks", "Length", "Start Address");
    for (int i = 0; i < n; ++i) {
        printf("%-8d %-15d %-10d %-15d\n", i, files[i].num, files[i].length, files[i].start);
    }

    while (1) {
        printf("\n1. Get the blocks\n");
        printf("2. Exit\n");
        printf("Enter your choice: ");
        int current;
        scanf("%d", &current);
        
        if (current == 1) {
            printf("Enter file number: ");
            int fn;
            scanf("%d", &fn);
            if (fn >= 0 && fn < n) {
                printf("Blocks for file %d: ", fn);
                for (int i = 0; i < files[fn].num; ++i) {
                    printf("%d ", files[fn].blocks[i]);
                }
                printf("\n");
            } else {
                printf("Invalid file number.\n");
            }
        } else if (current == 2) {
            
            for (int i = 0; i < n; ++i) {
                free(files[i].blocks);
            }
            return 0;
        } else {
            printf("Enter valid input\n");
        }
    }
}
