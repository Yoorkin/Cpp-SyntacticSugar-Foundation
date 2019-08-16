#ifndef CPP_DELEGATE
#define CPP_DELEGATE
#pragma once
#include <vector>

namespace Delegate {
    class Args {};

    template<typename Return, typename ...ParamList>
    class delegate {
    public:
        // return type: Return
        // CallBackFunc is a static function 
        // params is parameter list
        typedef Return(*CallBackFunc)(ParamList ...params);

        delegate(CallBackFunc p) : p_func(p) {};

        Return call(ParamList ...params) {
            return (*p_func)(params...);
        };

    private:
        CallBackFunc p_func = nullptr;
    };

    template<typename Return, typename ...ParamList>
    delegate<Return, ParamList...>* make_delegate(Return(function)(ParamList...params)) {
        return new delegate<Return, ParamList...>(function);
    };

    template<typename Return, typename ...ParamList>
    class event{
        std::vector<delegate<Return, ParamList...>*> delegates;
    public:
        void operator+=(delegate<Return, ParamList...>* x){
            delegates.push_back(x);
        };

        Return raise(ParamList...list){
            Return result;
            for(delegate<Return, ParamList...>* p : delegates)
                result = p->call(list...);
            return result;
        };

         Return operator()(ParamList ...list) {
            return raise(list...);
        };
    };
}

#endif 
