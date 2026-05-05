#ifndef PROCESS_H
#define PROCESS_H

struct Process {
    int pid;                  // Process ID
    int arrivalTime;          // Time when process arrives in queue
    int burstTime;            // CPU time required
    int priority;             // Priority (1-10, lower = higher priority)
    int waitTime;             // Calculated wait time
    int turnaroundTime;       // Calculated turnaround time (waitTime + burstTime)
    int completionTime;       // Time when process completes
    
    Process(int id, int arrival, int burst, int prio = 0)
        : pid(id), arrivalTime(arrival), burstTime(burst), priority(prio),
          waitTime(0), turnaroundTime(0), completionTime(0) {}
};

#endif // PROCESS_H
