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
    SetConsoleOutputCP(CP_UTF8);
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
	
    for(i=3;i<55;i++){
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
	}

    print("我", 10, 10);
    print("宝箱", 10, 20);

    setcolor(6);
    print("一张传说卡",3,31);
    setcolor(7);
    setcolor(13);
    print("一张史诗卡",3,32);
    setcolor(7);
    print("我是卡牌描述",32,31);
    print("血量：100/100",67,36);
    print("灵根：废灵根",67,37);
    print("灵力值：4",67,38);
    getch();
    return 0;
}