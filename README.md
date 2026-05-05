Name: Talukder Alif Mahmood
ID: 2233684642
Section: CSE323.1

Project: Process Scheduler Visualization

A comprehensive C++ implementation of CPU process scheduling algorithms with simulation, timing analysis, and performance statistics.

## Features

- **Four Scheduling Algorithms Implemented:**
  - **FCFS (First Come First Served)**: Processes execute in the order they arrive
  - **SJF (Shortest Job First)**: Process with shortest burst time executes first
  - **Round Robin (RR)**: Each process gets a fixed time quantum; configurable time slice
  - **Priority Scheduling**: Processes execute based on priority level (non-preemptive)

- **Performance Metrics:**
  - Average Wait Time: Average time a process waits in the queue
  - Average Turnaround Time: Average time from arrival to completion
  - Per-process statistics (completion time, wait time, turnaround time)

- **Two Operating Modes:**
  1. Pre-loaded sample comparison showing all algorithms side-by-side
  2. Custom process input for testing your own scenarios

## Project Structure

```
├── process.h              # Process structure definition
├── scheduler.h            # Base Scheduler class
├── fcfs_scheduler.h       # FCFS implementation
├── sjf_scheduler.h        # SJF implementation
├── round_robin_scheduler.h # Round Robin implementation
├── priority_scheduler.h    # Priority Scheduling implementation
├── main.cpp               # Main program with demo
└── README.md              # This file
```

## Compilation

On Terminal:

# Compile
g++ -std=c++11 -o scheduler main.cpp

# Run
.\scheduler.exe

### Option 1: Sample Comparison
- Automatically runs pre-defined sample processes through all four algorithms
- Displays detailed scheduling tables for each algorithm
- Shows comparative statistics across all algorithms
- Great for understanding algorithm differences

### Option 2: Custom Scheduler
- Input your own processes (PID, arrival time, burst time, priority)
- Select which algorithm to use
- For Round Robin, specify the time quantum
- Get detailed output for your custom scenario

## Algorithm Explanations

### FCFS (First Come First Served)
- Simplest scheduling algorithm
- Processes are served in the order of arrival
- Non-preemptive: once started, runs to completion
- Pros: Fair, simple implementation
- Cons: Can cause "convoy effect" with long processes

### SJF (Shortest Job First)
- Process with smallest burst time runs first
- Non-preemptive: once started, runs to completion
- Pros: Minimizes average wait time (optimal for non-preemptive)
- Cons: May starve long processes; requires knowing burst time in advance

### Round Robin (RR)
- Each process gets a fixed time slice (time quantum)
- Processes that don't finish are cycled back to the queue
- Time quantum affects performance: smaller = more context switches, fairness increases
- Pros: Fair, prevents starvation, responsive
- Cons: More context switch overhead

### Priority Scheduling
- Each process has a priority level (lower number = higher priority)
- Process with highest priority runs first
- Non-preemptive: once started, runs to completion
- Pros: Can prioritize important processes
- Cons: May cause starvation of low-priority processes

## Sample Output

```
========== PROCESS SCHEDULER SIMULATOR ==========

Input Processes:
PID	Arrival	Burst	Priority
---	-------	-----	--------
1	0	8	3
2	1	4	1
3	2	2	4
4	3	1	2
5	4	3	2

======================================================================
FIRST COME FIRST SERVED (FCFS) SCHEDULING
======================================================================

=== PROCESS SCHEDULE ===
PID	Arrival	Burst	Completion	Wait	Turnaround
----	-------	-----	----------	----	----------
1	0	8	8		0	8
2	1	4	12		7	11
3	2	2	14		10	12
4	3	1	15		11	12
5	4	3	18		10	14

=== STATISTICS ===
Average Wait Time: 7.6
Average Turnaround Time: 11.4
```

## Educational Use

This project is designed to help students understand:
1. How CPU schedulers work
2. Tradeoffs between different scheduling algorithms
3. Importance of metrics like wait time and turnaround time
4. How different parameters affect scheduling outcomes
5. Real-world scheduling considerations in operating systems

## Key Learning Points

- **Wake-up times and Idle CPU**: All algorithms handle CPU idle periods correctly
- **Process Arrival Ordering**: Processes are queued based on arrival time, not static order
- **Calculation of Times**:
  - Wait Time = Completion Time - Arrival Time - Burst Time
  - Turnaround Time = Completion Time - Arrival Time
- **Algorithm Comparison**: Same input produces different results and metrics with different algorithms

## Future Enhancements

Possible extensions to explore:
- Preemptive SJF and Priority scheduling
- Multilevel Queue Scheduling
- Multilevel Feedback Queue
- Real-time process scheduling
- Graphical visualization of the Gantt chart
- Statistics file export (CSV/JSON)
- Performance prediction and optimization suggestions


