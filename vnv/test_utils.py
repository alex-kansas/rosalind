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


def random_dna(cnt = None):
    if cnt is None:
        cnt = random.randint(1, 1000)
    return "".join([random.choice("ACGT") for _ in range(cnt)])


def run(args):
    # fixup file name
    if (len(args) > 1) and (not args[1].startswith("./bin")):
        args[1] = "vnv/" + args[1]

    out = subprocess.check_output(args)
    return(out.strip())


def run_with_string(cmd, dataset):
    tofile("vnv/test.txt", dataset)
    return run([cmd, "test.txt"])


def test(args, exp_out, exact = True):
    out = run(args)
    exp_out = exp_out.strip()
    verify(out, exp_out, exact)


def test_with_string(cmd, dataset, exp_out, exact = True):
    out = run_with_string(cmd, dataset)
    if not _verify(out, exp_out, exact = exact):
        print cmd
        print out
        print exp_out
        print "FAIL!"


def tofile(fname, s):
    f = open(fname, "w")
    f.write(s)
    f.close()


def _verify(out, exp_out, exact = True):
    if exact:
        return out == exp_out
    else:
        return out.startswith(exp_out)

def verify(out, exp_out, exact = True):
    if _verify(out, exp_out, exact = exact):
        pass #print "PASS"
    else:
        print out
        print exp_out
        print "FAIL"
        exit()