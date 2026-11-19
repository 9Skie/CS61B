PYTHON = python3
TESTER_FLAGS =
TESTS = $(wildcard samples/*.in student_tests/*.in *.in)
.PHONY: default check clean
default:
	$(MAKE) -C .. check
check:
	$(PYTHON) tester.py $(TESTER_FLAGS) $(TESTS)
clean:
	rm -rf __pycache__
