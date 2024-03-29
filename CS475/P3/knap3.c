//
// File name   : knap1.c
// Author      : DaeGon
// Modified by : Sanjay and Wim 
// HW done by  : Luke Burford
// Date        : Sep 29
// Description : Dynamic Programming for the 0/1 knapsack
//               problem. The table is partially saved by a memo table.
//

#include <stdio.h>
#include <stdlib.h>
#include "timer.h"


#define    MAX(x,y)   ((x)>(y) ? (x) : (y))
#define    table(i,j)    table[(i)*(C+1)+(j)]

//Function Prototypes:
void get_last_row(long start, long end, long C, long wt[], long prof[], long *row);
long solve_kp(long start, long end, long C, long wt[], long prof[], int sol[]);

/* what matt returns if you split k5x11 into k2x11 and k3x11:
k2 
    Last Row: | 0 | 1 | 6 | 7 | 7 | 7 | 7 | 7 | 7 | 7 | 7 | 7 |
k3
    Last Row: | 0 | 0 | 0 | 0 | 0 | 18 | 22 | 28 | 28 | 28 | 28 | 40 |
k5
    Last Row: | 0 | 1 | 6 | 7 | 7 | 18 | 22 | 28 | 29 | 34 | 35 | 40 |
*/
//TODO MAKE SURE THAT C* is being calculated correctly, possibly with miss indexing of C
// Recursivly Solve the Knapsack, use the return of the sol[] array to get the max profit.
//start is intially 1 and end is initally N
long solve_kp(long start, long end, long C, long wt[], long prof[], int sol[]) {
    long* A = (long *)calloc(C+1, sizeof(long));
    long* B = (long *)calloc(C+1, sizeof(long));
    // current number of objects
    int mid = (start+end)/2;
    // BASE CASE, only 1 object left
    if (end-start <= 1) {
        // object fits so we take it (set object to 1)
        if(wt[start] <= C) {
            sol[start] = 1;
            return prof[start];
        }
//         else dont take it (leave it as 0)
        return 0;
    }
    // get the last rows of A and B
        get_last_row(start, mid, C, wt, prof, A);
        get_last_row(mid, end, C, wt, prof, B);
    // using these two, solve for C*
    int C1 = 0; // C*
    int max = 0;
    for(int j = 0; j<=C; ++j) {
        if(A[j]+B[C-j] >= max) {
            C1 = j;
            max = A[j]+B[C-j];
        }
    }
    free(A);
    free(B);
     return solve_kp(start, mid, C1, wt, prof, sol) + solve_kp(mid, end, C-C1, wt, prof, sol);
}

void get_last_row(long start, long end, long C, long wt[], long prof[], long *row) {
    //iterate backwards through the capacity in order to solve for the next row that will be overwritten
    #pragma omp parallel for
    for(int i=start; i<end; ++i)
        for(int j=C; j>=wt[i]; --j)
            row[j] = MAX(row[j],row[j-wt[i]]+prof[i]);
}

int main(int argc, char **argv) {

   FILE   *fp;
   long    N, C;                   // # of objects, capacity 
   long    *weights, *profits;     // weights and profits
   int    verbose,count;

   // Temp variables
   long    i, j, size;

   // Time
   double time;

   // Read input file (# of objects, capacity, (per line) weight and profit )
   if ( argc > 1 ) {
      fp = fopen(argv[1], "r"); 
      if ( fp == NULL) {
         printf("[ERROR] : Failed to read file named '%s'.\n", argv[1]);
         exit(1);
      }
   } else {
      printf("USAGE : %s [filename].\n", argv[0]);
      exit(1);
   }

   if (argc > 2) verbose = atoi(argv[2]); else verbose = 0;

   fscanf(fp, "%ld %ld", &N, &C);
   printf("The number of objects is %d, and the capacity is %d.\n", N, C);

   size    = N * sizeof(long);
   weights = (long *)malloc(size);
   profits = (long *)malloc(size);

   if ( weights == NULL || profits == NULL ) {
      printf("[ERROR] : Failed to allocate memory for weights/profits.\n");
      exit(1);
   }

   for ( i=0 ; i < N ; i++ ) {
      count = fscanf(fp, "%ld %ld", &(weights[i]), &(profits[i]));
      if ( count != 2 ) {
         printf("[ERROR] : Input file is not well formatted.\n");
         exit(1);
      }
   }

   fclose(fp);

   // Solve for the optimal profit
   size = (C+1) * sizeof(long);

      long *table;
      size  = (C+1) * N * sizeof(long);
      table = (long *)malloc(size);
      if ( table == NULL ) {
         printf("[ERROR] : Failed to allocate memory for the whole table.\n");
         exit(1);
      }
   
   initialize_timer ();
   start_timer();
     long* row = (long *)calloc(C+1, sizeof(long));
   int* sol = (int *)calloc(N, sizeof(int));
//     get_last_row(0, N, C, weights, profits, row);
    long ans = solve_kp(0, N,C, weights, profits,sol);

   stop_timer();
   time = elapsed_time ();
  
   // End of "Solve for the optimal profit"

   // Backtracking
//       int c=C;
//       int solution[N];
//       for ( i=N-1 ; i > 0 ; i-- ) {
//          if ( c-weights[i] < 0 ) {
// 	   //printf("i=%d: 0 \n",i);
//             solution[i] = 0;
//          } else {
//             if ( table(i-1,c) > table(i-1,c-weights[i]) + profits[i] ) {
// 
// 	      //printf("i=%d: 0 \n",i);
//                solution[i] = 0;
//             } else {
// 	      //printf("i=%d: 1 \n",i);
//                solution[i] = 1;
//                c = c - weights[i];
//             }
//          }
//       } 
//       //wim: first row does not look back
//       if(c<weights[0]){
//         //printf("i=0: 1 \n");
// 	solution[0]=0;
//       } else {
//         //printf("i=0: 0 \n");
//         solution[0]=1;
//       }
// 
      printf("The optimal profit is %d \nTime taken : %lf.\n", ans, time);
     

      if (verbose==1) {

      printf("Solution vector is: ");
      for(int i=0; i<N ; ++i) {
         printf("%d ", sol[i]);
      }
      printf("\n");
      }

//       if (verbose==2) {
//     for (j=1; j<=C; j++){
//     printf ("%d\t", j);
//     for (i=0; i<N; i++)
//         printf ("%d ", table(i, j));
//         printf("\n");
//     }
//         }

    return 0;
}
