#ifndef MAIN_H
#define MAIN_H

#include <unidokkan/hook.h>

extern "C" {
    int unidokkan_init(ApplyHooksFn apply_hooks_fn);
}

#endif //MAIN_H
