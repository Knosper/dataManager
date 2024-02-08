#!/bin/bash
find . \( -name "*.cpp" -o -name "*.hpp" \) -exec grep . {} + > combined_code.txt
