# blackJack-game
基于C++开发的命令行21点扑克游戏的程序设计实验课作业

## 功能特点

- 完整的21点游戏规则实现
- 庄家点数<17时自动要牌
- 支持Ace的1/11点切换
- 友好的用户界面

## 技术栈

- C++ 11
- 面向对象编程
- STL容器（vector, algorithm, random）

## 类设计

- `Card` - 扑克牌类
- `Deck` - 牌组类
- `Hand` - 手牌类  
- `blackJack` - 游戏主控类

## 编译运行

```bash
g++ -std=c++11 main.cpp -o blackjack
./blackjack
