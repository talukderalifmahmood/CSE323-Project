#include <iostream>
#include <iomanip>
#include "process.h"
#include "fcfs_scheduler.h"
#include "sjf_scheduler.h"
#include "round_robin_scheduler.h"
#include "priority_scheduler.h"

using namespace std;

void printSeparator() {
    cout << "\n" << string(70, '=') << "\n";
}

void runSchedulerComparison() {
    // Sample processes: PID, Arrival Time, Burst Time, Priority
    vector<Process> processes = {
        Process(1, 0, 8, 3),
        Process(2, 1, 4, 1),
        Process(3, 2, 2, 4),
        Process(4, 3, 1, 2),
        Process(5, 4, 3, 2)
    };
    
    cout << "\n========== PROCESS SCHEDULER SIMULATOR ==========\n";
    cout << "\nInput Processes:\n";
    cout << "PID\tArrival\tBurst\tPriority\n";
    cout << "---\t-------\t-----\t--------\n";
    for (const auto& p : processes) {
        cout << p.pid << "\t" << p.arrivalTime << "\t" << p.burstTime 
             << "\t" << p.priority << "\n";
    }
    
    // FCFS Scheduling
    printSeparator();
    cout << "FIRST COME FIRST SERVED (FCFS) SCHEDULING\n";
    printSeparator();
    FCFSScheduler fcfs;
    fcfs.setProcesses(processes);
    fcfs.schedule();
    fcfs.displaySchedule();
    fcfs.displayStatistics();
    
    // SJF Scheduling
    printSeparator();
    cout << "SHORTEST JOB FIRST (SJF) SCHEDULING\n";
    printSeparator();
    SJFScheduler sjf;
    sjf.setProcesses(processes);
    sjf.schedule();
    sjf.displaySchedule();
    sjf.displayStatistics();
    
    // Round Robin Scheduling
    printSeparator();
    cout << "ROUND ROBIN (RR) SCHEDULING (Time Quantum = 2)\n";
    printSeparator();
    RoundRobinScheduler rr(2);
    rr.setProcesses(processes);
    rr.schedule();
    rr.displaySchedule();
    rr.displayStatistics();
    
    // Priority Scheduling
    printSeparator();
    cout << "PRIORITY SCHEDULING (Non-preemptive)\n";
    printSeparator();
    PriorityScheduler priority;
    priority.setProcesses(processes);
    priority.schedule();
    priority.displaySchedule();
    priority.displayStatistics();
    
    // Comparison
    printSeparator();
    cout << "COMPARISON OF ALGORITHMS\n";
    printSeparator();
    cout << left << setw(20) << "Algorithm" 
         << setw(25) << "Avg Wait Time" 
         << setw(25) << "Avg Turnaround Time\n";
    cout << string(70, '-') << "\n";
    cout << left << setw(20) << "FCFS" 
         << setw(25) << fixed << setprecision(2) << fcfs.getAvgWaitTime()
         << setw(25) << fcfs.getAvgTurnaroundTime() << "\n";
    cout << left << setw(20) << "SJF" 
         << setw(25) << sjf.getAvgWaitTime()
         << setw(25) << sjf.getAvgTurnaroundTime() << "\n";
    cout << left << setw(20) << "Round Robin (Q=2)" 
         << setw(25) << rr.getAvgWaitTime()
         << setw(25) << rr.getAvgTurnaroundTime() << "\n";
    cout << left << setw(20) << "Priority" 
         << setw(25) << priority.getAvgWaitTime()
         << setw(25) << priority.getAvgTurnaroundTime() << "\n";
}

void customSchedulerTest() {
    cout << "\n\n========== CUSTOM PROCESS SCHEDULER ==========\n";
    cout << "\nEnter number of processes: ";
    int n;
    cin >> n;
    
    if (n <= 0) {
        cout << "Invalid number of processes.\n";
        return;
    }
    
    vector<Process> processes;
    
    for (int i = 0; i < n; i++) {
        int pid, arrival, burst, priority;
        cout << "\nProcess " << (i + 1) << ":\n";
        cout << "  PID: ";
        cin >> pid;
        cout << "  Arrival Time: ";
        cin >> arrival;
        cout << "  Burst Time: ";
        cin >> burst;
        cout << "  Priority (1-10, lower = higher): ";
        cin >> priority;
        
        processes.emplace_back(pid, arrival, burst, priority);
    }
    
    int choice;
    cout << "\nSelect Scheduling Algorithm:\n";
    cout << "1. FCFS\n";
    cout << "2. SJF\n";
    cout << "3. Round Robin\n";
    cout << "4. Priority\n";
    cout << "Enter choice (1-4): ";
    cin >> choice;
    
    switch (choice) {
        case 1: {
            FCFSScheduler fcfs;
            fcfs.setProcesses(processes);
            fcfs.schedule();
            cout << "\n--- FCFS Scheduling ---\n";
            fcfs.displaySchedule();
            fcfs.displayStatistics();
            break;
        }
        case 2: {
            SJFScheduler sjf;
            sjf.setProcesses(processes);
            sjf.schedule();
            cout << "\n--- SJF Scheduling ---\n";
            sjf.displaySchedule();
            sjf.displayStatistics();
            break;
        }
        case 3: {
            cout << "Enter time quantum: ";
            int quantum;
            cin >> quantum;
            RoundRobinScheduler rr(quantum);
            rr.setProcesses(processes);
            rr.schedule();
            cout << "\n--- Round Robin Scheduling (Q=" << quantum << ") ---\n";
            rr.displaySchedule();
            rr.displayStatistics();
            break;
        }
        case 4: {
            PriorityScheduler priority;
            priority.setProcesses(processes);
            priority.schedule();
            cout << "\n--- Priority Scheduling ---\n";
            priority.displaySchedule();
            priority.displayStatistics();
            break;
        }
        default:
            cout << "Invalid choice.\n";
    }
}

int main() {
    int choice;
    
    cout << "\n**** OPERATING SYSTEM PROCESS SCHEDULER ****\n";
    cout << "\nChoose an option:\n";
    cout << "1. Run sample comparison of all algorithms\n";
    cout << "2. Create custom process scheduler\n";
    cout << "Enter choice (1-2): ";
    cin >> choice;
    
    if (choice == 1) {
        runSchedulerComparison();
    } else if (choice == 2) {
        customSchedulerTest();
    } else {
        cout << "Invalid choice.\n";
    }
    
    cout << "\n\nThank you for using the Process Scheduler!\n";
    return 0;
}
