#include<iostream>
#include"gamemap.h"
#include"console.h"
extern int roomPrintX,roomPrintY;
void print(Object object)
{
    setcolor(object.forecolor,object.backcolor);
    print(object.name,roomPrintX+object.x,roomPrintY+object.y);
}
void print(Room room)
{
    for (int i=0; i<room.object_s; i++)
    {
        print(room.object[i]);
    }
}