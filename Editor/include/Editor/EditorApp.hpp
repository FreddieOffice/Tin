#ifndef TINEDITOR_APP_HPP
#define TINEDITOR_APP_HPP

#include "Tin/Tin.hpp"

class EditorApp : public Tin::Application {
public:
    EditorApp();
    ~EditorApp();

    void Run() override;
};

#endif