import string
import subprocess

for (test,                       exp_out                            ) in [
    ("./dna",                    "Please supply dataset file name\n"),
    ("./dna dna_example.txt",    "20 12 17 21\n"                    ),
    ("./dna rosalind_dna.txt",   "219 221 240 257\n"                ),
    ("./rna",                    "Please supply dataset file name\n"),
    ("./rna rna_example.txt",    "GAUGGAACUUGACUACGUAAAUU\n"        ),
    ("./rna rosalind_rna.txt",   "rna_result.txt"                   ),
    ("./revc",                   "Please supply dataset file name\n"),
    ("./revc revc_example.txt",  "ACCGGGTTTT"                       ),
    ("./revc rosalind_revc.txt", "revc_result.txt"                  )]:

    out = subprocess.check_output(string.split(test))
    cmd = string.split(test)[0]
    if exp_out.endswith(".txt"):
        f = open(exp_out, 'r')
        exp_out = f.read()
    if out == exp_out:
        print cmd, "PASS"
    else:
        print cmd, "FAIL", out
