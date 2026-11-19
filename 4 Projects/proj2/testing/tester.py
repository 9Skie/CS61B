#!/usr/bin/env python3
"""C++ adapter for the CS61B Spring 2021 Gitlet integration-test format.

Supported directives: #, I, C, T, +, -, > ... <<< or <<<*, =, *, E, D.
Variables ${NAME} and regex captures ${1}, ${2}, ... retain course semantics.
Commands use shell-style quoting but execute directly, without a shell.
"""
import argparse
import re
import shlex
import sys
import tempfile
from glob import glob
from pathlib import Path
from subprocess import check_output, STDOUT, DEVNULL, CalledProcessError, TimeoutExpired
from os.path import basename, dirname, exists, join, splitext
from os import mkdir, remove
from shutil import copyfile, rmtree

TIMEOUT = 10
show = None
keep = False
verbose = False
src_dir = "src"
output_tolerance = 0
program = Path(__file__).resolve().parents[1] / "build" / "gitlet"

Mat = None
def Match(patn, s):
    global Mat
    Mat = re.match(patn, s)
    return Mat

def Group(n):
    return Mat.group(n)

def contents(filename):
    try:
        with open(filename) as inp:
            return inp.read()
    except FileNotFoundError:
        return None

def editDistance(s1, s2):
    dist = [list(range(len(s2) + 1))] + \
           [ [i] + [ 0 ] * len(s2) for i in range(1, len(s1) + 1) ]
    for i in range(1, len(s1) + 1):
        for j in range(1, len(s2) + 1):
            dist[i][j] = min(dist[i-1][j] + 1,
                             dist[i][j-1] + 1,
                             dist[i-1][j-1] + (s1[i-1] != s2[j-1]))
    return dist[len(s1)][len(s2)]

def createTempDir(base):
    return tempfile.mkdtemp(prefix=base + "-", dir=str(Path.cwd()))

def cleanTempDir(dir):
    rmtree(dir, ignore_errors=True)

def doDelete(name, dir):
    try:
        remove(join(dir, name))
    except OSError:
        pass

def doCopy(dest, src, dir):
    try:
        doDelete(dest, dir)
        copyfile(join(src_dir, src), join(dir, dest))
    except OSError:
        raise ValueError("file {} could not be copied to {}".format(src, dest))

def doExecute(cmnd, dir, timeout, line_num):
    try:
        argv = [str(program)] + shlex.split(cmnd)
        out = check_output(argv, cwd=dir, text=True, encoding="utf-8",
                           stdin=DEVNULL, stderr=STDOUT, timeout=timeout)
        return "OK", out
    except CalledProcessError as excp:
        return "program exited with code {}".format(excp.returncode), excp.output
    except TimeoutExpired:
        return "timeout", None
    except OSError as excp:
        return "could not execute: {}".format(excp), None

def fileExists(f, dir):
    return exists(join(dir, f))

def correctFileOutput(name, expected, dir):
    # Compare bytes: both missing files and newline conversions must not pass.
    try:
        return Path(dir, name).read_bytes() == Path(src_dir, expected).read_bytes()
    except OSError:
        return False

def correctProgramOutput(expected, actual, last_groups, is_regexp):
    expected = re.sub(r'[ \t]+\n', '\n', '\n'.join(expected))
    expected = re.sub(r'(?m)^[ \t]+', ' ', expected)
    actual = re.sub(r'[ \t]+\n', '\n', actual)
    actual = re.sub(r'(?m)^[ \t]+', ' ', actual)

    last_groups[:] = (actual,)
    if is_regexp:
        try:
            if not Match(expected.rstrip() + r"\Z", actual) \
                   and not Match(expected.rstrip() + r"\Z", actual.rstrip()):
                return False
        except:
            raise ValueError("bad pattern")
        last_groups[:] += Mat.groups()
    else:
        expected, actual = expected.rstrip(), actual.rstrip()
        if expected == actual:
            return True
        if output_tolerance == 0:
            return False
        if editDistance(expected, actual) > output_tolerance:
            return False
    return True

