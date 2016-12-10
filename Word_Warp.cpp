#include <iostream>
#include <string>
#include <sstream>
using namespace std;
string in,sub,WW;
int W;

// It's better to use printf("%.*s", length (last_index - start_index + 1), string_name.begin()+start_index);
int main()
{
    for (int i = 0 ; i < 10; i++)
    {
        getline(cin,WW);
        getline(cin,in);
        stringstream ss;
        ss.str(WW);
        ss>>W;
        int l = 0,r,rr;
        int len = in.size();
        while(1)
        {
            r = l+W-1;
            rr = r;
            if (r>=len-1)
            {
                sub = in.substr(l,len-l);
                cout<<sub<<endl;
                break;
            }
            else
            {
                while(in[r]!=' '&&r!=l)
                    r--;
                if (r!=l)
                {
                    if (in[rr+1]==' ')
                    {
                        sub = in.substr(l,W);
                        cout<<sub<<endl;
                        l = l+W+1;
                    }
                    else
                    {
                        sub = in.substr(l,r-l+1);
                        cout<<sub<<endl;
                        l = r+1;
                    }
                }
                else
                {
                    if (in[rr+1]==' ')
                    {
                        sub = in.substr(l,W+1);
                        cout<<sub<<endl;
                        l = l+W+1;
                    }
                    else
                    {
                        sub = in.substr(l,W);
                        cout<<sub<<endl;
                        l = l+W;
                    }
                }
            }

        }
        cout<<"=====";
        cout<<endl;
    }
}
