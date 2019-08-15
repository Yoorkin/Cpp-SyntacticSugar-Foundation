//#ifndef CPP_DELEGATE
//#define CPP_DELEGATE
#pragma once
#include <vector>

namespace Delegate {
    class Args {};

    template<typename Return, typename... ParamList>
    class delegateBase {
    public:
        virtual Return call(ParamList...params) {  return NULL;  };
    };
    template<typename...ParamList>
    class delegateBase<void,ParamList...> {
    public:
        virtual void call(ParamList...params) { };
    };

    template<typename Return, typename Object, typename... ParamList>
    class delegate :public delegateBase<Return, ParamList...> {
    public:
        typedef Return(Object::* CallBackFunc)(ParamList...params);
        delegate(Object* obj, CallBackFunc p) : p_object(obj), p_func(p) {};
        Return call(ParamList...params)override {
            return (p_object->*p_func)(params...);
        }
    private:
        Object* p_object = nullptr;
        CallBackFunc p_func = nullptr;
    };

    template<typename Return, typename Object, typename...ParamList>
    delegate<Return, Object, ParamList...>* make_delegate(Object* obj, Return(Object::* function)(ParamList...params)) {
        return new delegate<Return, Object, ParamList...>(obj, function);
    };

    template<typename Return,typename...ParamList>
    class event{
        std::vector<delegateBase<Return,ParamList...>*> delegates;
    public:
        void operator+=(delegateBase<Return,ParamList...>* x){
            delegates.push_back(x);
        };
        void raise(ParamList...list){
            for(delegateBase<Return,ParamList...>* p:delegates)
                p->call(list...);
        };
    };
}

//#endif 