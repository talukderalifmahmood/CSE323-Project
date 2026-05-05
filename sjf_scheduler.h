#ifndef SJF_SCHEDULER_H
#define SJF_SCHEDULER_H

#include "scheduler.h"
#include <climits>

// Shortest Job First (Non-preemptive)
class SJFScheduler : public Scheduler {
public:
    void schedule() override {
        scheduledProcesses.clear();
        
        std::vector<Process> remaining = processes;
        int currentTime = 0;
        std::vector<bool> completed(remaining.size(), false);
        
        while (true) {
            int shortestIdx = -1;
            int shortestBurst = INT_MAX;
            
            // Find the process with shortest burst time that has arrived
            for (size_t i = 0; i < remaining.size(); i++) {
                if (!completed[i] && remaining[i].arrivalTime <= currentTime) {
                    if (remaining[i].burstTime < shortestBurst) {
                        shortestBurst = remaining[i].burstTime;
                        shortestIdx = i;
                    }
                }
            }
            
            if (shortestIdx == -1) {
                // No process arrived yet, find earliest arrival
                int earliestIdx = -1;
                int earliestArrival = INT_MAX;
                for (size_t i = 0; i < remaining.size(); i++) {
                    if (!completed[i] && remaining[i].arrivalTime < earliestArrival) {
                        earliestArrival = remaining[i].arrivalTime;
                        earliestIdx = i;
                    }
                }
                
                if (earliestIdx == -1) break; // All done
                currentTime = remaining[earliestIdx].arrivalTime;
                continue;
            }
            
            completed[shortestIdx] = true;
            remaining[shortestIdx].completionTime = currentTime + remaining[shortestIdx].burstTime;
            remaining[shortestIdx].waitTime = currentTime - remaining[shortestIdx].arrivalTime;
            remaining[shortestIdx].turnaroundTime = remaining[shortestIdx].completionTime 
                                                     - remaining[shortestIdx].arrivalTime;
            
            currentTime = remaining[shortestIdx].completionTime;
            scheduledProcesses.push_back(remaining[shortestIdx]);
        }
        
        calculateStatistics();
    }
};

#endif // SJF_SCHEDULER_H
