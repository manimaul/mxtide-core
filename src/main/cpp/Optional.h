#pragma once

#include <functional>

namespace mdr {

    template <typename T>
    class Optional {
    private:
        bool hasValue;
        T value;

    public:
        Optional() : hasValue(false), value() {}
        explicit Optional(T val) : hasValue(true), value(val) {}

        template<class F>
        void let(F &&lambda) {
            if (hasValue) {
                lambda(value);
            }
        }

        template<typename F, typename FE>
        void ifLetElse(F &&lambda, FE &&lambdaElse) {
            if (hasValue) {
                lambda(value);
            } else {
                lambdaElse();
            }
        }
    };

}
