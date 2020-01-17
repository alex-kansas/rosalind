from test_utils import *

sample_datasets = {
    # http://rosalind.info/problems/dna/
    "AGCTTTTCATTCTGACTGCAACGGGCAATATGTCTCTGTGTGGATTAAAAAAAGAGTGTCTGATAGCAGC" : {
        "./bin/dna" : "20 12 17 21",
        "./bin/rna" : "AGCUUUUCAUUCUGACUGCAACGGGCAAUAUGUCUCUGUGUGGAUUAAAAAAAGAGUGUCUGAUAGCAGC",
        "./bin/revc": "GCTGCTATCAGACACTCTTTTTTTAATCCACACAGAGACATATTGCCCGTTGCAGTCAGAATGAAAAGCT",
        "./bin/gc"  : "unnamed string\n41.428571"},
    # http://rosalind.info/problems/rna/
    "GATGGAACTTGACTACGTAAATT" : {
        "./bin/dna" : "8 3 5 7",
        "./bin/rna" : "GAUGGAACUUGACUACGUAAAUU",
        "./bin/revc": "AATTTACGTAGTCAAGTTCCATC",
        "./bin/gc"  : "unnamed string\n34.782609"},
    # http://rosalind.info/problems/revc/
    "AAAACCCGGT" : {
        "./bin/dna" : "4 3 2 1",
        "./bin/rna" : "AAAACCCGGU",
        "./bin/revc": "ACCGGGTTTT",
        "./bin/gc"  : "unnamed string\n50.000000"},
    # http://rosalind.info/problems/fib/
    "5 3" : {
        "./bin/fib" : "19"},
    # http://rosalind.info/problems/gc/
    ">Rosalind_6404\n"
    "CCTGCGGAAGATCGGCACTAGAATAGCCAGAACCGTTTCTCTGAGGCTTCCGGCCTTCCC\n"
    "TCCCACTAATAATTCTGAGG\n"
    ">Rosalind_5959\n"
    "CCATCGGTAGCGCATCCTTAGTCCAATTAAGTCCCTATCCAGGCGCTCCGCCGAAGGTCT\n"
    "ATATCCATTTGTCAGCAGACACGC\n"
    ">Rosalind_0808\n"
    "CCACCCTCGTGGTATGGCTAGGCATTCAGGAACCGGAGAACGCTTCAGACCAGCCCGGAC\n"
    "TGGGAACCTGCGGGCAGTAGGTGGAAT" : {
        "./bin/gc" : "Rosalind_0808\n60.919540"},
    # http://rosalind.info/problems/hamm/
    ">A\nGAGCCTACTAACGGGAT\n>B\nCATCGTAATGACGGCCT" : {
        "./bin/gc"   : "A\n52.941176",
        "./bin/hamm" : "7",
        "./bin/subs" : "" },
    # http://rosalind.info/problems/iprb/
    "2 2 2" : {
        "./bin/fib"  : "1",
        "./bin/iprb" : "0.78333" },
    # http://rosalind.info/problems/prot/
    "AUGGCCAUGGCGCCCAGAACUGAGAUCAAUAGUACCCGUAUUAACGGGUGA" : {
        "./bin/dna"  : "15 12 14 10",
        "./bin/rna"  : "AUGGCCAUGGCGCCCAGAACUGAGAUCAAUAGUACCCGUAUUAACGGGUGA",
        "./bin/revc" : "TCACCCGTTAATACGGGTACTATTGATCTCAGTTCTGGGCGCCATGGCCAT",
        "./bin/gc"   : "unnamed string\n50.980392",
        "./bin/prot" : "MAMAPRTEINSTRING" },
    # http://rosalind.info/problems/subs/
    ">A\nGATATATGCATATACTT\n>B\nATAT" : {
        "./bin/gc"   : "A\n23.529412",
        "./bin/subs" : "2 4 10" },

    # Invalid string cases
    "" : {},
    "This is not a DNA string" : {},

    # Single string range test
    "A" : {
        "./bin/dna" : "1 0 0 0",
        "./bin/rna" : "A",
        "./bin/revc": "T",
        "./bin/gc"  : "unnamed string\n0.000000"},
    "A" * 16383: {
        "./bin/dna" : "16383 0 0 0",
        "./bin/rna" : "A" * 16383,
        "./bin/revc": "T" * 16383,
        "./bin/gc"  : "unnamed string\n0.000000",
        "./bin/prot": "K" * 5461},
    "C" : {
        "./bin/dna" : "0 1 0 0",
        "./bin/rna" : "C",
        "./bin/revc": "G",
        "./bin/gc"  : "unnamed string\n100.000000"},
    "C" * 16383: {
        "./bin/dna" : "0 16383 0 0",
        "./bin/rna" : "C" * 16383,
        "./bin/revc": "G" * 16383,
        "./bin/gc"  : "unnamed string\n100.000000",
        "./bin/prot": "P" * 5461},
    "G" : {
        "./bin/dna" : "0 0 1 0",
        "./bin/rna" : "G",
        "./bin/revc": "C",
        "./bin/gc"  : "unnamed string\n100.000000"},
    "G" * 16383 : {
        "./bin/dna" : "0 0 16383 0",
        "./bin/rna" : "G" * 16383,
        "./bin/revc": "C" * 16383,
        "./bin/gc"  : "unnamed string\n100.000000",
        "./bin/prot": "G" * 5461},
    "T" : {
        "./bin/dna" : "0 0 0 1",
        "./bin/rna" : "U",
        "./bin/revc": "A",
        "./bin/gc"  : "unnamed string\n0.000000"},
    "T" * 16383 : {
        "./bin/dna" : "0 0 0 16383",
        "./bin/rna" : "U" * 16383,
        "./bin/revc": "A" * 16383,
        "./bin/gc"  : "unnamed string\n0.000000",
        "./bin/prot": "F" * 5461},
    "ACGT" * 4095 : {
        "./bin/dna" : "4095 4095 4095 4095",
        "./bin/rna" : "ACGU" * 4095,
        "./bin/revc": "ACGT" * 4095,
        "./bin/gc"  : "unnamed string\n50.000000",
        "./bin/prot": "TYVR" * 1365},

    # Multiple strings corner cases
    ">ID\nACGT\n" * 17 : {},

    # Number input robustness tests
    str(random.randint(1, 100)) : {},
    "-1 1" : {},
    "1 -1" : {},
    "-1 1 1" : {},
    "1 -1 1" : {},
    "1 1 -1" : {
        "./bin/fib" : "1"}}

