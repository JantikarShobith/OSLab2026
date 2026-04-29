#include <stdio.h>
#include <math.h>

#define MAX 10

struct Task {
    int id;
    int C;              // Execution time
    int T;              // Period
    int remaining;      // Remaining execution
    int next_arrival;   // Next arrival time
};

int main() {
    int n, time_limit;
    struct Task tasks[MAX];

    float U = 0, bound;

    printf("Enter number of tasks: ");
    scanf("%d", &n);

    // Input
    for (int i = 0; i < n; i++) {
        printf("Enter C and T for Task %d: ", i + 1);
        scanf("%d %d", &tasks[i].C, &tasks[i].T);

        tasks[i].id = i + 1;
        tasks[i].remaining = 0;
        tasks[i].next_arrival = 0;

        U += (float)tasks[i].C / tasks[i].T;
    }

    // RMS Bound
    bound = n * (pow(2, 1.0 / n) - 1);

    printf("\nCPU Utilization = %.4f\n", U);
    printf("RMS Bound = %.4f\n", bound);

    if (U <= bound)
        printf("✔ Guaranteed Schedulable\n");
    else
        printf("⚠ Not Guaranteed (but still simulating)\n");

    // Sort by period (priority)
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (tasks[i].T > tasks[j].T) {
                struct Task temp = tasks[i];
                tasks[i] = tasks[j];
                tasks[j] = temp;
            }
        }
    }

    // Show priority order
    printf("\nPriority Order (High → Low):\n");
    for (int i = 0; i < n; i++) {
        printf("Task %d (T = %d)\n", tasks[i].id, tasks[i].T);
    }

    printf("\nEnter simulation time: ");
    scanf("%d", &time_limit);

    printf("\nTime\tRunning Task\n");

    // Simulation loop
    for (int t = 0; t < time_limit; t++) {

        // Arrival of tasks
        for (int i = 0; i < n; i++) {
            if (t == tasks[i].next_arrival) {
                tasks[i].remaining = tasks[i].C;
                tasks[i].next_arrival += tasks[i].T;
            }
        }

        // Pick highest priority ready task
        int selected = -1;
        for (int i = 0; i < n; i++) {
            if (tasks[i].remaining > 0) {
                selected = i;
                break;
            }
        }

        // Execute
        if (selected != -1) {
            printf("%d\tTask %d\n", t, tasks[selected].id);
            tasks[selected].remaining--;
        } else {
            printf("%d\tIdle\n", t);
        }
    }

    return 0;
}
