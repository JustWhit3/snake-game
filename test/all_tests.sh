#!/bin/bash

# Unit tests
#echo "======================================================"
#echo "     UNIT TESTS"
#echo "======================================================"
#echo ""
# Empty for the moment...

# Memory tests
#echo ""
#echo "======================================================"
#echo "     MEMORY TESTS"
#echo "======================================================"
#echo ""
#./test/profiling.sh memcheck ./build/examples/osmanip_graphics

# Threading tests
#echo ""
#echo "======================================================"
#echo "     THREADING TESTS"
#echo "======================================================"
#echo ""
#./test/profiling.sh helgrind ./build/examples/osmanip_graphics

# IWYU tests
#echo ""
#echo "======================================================"
#echo "     IWYU TESTS"
#echo "======================================================"
#echo ""

# Cppcheck
echo ""
echo "======================================================"
echo "     CPPCHECK TESTS"
echo "======================================================"
echo ""
cppcheck include/entities/* include/states/* include/widgets/* include/windows/* src/entities/* src/states/* src/widgets/* src/windows/* src/snake-game.cpp