for cmd in find_cmds():
    # Test program with a small dataset
    for inp in sample_datasets:
        if cmd in sample_datasets[inp]:
            test_with_string(cmd, inp, sample_datasets[inp][cmd])
        else:
            test_with_string(cmd, inp, "Error!", exact = False)

    # Test program with a large dataset
    dataset = "vnv/rosalind_" + cmd[6:] + ".txt"
    if os.path.isfile(dataset):
        test([cmd, "rosalind_" + cmd[6:] + ".txt"], fromfile(cmd[6:] + "_result.txt"))
    else:
        print 'Skipping', cmd

    # Test program without a dataset
    test([cmd], "Error!", exact = False)

    # Test program with a non-existing dataset file
    test([cmd, "notthere.txt"], "Error!", exact = False)

    # Test program with an invalid dataset (use binary file as the dataset)
    test([cmd, cmd], "Error!", exact = False)

    # Test program with an invalid dataset (use this python file as the dataset)
    test([cmd, "test.py"], "Error!", exact = False)

#
# Counting DNA Nucleotides
# http://rosalind.info/problems/dna/
#
dna = lambda s: run_with_string("./bin/dna", s)
a   = random_dna()
b   = random_dna()
# dna(a + b) = dna(a) + dna(b)
add = lambda a, b: " ".join([str(int(a.split()[i]) + int(b.split()[i])) for i in range(4)])
verify(dna(a + b), add(dna(a), dna(b)))
# dna(reverse(a)) = dna(a)
verify(dna(a[::-1]), dna(a))
# sum(dna(a)) = len(a)
verify(sum([int(x) for x in dna(a).split()]), len(a))

#
# Transcribing DNA into RNA
# http://rosalind.info/problems/rna/
#
rna = lambda s: run_with_string("./bin/rna", s)
a = random_dna()
b = random_dna()
# rna(a + b) = rna(a) + rna(b)
verify(rna(a + b), rna(a) + rna(b))
# rna(reverse(a)) = reverse(rna(a))
verify(rna(a[::-1]), rna(a)[::-1])
# rna(rna(a)) = rna(a) because of how U and T are representd in memory
verify(rna(rna(a)), rna(a))
# dna(rna(a)) = dna(a) because of how U and T are represented in memory
verify(dna(rna(a)), dna(a))

