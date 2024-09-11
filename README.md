## 项目名称

九州仙途 - 仙侠风格/箱庭RPG/MUD游戏

## 概述

《九州仙途》是一款基于C++开发的仙侠风格箱庭RPG游戏。游戏中玩家可以自由探索游戏世界，与NPC互动并完成任务，购买装备和道具，参与多人游戏模式等。游戏采用自研TUI系统。欢迎体验。

## 游戏特点

- 自研TUI系统
- 卡组构筑玩法
- 箱庭式RPG玩法
- 3500+行代码，打造完备的仙侠体系！
- 5000+字的剧情演出！

## 运行游戏

请从项目Release页面下载最新版本的游戏。解压后运行`Game.exe`即可开始游戏。

注意，游戏需要**在Windows环境下运行**。**`Game.exe`需要使用管理员权限运行，否则会偶现界面Bug。**

## 自行编译

- Clone本项目到本地。
- 在根目录，Windows环境中，使用下述命令编译项目：

```shell
g++ -std=c++17 -fexec-charset=GBK -g "*.cpp" -o "Game.exe"
```

- 静待大概10秒即可。编译完成后，运行`Game.exe`即可开始游戏。

*请确保您的编译环境支持C++17标准。*

## 贡献

欢迎对该项目进行贡献。如果您发现了任何问题或有改进建议，请提交问题或拉取请求。

## 版权和许可

本项目由 *《2024年夏·程序设计基础实践》21组版权所有* 。请勿抄袭或滥用该项目。
