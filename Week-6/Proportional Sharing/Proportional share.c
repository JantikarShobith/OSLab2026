#include <stdio.h>

#define MAX 10

struct Process {
    int id;
    int burst;
    int remaining;
    int weight;
    int completed;
};

int main() {
    int n, TIME_QUANTUM;
    struct Process p[MAX];
    int total_weight = 0;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    // Input
    for (int i = 0; i < n; i++) {
        printf("Enter burst time and weight for P%d: ", i + 1);
        scanf("%d %d", &p[i].burst, &p[i].weight);

        p[i].id = i + 1;
        p[i].remaining = p[i].burst;
        p[i].completed = 0;

        total_weight += p[i].weight;
    }

    printf("Enter TIME QUANTUM: ");
    scanf("%d", &TIME_QUANTUM);

    int time = 0;

    printf("\nTime\tRunning Process\n");

    while (1) {
        int all_done = 1;

        for (int i = 0; i < n; i++) {

            if (p[i].remaining > 0) {
                all_done = 0;

                // Calculate time slice
                int slice = (p[i].weight * TIME_QUANTUM) / total_weight;

                if (slice <= 0)
                    slice = 1; // ensure minimum execution

                // Run process
                int run_time = (p[i].remaining < slice) ? p[i].remaining : slice;

                for (int t = 0; t < run_time; t++) {
                    printf("%d\tP%d\n", time++, p[i].id);
                }

                p[i].remaining -= run_time;

                // If finished
                if (p[i].remaining <= 0) {
                    p[i].completed = 1;
                    total_weight -= p[i].weight;
                }
            }
        }

        if (all_done)
            break;
    }

    return 0;
}
