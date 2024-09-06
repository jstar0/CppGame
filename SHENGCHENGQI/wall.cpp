#include<iostream>
#include<string>
using namespace std;
int main()
{
    int x=0,y=0,n=0;
    string s="";
    while(x!=-1 && y!=-1)
    {   
        cin>>x>>y;
        if (x!=-1 && y!=-1) 
        {
            n++;
            s+=",("+to_string(x)+","+to_string(y)+")";
        }
    }
    cout<<n<<s;
    return 0;
}

