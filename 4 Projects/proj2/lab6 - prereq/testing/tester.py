#!/usr/bin/env python3
"""Run the original Capers .in fixtures against the C++ executable."""
import importlib.util
from pathlib import Path
here = Path(__file__).resolve()
spec = importlib.util.spec_from_file_location("gitlet_test_runner", here.parents[2] / "testing" / "tester.py")
runner = importlib.util.module_from_spec(spec)
spec.loader.exec_module(runner)
if __name__ == "__main__":
    raise SystemExit(runner.main(default_program=here.parents[1] / "build" / "capers"))
