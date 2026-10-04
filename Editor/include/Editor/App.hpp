#ifndef APP_HPP
#define APP_HPP

class App {
public:
    App();
    
    // Main
    int Run();
private:
    App(const App&) = delete;
    App& operator=(const App&) = delete;
};

#endif