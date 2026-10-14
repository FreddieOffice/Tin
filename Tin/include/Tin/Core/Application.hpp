#pragma once

#include <memory>

namespace Tin {
    class Application {
    public:
        Application();
        virtual ~Application();

        virtual void Run() = 0;
        // Processes all pending events
        void PollEvents() const;

        // Returns time passed since initialization in seconds
        [[nodiscard]] double GetTime() const;
    };

    // To be defined in client
    extern std::unique_ptr<Tin::Application> CreateApplication();
}
