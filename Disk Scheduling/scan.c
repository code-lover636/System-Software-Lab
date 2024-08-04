#include <stdio.h>
#include <stdlib.h>

int scanShedule(int no_of_requests, int requests[no_of_requests], int current, int direction, int diskSize){
    int seek_time = 0, start_index=0, counter;

    while(requests[start_index]<=current)
        start_index++;
    counter = start_index;

    if (direction == -1){
        while(counter>0){
            counter--;
            seek_time += abs(requests[counter] - current);
            current = requests[counter];
            
        }
        while(start_index < no_of_requests-1){

            seek_time += abs(requests[start_index] - current);
            current = requests[start_index];
            start_index++;
        }
    }
    else{
        while(start_index < no_of_requests){
            seek_time += abs(requests[start_index] - current);
            current = requests[start_index];
            start_index++;
        }
        while(counter>1){
            counter--;
            seek_time += abs(requests[counter] - current);
            current = requests[counter];
        }
    }

    return seek_time;
}

int main() {
    // Inputs
    int no_of_requests, current, diskSize, direction;
    printf("Enter the number of disk requests: ");
    scanf("%d", &no_of_requests);
    printf("Enter the size of disk: ");
    scanf("%d", &diskSize);
    printf("Enter initial head position: ");
    scanf("%d", &current);
    printf("Enter direction (1 or -1): ");
    scanf("%d", &direction);


    no_of_requests += 2;
    int requests[no_of_requests];
    requests[0] = 0;
    requests[1] = diskSize - 1;


    printf("Enter %d disk requests: ", no_of_requests-2);
    for (int i = 2; i < no_of_requests; i++)
        scanf("%d", &requests[i]);
    
    // Sort the request array
    for (int i=0; i < no_of_requests - 1; i++) {
        for (int j = 0; j < no_of_requests - i - 1; j++) {
            if (requests[j] > requests[j + 1]) {
                int temp = requests[j];
                requests[j] = requests[j + 1];
                requests[j + 1] = temp;
            }
        }
    }

    printf("No. of head movement = %d\n", scanShedule(no_of_requests, requests, current, direction, diskSize));
}
