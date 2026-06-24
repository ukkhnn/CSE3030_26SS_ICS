#!/usr/bin/env python3
"""Build temporary copies and compare the supplied Lab1/Lab3 sample outputs."""
from pathlib import Path
import shutil
import subprocess
import tempfile

ROOT = Path(__file__).resolve().parents[1]

def main():
    passed = 0
    with tempfile.TemporaryDirectory(prefix="ics-samples-") as directory:
        temporary = Path(directory)
        for relative, count, kind in [
            ("lab1/1-1", 2, "bit"),
            ("lab1/1-2", 2, "bit"),
            ("lab1/1-3", 2, "bit"),
            ("lab3/3-1", 4, "cache"),
            ("lab3/3-2", 2, "cache"),
        ]:
            project = temporary / relative
            shutil.copytree(ROOT / relative, project)
            subprocess.run(["make", "clean"], cwd=project, check=True, capture_output=True)
            subprocess.run(["make"], cwd=project, check=True, capture_output=True)
            for case in range(1, count + 1):
                inputs = ([f"testcase/tc-{case}"] if kind == "bit" else
                          [f"testcase/config-{case}", f"testcase/trace-{case}"])
                result = subprocess.run(["./main.bin", *inputs], cwd=project,
                                        capture_output=True, check=True, timeout=5)
                expected = (project / f"testcase/ans-{case}").read_bytes()
                if result.stdout != expected:
                    raise RuntimeError(f"{relative} case {case}: output differs from provided answer")
                passed += 1
            print(f"PASS {relative}: {count} samples")
    print(f"PASS: {passed} supplied samples")

if __name__ == "__main__":
    main()
