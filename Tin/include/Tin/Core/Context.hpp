#ifndef TIN_CORE_CONTEXT_HPP
#define TIN_CORE_CONTEXT_HPP

namespace Tin {
    class Context {
    public:
        // Returns context instance
        static Context& GetInstance();

        // Initializes the context
        void Init();
        // Destroys the context
        void Destroy();
        // Processes all pending events
        void PollEvents() const;

        // Returns time since initialization
        double GetTime() const;
    private:
        Context() = default;
        ~Context() = default;

        // Remove other constructors and copy assignment operators
        Context(const Context&) = delete;
        Context& operator=(const Context&) = delete;

        bool m_isInitialized;
    };
}

#endif