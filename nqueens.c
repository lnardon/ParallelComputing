#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <mpi.h>

int size, rank;
long long solutions_count = 0;
int *board;

void broadcast_data(int *n) {
    MPI_Bcast(n, 1, MPI_INT, 0, MPI_COMM_WORLD);
}

int is_solution(int n) {
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (board[i] == board[j] || abs(board[i] - board[j]) == abs(i - j)) {
                return 0;
            }
        }
    }
    return 1;
}

void brute_force(int n) {
    long long max = pow(n, n);

    for (long long i = rank; i < max; i += size) {
        for (int j = 0; j < n; j++) {
            board[j] = (i / (long long) pow(n, j)) % n;
        }
        solutions_count += is_solution(n);
    }
}

int main(int argc, char *argv[]) {
    // Setup MPI
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    // Get board size from command line and setup board
    int n = atoi(argv[1]);
    board = (int*)malloc(n * sizeof(int));

    // Start timer and solve problem
    double start = MPI_Wtime();
    broadcast_data(&n);
    brute_force(n);
    double end = MPI_Wtime();

    // Master and slave data handling
    if(rank == 0) {
        MPI_Reduce(MPI_IN_PLACE, &solutions_count, 1, MPI_LONG_LONG_INT, MPI_SUM, 0, MPI_COMM_WORLD);
        printf("Number of solutions: %lld\n", solutions_count);
        printf("Time elapsed: %f seconds\n", end - start);
    } else {
        MPI_Reduce(&solutions_count, &solutions_count, 1, MPI_LONG_LONG_INT, MPI_SUM, 0, MPI_COMM_WORLD);
    }

    // Cleanup and exit
    free(board);
    MPI_Finalize();
    return 0;
}
