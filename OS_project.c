#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <unistd.h>
#include <time.h>

void matrix_multiplication(int *a, int *b, int *result, int row_start, int row_end, int cols_a,int cols_b){
    for (int i = row_start; i < row_end; i++) { 
        for (int j = 0; j < cols_b; j++) {
            result[i * cols_b + j] = 0;
            for (int k = 0; k < cols_a; k++) {
                result[i * cols_b + j] += a[i * cols_a + k] * b[k * cols_b + j];
            }
        }
    }
    // printf("start row : %d     end row: %d\n", row_start,row_end);
}

int main() {
    FILE *file;
    file = fopen("input.txt", "r");
    if (file == NULL) {
        printf("File error!\n");
        return 1;
    }

    int shmid;
    key_t key = 1234; 
    int rows_a, cols_a, rows_b, cols_b, num_processes;
     
    // clock_t start_time, end_time;
    // double cpu_time_used;

    struct timeval start_time, end_time;

    // printf("Enter the first Matrix's rows and cols (rows cols): ");
    // scanf("%d %d", &rows_a, &cols_a);
    // printf("Enter the second Matrix's rows and cols (rows cols): ");
    // scanf("%d %d", &rows_b, &cols_b);

    fscanf(file, "%d %d", &rows_a, &cols_a);
    fscanf(file, "%d %d", &rows_b, &cols_b);

    if (cols_a != rows_b) {
        printf("Invalid Multiplication!\n");
        return 1;
    }

    // printf("Enter the Number of processes (Less than the rows of the first matrix): ");
    // scanf("%d", &num_processes);
    fscanf(file, "%d", &num_processes);

    if (num_processes > rows_a) {
        printf("The number of processes can't be above the rows of the first matrix!\n");
        return 1;
    }

    shmid = shmget(key, ((rows_a*cols_a)+(rows_b*cols_b)+(rows_a*cols_b)) * sizeof(int), IPC_CREAT | 0666);
    if (shmid < 0) {
        perror("shmget");
        exit(1);
    }

    int *data = (int *)shmat(shmid, NULL, 0);
    if (data == (int *)(-1)) {
        perror("shmat");
        exit(1);
    }

    int (*mat1)[cols_a] = (int (*)[cols_a])data;
    int (*mat2)[cols_b] = (int (*)[cols_b])(data + (rows_a * cols_a));
    int (*result)[cols_b] = (int (*)[cols_b])(data + (rows_a * cols_a) + (rows_b * cols_b));

    // printf("Enter elements of first matrix (%dx%d):\n", rows_a, cols_a);
    // for (int i = 0; i < rows_a; i++) {
    //     for (int j = 0; j < cols_a; j++) {
    //         scanf("%d", &mat1[i][j]);
    //     }
    // }

    // printf("Enter elements of second matrix (%dx%d):\n", rows_b, cols_b);
    // for (int i = 0; i < rows_b; i++) {
    //     for (int j = 0; j < cols_b; j++) {
    //         scanf("%d", &mat2[i][j]);
    //     }
    // }

    for (int i = 0; i < rows_a; i++) {
        for (int j = 0; j < cols_a; j++) {
            fscanf(file, "%d", &mat1[i][j]);
        }
    }

    for (int i = 0; i < rows_b; i++) {
        for (int j = 0; j < cols_b; j++) {
            fscanf(file, "%d", &mat2[i][j]);
        }
    }

    int rows_per_process = rows_a / num_processes;
    int extra_rows = rows_a % num_processes;

    int start_row = 0;

    gettimeofday(&start_time, NULL);


    for (int i = 0; i < num_processes; i++) {
        pid_t pid = fork();
        if (pid == 0) {
            int end_row = start_row + rows_per_process;
            if (i == num_processes - 1) { 
                end_row += extra_rows; 
            }
            matrix_multiplication((int *)mat1, (int *)mat2, (int *)result, start_row, end_row,cols_a, cols_b);
            // printf("Process %d finished\n",i);
            exit(0); 
        } else if (pid < 0) {
            perror("fork");
            exit(1);
        }
        start_row += rows_per_process;
    }

    for (int i = 0; i < num_processes; i++) {
        wait(NULL);
    }

    gettimeofday(&end_time, NULL);

    // printf("Resultant matrix:\n");
    // for (int i = 0; i < rows_a; i++) {
    //     for (int j = 0; j < cols_b; j++) {
    //         printf("%d ", result[i][j]);
    //     }
    //     printf("\n");
    // }

    long seconds = end_time.tv_sec - start_time.tv_sec;
    long microseconds = end_time.tv_usec - start_time.tv_usec;
    double elapsed = seconds + microseconds*1e-6;

    printf("Total elapsed time: %.6f seconds.\n", elapsed);

    shmdt(data);
    shmctl(shmid, IPC_RMID, NULL);

    fclose(file);

    return 0;
}
