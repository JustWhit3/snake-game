<p align="center"><img src="https://github.com/JustWhit3/snake-game/blob/main/img/images/logo.png" height=220></p>

<h3 align="center">A snake game created using SFML. </h3>
<p align="center">
  <img title="v0.1" alt="v0.1" src="https://img.shields.io/badge/version-v0.1-informational?style=flat-square">
  <img title="MIT License" alt="license" src="https://img.shields.io/badge/license-MIT-informational?style=flat-square">
	<img title="C++20" alt="C++20" src="https://img.shields.io/badge/c++-20-informational?style=flat-square"><br/>
	<img title="Code size" alt="code size" src="https://img.shields.io/github/languages/code-size/JustWhit3/snake-game?color=red">
	<img title="Repo size" alt="repo size" src="https://img.shields.io/github/repo-size/JustWhit3/snake-game?color=red">
	<img title="Lines of code" alt="total lines" src="https://img.shields.io/tokei/lines/github/JustWhit3/snake-game?color=red"></br>
  <img title="codeq" alt="codeq" src="https://github.com/JustWhit3/snake-game/actions/workflows/codeql-analysis.yml/badge.svg">
  <img title="doc" alt="doc" src="https://github.com/JustWhit3/snake-game/actions/workflows/DocGenerator.yml/badge.svg">
</p>

***

<img src="https://github.com/JustWhit3/snake-game/blob/main/img/examples/example.gif">

## Table of contents

- [Introduction](#introduction)
- [Architectures support](#architectures-support)
  - [Operating systems](#operating-systems)
  - [Compilers](#compilers)
- [Install and use](#install-and-use)
  - [Install](#install)
  - [Debug mode](#debug-mode)
- [States](#states)
  - [Menu](#menu)
  - [Game](#game)
  - [Scores](#scores)
  - [Options](#options)
- [Todo](#todo)
- [Credits](#credits)
  - [Project leaders](#project-leaders)
- [Stargazers over time](#stargazers-over-time)

## Introduction

In this repository a C++20 implementation of the popular snake game, using the [SFML](https://www.sfml-dev.org/) graphics library is provided.

> :warning: if you are connecting more than one screens in your pc there may be small graphics glitches due to SFML doesn't supporting multiple screens yet.

## Architectures support

### Operating systems

- **Linux**
  - *Ubuntu* (tested)
- **Windows** (release 10 or higher)
  - *Cygwin64* (tested)
  - *MSYS2* (tested)
  - *MinGW* (tested)
  - *WSL* (tested)
  - *Powershell* (tested)
- **MacOS**

### Compilers

- **gcc**:
  - *C++20*: 9/10/11/12
- **clang**:
  - *C++20*: 9/10/11/12/13
- **MSVC**:
  - *C++20*: // (not tested yet)

## Install and use

### Install

Steps to be reproduced:

**1)** Download one of the [releases](https://github.com/JustWhit3/snake-game/releases) of the repository.

**2)** Unzip and enter the downloaded repository directory.

**3)** Install and compile the game and its dependencies:

```bash
cmake -B build
```

Install:

```bash
sudo cmake --build build --target install
```

> :warning: `sudo` is not required on Windows.

Mandatory prerequisites (automatically installed with the script):

- C++20 standard
- g++ compiler
- [CMake](https://cmake.org/) (at least version 3.15)
- [SFML](https://www.sfml-dev.org/) library (version 2.5.1)

> :warning: on Linux other prerequisites for SFML are: `libx11-dev`, `xorg-dev`, `freeglut3-dev`, `libudev-dev`.

To run the game:

```bash
snake-game
```

Or if you don't want to install it:

```bash
cmake -B build
sudo cmake --build build
./build/src/snake-game
```

### Debug mode

To run debug mode:

```bash
cmake -B build -DCMAKE_BUILD_TYPE=Debug
sudo cmake --build build
```

Optional prerequisites for debug mode:

- [ptc::print](https://github.com/JustWhit3/ptc-print)
- [cppcheck](https://cppcheck.sourceforge.io/)

## States

### Menu

<img src="https://github.com/JustWhit3/snake-game/blob/main/img/examples/screenshots/menu.png">

Commands:

- **Key arrows** (Up / Down): to move from a button to another.
- **Esc**: quit the window.
- **Enter / Right mouse click**: click on a button.

### Game

<img src="https://github.com/JustWhit3/snake-game/blob/main/examples/screenshots/game.png">

Commands:

- **Key arrows** (Up / Down / Left / Right): move snake.
- **Esc**: pause game.

### Scores

Work in progress...

### Options

Work in progress...

## Todo

- Add animations.
- Add Score state.
- Add Options state.
- Add sounds and music.

## Credits

### Project leaders

<!-- ALL-CONTRIBUTORS-LIST:START - Do not remove or modify this section -->
<!-- prettier-ignore-start -->
<!-- markdownlint-disable -->
<table>
  <tr>
    <td align="center"><a href="https://justwhit3.github.io/"><img src="https://avatars.githubusercontent.com/u/48323961?v=4" width="100px;" alt=""/><br /><sub><b>Gianluca Bianco</b></sub></a></td>
  </tr>
</table>

<!-- markdownlint-restore -->
<!-- prettier-ignore-end -->

<!-- ALL-CONTRIBUTORS-LIST:END -->

## Stargazers over time

[![Stargazers over time](https://starchart.cc/JustWhit3/snake-game.svg)](https://starchart.cc/JustWhit3/snake-game)

