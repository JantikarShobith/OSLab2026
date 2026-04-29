#include <stdio.h>

int main()
{
    int n, i, time = 0, completed = 0;
    int at[10], bt[10], pr[10];
    int ct[10], tat[10], wt[10];
    int visited[10] = {0};
    float avg_wt = 0, avg_tat = 0;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    for(i = 0; i < n; i++)
    {
        printf("\nProcess %d\n", i+1);

        printf("Arrival Time: ");
        scanf("%d", &at[i]);

        printf("Burst Time: ");
        scanf("%d", &bt[i]);

        printf("Priority: ");
        scanf("%d", &pr[i]);
    }

    while(completed < n)
    {
        int highest = 9999;
        int index = -1;

        for(i = 0; i < n; i++)
        {
            if(at[i] <= time && visited[i] == 0)
            {
                if(pr[i] < highest)
                {
                    highest = pr[i];
                    index = i;
                }
            }
        }

        if(index == -1)
        {
            time++;
        }
        else
        {
            time += bt[index];

            ct[index] = time;

            tat[index] = ct[index] - at[index];
            wt[index] = tat[index] - bt[index];

            avg_wt += wt[index];
            avg_tat += tat[index];

            visited[index] = 1;
            completed++;
        }
    }

    printf("\nProcess\tAT\tBT\tPR\tCT\tTAT\tWT\n");

    for(i = 0; i < n; i++)
    {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
               i+1, at[i], bt[i], pr[i], ct[i], tat[i], wt[i]);
    }

    printf("\nAverage Waiting Time = %.2f", avg_wt/n);
    printf("\nAverage Turnaround Time = %.2f\n", avg_tat/n);

    return 0;
}
