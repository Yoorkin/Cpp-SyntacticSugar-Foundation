#ifndef SSF_PROPERTY
#define SSF_PROPERTY
#pragma once
#include"delegate.hpp"
namespace SSF{
    template<typename T>
    class Observer{
        //where store the data
        T* ptr_value;
        //the get delegate will be triggered when property is rvalue
        //the set delegate will be triggered when property is lvalue
        Delegate<T>*   get = nullptr;
        Delegate<void,T>* set = nullptr;

    public:

        Observer(T* value):ptr_value(value){};

        Observer(T* value,Delegate<void,T>* delegate_change):ptr_value(value){
            change+=delegate_change;
        }

        Observer(T* value,Delegate<T>* delegate_get,Delegate<T,T>* delegate_set)
        :get(delegate_get),set(delegate_set),ptr_value(value){};


        //provide an interface for data binding
        event<void,T> change;

        operator T(){
            if(get!= nullptr)
                return get->invoke();
            else
                return *ptr_value;
        }

        void operator=(T t){
            if(set!=nullptr)
                set->invoke(t);
            else
                *ptr_value=t;
            change(t);
        }

        bool is_empty(){
            return ptr_value==nullptr;
        }

        T* get_ptr(){
            return ptr_value;
        }

        ~Observer(){
            delete get;
            delete set;
            delete ptr_value;
        }
    };

    template<typename T>
    Observer<T> make_observer(T* t){
        return Observer<T>(t);
    }

    template<typename T>
    Observer<T> make_observer(T* t,Delegate<void,T>* change){
        return Observer<T>(t,change);
    }

    template<typename T>
    Observer<T> make_observer(T* t,Delegate<T>* get,Delegate<T,T>* set){
        return Observer<T>(t,get,set);
    }
}

#endif