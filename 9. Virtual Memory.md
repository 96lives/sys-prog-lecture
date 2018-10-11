# 9. Virtual Memory

## 9.1 Physical and Virtual Addressing

* *Physical Address(PA)*: The address of the real main memory.

* *Virtual Address(VA)*: The address of the ?

* *Address Translation*: The task of converting the PA to VA.

* *Memory Management Unit(MMU)*: The CPU chip that does address translation.


## 9.2 Address Space

The distinction of *virtual address space* and *physical address space* is needed.



## 9.3 VM as a Tool for Caching

## 9.4 VM as a Tool for Memory Management

## 9.5 VM as a Tool for Memory Protection

## 9.6 Address Translation

## 9.7 Case Study: The Intel Core i7/Linux Memory System

## 9.8 Memory Mapping

## 9.9 Dynamic Memory Allocation (Explicit Allocators)

* ***Heap***: The place where the dynamic memory allocator maintains the area.

  * Demand-zero-memory
  * Begins at the uninitialized data
  * Grows upward
  * `brk` points to the top of the heap

* Heap is a collection of various-size *blocks*. Each block is chunk of virtual memory and could either be allocated or free. The allocated block has been explicitly reserved for the use of application.

* ***Allocators***: Maintain the heap.

  * *Explicit Allocator*: Requires the app to explicitly free any allocated block. C programs allocate the block by `malloc` and free block by `free` function. (For C++, `new` and `delete` is used)

  * *Implicit Allocator (Garbage Collector)*: Requires the allocator to detect when an allocated block is no longer being used by the program and then free the block. High level languages support this.


### 9.9.1 The `malloc` and `free` functions

* `void *malloc(size_t size)`

  * returns a pointer to a block of memory at least `size` bytes that is aligned. 
  * If problem occurs, returns `NULL`.
  * The memory is not initialized .
  * In 64-bit mode, the block address must be multiple of 16. 

* `void *sbrk(intptr_t inc)` 

  * Grows or shrinks the heap by adding `incr` to the kernel's `brk` pointer. 
  * If successful returns old `brk` value, else returns `-1`. 

* `void free(void *ptr)`

  * The `ptr` parameter must point to the beginning of an allocated block that was obtained from `malloc`, `calloc` (initialized `malloc`) or `realloc` .

  * If not given correct parameter, not defined.

  * Hard to tell if something is wrong, since it returns nothing.


### 9.9.2 Why Dynamic Memory Allocation?

To allocate the memory with memory size found at run time. 



### 9.9.3 Allocator Requirements and Goals 

* Requirements

  * Handling arbitrary request sequence -> Allocator cannot make any assumptions about the sequence of allocate and free requests
  * Making immediate responses to requests -> cannot reorder the request
  * Using only the heap
  * Aligning blocks -> must hold any type of data
  * Not modifying the allocated blocks -> cannot move the allocated blocks

* Goals

  * Maximizing throughput -> maximize requests per unit time

  * Maximizing memory utilization 

    After the `k`th request finished, let *aggregate payload* `P_k` denote sum of resulting allocated blocks. Let `H_k` denote the current size of the heap. The goal is to maximize `P_k / H_k`. 


### 9.9.4 Fragmentation

***Fragmentation***: The phenomenon when unused memory is not available to allocate request. 

* *Internal fragmentation*: Occurs when the allocated block is larger than the payload. 

* *External fragmentation*: Occurs when there is enough aggregate free memory to satisfy an allocate request, but no single free block is large enough to handle the request. 


### 9.9.5 Implementation Issues

A practical allocator must consider the following

* *Free block organization*: how do keep of the free blocks?

* *Placement*: How do we choose which free block to allocate?

* *Splitting*: After allocation, what to do with the remainder free block?

* *Coalescing*: What to do with freed block?


### 9.9.6 Implicit Free Lists

Goal: To distinguish block boundaries.

* Heap Format
  1. ***Header***
     * One byte
     * Encodes 29 bit with block size and 3 *allocated bit* (which marks the allocation of the block)
     * Block size contains the header and padding.
     * ex) allocated block with 0x18 bytes and allocated -> header is 0x19 
  2. ***Payload***
  3. ***Padding***: has many reasons for doing so. 

*  ***Implicit Free List***
  * Free blocks are linked implicitly by the size fields in the headers. 
  * Ex) see pg884, fig9.36 



### 9.9.7 Placing Allocated Blocks

When an app requests a block of some bytes, the allocator searches the free list that is large enough to hold the requested block. ***Placement policy*** is the policy that handles allocation.

* *First fit* selects the first block found starting from the first beginning.

* *Next fit* selects the first block found, starting from the previous search left off.

* *Best fit* examines every block and chooses the first block with the smallest size.


### 9.9.8 Splitting Free Blocks

Once the allocator found the free block that fits, it must choose how much of the free bock to allocate. It can allocate the whole block or split the block.



### 9.9.9 Getting Additional Heap Memory

If the allocator is unable to find a fit for the block, then it first tries to merge the adjacent free block together. If the extended free block is still too small, then it request the kernel for additional heap memory by calling `sbrk` function. 



### 9.9.10 Coalescing Free Blocks 

* ***False fragmentation***: If the freed block is adjacent but regarded as 2 separate free blocks, it may fail to address allocation even though the whole memory fits.

* ***Coalescing***: Merging adjacent blocks each time a block is freed. 

  * *Immediate coalescing*: coalescing when freed.

  * *deferred coalescing*: coalescing later. 


### 9.9.11 Coalescing with Boundary Tags

Coalescing the next block is easy. To coalesce the previous block, use *footer* at the end of each block, where the footer is copy of header. Footer can be overhead when there all a lot of small blocks. Use one of 3 bits in the header to show that the previous block is free or not.



### 9.9.12 Putting It Together: Implementing a Simple Allocator

TODO: Write the code and put comments!!



### 9.9.13 Explicit Free Lists

Want: to optimize the data structure so that the next free block can be found faster. 

* *Doubly linked list*: add `succ` and `pred` to find the next free block -> reduces time of free block finding from # of blocks to # of free blocks.

* *LIFO (Last In First Out)*: Insert the newly freed blocks at the beginning of the list.

* *Address order*: address of each block in the list is less than the address of successor. 


### 9.9.14 Segregated Free Lists



## 9.10 Garbage Collection

One has to free the dynamically allocated memory. 

C, C++: conservative garbage collector. Unreachable nodes might be incorrectly identified as reachable. 

garbage collector is called whenever it needs heap space. 

### mark & sweep

marks all reachable descendents 



## 9.11 Common Memory-Related Bugs in C Programs

## 9.12 Summary

