#include "imgui/imgui_layer.h"
#include "window/window.h"

#include <imgui.h>

#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"

#include "core/managed_types.h"

static ChatMessageBuffer buffers[100];

ImGuiLayer::ImGuiLayer(Window* win) {
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;

    // Setup scaling
    ImGuiStyle& style = ImGui::GetStyle();

    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(win->GetWindow(), true);
    ImGui_ImplOpenGL3_Init("#version 430");


    for (auto& buf : buffers) {
        buf.Allocate(32, 512);
        buf.Reset("EXAMPLEUSER", "Example Message");
    }
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
        {
            ImGui::BeginChild("LogRegion", ImVec2(0, 0), 0, flags);
            // ... Render your text here ...
            for (auto& buf : buffers) {
                ImGui::TextWrapped("%s: %s", buf.username(), buf.message());
            }

            // Force scroll to bottom if new content is added
            if (ImGui::GetScrollY() >= ImGui::GetScrollMaxY())
                ImGui::SetScrollHereY(1.0f); 

            ImGui::EndChild();

        }
        ImGui::End();
    }
    ImGui::PopStyleColor(); 

    ImGui::Render();
    win->Clear();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}
