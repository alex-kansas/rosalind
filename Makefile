all: dna rna revc test

test:
	python2.7 test.py

dna: dna.c utils.h utils.c
	cc -o dna dna.c utils.c
	
rna: rna.c utils.h utils.c
	cc -o rna rna.c utils.c
	
revc: revc.c utils.h utils.c
	cc -o revc revc.c utils.c