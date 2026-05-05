#ifndef SCHEDULER_H
#define SCHEDULER_H

#include <vector>
#include <queue>
#include <algorithm>
#include <iostream>
#include "process.h"

class Scheduler {
protected:
    std::vector<Process> processes;
    std::vector<Process> scheduledProcesses;
    double avgWaitTime;
    double avgTurnaroundTime;
    
    void calculateStatistics() {
        if (scheduledProcesses.empty()) return;
        
        double totalWait = 0, totalTurnaround = 0;
        for (const auto& p : scheduledProcesses) {
            totalWait += p.waitTime;
            totalTurnaround += p.turnaroundTime;
        }
        
        avgWaitTime = totalWait / scheduledProcesses.size();
        avgTurnaroundTime = totalTurnaround / scheduledProcesses.size();
    }
    
public:
    Scheduler() : avgWaitTime(0), avgTurnaroundTime(0) {}
    
    virtual ~Scheduler() = default;
    
    void addProcess(int pid, int arrival, int burst, int priority = 0) {
        processes.emplace_back(pid, arrival, burst, priority);
    }
    
    void setProcesses(const std::vector<Process>& procs) {
        processes = procs;
    }
    
    virtual void schedule() = 0;
    
    void displaySchedule() const {
        std::cout << "\n=== PROCESS SCHEDULE ===\n";
        std::cout << "PID\tArrival\tBurst\tCompletion\tWait\tTurnaround\n";
        std::cout << "----\t-------\t-----\t----------\t----\t----------\n";
        
        for (const auto& p : scheduledProcesses) {
            std::cout << p.pid << "\t" << p.arrivalTime << "\t" << p.burstTime 
                      << "\t" << p.completionTime << "\t\t" << p.waitTime 
                      << "\t" << p.turnaroundTime << "\n";
        }
    }
    
    void displayStatistics() const {
        std::cout << "\n=== STATISTICS ===\n";
        std::cout << "Average Wait Time: " << avgWaitTime << "\n";
        std::cout << "Average Turnaround Time: " << avgTurnaroundTime << "\n";
    }
    
    void displayGanttChart() const {
        std::cout << "\n=== GANTT CHART ===\n";
        for (const auto& p : scheduledProcesses) {
            std::cout << p.pid << " ";
        }
        std::cout << "\n";
    }
    
    const std::vector<Process>& getSchedule() const {
        return scheduledProcesses;
    }
    
    double getAvgWaitTime() const { return avgWaitTime; }
    double getAvgTurnaroundTime() const { return avgTurnaroundTime; }
};

#endif // SCHEDULER_H
