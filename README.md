# c++实现的类C#回调机制

## 用法
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