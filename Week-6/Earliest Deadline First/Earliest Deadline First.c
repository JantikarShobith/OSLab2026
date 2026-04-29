#include <stdio.h>

#define MAX 10

struct Process {
    int id;
    int C;              // Execution time
    int D;              // Deadline
    int arrival;        // Arrival time
    int remaining;      // Remaining time
    int completed;
};

int main() {
    int n, time_limit;
    struct Process p[MAX];
    float U = 0;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    // Input
    for (int i = 0; i < n; i++) {
        printf("Enter C, D, Arrival for P%d: ", i + 1);
        scanf("%d %d %d", &p[i].C, &p[i].D, &p[i].arrival);

        p[i].id = i + 1;
        p[i].remaining = p[i].C;
        p[i].completed = 0;

        U += (float)p[i].C / p[i].D;
    }

    // Feasibility check
    printf("\nCPU Utilization = %.2f\n", U);
    if (U <= 1)
        printf(" Scheduling feasible\n");
    else
        printf(" Not guaranteed feasible\n");

    printf("\nEnter simulation time: ");
    scanf("%d", &time_limit);

    printf("\nTime\tRunning Process\n");

    // Simulation
    for (int t = 0; t < time_limit; t++) {

        int selected = -1;
        int earliest_deadline = 999999;

        // Find process with earliest deadline
        for (int i = 0; i < n; i++) {
            if (p[i].arrival <= t && p[i].remaining > 0) {
                if (p[i].D < earliest_deadline) {
                    earliest_deadline = p[i].D;
                    selected = i;
                }
            }
        }

        // Execute
        if (selected != -1) {
            printf("%d\tP%d\n", t, p[selected].id);
            p[selected].remaining--;

            if (p[selected].remaining == 0) {
                p[selected].completed = 1;
            }
        } else {
            printf("%d\tIdle\n", t);
        }
    }

    return 0;
}
