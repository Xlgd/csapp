/* 
 * trans.c - Matrix transpose B = A^T
 *
 * Each transpose function must have a prototype of the form:
 * void trans(int M, int N, int A[N][M], int B[M][N]);
 *
 * A transpose function is evaluated by counting the number of misses
 * on a 1KB direct mapped cache with a block size of 32 bytes.
 */ 
#include <stdio.h>
#include "cachelab.h"

int is_transpose(int M, int N, int A[N][M], int B[M][N]);

/* 
 * transpose_submit - This is the solution transpose function that you
 *     will be graded on for Part B of the assignment. Do not change
 *     the description string "Transpose submission", as the driver
 *     searches for that string to identify the transpose function to
 *     be graded. 
 */
char transpose_submit_desc[] = "Transpose submission";
void transpose_submit(int M, int N, int A[N][M], int B[M][N])
{
    int i, j, n, m, temp1, temp2, temp3, temp4, temp5, temp6, temp7, temp8;
    if (M == 32) {
        for (i = 0; i < N; i += 8) {
            for (j = 0; j < M; j += 8) {
                for (n = i; n < i + 8; n++) {
                    temp1 = A[n][j];
                    temp2 = A[n][j+1];
                    temp3 = A[n][j+2];
                    temp4 = A[n][j+3];
                    temp5 = A[n][j+4];
                    temp6 = A[n][j+5];
                    temp7 = A[n][j+6];
                    temp8 = A[n][j+7];

                    B[j][n] = temp1;
                    B[j+1][n] = temp2;
                    B[j+2][n] = temp3;
                    B[j+3][n] = temp4;
                    B[j+4][n] = temp5;
                    B[j+5][n] = temp6;
                    B[j+6][n] = temp7;
                    B[j+7][n] = temp8;
                }
            }
        }
    }
    else if (M == 64) {
        for (i = 0; i < N; i += 8) {
            for (j = 0; j < M; j += 8) {
                for (n = i; n < i + 4; n++) {
                    temp1 = A[n][j];
                    temp2 = A[n][j+1];
                    temp3 = A[n][j+2];
                    temp4 = A[n][j+3];
                    temp5 = A[n][j+4];
                    temp6 = A[n][j+5];
                    temp7 = A[n][j+6];
                    temp8 = A[n][j+7];

                    B[j][n] = temp1;
                    B[j+1][n] = temp2;
                    B[j+2][n] = temp3;
                    B[j+3][n] = temp4;

                    B[j][n+4] = temp8;
                    B[j+1][n+4] = temp7;
                    B[j+2][n+4] = temp6;
                    B[j+3][n+4] = temp5;
                }
                for (m = 0; m < 4; m++) {
                    temp1 = A[i+4][j+3-m];
                    temp2 = A[i+5][j+3-m];
                    temp3 = A[i+6][j+3-m];
                    temp4 = A[i+7][j+3-m];
                    temp5 = A[i+4][j+4+m];
                    temp6 = A[i+5][j+4+m];
                    temp7 = A[i+6][j+4+m];
                    temp8 = A[i+7][j+4+m];

                    B[j+4+m][i] = B[j+3-m][i+4];
                    B[j+4+m][i+1] = B[j+3-m][i+5];
                    B[j+4+m][i+2] = B[j+3-m][i+6];
                    B[j+4+m][i+3] = B[j+3-m][i+7];

                    B[j+3-m][i+4] = temp1;
                    B[j+3-m][i+5] = temp2;
                    B[j+3-m][i+6] = temp3;
                    B[j+3-m][i+7] = temp4;
                    B[j+4+m][i+4] = temp5;
                    B[j+4+m][i+5] = temp6;
                    B[j+4+m][i+6] = temp7;
                    B[j+4+m][i+7] = temp8;
                }
            }
        }
        
    }
    else {
        for (i = 0; i < N; i += 16) {
            for (j = 0; j < M; j += 16) {
                for (n = i; n < i + 16 && n < N; n++) {
                    for (m = j; m < j + 16 && m < M; m++) {
                        B[m][n] = A[n][m];
                    }
                }
            }
        }
    }
}

/* 
 * You can define additional transpose functions below. We've defined
 * a simple one below to help you get started. 
 */ 

/* 
 * trans - A simple baseline transpose function, not optimized for the cache.
 */
char trans_desc[] = "Simple row-wise scan transpose";
void trans(int M, int N, int A[N][M], int B[M][N])
{
    int i, j, tmp;

    for (i = 0; i < N; i++) {
        for (j = 0; j < M; j++) {
            tmp = A[i][j];
            B[j][i] = tmp;
        }
    }    

}

/*
 * registerFunctions - This function registers your transpose
 *     functions with the driver.  At runtime, the driver will
 *     evaluate each of the registered functions and summarize their
 *     performance. This is a handy way to experiment with different
 *     transpose strategies.
 */
void registerFunctions()
{
    /* Register your solution function */
    registerTransFunction(transpose_submit, transpose_submit_desc); 

    /* Register any additional transpose functions */
    registerTransFunction(trans, trans_desc); 

}

/* 
 * is_transpose - This helper function checks if B is the transpose of
 *     A. You can check the correctness of your transpose by calling
 *     it before returning from the transpose function.
 */
int is_transpose(int M, int N, int A[N][M], int B[M][N])
{
    int i, j;

    for (i = 0; i < N; i++) {
        for (j = 0; j < M; ++j) {
            if (A[i][j] != B[j][i]) {
                return 0;
            }
        }
    }
    return 1;
}

