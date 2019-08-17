#include <iostream>
#include "delegate.hpp"
#include "observer.hpp"
#include "binding.hpp"

using namespace std;
using namespace SSF;

void ID_change(int value)
{
    cout<<"myapp's ID has changed to "<<value<<endl;
}

class MyApp
{
public:
    Observer<int> ID = make_observer(new int(8848),make_delegate(ID_change));
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

    auto id = make_observer(new int);
    Binding<int> id_binding = make_binding(&id,&myapp->ID);
    myapp->ID=9099;
    cout<<"binding id is "<<id<<endl;
    cout<<myapp->ID<<endl;
}