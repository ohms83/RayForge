#include <iostream>
#include "RayForge.h"

class MyApplication : public rf::Application
{
public:
    MyApplication() = default;
};

int main() {
    rf::ApplicationConfig config;
    config.windowWidth = 800;
    config.windowHeight = 600;
    config.windowTitle = "RayForge";
    config.targetFPS = 60;

    return rf::RunApplication<MyApplication>(config);
}