def reportDetails(test, included_files, line_num):
    if show is None:
        return
    if isinstance(show, int) and show <= 0:
        print("   Limit on error details exceeded.")
        return
    print("    Error on line {} of {}".format(line_num, basename(test)))

    for base in [basename(test)] + included_files:
        full = join(dirname(test), base)
        print(("-" * 20 + " {} " + "-" * 20).format(base))
        text_lines = list(enumerate(contents(full).splitlines()))
        fmt = "{{:{}d}}. {{}}".format(len(str(max(1, len(text_lines)))))
        text = '\n'.join(map(lambda p: fmt.format(p[0] + 1, p[1]), text_lines))
        print(text)
        print("-" * (42 + len(base)))

def chop_nl(s):
    if s and s[-1] == '\n':
        return s[:-1]
    else:
        return s

def line_reader(f, prefix):
    n = 0
    try:
        with open(f) as inp:
            while True:
                L = inp.readline()
                if L == '':
                    return
                n += 1
                included_file = yield (prefix + str(n), L)
                if included_file:
                    yield None
                    yield from line_reader(included_file, prefix + str(n) + ".")
    except FileNotFoundError:
        raise ValueError("file {} not found".format(f))

def doTest(test):
    last_groups = []
    base = splitext(basename(test))[0]
    print("{}:".format(base))
    cdir = tmpdir = createTempDir(base)

    if verbose:
        print("Testing directory: {}".format(tmpdir))

    timeout = TIMEOUT
    defns = {}

    def do_substs(L):
        c = 0
        L0 = None
        while L0 != L and c < 10:
            c += 1
            L0 = L
            L = re.sub(r'\$\{(.*?)\}', subst_var, L)
        return L

    def subst_var(M):
        key = M.group(1)
        if Match(r'\d+$', key):
            try:
                return last_groups[int(key)]
            except IndexError:
                raise ValueError("FAILED (nonexistent group: {{{}}})"
                                 .format(key))
        elif M.group(1) in defns:
            return defns[M.group(1)]
        else:
            raise ValueError("undefined substitution: ${{{}}}".format(M.group(1)))

    try:
        line_num = None
        inp = line_reader(test, '')
        included_files = []
        while True:
            line_num, line = next(inp, (line_num, ''))
            if line == "":
                print("OK")
                return True
            if not Match(r'\s*#', line):
                line = do_substs(line)
            if verbose:
                print("+ {}".format(line.rstrip()))
            if Match(r'\s*#', line) or Match(r'\s+$', line):
                pass
            elif Match(r'I\s+(\S+)', line):
                inp.send(join(dirname(test), Group(1)))
                included_files.append(Group(1))
            elif Match(r'C\s*(\S*)', line):
                if Group(1) == "":
                    cdir = tmpdir
                else:
                    cdir = join(tmpdir, Group(1))
                    if not exists(cdir):
                        mkdir(cdir)
            elif Match(r'T\s*(\S+)', line):
                try:
                    timeout = float(Group(1))
                    if timeout <= 0:
                        raise ValueError()
                except ValueError:
                    raise ValueError("bad time: {}".format(line))
            elif Match(r'\+\s*(\S+)\s+(\S+)', line):
                doCopy(Group(1), Group(2), cdir)
            elif Match(r'-\s*(\S+)', line):
                doDelete(Group(1), cdir)
            elif Match(r'>\s*(.*)', line):
                cmnd = Group(1)
                expected = []
                while True:
                    line_num, L = next(inp, (line_num, ''))
                    if L == '':
                        raise ValueError("unterminated command: {}"
                                         .format(line))
                    L = L.rstrip()
                    if Match(r'<<<(\*?)', L):
                        is_regexp = Group(1)
                        break
                    expected.append(do_substs(L))
                msg, out = doExecute(cmnd, cdir, timeout, line_num)
                if verbose:
                    if out:
                        print(re.sub(r'(?m)^', '- ', chop_nl(out)))
                if msg == "OK":
                    if not correctProgramOutput(expected, out, last_groups,
                                                is_regexp):
                        msg = "incorrect output"
                if msg != "OK":
                    print("ERROR ({})".format(msg))
                    if out and not verbose:
                        print(out.rstrip())
                    reportDetails(test, included_files, line_num)
                    return False
            elif Match(r'=\s*(\S+)\s+(\S+)', line):
                if not correctFileOutput(Group(1), Group(2), cdir):
                    print("ERROR (file {} has incorrect content)"
                          .format(Group(1)))
                    reportDetails(test, included_files, line_num)
                    return False
            elif Match(r'\*\s*(\S+)', line):
                if fileExists(Group(1), cdir):
                    print("ERROR (file {} present)".format(Group(1)))
                    reportDetails(test, included_files, line_num)
                    return False
            elif Match(r'E\s*(\S+)', line):
                if not fileExists(Group(1), cdir):
                    print("ERROR (file or directory {} not present)"
                          .format(Group(1)))
                    reportDetails(test, included_files, line_num)
                    return False
            elif Match(r'(?s)D\s*([a-zA-Z_][a-zA-Z_0-9]*)\s*"(.*)"\s*$', line):
                defns[Group(1)] = Group(2)
            else:
                raise ValueError("bad test line at {}".format(line_num))
    finally:
        if not keep:
            cleanTempDir(tmpdir)
        else:
            print("Directory state saved in {}".format(tmpdir))


