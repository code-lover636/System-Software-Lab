#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void display(int num_of_frames, int frames[num_of_frames]) {
    for (int i = 0; i < num_of_frames; i++) {
        if (frames[i] != -1)
            printf("%d ", frames[i]);
        else
            printf("_ ");
    }
    printf("\n");
}


void FIFO(int num_of_frames, int frames[num_of_frames], int num_of_pages, int pages[num_of_pages]) {
    int page_faults = 0, rear=0;

    for (int i = 0; i < num_of_pages; i++) {
        int found = 0;

        for (int j = 0; j < num_of_frames; j++) {
            if (frames[j] == pages[i]) {
                found = 1;
                printf("\nHIT: page %d is present \n",pages[i]);
                break;
            }
        }

        if (!found) {
            printf("\nMISS: page %d is not present\n", pages[i]);
            page_faults++;
            frames[rear] = pages[i];
            rear = (rear + 1) % num_of_frames;
        }

        display(num_of_frames, frames);
    }

    printf("Total Page Faults: %d\n", page_faults);
}

int main() {
    int num_of_pages, num_of_frames;
    printf("FIFO Page Replacement Algorithm\n");
    printf("Enter no. of pages: ");
    scanf("%d", &num_of_pages);
    int pages[num_of_pages];

    printf("Enter page reference sequence: ");
    for (int i = 0; i < num_of_pages; i++)
        scanf("%d", &pages[i]);

    printf("Enter no. of frames: ");
    scanf("%d", &num_of_frames);
    int frames[num_of_frames];

    memset(frames, -1, sizeof(frames));
    FIFO(num_of_frames, frames, num_of_pages, pages);
}