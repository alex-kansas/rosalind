import os
import os.path
import string
import subprocess
import random

num_cmds = ["./bin/" + x for x in ["fib", "iprb"]]

def find_cmds():
    """ Scan the first line of the make file for names of prorgams to test """
    cmds = []
    f = open("Makefile", "r")
    for l in f:
        if l.startswith("all:"):
            cmds = ["./" + x for x in l.split() if x != "all:" and x != "test"]
    if not cmds:
        print "FAIL!  Can't find programs to test"
    f.close()
    return cmds


def fromfile(fname):
    fname = "vnv/" + fname  # fixup file name
    f = open(fname, "r")
    s = f.read()
    f.close()
    return s


def test(args, exp_out, exact = True):
    # fixup file name
    if (len(args) > 1) and (not args[1].startswith("./bin")):
        args[1] = "vnv/" + args[1]

    # In some cases make exception for fib and iprb
    if args[0] in ["./bin/" + x for x in ["fib", "iprb"]]:
        if exp_out.strip() in ["Error! Too many DNA strings",
                               "Error! Invalid DNA string",
                               "Error! Buffer to small",
                               "Error! Found 0 DNA strings"]:
            exp_out = "Error! Invalid input\n"

    out = subprocess.check_output(args)
    if not verify(out, exp_out, exact):
        print args, "FAIL"
        print exp_out[:64]
        print out[:64]


def _test_with_string(cmd, dataset, exp_out, exact = True):
    tofile("vnv/test.txt", dataset)
    test([cmd, "test.txt"], exp_out, exact = exact)

def test_with_string(cmd, dataset, exp_out, exact = True):
    # Test as given
    _test_with_string(cmd, dataset, exp_out, exact = exact)

    # Test with leading and trailing whitespace
    if len(dataset) < 1024 * 16 - 2:
        _test_with_string(cmd, " " + dataset + " ", exp_out, exact = exact)


def tofile(fname, s):
    f = open(fname, "w")
    f.write(s)
    f.close()


def verify(out, exp_out, exact):
    if exact:
        return out == exp_out
    else:
        return out.startswith(exp_out)


for cmd in find_cmds():
    # Test program without a dataset
    test([cmd], "Error! Please provide a dataset\n", exact = False)

    # Test program with a non-existing dataset file
    test([cmd, "notthere.txt"], "Error! Unable to open file vnv/notthere.txt\n", exact = False)

    # Test program with an invalid dataset (use binary file as the dataset)
    test([cmd, cmd], "Error! Buffer to small\n", exact = False)

    # Test program with an invalid dataset (use this python file as the dataset)
    test([cmd, "test.py"], "Error! Invalid DNA string", exact = False)

    # Test program with another invalid dataset
    test_with_string(cmd, "This is not a DNA string", "Error! Invalid DNA string", exact = False)

    # Test program with an empty dataset
    test_with_string(cmd, "", "Error! Found 0 DNA strings", exact = False)

    # Test program with too many DNA strings
    test_with_string(cmd, ">ID\nACGT\n" * 17, "Error! Too many DNA strings\n", exact = False)

    # Test program with a small dataset
    test([cmd, cmd[6:] + "_example.txt"], fromfile(cmd[6:] + "_example_result.txt"))

    # Test program with a large dataset
    dataset = "vnv/rosalind_" + cmd[6:] + ".txt"
    if os.path.isfile(dataset):
        test([cmd, "rosalind_" + cmd[6:] + ".txt"], fromfile(cmd[6:] + "_result.txt"))
    else:
        print 'Skipping', cmd

for cmd in num_cmds:
    # Test with not enough numbers
    test_with_string(
            cmd,
            str(random.randint(1, 10)),
            "Error! Invalid input\n")

    # Test with negative numbers
    for fmt in ["%s 3 3", "3 %s 3"]:
        test_with_string(
                cmd,
                fmt % str(random.randint(-999999999, -1)),
                "Error! Negative integer detected", exact = False)

# Test dna corner cases
test_with_string("bin/dna", ("ACGT" * 1024 * 4)[:-1], "4096 4096 4096 4095\n")

# Test rna corner cases
test_with_string("bin/rna", ("ACGT" * 1024 * 4)[:-1], ("ACGU" * 1024 * 4)[:-1] + "\n")

# Test revc corner cases
test_with_string("bin/revc", ("ACGT" * 256)[:-1], ("ACGT" * 256)[1:])
test_with_string("bin/revc", "ACGT" * 256, "Error! DNA string is too long (1024)")

# Test fib corner cases
test_with_string("bin/fib", "0 5", "1\n")
test_with_string("bin/fib", "1 5", "1\n")
test_with_string("bin/fib", "2 5", "1\n")
test_with_string("bin/fib", "3 5", "6\n")
tofile("vnv/test.txt", "38 5")
F38 = int(subprocess.check_output(["bin/fib", "vnv/test.txt"]))
tofile("vnv/test.txt", "39 5")
F39 = int(subprocess.check_output(["bin/fib", "vnv/test.txt"]))
test_with_string("bin/fib", "40 5", str(F38 * 5 + F39) + "\n")
for x in ["41", "9999999999"]:
    test_with_string("bin/fib", x + " 5", "Error! N", exact = False)
    test_with_string("bin/fib", "5 " + x, "Error! K", exact = False)

# Test gc corner cases
test_with_string(
        "bin/gc",
        ">A\n>B\n>C\n>D",
        "A\n0.000000\n", exact = False)
test_with_string(
        "bin/gc",
        ">A\nAAAA\n>B\nAAAA\n>C\nAAAA\n>D\nAAAG",
        "D\n25.000000\n")
test_with_string(
        "bin/gc",
        ">A\nAAAA\n>B\nAAAA\n>C\nAACG\n>D\nAAAG",
        "C\n50.000000\n")
test_with_string(
        "bin/gc",
        ">A\nAAAA\n>B\nACCC\n>C\nAACG\n>D\nAAAG",
        "B\n75.000000\n")
test_with_string(
        "bin/gc",
        ">A\nAAA\n>B\nCCC\n>C\nGGG\n>D\nTTT",
        "B\n100.000000\n")
x = random.randint(1,99)
test_with_string(
        "bin/gc",
        ">NOT_THIS_ONE\n%s\n>THIS_ONE\n%s%s" % ("A"*x, "C"*x, "A"*(100-x)),
        "THIS_ONE\n%d.000000\n" % x)
test_with_string(
        "bin/gc",
        ">NOT_THIS_ONE\n%s\n>THIS_ONE\n%s%s" % ("A"*x, "C", "A"*9999),
        "THIS_ONE\n0.010000\n")
test_with_string(
        "bin/gc",
        ">NOT_THIS_ONE\n%s\n>THIS_ONE\n%s%s" % ("A"*x, "A", "C"*9999),
        "THIS_ONE\n99.990000\n")

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
test_with_string(
        "bin/iprb",
        str(random.randint(2, 999999)) + " 0 0",
        "1.00000\n")
test_with_string(
        "bin/iprb",
        str(random.randint(2, 999999)) + " 1 0",
        "1.00000\n")
test_with_string(
        "bin/iprb",
        "0 " + str(random.randint(2, 999999)) + " 0",
        "0.75000\n")
test_with_string(
        "bin/iprb",
        "0 0 " + str(random.randint(2, 999999)),
        "0.00000\n")