def main(argv=None, default_program=None):
    global show, keep, verbose, src_dir, output_tolerance, program, TIMEOUT
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--program", type=Path,
                        default=default_program or Path(__file__).resolve().parents[1] / "build" / "gitlet",
                        help="Path to the compiled executable (resolved before changing directories)")
    parser.add_argument("--show", default=None, metavar="N|all", help="Show failing test source")
    parser.add_argument("--keep", action="store_true", help="Keep temporary test directories")
    parser.add_argument("--verbose", action="store_true")
    parser.add_argument("--src", type=Path, default=Path("src"), help="Fixture directory")
    parser.add_argument("--timeout", type=float, default=10)
    parser.add_argument("--tolerance", type=int, default=0, help="Output edit tolerance; default exact")
    parser.add_argument("tests", nargs="+", help="Test .in files or glob patterns")
    opts = parser.parse_args(argv)
    if opts.timeout <= 0 or opts.tolerance < 0:
        parser.error("timeout must be positive and tolerance non-negative")
    if opts.show is None or opts.show == "all":
        show = opts.show
    else:
        try:
            show = int(opts.show)
            if show < 0: raise ValueError()
        except ValueError:
            parser.error("--show must be a non-negative integer or all")
    keep, verbose = opts.keep, opts.verbose
    src_dir = str(opts.src.resolve())
    TIMEOUT, output_tolerance = opts.timeout, opts.tolerance
    program = opts.program.resolve()
    if not program.is_file():
        parser.error("Executable not found: {}. Build it with make first.".format(program))
    files = []
    for pattern in opts.tests:
        matches = sorted(glob(pattern))
        if not matches:
            parser.error("No tests match: {}".format(pattern))
        for name in matches:
            if name not in files:
                files.append(name)
    failures = 0
    for test in files:
        try:
            passed = doTest(test)
        except (ValueError, OSError) as error:
            print("FAILED ({})".format(error))
            passed = False
        if not passed:
            failures += 1
            if isinstance(show, int): show -= 1
    print("\nRan {} tests. {} passed; {} failed.".format(len(files), len(files)-failures, failures))
    return 1 if failures else 0

if __name__ == "__main__":
    sys.exit(main())
