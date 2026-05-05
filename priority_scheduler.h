#ifndef PRIORITY_SCHEDULER_H
#define PRIORITY_SCHEDULER_H

#include "scheduler.h"
#include <climits>

// Priority Scheduling (Non-preemptive)
// Lower priority number = higher priority
class PriorityScheduler : public Scheduler {
public:
    void schedule() override {
        scheduledProcesses.clear();
        
        std::vector<Process> remaining = processes;
        int currentTime = 0;
        std::vector<bool> completed(remaining.size(), false);
        
        while (true) {
            int highestPriorityIdx = -1;
            int highestPriority = INT_MAX;
            
            // Find the process with highest priority that has arrived
            for (size_t i = 0; i < remaining.size(); i++) {
                if (!completed[i] && remaining[i].arrivalTime <= currentTime) {
                    if (remaining[i].priority < highestPriority) {
                        highestPriority = remaining[i].priority;
                        highestPriorityIdx = i;
                    }
                }
            }
            
            if (highestPriorityIdx == -1) {
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
            
            completed[highestPriorityIdx] = true;
            remaining[highestPriorityIdx].completionTime = currentTime + remaining[highestPriorityIdx].burstTime;
            remaining[highestPriorityIdx].waitTime = currentTime - remaining[highestPriorityIdx].arrivalTime;
            remaining[highestPriorityIdx].turnaroundTime = remaining[highestPriorityIdx].completionTime 
                                                           - remaining[highestPriorityIdx].arrivalTime;
            
            currentTime = remaining[highestPriorityIdx].completionTime;
            scheduledProcesses.push_back(remaining[highestPriorityIdx]);
        }
        
        calculateStatistics();
    }
};

#endif // PRIORITY_SCHEDULER_H
