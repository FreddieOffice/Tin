#pragma once

#include "Tin/Tin.hpp"

class EditorApp : public Tin::Application {
public:
    EditorApp();
    ~EditorApp();

    void Run() override;
};
