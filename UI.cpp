#include <windows.h>
#include <vector>
#include <string>
#include "console.h"
#include "UI.h"
#include "config.h"

bool initUI()
{
    setCursor(false);
    setScreenSize(101, 42);
    HWND consoleWindow = GetConsoleWindow();              // 获取控制台窗口句柄
    LONG style = GetWindowLong(consoleWindow, GWL_STYLE); // 获取当前窗口样式
    style &= ~(WS_MAXIMIZEBOX | WS_SIZEBOX);              // 禁用最大化按钮和调整窗口大小
    SetWindowLong(consoleWindow, GWL_STYLE, style);       // 设置新的窗口样式
    system("color 0C");

    return true;
}
bool printUI()
{
    setPrintColor("white", "black");
    for (int i = 0; i < 100; i++)
        print("#", i, 0);
    for (int i = 0; i <= 40; i++)
        print("#", 0, i);
    for (int i = 0; i <= 40; i++)
        print("#", 100, i);
    for (int i = 0; i <= 100; i++)
        print("#", i, 41);
    for (int i = 1; i < 60; i++)
        print("=", i, 30);
    for (int i = 60; i < 100; i++)
        print("=", i, 35);
    for (int i = 60; i < 100; i++)
        print("=", i, 15);
    for (int i = 31; i <= 40; i++)
        print("|", 30, i);
    std::vector<std::string> s1 =
        {
            "┌──────────────┐",
            "│              │",
            "│              │",
            "│              │",
            "│              │",
            "│              │",
            "│              │",
            "│              │",
            "│              │",
            "└──────────────┘"};
    print(s1, 37, 31);
    for (int i = 1; i <= 40; i++)
        print("|", 60, i);
    for (int i = 3; i < 55; i++)
        print("空", i, 3);
    for (int i = 3; i <= 27; i++)
        print("空", 3, i);
    for (int i = 3; i <= 27; i++)
        print("空", 55, i);
    for (int i = 3; i <= 55; i++)
        print("空", i, 27);

    return true;
}

std::vector<Message> messagebox;
void message(std::string s, std::string fore /* ="white" */, std::string back /* ="black" */)
{
    if (messagebox.size() >= MessageConfig::max)
        messagebox.erase(messagebox.begin());
    messagebox.push_back(Message(s, fore, back));
    clear(MessageConfig::printX, MessageConfig::printY, MessageConfig::printX2, MessageConfig::printY2);
    for (int i = 0; i < messagebox.size(); i++)
    {
        setPrintColor(messagebox[i].fore, messagebox[i].back);
        if (messagebox[i].s != "")
            print(messagebox[i].s, MessageConfig::printX, MessageConfig::printY + i);
    }
}