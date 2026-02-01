#pragma once

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include <functional>

#include "event/event.h"

struct WindowProperties {
    std::string Title;
    uint32_t Width = 700;
    uint32_t Height = 800;
    int32_t PosX = 0;
    int32_t PosY = 0;
};

class Window
{
public:
    using EventCallbackFn = std::function<void(Event&)>;

    Window(const WindowProperties& props = WindowProperties());
    ~Window();

    void OnUpdate();

    void Clear();

    inline void SetEventCallback(const EventCallbackFn& callback) { m_Data.EventCallback = callback; }

    uint32_t GetWidth() const { return m_Data.Width; }
    uint32_t GetHeight() const { return m_Data.Height; }

    int32_t GetPosX() const { return m_Data.PosX; }
    int32_t GetPosY() const { return m_Data.PosY; }

    GLFWwindow* GetWindow() { return m_Window; }

private:

    void Init(const WindowProperties& props);
    void Shutdown();

private:
    GLFWwindow* m_Window;
    
    struct WindowData {
        std::string Title;
        uint32_t Width, Height;
        int PosX, PosY;
        EventCallbackFn EventCallback;
    };

    WindowData m_Data;
};
