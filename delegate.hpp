#ifndef CPP_DELEGATE
#define CPP_DELEGATE
#pragma once
#include <vector>

namespace Delegate {
    class Args {};

    template<typename Return, typename ...ParamList>
    class Delegate {
    public:
        // CallBackFunc is a static function 
        // params is parameter list
        typedef Return (*CallbackFunc) (ParamList ...params);

        Delegate(CallbackFunc p) : func(p) {};

        Delegate() = default;

        virtual Return call(ParamList ...params) {
            return (*func)(params...);
        };

    private:
        CallbackFunc func = nullptr;
    };

    template <typename Return, typename Object, typename ...ParamList>
    class MDelegate : public Delegate<Return, ParamList...> {
    public:
        //CallbackFunc is now a member function in Object
        typedef Return(Object::* CallbackFunc)(ParamList ...params);

        MDelegate(Object *obj, CallbackFunc callback) : object(obj), func(callback) {};

        Return call(ParamList ...params) override {
            return (object->*func)(params...);
        }
    private:
        Object *object = nullptr;
        CallbackFunc func = nullptr;
    };

    template<typename Return, typename ...ParamList>
    Delegate<Return, ParamList...>* make_Delegate(Return(function)(ParamList...params)) {
        return new Delegate<Return, ParamList...>(function);
    };

    template <typename Return, typename Object, typename ...ParamList>
    Delegate<Return, ParamList...>* make_Delegate(Object* obj, Return(Object::* function)(ParamList...params)) {
        return new MDelegate<Return, Object, ParamList...>(obj, function);
    };

    template<typename Return, typename ...ParamList>
    class event{
        std::vector<Delegate<Return, ParamList...>*> delegates;
    public:
        void operator+=(Delegate<Return, ParamList...>* x){
            delegates.push_back(x);
        };

        Return raise(ParamList ...list){
            Return result;
            for(Delegate<Return, ParamList...>* p : delegates)
                result = p->call(list...);
            return result;
        };

         Return operator()(ParamList ...list) {
            return raise(list...);
        };
    };
}

#endif 
