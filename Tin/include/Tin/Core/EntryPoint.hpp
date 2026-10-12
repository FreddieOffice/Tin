// Entry point must be included only once
#ifdef TIN_ENTRY_POINT
    #error Entry point already included!
#endif

#define TIN_ENTRY_POINT

#include "Tin/Core/Application.hpp"

// Entry point
int main() {
    std::unique_ptr<Tin::Application> app = Tin::CreateApplication();
    app->Run();

    return 0;
}
