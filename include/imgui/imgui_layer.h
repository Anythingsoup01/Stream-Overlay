#pragma once

class Window;

class ImGuiLayer {
public:
    ImGuiLayer(Window* win);

    void OnUpdate();
    void OnRender(Window* win);

private:
};
