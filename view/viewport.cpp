#include <iostream>
#include <windows.h> 
#include <conio.h>
#include "console.h"
using namespace std;


void setConsoleSize(int width, int height) {  
    // 获取控制台窗口句柄  
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);  
    
    // 设置缓冲区大小  
    COORD coord;  
    coord.X = width;  
    coord.Y = height;  
    SetConsoleScreenBufferSize(hConsole, coord);  
    
    // 设置窗口大小  
    SMALL_RECT rect;  
    rect.Left = 0;  
    rect.Top = 0;  
    rect.Right = width - 1;  
    rect.Bottom = height - 1;  
    SetConsoleWindowInfo(hConsole, TRUE, &rect);  
}  

int main(){
	setscreensize(120, 50);
    int i;
    for(i=0;i<100;i++){
    	print("#",i,0);
	}
	for(i=0;i<=40;i++){
    	print("#",0,i);
	}
	for(i=0;i<=40;i++){
    	print("#",100,i);
	}
    for(i=0;i<=100;i++){
    	print("#",i,41);
	}
	
    for(i=1;i<60;i++){
		print("=",i, 30);  
	}
    for(i=60;i<100;i++){
		print("=",i, 35);  
	}
    for(i=60;i<100;i++){
		print("=",i, 15);  
	}
    
    for(i=31;i<=40;i++){
		print("|",30, i);  
	}
    for(i=1;i<=40;i++){
		print("|",60, i);  
	}
	
/*     for(i=3;i<55;i++){
    	print("墙",i,3);
	}
	for(i=3;i<=27;i++){
    	print("墙",3,i);
	}
	for(i=3;i<=27;i++){
    	print("墙",55,i);
	}
    for(i=3;i<=55;i++){
    	print("墙",i,27);
	} */
    setcolor("red");
    print("铁血战士", 10, 5);
    setcolor("red");
    print("80/80", 10, 6);
    setcolor("yellow");
    print("灵力值：3/3", 10, 7);
    setcolor("red");
    print("力量: 3", 10, 8);
    setcolor("green");
    print("敏捷：2", 10, 9);
    setcolor("white");
    print("脆弱：2", 10, 10);
    print("虚弱：3", 10, 11);
    print("易伤：3", 10, 12);
    print("缠绕：1", 10, 13);
    //print("宝箱", 10, 20);
    print("怪物名字", 30, 5);
    setcolor("red");
    print("41/41", 30, 6);
    setcolor("blue");
    print("意图：攻击11点伤害", 30, 7);
    setcolor("red");
    print("力量: 3", 30, 8);
    setcolor("green");
    print("敏捷：2", 30, 9);
    setcolor("white");
    print("脆弱：2", 30, 10);
    print("虚弱：3", 30, 11);
    print("易伤：3", 30, 12);
    setcolor("white");
    print("1. 打击  6  1",3,31);
    setcolor("white");
    print("2. 痛击",3,32);
    setcolor("red");
    print("8", 5, 32);
    setcolor("green");
    print("3.耸肩无视", 3, 33);
    setcolor("blue");
    print("4.硬撑", 3, 34);
    setcolor("purple");
    print("5.黑暗之拥", 3, 35);
    setcolor("red");
    print("6.死亡收割", 3, 36);
    setcolor("yellow");
    print("2", 31, 31);
    setcolor("red");
    print("死亡收割",34,31);
    setcolor("white");
    print("对所有敌人造成4点伤害", 31, 33);
    print("未被格挡的伤害将会回复你的生", 31, 34);
    print("命值", 31, 35);
    print("血量：100/100",67,36);
    print("灵根：废灵根",67,37);
    print("灵力值：4",67,38);
    getch();
    return 0;
}