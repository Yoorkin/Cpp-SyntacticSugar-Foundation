#include <iostream>
#include <vector>
#include "delegate.hpp"
using namespace std;
using namespace Delegate;
class MouseArgs:public Args{
public:
    bool is_lbtn_down;
    bool is_rbtn_down;
};

class Window{
public:
    event click_event;
    string title="window";
    void click(){
        MouseArgs args;
        args.is_lbtn_down=false;
        args.is_rbtn_down=true;
        click_event.raise(this,&args);
    };
};

class myclass{
public:
    int index=0;
    myclass(int v):index(v){};
    friend delegate<myclass,myclass>;
    friend int main();
private:
    void button_click(void* sender,Args* args);
};

void myclass::button_click(void* sender,Args* args){
    auto s=(Window*)sender;
    auto a=(MouseArgs*)args;
    cout<<"click"<<index<<endl;
    cout<<s->title<<endl;
    cout<<a->is_rbtn_down<<endl;
};


int main() {
    myclass a(5),b(8);
    Window window;
    window.click_event+=make_delegate(&a,&myclass::button_click);
    window.click_event+=make_delegate(&b,&myclass::button_click);
    window.click();
}