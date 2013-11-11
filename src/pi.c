
/*

This program will numerically compute the integral of

                  4/(1+x*x)

from 0 to 1.  The value of this integral is pi -- which
is great since it gives us an easy way to check the answer.

The is the original sequential program.  It uses the timer
from the OpenMP runtime library

History: Written by Tim Mattson, 11/99.

*/
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
static long num_steps = 100000000;

int parse(int , char **);
void printUsage();

double step;
int main (int argc, char *argv[])
{
  if(parse(argc, argv) == 0)
  {
    exit(0);
  }

  int i;
  double x, pi, sum = 0.0;
  double start_time, run_time;

  step = 1.0/(double) num_steps;


  start_time = omp_get_wtime();

  for (i=0;i<= num_steps; i+=1){
      x = (i-0.5)*step;
      sum +=  4.0/(1.0+x*x);
  }

  pi = step * sum;
  run_time = omp_get_wtime() - start_time;

  printf("\n pi = %d (%f steps). ", pi,num_steps);
  printf("\n Executed for %f seconds. (sequentially) \n\n",run_time);
}

int parse(int argc, char *argv[])
{

  if(argc < 2)
  {
    return 0;
  }
  else 
  {
    num_steps = strtol( argv[1], NULL, 10);
  }
  if(num_steps < 1)
  {
    printUsage();
    return 0;
  }
  return 1;
}

void printUsage()
{
  printf("\nUsage: pi <num_steps> \n");
}