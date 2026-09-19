#ifndef APP_HPP
#define APP_HPP

class App {
public:
    static App* GetInstance();

    // main
    int Run();
private:
    App() = default; 
    ~App() = default;

    App(const App&) = delete;
    App& operator=(const App&) = delete;
};

#endif