
#include "window/window.h"
#include "imgui/imgui_layer.h"
#include "event/application_event.h"

#include "window/serializer.h"

#include <imgui.h>


bool OnWindowMoveEvent(WindowMoveEvent& e) {
    return false;
}

void OnEvent(Event& e) {
    EventDispatcher dispatcher(e);

    dispatcher.Dispatch<WindowMoveEvent>(BIND_EVENT_FN(OnWindowMoveEvent));
}

int main(void)
{
    SerializedWindowData data = WindowSerializer::Deserialize();

    WindowProperties props = WindowProperties();

    if (!data.Title.empty())
    {
        props.Title = data.Title;
        props.Width = data.Width;
        props.Height = data.Height;
        props.PosX = data.PosX;
        props.PosY = data.PosY;
    }

    Window win = Window(props);
    win.SetEventCallback(BIND_EVENT_FN(OnEvent));

    ImGuiLayer gui = ImGuiLayer(&win);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(win.GetWindow()))
    {
        win.OnUpdate();

        gui.OnRender(&win);
    }

    WindowSerializer::Serialize(SerializedWindowData({
        .Title=props.Title,
        .Width=win.GetWidth(),
        .Height=win.GetHeight(),
        .PosX=win.GetPosX(),
        .PosY=win.GetPosY(),
    }));


    return 0;
}

/*
 *
 *  int main(void)
 *
 *      Init_Window()
 *      Init_Gui()
 *      Init_Client()
 *
 *      while(running)
 *          Client_Update()
 *          Gui_Render()
 * */
