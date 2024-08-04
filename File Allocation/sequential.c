#include <stdio.h>
#include <string.h>

#define DISK_SIZE 100 // Total number of blocks on the disk
#define FILENAME_SIZE 20

typedef struct {
    char filename[FILENAME_SIZE];
    int startBlock;
    int size;
} File;

File disk[DISK_SIZE];
int diskUsage[DISK_SIZE] = {0}; // 0 indicates free, 1 indicates occupied

void initializeDisk() {
    for (int i = 0; i < DISK_SIZE; i++) {
        disk[i].filename[0] = '\0'; // Empty filename indicates no file
    }
}

void displayDisk() {
    printf("File Allocation Table:\n");
    for (int i = 0; i < DISK_SIZE; i++) {
        if (diskUsage[i] == 1) {
            printf("Block %d: %s\n", i, disk[i].filename);
        } else {
            printf("Block %d: [free]\n", i);
        }
    }
}

int allocateFile(char* filename, int size) {
    if (size > DISK_SIZE) {
        printf("File size is too large!\n");
        return -1;
    }
    
    // Find a contiguous block of free space
    for (int i = 0; i <= DISK_SIZE - size; i++) {
        int found = 1;
        for (int j = 0; j < size; j++) {
            if (diskUsage[i + j] == 1) {
                found = 0;
                break;
            }
        }
        
        if (found) {
            for (int j = 0; j < size; j++) {
                diskUsage[i + j] = 1;
                strcpy(disk[i + j].filename, filename);
            }
            printf("File '%s' allocated from block %d to block %d\n", filename, i, i + size - 1);
            return i;
        }
    }
    
    printf("Not enough contiguous space available!\n");
    return -1;
}


void main() {
    initializeDisk();
    
    int no_of_files;
    printf("Enter no. of files to be allocated: ");
    scanf("%d", &no_of_files);

    if(no_of_files>DISK_SIZE)
        printf("Not enough space in disk.\n");
    
    for(int i=0; i<no_of_files; i++){
        printf("Enter name of file%d: ", i+1);
        scanf("%d", &disk[i].filename);
        printf("Enter starting block of file%d: ", i+1);
        scanf("%d", &disk[i].startBlock);
        printf("Enter size of file%d: ", i+1);
        scanf("%d", &disk[i].size);
        printf("\n");
    }
    displayDisk();
}
