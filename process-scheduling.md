# Process Scheduling

## Goal

To achieve the CPU virtualization, sharing the CPU between multiple tasks is needed. Scheduler is an algorithm that is used to select one task at a time form the multiple available runnable tasks. To be more precise...

* Maximize CPU utilization (keep CPU busy)

* Fair distribution of CPU resources 

* Minimize *response time* (amount of time it takes from when a request was submitted until the first response is produced)

* Minimize *turnaround time* (amount of time to execute a particular process)

* Maximize *throughput* (# of processes that complete per time unit)



#### Things to Consider in Scheduler

1. Many tasks have different priorities. Interactive web browsers and GUIs have higher priority then program compilation since, the former must respond immediately.
2. No starvation of lower priorities must occur.
3. Interactivity of a task should be considered. Interactive processes like GUIs would need very small amount of time on the CPU and rapidly cycle between processes. On the contrary, non-interactive processes need less context switching since switching operation is expensive.



## Basic Concepts & Terminologies

### CPU and I/O burst

* *CPU Burst*: A CPU burst of performing calculations. 
* "I/O Burst": Waiting for data transfer in or out of the system. 
* The scheduling system allows one process to use the CPU while another is waiting for I/O.

### CPU Scheduler

* **Non-preemptive** scheduling: process keeps CPU until waiting state or termination.

* **preemptive** scheduling: process can be interrupted. Requires process coordination and locks to access shared data. 


### Dispatcher 

Dispatcher module gives control of CPU to the process selected by the short-term scheduler

* switching context
* switching to user mode





## Process Scheduling Algorithms

For all of the algorithms, it is important to compute the average waiting time for the algorithm examples. 

### First-come First-serve

Non-preemptive scheduler (제곧내)

### Shortest Job First

* Associate each process with the length of its next CPU burst to schedule the process. (FCFS for equal length tie breaking). 

* *It is theoretically **optimal**, but it is difficult to know the length of the next CPU request. So we estimate the length. 

* Can be done with preemptive with shortest-remaining-time-first.


### Priority Scheduling

* A priority # is associated with each process.

* Suffers from **starvation** -> solution is *aging* (to lower the priority as time goes by)


### Round Robin

* Each process gets a small unit of CPU time (time quantum *q*). After this time is elapsed, the process is preempted and added to the end of the ready queue.

* Performance 

  * *q* large -> FIFO

  * *q* small is bad, due to overhead of context switch.


### Multilevel Queue

* Ready queue is partitioned into separate queues. 

* Ex) foreground (interactive), background (batch)

* Each queue can have different scheduling algorithms 


### Multilevel Feedback Queue

* All of above combined... 



### Completely Fair Scheduler

#### Overview

* Key idea: To maintain fairness in providing process time to tasks.  -> Use rb-tree

* Each node in rb-tree corresponds to a task and each task has it's virtual runtime (the amount of time provided to a given task). So, the highest priority task is stored at the most left of the tree.

* CFS considers **sleeper fairness** to ensure that tasks that are not currently runnable (i.e. waiting for I/O) receive a comparable share of the processor.

#### Internals

* All tasks in Linux are represented with a task structure in `task_struct`. This struct describes the task's state, stack, process flags, priority etc.. (In ./linux/include/linux/sched.h)

  * `task_struct` -> `sched_entity` -> `rb_node` (actual tree node). The -> sign represents that the lhs has rhs as field. Only runnable tasks have `sched_entity`.

* `put_prev_task()`: returns currently running task

* `pick_next_task()`: returns the left most node of associated `sched_entity` of rb-tree.

#### Priorities

* CFS uses priority as a decay factor for the time a task is permitted to execute, rather than using them directly.

* Lower priority tasks have higher factors of decay.

#### Group Scheduling

* Goal is to divide the CPU time fairly across user/systems.

* The key idea is to group the processes across user/systems and maintain the group virtual runtime while maintaining virtual runtime for each process. This way, the CPU time is distributed fairly in the aspect of both group and individual process.

#### Scheduling Classes and Domains

* Different tasks require different scheduling policy, so the base class was made to organize schedulers.





## References

1.  [CPU Scheduling](https://www.cs.uic.edu/~jbell/CourseNotes/OperatingSystems/6_CPU_Scheduling.html)
2. [CFS](www.linuxjournal.com/node/10267)





- Process vs. threads

  - A process can be viewed as a single thread.

  - A process can contain multiple threads that share some number of resources (code or data).


