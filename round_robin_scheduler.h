#ifndef ROUND_ROBIN_SCHEDULER_H
#define ROUND_ROBIN_SCHEDULER_H

#include "scheduler.h"
#include <queue>
#include <map>

// Round Robin with Time Quantum
class RoundRobinScheduler : public Scheduler {
private:
    int timeQuantum;
    
public:
    RoundRobinScheduler(int quantum = 2) : timeQuantum(quantum) {}
    
    void setTimeQuantum(int quantum) {
        timeQuantum = quantum;
    }
    
    void schedule() override {
        scheduledProcesses.clear();
        
        std::queue<Process> readyQueue;
        std::vector<Process> allProcesses = processes;
        std::sort(allProcesses.begin(), allProcesses.end(),
                  [](const Process& a, const Process& b) {
                      return a.arrivalTime < b.arrivalTime;
                  });
        
        int currentTime = 0;
        size_t nextArrival = 0;
        std::vector<int> remainingBurst;
        std::map<int, int> waitTimeStart;
        
        for (size_t i = 0; i < allProcesses.size(); i++) {
            remainingBurst.push_back(allProcesses[i].burstTime);
        }
        
        while (nextArrival < allProcesses.size() || !readyQueue.empty()) {
            // Add all processes that have arrived
            while (nextArrival < allProcesses.size() && 
                   allProcesses[nextArrival].arrivalTime <= currentTime) {
                readyQueue.push(allProcesses[nextArrival]);
                waitTimeStart[allProcesses[nextArrival].pid] = currentTime;
                nextArrival++;
            }
            
            if (readyQueue.empty()) {
                // Jump to next arrival time
                if (nextArrival < allProcesses.size()) {
                    currentTime = allProcesses[nextArrival].arrivalTime;
                }
                continue;
            }
            
            Process current = readyQueue.front();
            readyQueue.pop();
            
            int idx = std::find_if(allProcesses.begin(), allProcesses.end(),
                                   [&current](const Process& p) {
                                       return p.pid == current.pid;
                                   }) - allProcesses.begin();
            
            int executeTime = std::min(timeQuantum, remainingBurst[idx]);
            currentTime += executeTime;
            remainingBurst[idx] -= executeTime;
            
            // Add newly arrived processes
            while (nextArrival < allProcesses.size() && 
                   allProcesses[nextArrival].arrivalTime <= currentTime) {
                readyQueue.push(allProcesses[nextArrival]);
                waitTimeStart[allProcesses[nextArrival].pid] = currentTime;
                nextArrival++;
            }
            
            if (remainingBurst[idx] > 0) {
                readyQueue.push(current);
            } else {
                // Process completed
                current.completionTime = currentTime;
                current.turnaroundTime = current.completionTime - current.arrivalTime;
                current.waitTime = current.turnaroundTime - current.burstTime;
                scheduledProcesses.push_back(current);
            }
        }
        
        calculateStatistics();
    }
};

#endif // ROUND_ROBIN_SCHEDULER_H
