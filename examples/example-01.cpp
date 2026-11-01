#include "RayForge.h"

#include <iostream>
#include <array>

#define RLIGHTS_IMPLEMENTATION
#include "rlights.h"

class ExampleApplication : public rf::Application
{
public:
    ExampleApplication() = default;

protected:
    bool Init_Internal(const rf::ApplicationConfig& info) override
    {
        // Define the camera to look into our 3d world
        _camera = { 0 };
        _camera.position = (Vector3){ 10.0f, 10.0f, 10.0f }; // Camera position
        _camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };      // Camera looking at point
        _camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };          // Camera up vector (rotation towards target)
        _camera.fovy = 45.0f;                                // Camera field-of-view Y
        _camera.projection = CAMERA_PERSPECTIVE;             // Camera projection type

        // Load basic lighting shader
        _shader = LoadShader(TextFormat("%s/shaders/lighting.vs", RF_ASSETS_DIR),
                             TextFormat("%s/shaders/lighting.fs", RF_ASSETS_DIR));
                             // Get some required shader locations
        _shader.locs[SHADER_LOC_VECTOR_VIEW] = GetShaderLocation(_shader, "viewPos");
        // NOTE: "matModel" location name is automatically assigned on shader loading,
        // no need to get the location again if using that uniform name
        //_shader.locs[SHADER_LOC_MATRIX_MODEL] = GetShaderLocation(_shader, "matModel");

        // Ambient light level (some basic lighting)
        int ambientLoc = GetShaderLocation(_shader, "ambient");
        SetShaderValue(_shader, ambientLoc, (float[4]){ 0.1f, 0.1f, 0.1f, 1.0f }, SHADER_UNIFORM_VEC4);

        // Create lights
        _lights[0] = CreateLight(LIGHT_POINT, (Vector3){ -2, 2, -2 }, Vector3Zero(), YELLOW, _shader);
        _lights[1] = CreateLight(LIGHT_POINT, (Vector3){ 2, 2, 2 }, Vector3Zero(), RED, _shader);
        _lights[2] = CreateLight(LIGHT_POINT, (Vector3){ -2, 2, 2 }, Vector3Zero(), GREEN, _shader);
        _lights[3] = CreateLight(LIGHT_POINT, (Vector3){ 2, 2, -2 }, Vector3Zero(), BLUE, _shader);

        return true;
    }

    void Update(float deltaTime) override
    {
        // UpdateCamera(&_camera, CAMERA_FREE);
        UpdateCamera(&_camera, CAMERA_ORBITAL);
    }

    void BeginDraw() override
    {
        rf::Application::BeginDraw();
        BeginMode3D(_camera);
    }

    void Render() override
    {
        SetShaderValue(_shader, _shader.locs[SHADER_LOC_VECTOR_VIEW], &_camera.position, SHADER_UNIFORM_VEC3);

        BeginShaderMode(_shader);
        {
            Vector3 cubePosition = { 0.0f, 0.0f, 0.0f };
            DrawCube(cubePosition, 2.0f, 2.0f, 2.0f, WHITE);
        }
        EndShaderMode();
        DrawGrid(10, 1.0f);
    }

    void EndDraw() override
    {
        rf::Application::EndDraw();
        EndMode3D();
    }

private:
    Camera3D _camera;
    Shader _shader;
    Model _model;
    std::array<Light, 4> _lights;
};

int main() {
    rf::ApplicationConfig config;
    config.windowWidth = 1024;
    config.windowHeight = 768;
    config.windowTitle = "RayForge";
    config.targetFPS = 60;

    return rf::RunApplication<ExampleApplication>(config);
}