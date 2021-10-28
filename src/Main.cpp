#include <iostream>

#include "Log.hpp"

int main(int argc, char** argv) {
    Texturia::Log::Init();
    TX_INFO("Initialized Logger");
    
    TX_WARN("Hello World");

    return 0;
}
