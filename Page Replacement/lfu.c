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


int findFrame(int counter[], int num_of_frames) {
    int min = counter[0], target_frame = 0;

    for (int i = 1; i < num_of_frames; i++) {
        if (counter[i] < min) {
            min = counter[i];
            target_frame = i;
        }
    }
    return target_frame;
}

void LFU(int num_of_frames, int frames[num_of_frames], int num_of_pages, int pages[num_of_pages]) {
    int page_faults = 0, counter[num_of_frames];
    memset(counter, 0, sizeof(int)*num_of_frames);

    for (int i = 0; i < num_of_pages; i++) {
        int found = 0;

        for (int j = 0; j < num_of_frames; j++) {
            if (frames[j] == pages[i]) {
                found = 1;
                counter[j]++;
                printf("HIT: page %d is present \n",pages[i]);
                break;
            }
        }

        if (!found) {
            int target_frame = findFrame(counter, num_of_frames);
            frames[target_frame] = pages[i];
            counter[target_frame] = 1;
            page_faults++;
            printf("MISS: page %d is not present\n", pages[i]);
        }

        display(num_of_frames, frames);
    }

    printf("Total Page Faults: %d\n", page_faults);
}

int main() {
    int num_of_pages, num_of_frames;
    printf("LFU Page Replacement Algorithm\n");
    printf("Enter no. of pages: ");
    scanf("%d", &num_of_pages);
    int pages[num_of_pages];

    printf("Enter page reference sequence: ");
    for (int i = 0; i < num_of_pages; i++)
        scanf("%d", &pages[i]);

    printf("Enter no. of frames: ");
    scanf("%d", &num_of_frames);
    int frames[num_of_frames];

    memset(frames, -1, sizeof(int)*num_of_frames);
    LFU(num_of_frames, frames, num_of_pages, pages);
}