/**
 * @file startscene.cpp
 * @author 《2024年夏·程序设计基础实践》21组
 * @brief 包含开始屏幕相关函数
 * @version 1.0
 * @date 2024-09-11
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include <string>
#include <vector>
#include <string>
#include <windows.h>
#include <conio.h>
#include <thread>
#include <mutex>
#include <map>
#include "startScene.h"
#include "save.h"
#include "UI.h"
#include "console.h"

std::map<int, std::vector<std::tuple<std::string, int, int>>> groupedLOGO = {
    {2, {{"        ", 52, 2}}},
    {3, {{"  ", 50, 3}, {"  ", 60, 3}}},
    {4, {{"          ", 46, 4}, {"  ", 60, 4}}},
    {5, {{"                ", 44, 5}}},
    {6, {{"  ", 42, 6}, {"  ", 48, 6}, {"      ", 54, 6}}},
    {7, {{"  ", 40, 7}, {"  ", 46, 7}, {"  ", 52, 7}, {"    ", 58, 7}}},
    {8, {{"  ", 38, 8}, {"  ", 44, 8}, {"  ", 50, 8}, {"  ", 56, 8}, {"  ", 62, 8}}},
    {9, {{"                  ", 38, 9}, {"    ", 60, 9}}},
    {10, {{"    ", 36, 10}, {"  ", 44, 10}, {"      ", 54, 10}, {"  ", 62, 10}}},
    {11, {{"  ", 36, 11}, {"  ", 54, 11}, {"    ", 60, 11}}},
    {12, {{"  ", 36, 12}, {"  ", 54, 12}, {"  ", 58, 12}, {"  ", 62, 12}}},
    {13, {{"      ", 36, 13}, {"          ", 48, 13}, {"  ", 62, 13}}},
    {14, {{"  ", 36, 14}, {"  ", 42, 14}, {"  ", 46, 14}, {"    ", 54, 14}, {"  ", 60, 14}}},
    {15, {{"       ", 38, 15}, {"      ", 46, 15}, {"      ", 54, 15}, {"  ", 62, 15}}},
    {16, {{"  ", 38, 16}, {" ", 44, 16}, {"    ", 54, 16}, {"  ", 62, 16}}},
    {17, {{"  ", 38, 17}, {"  ", 42, 17}, {"    ", 54, 17}, {"  ", 62, 17}}},
    {18, {{"    ", 38, 18}, {"  ", 44, 18}, {"    ", 54, 18}, {"  ", 62, 18}}},
    {19, {{"  ", 38, 19}, {"  ", 42, 19}, {"      ", 52, 19}, {"  ", 62, 19}}},
    {20, {{"  ", 38, 20}, {"  ", 42, 20}, {"    ", 48, 20}, {"    ", 54, 20}, {"  ", 64, 20}}},
    {21, {{"  ", 38, 21}, {"    ", 44, 21}, {"    ", 54, 21}, {"  ", 64, 21}, {"  ", 64, 21}}},
    {22, {{"  ", 38, 22}, {"   ", 45, 22}, {"  ", 54, 22}, {"  ", 58, 22}, {"  ", 66, 22}}},
    {23, {{"      ", 38, 23}, {"   ", 45, 23}, {"  ", 54, 23}, {"      ", 58, 23}, {"  ", 66, 23}}},
    {24, {{"    ", 38, 24}, {"    ", 38, 24}, {"    ", 44, 24}, {"  ", 54, 24}, {"  ", 58, 24}, {"  ", 64, 24}, {"  ", 68, 24}}},
    {25, {{"       ", 36, 25}, {"    ", 44, 25}, {"      ", 54, 25}, {"    ", 66, 25}}},
    {26, {{"    ", 32, 26}, {"        ", 40, 26}, {"    ", 52, 26}, {"  ", 58, 26}, {"    ", 70, 26}}},
    {27, {{"    ", 28, 27}, {"  ", 40, 27}, {"        ", 44, 27}, {"  ", 54, 27}, {"  ", 58, 27}, {"  ", 74, 27}}},
    {28, {{"  ", 26, 28}, {"    ", 40, 28}, {"    ", 46, 28}, {"  ", 54, 28}, {"  ", 58, 28}, {"  ", 76, 28}}},
    {29, {{"  ", 26, 29}, {"    ", 38, 29}, {"    ", 44, 29}, {"  ", 50, 29}, {"  ", 54, 29}, {"  ", 58, 29}, {"  ", 78, 29}}},
    {30, {{"  ", 24, 30}, {"  ", 38, 30}, {"    ", 42, 30}, {"  ", 50, 30}, {"  ", 56, 30}, {"  ", 78, 30}}},
    {31, {{"  ", 24, 31}, {"  ", 38, 31}, {"  ", 42, 31}, {"  ", 50, 31}, {"  ", 78, 31}}},
    {32, {{"  ", 24, 32}, {"    ", 40, 32}, {"  ", 50, 32}, {"  ", 80, 32}}},
    {33, {{"  ", 22, 33}, {"  ", 42, 33}, {"  ", 52, 33}, {"  ", 80, 33}}},
    {34, {{"                                                            ", 22, 34}}}
};

std::map<int, std::vector<std::tuple<std::string, int, int>>> groupedText_1 = {
    {4, {{"      ", 2, 4}, {"    ", 13, 4}, {"        ", 21, 4}, {"  ", 31, 4}, {"  ", 37, 4}, {"        ", 69, 4}, {"  ", 79, 4}, {"  ", 85, 4}, {"       ", 90, 4}}},
    {5, {{"  ", 2, 5}, {"  ", 7, 5}, {"  ", 11, 5}, {"  ", 17, 5}, {"  ", 24, 5}, {"  ", 31, 5}, {"  ", 37, 5}, {"  ", 61, 5}, {"  ", 72, 5}, {"  ", 79, 5}, {"  ", 85, 5}, {"  ", 90, 5}}},
    {6, {{"      ", 2, 6}, {"  ", 11, 6}, {"  ", 17, 6}, {"  ", 24, 6}, {"        ", 31, 6}, {"  ", 61, 6}, {"  ", 72, 6}, {"        ", 79, 6}, {"       ", 90, 6}}},
    {7, {{"  ", 2, 7}, {"        ", 11, 7}, {"  ", 24, 7}, {"  ", 31, 7}, {"  ", 37, 7}, {"  ", 61, 7}, {"  ", 72, 7}, {"  ", 79, 7}, {"  ", 85, 7}, {"  ", 90, 7}}},
    {8, {{"  ", 2, 8}, {"  ", 11, 8}, {"  ", 17, 8}, {"  ", 24, 8}, {"  ", 31, 8}, {" ", 37, 8}, {"  ", 72, 8}, {"  ", 79, 8}, {"  ", 85, 8}, {"       ", 90, 8}}}
};

std::map<int, std::vector<std::tuple<std::string, int, int>>> groupedText_2 = {
    {15, {{"  ", 1, 15}, {"  ", 5, 15}, {"  ", 13, 15}, {"  ", 17, 15}, {"  ", 25, 15}, {"      ", 30, 15}, {" ", 64, 15}, {"  ", 69, 15}, {"  ", 79, 15}, {"        ", 83, 15}, {"  ", 93, 15}, {"  ", 99, 15}}},
    {16, {{"    ", 5, 16}, {"    ", 11, 16}, {"    ", 17, 16}, {"    ", 23, 16}, {"  ", 29, 16}, {"  ", 35, 16}, {"  ", 65, 16}, {"  ", 69, 16}, {"  ", 86, 16}, {"  ", 94, 16}, {"  ", 98, 16}}},
    {17, {{"  ", 1, 17}, {"  ", 5, 17}, {"  ", 9, 17}, {"  ", 13, 17}, {"  ", 17, 17}, {"  ", 21, 17}, {"  ", 25, 17}, {"  ", 29, 17}, {"  ", 35, 17}, {"  ", 65, 17}, {"  ", 69, 17}, {"  ", 79, 17}, {"  ", 86, 17},  {"  ", 96, 17}}},
    {18, {{"  ", 1, 18}, {"  ", 5, 18}, {"  ", 9, 18}, {"  ", 13, 18}, {"  ", 17, 18}, {"  ", 21, 18}, {"  ", 25, 18}, {"  ", 29, 18}, {"  ", 35, 18}, {"   ", 64, 18}, {"  ", 69, 18}, {"  ", 79, 18}, {"  ", 86, 18},  {"  ", 96, 18}}},
    {19, {{"  ", 1, 19}, {"  ", 5, 19}, {"  ", 9, 19}, {"  ", 13, 19}, {"  ", 17, 19}, {"  ", 21, 19}, {"  ", 25, 19}, {"      ", 30, 19}, {"  ", 65, 19}, {"        ", 69, 19}, {"  ", 79, 19}, {"  ", 86, 19},  {"  ", 96, 19}}},
};

// 创建互斥锁
std::mutex screenMtx;

// 场景主循环终止信号
bool startSceneMainLoopEnd = false;

// 直接退出游戏的标识
bool exitGame = false;

void UserLogin()
{
    // WIP
}

void UserRegister()
{
    // WIP
}

void loginOrRegister()
{
    screenMtx.lock();
    clear(4, 26, 22, 30);
    screenMtx.unlock();
    int userLoginChoice = 0;

    screenMtx.lock();
    setPrintColor("white", "yellow");
    print(">登入服务器 ", 8, 27);
    setPrintColor("white", "black");
    print("注册账号  ", 8, 28);
    print("返回上级菜单  ", 8, 30);
    screenMtx.unlock();

    while(!startSceneMainLoopEnd)
    {
        if (_kbhit())
        {
            char ch = _getch();
            if (ch == 87 || ch == 119)
                userLoginChoice = (userLoginChoice - 1 + 3) % 3;
            else if (ch == 83 || ch == 115)
                userLoginChoice = (userLoginChoice + 1) % 3;
            else if (ch == 13)
            {
                if (userLoginChoice == 0)
                    UserLogin();
                else if (userLoginChoice == 1)
                    UserRegister();
                else if (userLoginChoice == 2)
                {
                    screenMtx.lock();
                    clear(4, 26, 22, 30);
                    screenMtx.unlock();
                    return;
                }
            }
            else if (ch == 27)
            {
                exitGame = true;
                startSceneMainLoopEnd = true;
                return;
            }
        }
        if (userLoginChoice == 0)
        {
            screenMtx.lock();
            setPrintColor("white", "yellow");
            print(">登入服务器 ", 8, 27);
            setPrintColor("white", "black");
            print("注册账号    ", 8, 28);
            print("返回上级菜单    ", 8, 30);
            screenMtx.unlock();
        }
        else if (userLoginChoice == 1)
        {
            screenMtx.lock();
            setPrintColor("white", "black");
            print("登入服务器    ", 8, 27);
            setPrintColor("white", "yellow");
            print(">注册账号 ", 8, 28);
            setPrintColor("white", "black");
            print("返回上级菜单    ", 8, 30);
            screenMtx.unlock();
        }
        else if (userLoginChoice == 2)
        {
            screenMtx.lock();
            setPrintColor("white", "black");
            print("登入服务器    ", 8, 27);
            print("注册账号    ", 8, 28);
            setPrintColor("white", "yellow");
            print(">返回上级菜单 ", 8, 30);
            setPrintColor("white", "black");
            screenMtx.unlock();
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

void startSceneMainLoop()
{
    // 两个LOGO显示线程，互不干扰，但加互斥锁
    std::thread displayLOGO1([]() {
        while(!startSceneMainLoopEnd)
        {
            for (const auto& [key, group] : groupedLOGO) {
                for (const auto& [str, x, y] : group) {
                    screenMtx.lock();
                    setPrintColor("lightyellow", "lightyellow");
                    print(str, x, y);
                    screenMtx.unlock();
                    if (startSceneMainLoopEnd)
                        goto end;
                }
                std::this_thread::sleep_for(std::chrono::milliseconds(110));
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(200));
        }
        end:;
    });

    std::this_thread::sleep_for(std::chrono::milliseconds(440));

    std::thread displayLOGO2([]() {
        while(!startSceneMainLoopEnd)
        {
            for (const auto& [key, group] : groupedLOGO) {
                for (const auto& [str, x, y] : group) {
                    screenMtx.lock();
                    setPrintColor("white", "white");
                    print(str, x, y);
                    screenMtx.unlock();
                    if (startSceneMainLoopEnd)
                        goto end;
                }
                std::this_thread::sleep_for(std::chrono::milliseconds(110));
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(200));
        }
        end:;
    });

    // TextLOGO 1

    std::thread displayTextLOGO1_1([]() {
        while(!startSceneMainLoopEnd)
        {
            for (const auto& [key, group] : groupedText_1) {
                for (const auto& [str, x, y] : group) {
                    screenMtx.lock();
                    setPrintColor("lightgray", "lightgray");
                    print(str, x, y);
                    screenMtx.unlock();
                    if (startSceneMainLoopEnd)
                        goto end;
                }
                std::this_thread::sleep_for(std::chrono::milliseconds(170));
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(200));
        }
        end:;
    });

    std::this_thread::sleep_for(std::chrono::milliseconds(220));

    std::thread displayTextLOGO1_2([]() {
        while(!startSceneMainLoopEnd)
        {
            for (const auto& [key, group] : groupedText_1) {
                for (const auto& [str, x, y] : group) {
                    screenMtx.lock();
                    setPrintColor("white", "white");
                    print(str, x, y);
                    screenMtx.unlock();
                    if (startSceneMainLoopEnd)
                        goto end;
                }
                std::this_thread::sleep_for(std::chrono::milliseconds(170));
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(200));
        }
        end:;
    });

    std::this_thread::sleep_for(std::chrono::milliseconds(900));

    // Text LOGO 2

    std::thread displayTextLOGO2_1([]() {
        while(!startSceneMainLoopEnd)
        {
            for (const auto& [key, group] : groupedText_2) {
                for (const auto& [str, x, y] : group) {
                    screenMtx.lock();
                    setPrintColor("lightgray", "lightgray");
                    print(str, x, y);
                    screenMtx.unlock();
                    if (startSceneMainLoopEnd)
                        goto end;
                }
                std::this_thread::sleep_for(std::chrono::milliseconds(170));
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(200));
        }
        end:;
    });

    std::this_thread::sleep_for(std::chrono::milliseconds(220));

    std::thread displayTextLOGO2_2([]() {
        while(!startSceneMainLoopEnd)
        {
            for (const auto& [key, group] : groupedText_2) {
                for (const auto& [str, x, y] : group) {
                    screenMtx.lock();
                    setPrintColor("white", "white");
                    print(str, x, y);
                    screenMtx.unlock();
                    if (startSceneMainLoopEnd)
                        goto end;
                }
                std::this_thread::sleep_for(std::chrono::milliseconds(170));
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(200));
        }
        end:;
    });

    screenMtx.lock();
    setPrintColor("lightyellow", "black");
    print("九州仙途", 8, 24);
    setPrintColor("white", "yellow");
    print(">新游戏 ", 8, 27);
    setPrintColor("white", "black");
    print("加载游戏", 8, 28);
    print("在线游戏", 8, 29);
    print("退出游戏", 8, 30);
    screenMtx.unlock();

    int userChoice = 0;

    while(!startSceneMainLoopEnd)
    {
        if (_kbhit())
        {
            char ch = _getch();
            if (ch == 27)
            {
                exitGame = true;
                startSceneMainLoopEnd = true;
            }
            else if (ch == 87 || ch == 119)
                userChoice = (userChoice - 1 + 4) % 4;
            else if (ch == 83 || ch == 115)
                userChoice = (userChoice + 1) % 4;
            else if (ch == 13)
            {
                if (userChoice == 0)
                {
                    startSceneMainLoopEnd = true;
                }
                else if (userChoice == 1)
                {
                    startSceneMainLoopEnd = true;
                }
                else if (userChoice == 2)
                {
                    loginOrRegister();
                }
                else if (userChoice == 3)
                {
                    exitGame = true;
                    startSceneMainLoopEnd = true;
                }
            }
        }
        if (userChoice == 0)
        {
            screenMtx.lock();
            setPrintColor("white", "yellow");
            print(">新游戏 ", 8, 27);
            setPrintColor("white", "black");
            print("加载游戏   ", 8, 28);
            print("在线游戏   ", 8, 29);
            print("退出游戏   ", 8, 30);
            screenMtx.unlock();
        }
        else if (userChoice == 1)
        {
            screenMtx.lock();
            setPrintColor("white", "black");
            print("新游戏     ", 8, 27);
            setPrintColor("white", "yellow");
            print(">加载游戏 ", 8, 28);
            setPrintColor("white", "black");
            print("在线游戏   ", 8, 29);
            print("退出游戏   ", 8, 30);
            screenMtx.unlock();
        }
        else if (userChoice == 2)
        {
            screenMtx.lock();
            setPrintColor("white", "black");
            print("新游戏     ", 8, 27);
            print("加载游戏   ", 8, 28);
            setPrintColor("white", "yellow");
            print(">在线游戏 ", 8, 29);
            setPrintColor("white", "black");
            print("退出游戏   ", 8, 30);
            screenMtx.unlock();
        }
        else if (userChoice == 3)
        {
            screenMtx.lock();
            setPrintColor("white", "black");
            print("新游戏     ", 8, 27);
            print("加载游戏   ", 8, 28);
            print("在线游戏   ", 8, 29);
            setPrintColor("white", "yellow");
            print(">退出游戏 ", 8, 30);
            setPrintColor("white", "black");
            screenMtx.unlock();
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    // 销毁线程
    displayLOGO1.join();
    displayLOGO2.join();
    displayTextLOGO1_1.join();
    displayTextLOGO1_2.join();
    displayTextLOGO2_1.join();
    displayTextLOGO2_2.join();

    // 清屏
    clear();

}