#include <iostream>
//#include "lib/Kinw.h"
#include "delegate.hpp"
//using namespace Razor;
using namespace std;
using namespace Delegate;
class Button
{
public:
    //event<int, bool, bool, int, int> click;
    //event<void, int> active;
};

class MyApp
{
public:
    int Btn_click(bool LButton, bool RButton, int x, int y)
    {
        cout << LButton << endl;
        cout << RButton << endl;
        cout << x << endl;
        cout << y << endl;
        return 7;
    }

    void Btn_active(int state)
    {
        cout << "function button state:" << state << endl;
    }

    static void Static_Btn_active(int state)
    {
        cout << "static function button state:" << state << endl;
    }
};

void global_active(int state)
{
    cout << "global function button state:" << state << endl;
}

int main() {
    MyApp *myapp = new MyApp();

    event<void, int> active;
    active += global_active;
    active += &MyApp::Static_Btn_active;
    active += make_delegate(myapp, &MyApp::Btn_active);

    active(6);
}