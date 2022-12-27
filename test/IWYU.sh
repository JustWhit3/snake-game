#!/bin/bash

# Variables
declare -a source_files=(
  "entities/snake_body.cpp"
  "states/state.cpp"
  "states/menu_state.cpp"
  "states/game_state.cpp"
  "widgets/button.cpp"
  "windows/confirm_window.cpp"
  "windows/game_window.cpp"
  "snake-game.cpp"
)

# Source code check
echo ""
echo "======================================================"
echo "     IWYU Checks"
echo "======================================================"
echo ""
for source in "${source_files[@]}"; do
  include-what-you-use \
    -std=c++17 \
    -I/usr/lib/llvm-14/lib/clang/14.0.0/include \
    -Iinclude \
    src/"$source"

  echo ""
  echo "--------------------------------------------------"
  echo ""
done
