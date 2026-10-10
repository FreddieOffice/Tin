// Entry point must be included only once
#ifdef TIN_CORE_ENTRY_POINT_HPP
    #error Entry point already included!
#endif

#define TIN_CORE_ENTRY_POINT_HPP

#include "Tin/Core/Application.hpp"

// Entry point
int main() {
    std::unique_ptr<Tin::Application> app = Tin::CreateApplication();
    app->Run();

    return 0;
}
