#!bin/bash
find . \( -name "*.cpp" -o -name "*.hpp" \) -exec cat {} + > combined_code.txt