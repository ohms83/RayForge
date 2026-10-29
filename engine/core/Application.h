#pragma once

#include "RFDefine.h"
#include "debug/Logging.h"

#include <string>

RF_DECLARE_LOG_EXTERN(Application);

RF_NAMESPACE
{
    struct RF_API ApplicationConfig
    {
        int windowWidth = 800;
        int windowHeight = 600;
        std::string windowTitle = "RayForge";
        int targetFPS = 60;
    };

    class RF_API Application
    {
    public:
        Application() = default;
        virtual ~Application() = default;

        bool Init(const ApplicationConfig& info);
        int BeginMainLoop();
        void RequestQuit();

    protected:
        virtual void Update(float deltaTime);
        virtual void BeginDraw();
        virtual void EndDraw();
        virtual void Render();

    private:
        bool m_isRunning = false;
    };
    

    template<typename T>
    requires std::derived_from<T, Application>
    int RunApplication(const ApplicationConfig& initInfo)
    {
        T application = T();
        if (!application.Init(initInfo)) {
            RF_LOG_ERROR(LogApplication, "Failed to initialize application!");
            return -1;
        }
        return application.BeginMainLoop();
    }
}