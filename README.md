OpenMP-Pi-Sample
================

An introductory program for using the OpenMP framework using C.


================
 Usage
================

All programs can be executed using the committed bash scripts. 


Otherwise if just the program itself should be run:

bin/pi <num_step>
bin/pi_1 <num_thread> <num_step>
bin/pi_2 <num_thread> <num_step>
bin/pi_3 <num_thread> <num_step>


num_thread: Is the max number of threads to execute this program in parallel with.
num_step  : Is the number of iterations to do in order to approximate pii. (see code)
