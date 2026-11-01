#include "RayForge.h"

class ExampleApplication : public rf::Application
{
public:
    ExampleApplication() = default;
};

int main() {
    rf::ApplicationConfig config;
    config.windowWidth = 800;
    config.windowHeight = 600;
    config.windowTitle = "RayForge";
    config.targetFPS = 60;

    return rf::RunApplication<ExampleApplication>(config);
}