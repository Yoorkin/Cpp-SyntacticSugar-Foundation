# c++语法糖基础类库
目前已有的类和功能

|File|Description|
|---|---|
|delegate.hpp|类C#委托，实现任意目标函数回调|
|observer.hpp|数据观察者，当观察的对象被获取或改变时利用delegate回调
|binding.hpp|以observer为基础，绑定两个observer对象以实现数据同步
## delegate用法
```
    //按钮button内部添加点击事件
    event<void,int,int> click;
```

```$xslt
    //触发事件(不传递附加参数）
    click(100,99);
```

```$xslt
    //在类MyApp的实例myapp中订阅事件
    void btn_click(int x,int y){
        cout<<"按钮button被按下！"<<endl;
    }
    ...
    button.click+=make_delegate(&this,&MyApp::btn_click);
```

### 详细见[ main.cpp](main.cpp)