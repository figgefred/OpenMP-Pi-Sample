all: pi_0 pi_1 pi_2 pi_3

clean:
	rm bin/*

pi_0: src/pi.c
	gcc src/pi.c -fopenmp -O -o bin/pi

pi_1: src/pi_1.c
	gcc src/pi_1.c -fopenmp -O -o bin/pi_1

pi_2: src/pi_2.c
	gcc src/pi_2.c -fopenmp -O -o bin/pi_2
pi_3: src/pi_3.c
	gcc src/pi_3.c -fopenmp -O -o bin/pi_3
