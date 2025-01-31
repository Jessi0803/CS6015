//
//  run.cpp
//  msdscript
//
//  Created by Oliver Wang on 1/30/25.
//

extern "C" {
    #include "run.hpp"
};

#define CATCH_CONFIG_RUNNER
#include "../Project Phase 1/catch.h"
bool run_tests() {
    const char *argv[] = { "test" };
    return (Catch::Session().run(1, argv) == 0);
}
