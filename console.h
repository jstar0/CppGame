#include<vector>
using namespace std;
void setscreensize(int cols,int lines);
void setcolor(int fore=7,int back=0);
void setcolor(string fore_s,string back_s);
void setposition(int x=1,int y=1);
void setcursor(bool show=true);
void print(string s,int x=0,int y=0);
void print(vector<string> s,int x=0,int y=0,int l=-1,int r=-1);
void clear();
void clear(int X1,int Y1,int X2,int Y2);
