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

int findFrame(int num_of_frames, int counter[num_of_frames]) {
    int max = counter[0];
    int target_frame = 0;

    for (int i = 1; i < num_of_frames; i++) {
        if (counter[i] > max) {
            max = counter[i];
            target_frame = i;
        }
    }

    return target_frame;
}


void LRU(int num_of_frames, int frames[num_of_frames],int num_of_pages, int pages[num_of_pages]) {

    int page_faults = 0, counter[num_of_frames];
    memset(counter, 0, sizeof(int)*num_of_frames);

    for (int i = 0; i < num_of_pages; i++) {
        int found = 0;

        for (int j = 0; j < num_of_frames; j++) {
            if (frames[j] == pages[i]) {
                found = 1;
                printf("HIT: page %d is present \n",pages[i]);
                break;
            }
        }

        if (!found) {
            int target_frame = findFrame(num_of_frames, counter);
            printf("MISS: page %d is not present\n",pages[i]);
            frames[target_frame] = pages[i];
            counter[target_frame] = 0;
            page_faults++;
        }

        for (int j = 0; j < num_of_frames; j++)
            counter[j]++;

        for (int j = 0; j < num_of_frames; j++) {
            if (frames[j] == pages[i]) {
                counter[j] = 0;
                break;
            }
        }

        display(num_of_frames, frames);
    }

    printf("Total Page Faults: %d\n", page_faults);
}

int main() {
    int num_of_pages, num_of_frames;
    printf("LRU Page Replacement Algorithm\n");
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
    LRU(num_of_frames, frames, num_of_pages, pages);
}