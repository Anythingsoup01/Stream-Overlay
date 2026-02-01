#include "imgui/imgui_layer.h"
#include "window/window.h"

#include <imgui.h>
#include <iostream>

#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"

ImGuiLayer::ImGuiLayer(Window* win) {
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;

    // Setup scaling
    ImGuiStyle& style = ImGui::GetStyle();

    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(win->GetWindow(), true);
    ImGui_ImplOpenGL3_Init("#version 430");
}

void ImGuiLayer::OnUpdate() {
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
}

void ImGuiLayer::OnRender(Window* win) {


    OnUpdate();
    /* Render here */

    ImGui::SetNextWindowSize({(float)win->GetWidth(), (float)win->GetHeight()});
    ImGui::SetNextWindowPos({ 0, 0});

    ImGui::PushStyleColor(ImGuiCol_WindowBg, {0, 0, 0, 0.25});
    {
        ImGuiWindowFlags flags = 
            ImGuiWindowFlags_NoResize
            | ImGuiWindowFlags_NoMove
            | ImGuiWindowFlags_NoDecoration
            | ImGuiWindowFlags_NoInputs;
        ImGui::Begin("##CHAT_WINDOW", nullptr, flags);

        ImGui::End();
    }
    ImGui::PopStyleColor(); 

    ImGui::Render();
    win->Clear();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}
