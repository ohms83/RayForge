#include "Application.h"
#include "raylib.h"

USING_RF;

RF_DEFINE_LOG(Application);

bool Application::Init(const ApplicationConfig &info)
{
    InitWindow(info.windowWidth, info.windowHeight, info.windowTitle.c_str());
    SetTargetFPS(info.targetFPS);
    if (info.enableFullscreen) {
        ToggleFullscreen();
    }
    if (!info.showCursor) {
        DisableCursor();
    }
    return Init_Internal(info);
}

int Application::BeginMainLoop()
{
    m_isRunning = true;
    while (m_isRunning && !WindowShouldClose())
    {
        float deltaTime = GetFrameTime();
        Update(deltaTime);

        BeginDraw();
        Render();
        EndDraw();
    }
    return 0;
}

void Application::RequestQuit()
{
    m_isRunning = false;
}

void Application::Update(float deltaTime)
{
}

void Application::BeginDraw()
{
    BeginDrawing();
    ClearBackground(GRAY);
}

void Application::EndDraw()
{
    EndDrawing();
}

void Application::Render()
{
}
