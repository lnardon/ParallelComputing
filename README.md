# Parallel Computing: N-Queens Problem
This repository contains a parallel computing solution for the n-queens problem using brute force and OpenMPI, implemented as part of the final assignment for my university course in Parallel Computing.

## Prerequisites
Ensure you have the following installed on your local machine:

- OpenMPI
- GCC


### Getting Started
First, you'll need to compile the program using the command below:
```bash
mpicc -o nqueens ./nqueens.c -lm
```

After that, you can run the script with the command below:
```bash
mpirun -np <number_of_processes_to_use> nqueens <board_size>
```