#
# Complementing a Strand of DNA
# http://rosalind.info/problems/revc/
#
revc = lambda s: run_with_string("./bin/revc", s)
a = random_dna()
b = random_dna()
# revc(a + b) = revc(b) + revc(a)
verify(revc(a + b), revc(b) + revc(a))
# revc(reverse(a)) = reverse(revc(a))
verify(revc(a[::-1]), revc(a)[::-1])
# revc(revc(a)) = a
verify(revc(revc(a)), a)
# dna(revc(a)) = reverse(dna(a))
reverse = lambda x: " ".join(x.split()[::-1])
verify(dna(revc(a)), reverse(dna(a)))
# revc(rna(a)) == revc(a) because of how U and T are represented in memory
verify(revc(rna(a)), revc(a))

#
# Rabbits and Recurrence Relations
# http://rosalind.info/problems/fib/
#
fib = lambda n, k: int(run_with_string("./bin/fib", "%d %d" % (n, k)))
n = random.randint(3, 40)
k = random.randint(1, 5)
# fib(0..2, k) = 1
for i in range(3): verify(fib(i, k), 1)
# fib(3, k) = k
verify(fib(3, k), k + 1)
# fib(n, k) = fib(n-2, k) + k*fin(n-1,k)
verify(fib(n, k), fib(n-1, k) + k * fib(n-2, k))
exit()

#
# Computing GC Content
# http://rosalind.info/problems/gc/
#
gc = lambda l: float(run_with_string("./bin/gc", "\n".join(l)).split()[1])
a = [random_dna() for _ in random.randint(1, 10)]
b = random_dna()
# gc(a + b) = max(gc(a), gc(b))
verify(gc(a.append(b)), max(gc(a), gc(b)))
# gc(reverse(a)) = gc(a)
verify(gc(a[::-1]), gc(a))
verify(gc(b[::-1]), gc(b))
# gc(b + b) = gc(b)
verify(gc(b + b), gc(b))
# gc(b) = 100.0 * (dna(a)[1] + dna(a)[2]) / sum(dna(a))
verify(gc(b),
       100.0 * (int(dna(b).split()[1]) + int(dna(b).split()[2]))
             / sum([int(x) for x in dna(b).split()]))
# gc(b + A) = (gc(b) * len(b))/(len(b) + 1)
verify(gc(b + "A"), (gc(b) * len(b))/(len(b) + 1))
verify(gc(b + "T"), (gc(b) * len(b))/(len(b) + 1))
verify(gc(b + "U"), (gc(b) * len(b))/(len(b) + 1))
# gc(b + G) = (gc(b) * leb(b) + 100)/(len(b) + 1)
verify(gc(b + "G"), (gc(b) * len(b) + 100)/(len(b) + 1))
verify(gc(b + "C"), (gc(b) * len(b) + 100)/(len(b) + 1))
# gc(revc(b)) = gc(b)
verify(gc(revc(b)), gc(b))
# gc(rna(b)) = gc(b)
verify(gc(rna(b)), gc(b))

# Test hamm corner cases
test_with_string(
        "bin/hamm",
        "GA\nTT\nGA",
        "Error! Found 3 DNA strings of lengths 2 and 2\n")
test_with_string(
        "bin/hamm",
        "GATTA\nGA",
        "Error! Found 2 DNA strings of lengths 5 and 2\n")
test_with_string(
        "bin/hamm",
        "GATTACA" * 1024 + '\n' + "GATTACA" * 1024,
        "0\n")
test_with_string(
        "bin/hamm",
        "AATTACA" * 1024 + '\n' + "CATTACA" * 1024,
        "1024\n")
test_with_string(
        "bin/hamm",
        "AAAAAAA" * 1024 + '\n' + "CCCCCCC" * 1024,
        "7168\n")
test_with_string(
        "bin/hamm",
        "GA TTA GA\nGATTA GA",
        "0\n")
test_with_string(
        "bin/hamm",
        "GA CT AGA\nGAGTA GA",
        "1\n")

# Test iprb corner cases
for i in range(4):
    test_with_string(
            "bin/iprb",
            " ".join([str(int(i==j)) for j in range(3)]),
            "Error! At least two individuals are required\n")
test_with_string("bin/iprb", "0 1 1", "0.50000\n")
test_with_string("bin/iprb", "1 0 1", "1.00000\n")
test_with_string("bin/iprb", "1 1 0", "1.00000\n")
test_with_string("bin/iprb", "2 0 0", "1.00000\n")
test_with_string("bin/iprb", "2 1 0", "1.00000\n")
test_with_string("bin/iprb", "0 2 0", "0.75000\n")
test_with_string("bin/iprb", "0 0 2", "0.00000\n")
test_with_string("bin/iprb", "1000000 1000000 1000000", "0.75000\n")

# Test subs corner cases
