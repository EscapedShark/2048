# Console 2048 Game (控制台版 2048 游戏)

[English](#english) | [中文](#chinese)

## English

### Introduction
A simple implementation of the classic 2048 game that runs in the terminal/console environment, specifically optimized for macOS and Linux systems. The game features a clean interface with keyboard controls and score tracking.

### Features
- Clean terminal-based user interface
- Keyboard controls (WASD)
- Score tracking
- Random generation of new numbers (2 or 4)
- Game over detection
- Cross-platform compatibility (macOS/Linux)

### Requirements
- C++ compiler (supporting C++11 or later)
- Terminal that supports ANSI escape codes
- macOS or Linux operating system

### How to Compile
```bash
g++ -o 2048 2048.cpp
```

### How to Play
1. Run the compiled program:
```bash
./2048
```

2. Use the following controls:
- W: Move Up
- S: Move Down
- A: Move Left
- D: Move Right
- Q: Quit Game

### Game Rules
- Start with two random numbers (2 or 4) on the board
- Move tiles in four directions
- Tiles with the same number merge when they collide
- After each move, a new tile (2 or 4) appears
- Game ends when no more moves are possible
- Try to create a tile with the number 2048!

---

## Chinese

### 简介
这是一个在终端/控制台环境运行的经典 2048 游戏实现，专门针对 macOS 和 Linux 系统优化。游戏具有简洁的界面，支持键盘控制和分数跟踪。

### 特性
- 清晰的终端用户界面
- 键盘控制（WASD）
- 分数追踪
- 随机生成新数字（2或4）
- 游戏结束检测
- 跨平台兼容（macOS/Linux）

### 运行要求
- C++ 编译器（支持 C++11 或更高版本）
- 支持 ANSI 转义码的终端
- macOS 或 Linux 操作系统

### 如何编译
```bash
g++ -o 2048 2048.cpp
```

### 游戏操作
1. 运行编译后的程序：
```bash
./2048
```

2. 使用以下按键控制：
- W：向上移动
- S：向下移动
- A：向左移动
- D：向右移动
- Q：退出游戏

### 游戏规则
- 游戏开始时棋盘上随机出现两个数字（2或4）
- 可以向四个方向移动方块
- 相同数字的方块相撞时会合并
- 每次移动后会出现一个新的方块（2或4）
- 无法移动时游戏结束
- 尝试创建一个数字为2048的方块！

### 技术特点
- 使用 C++ 标准库实现
- 采用 ANSI 转义序列实现清屏效果
- 使用 termios.h 实现无缓冲键盘输入
- 合理的代码结构和游戏逻辑封装