# Multithreaded Sorting Application

This is a C program that demonstrates a multithreaded sorting application. The program divides a list of integers into two smaller sublists, sorts each sublist using separate sorting threads, and then merges the sorted sublists into a single sorted list using a merging thread.

## Description

The program performs the following steps:

1. **Divide**: The list of integers is divided into two smaller sublists of equal size.

2. **Sort**: Two separate sorting threads are created, each responsible for sorting one sublist using the insertion sort algorithm.

3. **Merge**: After both sorting threads have completed their tasks, a merging thread merges the two sorted sublists into a single sorted list using a merging algorithm.

4. **Output**: The sorted array is printed to the console.

## Usage

To compile and run the program, follow these steps:

1. **Clone the Repository**:

   ```bash
   git clone https://github.com/jicodes/operating-system-projects
   cd threads
   ```

2. **Compile the Program**:

   ```bash
   gcc -o multithread-sorting multithread-sorting.c -pthread
   ```

3. **Run the Program**:

   ```bash
   ./multithread-sorting

   # The program will output the sorted array to the console.
   # Sorted array: 1 2 3 4 5 6 7 8 9 10
   ```
