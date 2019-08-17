#ifndef SSF_DELEGATE
#define SSF_DELEGATE
#pragma once
#include <vector>

namespace SSF {

    template<typename Return, typename ...ParamList>
    class Delegate {
    public:
        // CallBackFunc is a static function 
        // params is parameter list
        typedef Return (*CallbackFunc) (ParamList ...params);

        Delegate(CallbackFunc p) : func(p) {};

        Delegate() = default;

        virtual Return invoke(ParamList ...params) {
            return (*func)(params...);
        };

    private:
        CallbackFunc func = nullptr;
    };

    template <typename Return, typename Object, typename ...ParamList>
    class MemberDelegate : public Delegate<Return, ParamList...> {
    public:
        //CallbackFunc is now a member function in Object
        typedef Return(Object::* CallbackFunc)(ParamList ...params);

        MemberDelegate(Object *obj, CallbackFunc callback) : object(obj), func(callback) {};

        Return invoke(ParamList ...params) override {
            return (object->*func)(params...);
        }
    private:
        Object *object = nullptr;
        CallbackFunc func = nullptr;
    };

    template<typename Return, typename ...ParamList>
    Delegate<Return, ParamList...>* make_delegate(Return(function)(ParamList...params)) {
        return new Delegate<Return, ParamList...>(function);
    };

    template <typename Return, typename Object, typename ...ParamList>
    Delegate<Return, ParamList...>* make_delegate(Object* obj, Return(Object::* function)(ParamList...params)) {
        return new MemberDelegate<Return, Object, ParamList...>(obj, function);
    };

    template<typename Return, typename ...ParamList>
    class event{
        std::vector<Delegate<Return, ParamList...>*> delegates;
    public:
        void operator+=(Delegate<Return, ParamList...>* x){
            delegates.push_back(x);
        };

        void operator+=(Return(*function)(ParamList...)){
            delegates.push_back(make_delegate<Return,ParamList...>(function));
        }

        Return raise(ParamList ...list){
            Return result;
            for(Delegate<Return, ParamList...>* p : delegates)
                result = p->invoke(list...);
            return result;
        };

        Return operator()(ParamList ...list) {
            return raise(list...);
        };
    };

    template<typename ...ParamList>
    class event<void,ParamList...>{
        std::vector<Delegate<void, ParamList...>*> delegates;
    public:
        void operator+=(Delegate<void, ParamList...>* x){
            delegates.push_back(x);
        };

        void operator+=(void(*function)(ParamList...)){
            delegates.push_back(make_delegate<void,ParamList...>(function));
        }

        void raise(ParamList ...list){
            for(Delegate<void, ParamList...>* p : delegates)
                p->invoke(list...);
        };

        void operator()(ParamList ...list) {
            raise(list...);
        };
    };
}

#endif 
