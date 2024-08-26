class Object{
public:
    std::string name="",forecolor="white",backcolor="black";
    int x,y;
    //virtual void run();
    friend void print(Object object);
};
class Room{
public:
    int ID,UP_ID,DOWN_ID,RIGHT_ID,LEFT_ID,object_s;
    bool store,enemy;
    std::string name="";
    Object object[10];
    friend void print(Room room);
};
