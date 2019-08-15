#ifndef CPP_DELEGATE
#define CPP_DELEGATE
#include <vector>

namespace Delegate{
    class Args{};

    class delegateBase{
    public:
        virtual void call(void* sender,Args* args)=0;
    };

    template<typename O,typename T>
    class delegate:public delegateBase{
    public:
        typedef void (T::*CallBackFunc)(void*,Args*);
        delegate(O* obj,CallBackFunc p):p_object(obj),p_func(p){};
        void call(void* sender,Args* args)override{
            (p_object->*p_func)(sender,args);
        }
    private:
        O* p_object=nullptr;
        CallBackFunc p_func=nullptr;
    };

    template<typename O,typename T>
    delegate<O,T>* make_delegate(O* obj,void (T::*function)(void*,Args*)){
        return new delegate<O,T>(obj,function);
    };

    class event{
        std::vector<delegateBase*> delegates;
    public:
        void operator+=(delegateBase* x){
            delegates.push_back(x);
        };
        void raise(void* sender,Args* args){
            for(delegateBase* p:delegates)
                p->call(sender,args);
        };
    };
}

#endif