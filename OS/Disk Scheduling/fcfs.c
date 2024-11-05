#include <stdio.h>
#include <stdlib.h>

int main() {
    int no_of_requests, seek_time = 0, current;
    printf("Enter the number of disk requests: ");
    scanf("%d", &no_of_requests);
    int requests[no_of_requests];

    printf("Enter initial head position: ");
    scanf("%d", &current);

    printf("Enter %d disk requests: ", no_of_requests);
    for (int i = 0; i < no_of_requests; i++)
        scanf("%d", &requests[i]);

    for (int i = 0; i < no_of_requests; i++) {
        seek_time += abs(current - requests[i]);
        current = requests[i];
    }

    printf("No. of head movement = %d\n", seek_time);
}