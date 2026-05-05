# Process Scheduler - Usage Guide and Examples

## Quick Start

### 1. Compile the Program

**On Linux/macOS:**
```bash
cd d:/CSE323/Project
make
```

**On Windows (with g++ installed):**
```bash
cd d:\CSE323\Project
mingw32-make
```

**Manual compilation (all platforms):**
```bash
g++ -std=c++11 -o scheduler main.cpp
```

### 2. Run the Program
```bash
./scheduler
```

## Mode 1: Sample Comparison (Option 1)

This mode automatically runs a predefined set of processes through all four scheduling algorithms.

### What it shows:
- Individual scheduling tables for FCFS, SJF, Round Robin, and Priority
- Statistics (average wait time, average turnaround time) for each algorithm
- A comparison table to see which algorithm performs best

### Sample Input (automatic):
```
Process 1: Arrival=0, Burst=8, Priority=3
Process 2: Arrival=1, Burst=4, Priority=1
Process 3: Arrival=2, Burst=2, Priority=4
Process 4: Arrival=3, Burst=1, Priority=2
Process 5: Arrival=4, Burst=3, Priority=2
```

### Expected Output Example:

**FCFS Results:**
```
PID	Arrival	Burst	Completion	Wait	Turnaround
1	0	8	8		0	8
2	1	4	12		7	11
3	2	2	14		10	12
4	3	1	15		11	12
5	4	3	18		10	14

Average Wait Time: 7.6
Average Turnaround Time: 11.4
```

**SJF Results:**
```
PID	Arrival	Burst	Completion	Wait	Turnaround
4	3	1	4		0	1
3	2	2	6		2	4
5	4	3	9		1	5
2	1	4	13		8	12
1	0	8	21		13	21

Average Wait Time: 4.8
Average Turnaround Time: 8.6
```

## Mode 2: Custom Scheduler (Option 2)

Create your own processes and test a specific algorithm.

### Steps:

1. Choose Option 2 from the main menu
2. Enter the number of processes you want to create
3. For each process, enter:
   - **PID**: Process identifier (can be any integer)
   - **Arrival Time**: When the process enters the queue (in time units)
   - **Burst Time**: How long the process takes to execute (in time units)
   - **Priority**: Priority level 1-10 (only used if selecting Priority algorithm; 1=highest, 10=lowest)
4. Select which algorithm to test (1-4)
5. For Round Robin, enter the time quantum

### Example Session:

```
Enter number of processes: 3

Process 1:
  PID: 10
  Arrival Time: 0
  Burst Time: 5
  Priority (1-10, lower = higher): 2

Process 2:
  PID: 20
  Arrival Time: 1
  Burst Time: 3
  Priority (1-10, lower = higher): 1

Process 3:
  PID: 30
  Arrival Time: 2
  Burst Time: 4
  Priority (1-10, lower = higher): 3

Select Scheduling Algorithm:
1. FCFS
2. SJF
3. Round Robin
4. Priority
Enter choice (1-4): 3
Enter time quantum: 2

--- Round Robin Scheduling (Q=2) ---

=== PROCESS SCHEDULE ===
PID	Arrival	Burst	Completion	Wait	Turnaround
10	0	5	10		1	10
20	1	3	9		5	8
30	2	4	12		6	10

=== STATISTICS ===
Average Wait Time: 4
Average Turnaround Time: 9.33
```

## Understanding the Output

### Schedule Table

| Column | Meaning |
|--------|---------|
| **PID** | Process ID |
| **Arrival** | When the process arrives in the queue |
| **Burst** | How long the process needs to run |
| **Completion** | When the process finishes execution |
| **Wait** | Time spent waiting: `Completion - Arrival - Burst` |
| **Turnaround** | Total time from arrival to completion: `Completion - Arrival` |

### Statistics

- **Average Wait Time**: Mean of all wait times. Lower is better (less idle time for processes)
- **Average Turnaround Time**: Mean of all turnaround times. Lower is better (faster overall completion)

## Practical Test Cases

### Test Case 1: Short vs. Long Processes
Demonstrate how SJF and Round Robin handle mixed burst times better than FCFS.

```
Process 1: Arrival=0, Burst=20, Priority=1
Process 2: Arrival=1, Burst=1, Priority=1
Process 3: Arrival=2, Burst=1, Priority=1
```

**Expected**: SJF will perform much better than FCFS (Process 2 and 3 won't be blocked by Process 1)

### Test Case 2: Staggered Arrivals
```
Process 1: Arrival=0, Burst=5, Priority=2
Process 2: Arrival=10, Burst=3, Priority=1
Process 3: Arrival=15, Burst=2, Priority=3
```

**Expected**: Demonstrates how arrival time affects scheduling decisions

### Test Case 3: Priority Based
```
Process 1: Arrival=0, Burst=10, Priority=3
Process 2: Arrival=0, Burst=5, Priority=1
Process 3: Arrival=0, Burst=3, Priority=2
```

**Expected**: Priority scheduler runs: P2 (priority 1) → P3 (priority 2) → P1 (priority 3)

### Test Case 4: Round Robin with Different Quantum
Same processes, different quantum values show tradeoff between context switches and fairness.

```
Process 1: Arrival=0, Burst=5, Priority=0
Process 2: Arrival=0, Burst=5, Priority=0
Process 3: Arrival=0, Burst=5, Priority=0
```

- **Quantum=1**: More fair, more context switches
- **Quantum=5**: Less fair (like FCFS), fewer context switches

## Troubleshooting

### Program doesn't compile
- Ensure you have g++ installed: `g++ --version`
- Use C++11 or later: `g++ -std=c++11 ...`

### Program crashes after entering processes
- Check that all values are positive integers
- Arrival times should be non-negative
- Burst times should be positive (> 0)

### Results don't match expectations
- Verify arrival times are in ascending order in input
- Check that priority values are within 1-10 range
- For Round Robin, try a different time quantum value

## Performance Tips

- **For worst FCFS performance**: One long process followed by many short ones
- **For best SJF performance**: When process burst times are known accurately in advance
- **For Round Robin tuning**: Smaller quantum = fairness but more overhead; larger = less overhead but less fair
- **For Priority tuning**: Mix of high and low priority processes shows starvation potential

## Analyzing Results

### How to choose the best algorithm:

1. **FCFS**: Simple, predictable, fair. Use when simplicity matters more than performance.
2. **SJF**: Best average wait time for non-preemptive scheduling. Use when burst times are known.
3. **Round Robin**: Fair, prevents starvation. Use for general-purpose time-sharing systems.
4. **Priority**: Useful when some processes are more important. Watch for starvation.

---

For more details on algorithms, refer to your OS textbook or the README.md file.
