all:
	gcc parsermain.c -o NMEAParse

test:
	head -301 | ./NMEAParse
