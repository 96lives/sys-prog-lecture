# Completely Fair Scheduler

## Scheduler

### Goal

To achieve the CPU virtualization, sharing the CPU between multiple tasks is needed. Scheduler is an algorithm that is used to select one task at a time form the multiple available runnable tasks.

### Things to Consider in Scheduler

1. Many tasks have different priorities. Interactive web browsers and GUIs have higher priority then program compilation since, the former must respond immediately.
2. No starvation of lower priorities must occur.
3. Interactivity of a task should be considered. Interactive processes like GUIs would need very small amount of time on the CPU and rapidly cycle between processes. On the contrary, non-interactive processes need less context switching since switching operation is expensive.

Reference: <www.linuxjournal.com/node/10267>



## History of Linux Schedulers

1. Round-Robin
2. Symmetric Multiprocessing (SMP)
3. Rotating Staircase Deadline Scheduler

They exist.



* Process vs. threads
  * A process can be viewed as a single thread.
  * A process can contain multiple threads that share some number of resources (code or data).

## CSF

### Overview

* Key idea: To maintain fairness in providing process time to tasks.  -> Use rb-tree

* Each node in rb-tree corresponds to a task and each task has it's virtual runtime (the amount of time provided to a given task). So, the highest priority task is stored at the most left of the tree.

* CFS considers **sleeper fairness** to ensure that tasks that are not currently runnable (i.e. waiting for I/O) receive a comparable share of the processor.


### Internals

* All tasks in Linux are represented with a task structure in `task_struct`. This struct describes the task's state, stack, process flags, priority etc.. (In ./linux/include/linux/sched.h)

  * `task_struct` -> `sched_entity` -> `rb_node` (actual tree node). The -> sign represents that the lhs has rhs as field. Only runnable tasks have `sched_entity`.

* `put_prev_task()`: returns currently running task

* `pick_next_task()`: returns the left most node of associated `sched_entity` of rb-tree.


### Priorities

* CFS uses priority as a decay factor for the time a task is permitted to execute, rather than using them directly.

* Lower priority tasks have higher factors of decay.


### Group Scheduling

* Goal is to divide the CPU time fairly across user/systems.

* The key idea is to group the processes across user/systems and maintain the group virtual runtime while maintaining virtual runtime for each process. This way, the CPU time is distributed fairly in the aspect of both group and individual process.


### Scheduling Classes and Domains

* Different tasks require different scheduling policy, so the base class was made to organize schedulers.





