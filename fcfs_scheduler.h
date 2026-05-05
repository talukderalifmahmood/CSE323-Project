#ifndef FCFS_SCHEDULER_H
#define FCFS_SCHEDULER_H

#include "scheduler.h"

// First Come First Served
class FCFSScheduler : public Scheduler {
public:
    void schedule() override {
        scheduledProcesses.clear();
        
        // Sort by arrival time
        std::vector<Process> sorted = processes;
        std::sort(sorted.begin(), sorted.end(), 
                  [](const Process& a, const Process& b) {
                      return a.arrivalTime < b.arrivalTime;
                  });
        
        int currentTime = 0;
        
        for (auto p : sorted) {
            // Process can't start before it arrives
            currentTime = std::max(currentTime, p.arrivalTime);
            
            p.completionTime = currentTime + p.burstTime;
            p.waitTime = currentTime - p.arrivalTime;
            p.turnaroundTime = p.completionTime - p.arrivalTime;
            
            currentTime = p.completionTime;
            scheduledProcesses.push_back(p);
        }
        
        calculateStatistics();
    }
};

#endif // FCFS_SCHEDULER_H
