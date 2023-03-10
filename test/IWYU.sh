#!/bin/bash

# Variables
declare -a source_files=(
  "entities/entity.cpp"
  "entities/food.cpp"
  "entities/snake.cpp"
  "states/state.cpp"
  "states/menu_state.cpp"
  "states/game_state.cpp"
  "states/loose_state.cpp"
  "states/options_state.cpp"
  "states/pause_state.cpp"
  "states/scores_state.cpp"
  "utility/gui.cpp"
  "widgets/button.cpp"
  "widgets/widget.cpp"
  "widgets/textbox.cpp"
  "windows/base_window.cpp"
  "windows/pause_window.cpp"
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
