#include<iostream>
using namespace std;
int main()
{
    int T=0;
    cin>>T;
    for (int i=1; i<=T; i++)
    {
        int x1,y1,x2,y2;
        cin>>x1>>y1>>x2>>y2;
        for (int i=x1; i<=x2; i++)
        {
            for (int j=y1; j<=y2; j++)
            {
                cout<<2*i<<' '<<j<<' ';
            }
        }
    }
    return 0;
}