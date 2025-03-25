#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *file = fopen("input.txt", "w");
    
    if (file == NULL) {
        printf("File error!\n");
        return 1;
    }

    int rows_a = 300;
    int cols_a = 2000;
    int rows_b = 2000;
    int cols_b = 700;
    int range = 10;

    fprintf(file, "%d %d\n",rows_a,cols_a);
    fprintf(file, "%d %d\n",rows_b,cols_b);
    for (int i = 0; i < rows_a; i++) {
        for (int j = 0; j < cols_a; j++) {
            fprintf(file, "%d ", rand() % range); // random number from 0 to 99
        }
        fprintf(file, "\n");
    }
    for (int i = 0; i < rows_b; i++) {
        for (int j = 0; j < cols_b; j++) {
            fprintf(file, "%d ", rand() % range); // random number from 0 to 99
        }
        fprintf(file, "\n");
    }

    // نمونه اول: ماتریس 1000x1000
    // fprintf(file, "1000 1000\n");
    // fprintf(file, "1000 1000\n");
    // for (int i = 0; i < 1000; i++) {
    //     for (int j = 0; j < 1000; j++) {
    //         fprintf(file, "%d ", rand() % 100); // مقادیر تصادفی بین 0 تا 9
    //     }
    //     fprintf(file, "\n");
    // }
    // for (int i = 0; i < 1000; i++) {
    //     for (int j = 0; j < 1000; j++) {
    //         fprintf(file, "%d ", rand() % 100); // مقادیر تصادفی بین 0 تا 9
    //     }
    //     fprintf(file, "\n");
    // }


    // fprintf(file, "10 10\n");
    // fprintf(file, "10 10\n");
    // for (int i = 0; i < 10; i++) {
    //     for (int j = 0; j < 10; j++) {
    //         fprintf(file, "%d ", rand() % 100); // مقادیر تصادفی بین 0 تا 9
    //     }
    //     fprintf(file, "\n");
    // }
    // for (int i = 0; i < 10; i++) {
    //     for (int j = 0; j < 10; j++) {
    //         fprintf(file, "%d ", rand() % 100); // مقادیر تصادفی بین 0 تا 9
    //     }
    //     fprintf(file, "\n");
    // }

    // fprintf(file, "2000 1000\n");
    // fprintf(file, "1000 3000\n");
    // for (int i = 0; i < 2000; i++) {
    //     for (int j = 0; j < 1000; j++) {
    //         fprintf(file, "%d ", rand() % 100); // مقادیر تصادفی بین 0 تا 9
    //     }
    //     fprintf(file, "\n");
    // }
    // for (int i = 0; i < 1000; i++) {
    //     for (int j = 0; j < 3000; j++) {
    //         fprintf(file, "%d ", rand() % 100); // مقادیر تصادفی بین 0 تا 9
    //     }
    //     fprintf(file, "\n");
    // }

    // fprintf(file, "2 1\n");
    // fprintf(file, "1 3\n");
    // for (int i = 0; i < 2; i++) {
    //     for (int j = 0; j < 1; j++) {
    //         fprintf(file, "%d ", rand() % 10); // مقادیر تصادفی بین 0 تا 9
    //     }
    //     fprintf(file, "\n");
    // }
    // for (int i = 0; i < 1; i++) {
    //     for (int j = 0; j < 3; j++) {
    //         fprintf(file, "%d ", rand() % 10); // مقادیر تصادفی بین 0 تا 9
    //     }
    //     fprintf(file, "\n");
    // }




    fclose(file);
    return 0;
}
