
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
"Using a parallel region and a private variable for the local 
sum in the parallel region that is combined with the global sum 
before exiting the parallel region. Use the best synchronization 
primitive in OpenMP (hint check difference between critical and atomic)."

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


  int i;
  double x, pi, sum = 0.0;
  double start_time, run_time;

  step = 1.0/(double) num_steps;

  start_time = omp_get_wtime();

  // The size of workload
  int chunk = num_steps/threadcount;

  double partSum =0.0;
  #pragma omp parallel private(partSum, x) // Priavte assignment of a resp. partSum to all threads
  {
    int myId = omp_get_thread_num();

    // Thread id is used to calculate the region that the current thread will calculate over.
    int index = myId*chunk;
    int end = index+chunk;

    if(myId == threadcount-1 && end % 2 != 0)
    {
      end += 1;
    }

    // Some status of current thread
    printf("Thread-%i: plans to iterate %i times.\n", myId, (end-index));
    
    // Current loop is completely independent of other threads
    for (; (index< num_steps) && index < end; index+=1){
        x = (index-0.5)*step;
        partSum +=  4.0/(1.0+x*x);
    }
    partSum *= step;

    // Critical section. Thus added atomically.
    #pragma omp atomic 
      pi += partSum;
  }

  run_time = omp_get_wtime() - start_time;
  printf("\n pi = %d (%f steps). ", pi,num_steps);
  printf("\n Executed for %f seconds. (%i threads) \n\n",run_time,threadcount);
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