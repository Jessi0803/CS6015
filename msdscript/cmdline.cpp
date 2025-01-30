//
//  cmdline.cpp
//  Project Phase 1
//
//  Created by Jessi on 1/13/25.
//

#include <iostream>
#include <cstdlib>
#include "cmdline.h"
#include <catch2/catch_all.hpp>

void use_arguments(int argc, char** argv) {
    bool saw_test = false;

    for(int i = 1; i < argc; i++) {
        if(argv[i] == std::string("--help")) {
            std::cout << "Input argument description:\n";
            std::cout << "--help : Show help information\n";
            std::cout << "--test : Run tests\n";
            exit(0);
        }
        else if(argv[i] == std::string("--test")) {
            if(saw_test) {
                std::cerr << "Error: --test can only be used once\n";
                exit(1);
            }
            saw_test = true;

            // Run tests
            int result = Catch::Session().run();
            if(result != 0) {
                exit(1);
            }
        }
        else {
            std::cerr << "Error: Unrecognized argument " << argv[i] << "\n";
            exit(1);
        }
    }
}



//使用 for 迴圈逐一檢查傳入的參數（argv）。
//如果是 --help，則顯示幫助訊息，並立即結束程式（exit(0)）。
//如果是 --test，執行測試，並檢查是否重複使用該參數。如果測試失敗，程式將結束並返回錯誤代碼（exit(1)）。
//如果輸入了未定義的參數，則顯示錯誤訊息並退出程式。
