#include <stdio.h>
#include <string.h>

int printTable(int n, int id[n], int bt[n], int at[n], int tat[n], int wt[n], int pt[n])
{
    int avgT = 0, avgW = 0;
    printf("Process ID:\tArrival Time:\tBurst Time:\tPriority:\tTurn Around Time:\tWait Time:\n");
    for (int i = 0; i < n; i++)
    {
        printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t\t%d\n", id[i], at[i], bt[i], pt[i], tat[i], wt[i]);
        avgT += tat[i];
        avgW += wt[i];
    }
    printf("Average Turn Around Time: %f\n", (float)avgT / n);
    printf("Average Waiting Time: %f\n", (float)avgW / n);
}



void prioritySchedule(int n, int bt[n], int at[n], int tat[n], int wt[n])
{
    int completed = 0, time = 0, flag, completedProcesses[n];

    memset(completedProcesses, -1, sizeof(completedProcesses));

    while (completed < n)
    {
        flag = 0;
        for (int i = 0; i < n; i++)
        {
            if (at[i] <= time && completedProcesses[i] != 1)
            {
                time += bt[i];
                tat[i] = time - at[i];
                wt[i] = tat[i] - bt[i];
                completedProcesses[i] = 1;
                completed++;
                flag = 1;
                break;
            }
        }
        if (!flag)
        {
            time++;
        }
    }
}

int main()
{
    int n, temp;
    printf("Enter number of processes: ");
    scanf("%d", &n);
    int id[n], at[n], bt[n], wt[n], tat[n], pt[n];

    printf("Enter (arrival time, burst time, priority) for %d process\n", n);
    for (int i = 0; i < n; i++)
    {
        // printf("Enter arrival time of process %d: ", i+1);
        scanf("%d", &at[i]);
        // printf("Enter burst time of process %d: ", i+1);
        scanf("%d", &bt[i]);
        // printf("Enter priority of process %d: ", i+1);
        scanf("%d", &pt[i]);
        id[i] = i;
    }

    // Sort processes
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (pt[j] > pt[j + 1])
            {
                temp = at[j];
                at[j] = at[j + 1];
                at[j + 1] = temp;

                temp = bt[j];
                bt[j] = bt[j + 1];
                bt[j + 1] = temp;

                temp = pt[j];
                pt[j] = pt[j + 1];
                pt[j + 1] = temp;

                temp = id[j];
                id[j] = id[j + 1];
                id[j + 1] = temp;
            }
        }
    }

    prioritySchedule(n, bt, at, tat, wt);
    printTable(n, id, bt, at, tat, wt, pt);
}

/*

0 8 3
1 2 4
3 4 4
4 1 5
5 6 2
6 5 6
10 1 1

*/
