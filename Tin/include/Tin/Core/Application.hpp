#ifndef TIN_CORE_APPLICATION_HPP
#define TIN_CORE_APPLICATION_HPP

#include <memory>

namespace Tin {
    class Application {
    public:
        Application();
        virtual ~Application();

        virtual void Run();
        // Processes all pending events
        void PollEvents() const;

        // Returns time passed since initialization in seconds
        float GetTime() const;
    };

    // To be defined in client
    extern std::unique_ptr<Tin::Application> CreateApplication();
}

#endif