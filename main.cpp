#include <iostream>
//#include "lib/Kinw.h"
#include "delegate.hpp"
//using namespace Razor;
using namespace std;
using namespace Delegate;
class Button
{
public:
    event<int, bool, bool, int, int> click;
    event<void, int> active;
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
        cout << "button state:" << state;
    }
};


int main() {
    Button btn;
    MyApp* myapp = new MyApp();
    btn.click += make_delegate<int>(myapp, &MyApp::Btn_click);
    btn.active += make_delegate<void>(myapp, &MyApp::Btn_active);
    btn.click.raise(true,false,100,99);//委托多播暂时不支持获得返回值

    //btn.active->call(8);
    //    IFactory* factory = CreateFactory();
    //    IPosition* pos= factory->Bound(100,100,500,500);
    //    IForm* form=factory->CreateFrom(pos,"lalala");
    //    form->Show();
    //    Pause();
    //    factory->Dispose();
}
