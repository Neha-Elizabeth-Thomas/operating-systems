# Operating Systems Lab Repository

This repository contains a collection of Operating Systems lab programs organized by topic, implemented primarily in **C** and **Shell Scripting**. It includes solutions to synchronization problems, inter-process communication, threading, memory management, system calls, and more.

> ⚠️ **Note:** Some programs are intended to be compiled and run on **Linux (Ubuntu)** systems only, as they make use of Linux-specific headers and system calls.

---

## 🗂 Folder Structure

```
operating-systems/
│
├── ShellScripting/             # Advanced shell script programs
├── basic-shell-scripting/     # Basic shell scripting concepts
├── SystemCalls/               # Programs using system calls like fork, exec, wait
├── ipc/                       # Inter-process communication (shared memory, message queues)
├── synchronization/           # Synchronization problems like Producer-Consumer, Dining Philosophers
├── threads/                   # POSIX thread-based programs
│
├── Bankers_latest.c           # Banker's Algorithm (Resource Allocation)
├── Bankers_latest_safety.c    # Banker's Algorithm (Safety Check)
├── Mem_allocation_latest.c    # Memory Allocation Strategies
├── disk_scheduling.c          # Disk Scheduling Algorithms
├── page_replace_latest.c      # Page Replacement Algorithms
├── scheduling_latest.c        # CPU Scheduling Algorithms
└── .gitignore
```

---

## 📁 Directory Details

### 1. `ShellScripting/`

* Contains shell scripts for:

  * File search
  * Fibonacci series
  * Command-line argument processing
  * Simple calculators

### 2. `basic-shell-scripting/`

* Basic concepts of shell scripting:

  * Variables, arrays, loops
  * Arithmetic operations
  * Conditional branching

### 3. `SystemCalls/`

* C programs using:

  * `fork()`, `exec()`, `wait()`
  * File operations using `open()`, `read()`, `write()`
  * Process management

### 4. `ipc/` (Inter-Process Communication)

* Programs demonstrating:

  * Shared memory (`shmget`, `shmat`, etc.)
  * Message queues
  * Chat applications using message queues
  * Producer-consumer problem with shared memory

### 5. `synchronization/`

* Classic synchronization problems:

  * Peterson's solution
  * Producer-consumer using semaphores
  * Dining Philosophers
  * Reader-Writer problem

### 6. `threads/`

* Programs using **POSIX threads**:

  * Creating threads
  * Printing odd-even numbers using threads
  * Returning values from threads

---

## ⚙️ Linux-Only Files

These files include Linux-specific headers (`<unistd.h>`, `<sys/types.h>`, `<sys/ipc.h>`, `<pthread.h>`, etc.) and must be compiled/run on a Linux environment (e.g., Ubuntu):

* All files inside:

  * `SystemCalls/`
  * `ipc/`
  * `synchronization/`
  * `threads/`

📌 Use `gcc` or `gcc -pthread` (for thread programs) to compile.

---

## 🧪 How to Run

### On Ubuntu/Linux:

```bash
# Compile a C file
gcc filename.c -o output

# For thread programs
gcc filename.c -o output -pthread

# Run the compiled binary
./output
```

### Shell Scripts:

```bash
# Make script executable
chmod +x script.sh

# Run script
./script.sh
```

---

## 📌 Requirements

* GCC compiler (`sudo apt install build-essential`)
* Shell (bash)
* Linux environment (preferably Ubuntu)

---

## 📜 License

This project is for academic and learning purposes only. You are free to use and modify it for personal or educational use.
