DEPS = src/utils.h src/rosalind.h
OBJS = bin/utils.o bin/rosalind.o

all: bin/dna bin/rna bin/revc bin/fib bin/gc bin/hamm bin/iprb bin/prot test

test:
	python2.7 vnv/test.py

bin/dna: src/dna.c $(OBJS) $(DEPS)
	cc -o $@ src/dna.c $(OBJS)

bin/rna: src/rna.c $(OBJS) $(DEPS)
	cc -o $@ src/rna.c $(OBJS)

bin/revc: src/revc.c $(OBJS) $(DEPS)
	cc -o $@ src/revc.c $(OBJS)

bin/fib: src/fib.c $(OBJS) $(DEPS)
	cc -o $@ src/fib.c $(OBJS)

bin/gc: src/gc.c $(OBJS) $(DEPS)
	cc -o $@ src/gc.c $(OBJS)

bin/hamm: src/hamm.c $(OBJS) $(DEPS)
	cc -o $@ src/hamm.c $(OBJS)

bin/iprb: src/iprb.c $(OBJS) $(DEPS)
	cc -o $@ src/iprb.c $(OBJS)

bin/prot: src/prot.c $(OBJS) $(DEPS)
	cc -o $@ src/prot.c $(OBJS)

bin/utils.o: src/utils.c $(DEPS)
	cc -c src/utils.c -o $@

bin/rosalind.o: src/rosalind.c $(DEPS)
	cc -c src/rosalind.c -o $@

clean:
	rm bin/*