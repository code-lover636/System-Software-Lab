#include <stdio.h>
#include <stdlib.h>

int cScanShedule(int no_of_requests, int requests[no_of_requests], int current, int diskSize, int direction){
    int seek_time = 0, start_index=0;

    while(requests[start_index]<=current)
        start_index++;

    if(direction == 1){
        for(int i=start_index; i<no_of_requests; i++){
            seek_time += abs(requests[i] - current);
            current = requests[i];
            printf(">>%d\n", current);
        }
        current = 0;
        for(int i=0; i<start_index; i++){
            seek_time += abs(requests[i] - current);
            current = requests[i];
            printf("::%d\n", current);
        }
    }
    else{
        for(int i=start_index-1; i>=0; i--){
            seek_time += abs(requests[i] - current);
            current = requests[i];
            printf(">>%d\n", current);
        }
        current = 0;
        for(int i=start_index; i<no_of_requests; i++){
            seek_time += abs(requests[i] - current);
            current = requests[i];
            printf("::%d\n", current);
        }
    }

    return seek_time;
}

int main() {
    int no_of_requests, current, diskSize, direction;
    printf("Enter the number of disk requests: ");
    scanf("%d", &no_of_requests);
    printf("Enter initial head position: ");
    scanf("%d", &current);
    printf("Enter total disk size: ");
    scanf("%d", &diskSize);
    printf("Enter direction (1, -1): ");
    scanf("%d", &direction);

    no_of_requests += 2;
    int requests[no_of_requests];
    requests[0] = 0;
    requests[1] = diskSize-1;


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

    printf("\nNo. of head movement = %d\n", cScanShedule(no_of_requests, requests, current, diskSize, direction));
}
