# 8. Exceptional Control Flow

## 8.1 Exceptions

### 8.1.1 Exception Handling
* **Exception number**
  
* Every possible exception in system is assigned a unique nonnegative number
  
* **Exception Table**
  * At system boot time, the OS initializes a jump table called exception table
  * At run time, every entry handles one of the exception.

* **Kernel**
  * Memory resident part of the operating system
  
  * Exception handlers run in **kernel mode** (traps use this intentionally)
  
    

### 8.1.2 Classes of Exceptions

|              | Interrupts                     | Traps                          | Faults                              | Aborts                |
| ------------ | ------------------------------ | ------------------------------ | ----------------------------------- | --------------------- |
| Cause        | signal from I/O                | Intentional exception          | recoverable error                   | Non-recovarable error |
| Async / Sync | async                          | sync                           | sync                                | sync                  |
| Return       | always return next instruction | always return next instruction | might return to current instruction | never return          |

* Fault
  * If the handler is able to correct the error condition, it returns control to faulting instruction and re-execute it. Otherwise, the handler returns to an abort routine.
* **System calls**
  * Linux provides lots of system calls that application programs use when  they want to request service from the kernel.
  * System calls are provided via trap instructions called `syscall`.
  * Ex) Writing file, reading file, creating new process...

## 8.2 Processes

* **Process**
  * An instance of ad program in execution.
  * A process appears to have exclusive use of both the **processor** and the **memory**.



### 8.2.1 Logical Control Flow

* **Logical Control Flow**: Series of PC values of one process.
  * Processes take turns using the processor.
  * Each time the processor stalls, it resumes execution without any change to the contents of the program's memory locations or registers.



### 8.2.2 Concurrent Flows

* **Concurrent Flow**: A logical flow whose execturion overlaps in time with another flow.
* **Parallel Flow**: 2 flows running concurrently on different processors.



### 8.2.3 Private Address Space

* **Private Address Space**: Memory in this address cannot be read/written by other processes.



### 8.2.4 User and Kernel Modes

* **Kernel Mode**: A process running in kernel mode can execute any instruction and access any memory location.
* **User Mode**: A process in user mode is not allowed to execute privileged instructions or access kernel memory. 



### 8.2.5 Context Switches

* **Context**: State that the kernel needs to restart the preempted process. 
  * Ex) General purpose registers, pc, user's stack, *page table (characterize address space)*, *process table (contains info about current process)*, *file table (contains info about files that process has opened)*
* **Scheduling**: The kernel can decide to preempt the current process and restart a previously preemted process.



## 8.4 Process Control

This section describes important functions of system calls for manipulating process from C in UNIX.

### 8.4.1 Obtaining process IDs

 `pid_t getpid(void)`

### 8.4.2 Creating and terminating process IDs

* Process can be 1 of 3 states
  * Running: Either executing on CPU or waiting to be executed, and will be scheduled by kernel. 
  * Stopped: The execution of process is suspended and will not be scheduled. It remains stopped until it recieves SIGTTOU signal.
  * Terminated: The process is stopped permanently. 
* Terminating process: `void exit(int status)`
* Parent process creating child process: `pid_t fork(void)`
  * The child gets an identical(but seperate) copy of the parent's user-level virtual address space. 
  * The parent and child have different PIDs.
  *  It is called once and returns twice on parent and child. The parent `fork` returns the PID of child and child `fork` returns 0 (All PID is non-zero).

### 8.4.3 Reaping child processes

* When the process terminates, the process is kept around in terminated state until it is *reaped* by its parent. That process is called *zombie*. *zombies* still consume system memory resources.
* *init* process is started from the system-startup and is ancestor of every processes. 
* `pid_t waitpid(pid_t pid, int *statusp, int options)`: A process waits for its children to terminate or stop.



### 8.4.4 Putting Processes to Sleep

* `unsigned int sleep(unsigned int secs)`: Suspends a process for a specified period of time. 
* `int pause(void)`: Puts calling function to sleep until a signal is received by the process. 



### 8.4.5 Loading and Running Programs

* `int execve(const char *filename, const char *argv[], const char *envp)`: Loads and runs a new program in the context of the current process. Runs object file `filename` with argument list `argv` and environment variable `envp`. It does not return unless there is an error.

* SKIP....
