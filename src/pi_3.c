
/*

This program will numerically compute the integral of

                  4/(1+x*x)

from 0 to 1.  The value of this integral is pi -- which
is great since it gives us an easy way to check the answer.

The is the original sequential program.  It uses the timer
from the OpenMP runtime library

History: Written by Tim Mattson, 11/99.

-----------------------------------------------------------
Task is implemented on the algorithm written by Tim Mattson

Task:
"Using the for work sharing construct with the reduction variable."

Implemented by: Frederick Ceder

*/
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

static long num_steps = 100000000;
static long int threadcount;

void printUsage();
int parse(int, char**);


double step;
int main (int argc, char *argv[])
{

  if(parse(argc, argv) == 0)
  {
    exit(0);
  }
  omp_set_num_threads(threadcount);


  
  double x, pi, sum = 0.0;
  double start_time, run_time;

  step = 1.0/(double) num_steps;
  start_time = omp_get_wtime();
  int i;
  #pragma parallel omp for reduction(+:sum) private(x, sum)
    for (i = 0; (i< num_steps); i+=1){
        x = (i-0.5)*step;
        sum +=  4.0/(1.0+x*x);
    }
  pi += sum*step;
  run_time = omp_get_wtime() - start_time;
  printf("\n pi = %d (%f steps). ", pi,num_steps);
  printf("\n Executed for %f seconds. (%i threads) \n\n",run_time, threadcount);
}

int parse(int argc, char *argv[])
{

  if(argc < 2)
  {
    threadcount = omp_get_num_procs();
  }
  else if(argc == 2)
  {
    threadcount = strtol( argv[1], NULL, 10);
  }
  else 
  {
    threadcount = strtol( argv[1], NULL, 10);
    num_steps = strtol( argv[2], NULL, 10);
  }
  
  if(threadcount < 1 || num_steps < 1)
  {
    printUsage();
    return 0;
  }
  return 1;
}

void printUsage()
{
  printf("\nUsage: pi <thread_count> <num_steps> \n");
}