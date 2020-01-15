import os
import os.path
import string
import subprocess
import random

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


def test(args, exp_out, exact = True, except_fib = False):
    # fixup file name
    if (len(args) > 1) and (not args[1].startswith("./bin")):
        args[1] = "vnv/" + args[1]

    # Make exception for fib
    if except_fib and args[0].endswith("fib"):
        exp_out = "Error! Unable to read n and k from file %s" % args[1]

    out = subprocess.check_output(args)
    if not verify(out, exp_out, exact):
        print "FAIL: ", args, out


def _test_with_string(cmd, dataset, exp_out, exact = True, except_fib = False):
    tofile("vnv/test.txt", dataset)
    test([cmd, "test.txt"], exp_out, exact = exact, except_fib = except_fib)

def test_with_string(cmd, dataset, exp_out, exact = True, except_fib = False):
    # Test as given
    _test_with_string(cmd, dataset, exp_out, exact = exact, except_fib = except_fib)

    # Test with leading and trailing whitespace
    if len(dataset) < 1024 * 16 - 2:
        _test_with_string(cmd, " " + dataset + " ", exp_out, exact = exact, except_fib = except_fib)


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
    test([cmd, cmd], "Error! Buffer to small\n", exact = False, except_fib = True)

    # Test program with an invalid dataset (use this python file as the dataset)
    test([cmd, "test.py"], "Error! Invalid DNA string", exact = False, except_fib = True)

    # Test program with another invalid dataset
    test_with_string(cmd, "This is not a DNA string", "Error! Invalid DNA string", exact = False, except_fib = True)

    # Test program with an empty dataset
    test_with_string(cmd, "", "Error! Found 0 DNA strings", except_fib = True)

    # Test program with too many DNA strings
    test_with_string(cmd, "ACGT " * 17, "Error! Too many DNA strings\n", exact = False, except_fib = True)

    # Test program with a small dataset
    test([cmd, cmd[6:] + "_example.txt"], fromfile(cmd[6:] + "_example_result.txt"))

    # Test program with a large dataset
    dataset = "vnv/rosalind_" + cmd[6:] + ".txt"
    if os.path.isfile(dataset):
        test([cmd, "rosalind_" + cmd[6:] + ".txt"], fromfile(cmd[6:] + "_result.txt"))
    else:
        print 'Skipping', cmd

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
for x in [41, 0x7FFFFFFF, 0xFFFFFFFF, -1]:
    test_with_string("bin/fib", str(x) + " 5", "Error! N", exact = False)
    test_with_string("bin/fib", "5 " + str(x), "Error! K", exact = False)

# Test gc corner cases
test_with_string(
        "bin/gc",
        ">A\n>B\n>C\n>D",
        "Error! Invalid DNA string: >B\n", exact = False)
test_with_string(
        "bin/gc",
        ">A\nAAAA\n>B\nAAAA\n>C\nAAAA\n>D\nAAAG",
        "D\n25.0000\n")
test_with_string(
        "bin/gc",
        ">A\nAAAA\n>B\nAAAA\n>C\nAACG\n>D\nAAAG",
        "C\n50.0000\n")
test_with_string(
        "bin/gc",
        ">A\nAAAA\n>B\nACCC\n>C\nAACG\n>D\nAAAG",
        "B\n75.0000\n")
test_with_string(
        "bin/gc",
        ">A\nAAA\n>B\nCCC\n>C\nGGG\n>D\nTTT",
        "B\n100.0000\n")
x = random.randint(1,99)
test_with_string(
        "bin/gc",
        ">NOT_THIS_ONE\n%s\n>THIS_ONE\n%s%s" % ("A"*x, "C"*x, "A"*(100-x)),
        "THIS_ONE\n%d.0000\n" % x)
test_with_string(
        "bin/gc",
        ">NOT_THIS_ONE\n%s\n>THIS_ONE\n%s%s" % ("A"*x, "C", "A"*9999),
        "THIS_ONE\n0.0099\n")
test_with_string(
        "bin/gc",
        ">NOT_THIS_ONE\n%s\n>THIS_ONE\n%s%s" % ("A"*x, "A", "C"*9999),
        "THIS_ONE\n99.9900\n")
