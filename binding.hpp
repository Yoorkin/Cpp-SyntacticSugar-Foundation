#ifndef SSF_BINDING
#define SSF_BINDING
#pragma once
#include "observer.hpp"
namespace SSF{
    template<typename T>
    class Binding{
        Observer<T>* ptr_member1;
        Observer<T>* ptr_member2;

        bool ignore_change = false;

        void member1_change(T t){
            if(!ignore_change){
                ignore_change = true;
                ptr_member2->operator=(t);
                ignore_change = false;
            }
        }
        void member2_change(T t){
            if(!ignore_change){
                ignore_change = true;
                ptr_member1->operator=(t);
                ignore_change = false;
            }
        }

    public:
        friend MemberDelegate<void,T>;
        Binding(Observer<T>* member1,Observer<T>* member2):ptr_member1(member1),ptr_member2(member2){
            ptr_member1->change+=make_delegate(this,&Binding::member1_change);
            ptr_member2->change+=make_delegate(this,&Binding::member2_change);
        }
    };

    template<typename T>
    Binding<T> make_binding(Observer<T>* x,Observer<T>* y){
        return Binding<T>(x,y);
    };
}


#endif