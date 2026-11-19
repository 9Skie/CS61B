#!/usr/bin/env python3
"""Compatibility entry point: same C++ runner as tester.py. Run make first."""
from tester import main
if __name__ == "__main__":
    raise SystemExit(main())
