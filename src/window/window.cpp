#include <sopch.h>
#include "window/window.h"

#include <glad/glad.h>

#include "event/application_event.h"

#include "core/managed_types.h"

// Setting GLFW Functions and Variables
static bool s_GLFWInitialized = false;

static void GLFWErrorCallback(int error, const char* description) {
    printf("GLFW Error (%d) : %s", error, description);
}

Window::Window(const WindowProperties& props)
{
    Init(props);
}

Window::~Window()
{
    Shutdown();
}

void Window::OnUpdate()
{
    glfwPollEvents();
    glfwSwapBuffers(m_Window);
}

void Window::Clear()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Window::Init(const WindowProperties& props)
{
    // Setting Data props to equal inputted props
    m_Data.Title = props.Title;
    m_Data.Width = props.Width;
    m_Data.Height = props.Height;
    m_Data.PosX = props.PosX;
    m_Data.PosY = props.PosY;

    #ifdef SO_PLATFORM_LINUX
    glfwInitHint(GLFW_PLATFORM, GLFW_PLATFORM_X11);
    #endif

    // Initializing GLFW
    if (!s_GLFWInitialized) {
        int success = glfwInit();
        glfwSetErrorCallback(GLFWErrorCallback);
        assert(success);
    }

    glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER, GLFW_TRUE);

    m_Window = glfwCreateWindow((int)props.Width, (int)props.Height, m_Data.Title.c_str(), nullptr, nullptr);


    glfwMakeContextCurrent(m_Window);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        glfwTerminate();
        assert(false);
    }
    
    glfwSetWindowUserPointer(m_Window, &m_Data);

    // Setting GLFW Callbacks-------------------------------------------------------------------

    // Close Callback
    glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window)
    {
        WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
        WindowCloseEvent event;
        data.EventCallback(event);
    });

    // Resize Callback
    glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height)
    {
        WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
        data.Width = width;
        data.Height = height;

        WindowResizeEvent event(width, height);

        data.EventCallback(event);
    });

    glfwSetWindowPosCallback(m_Window, [](GLFWwindow* window, int posX, int posY)
    {
        WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
        data.PosX = posX;
        data.PosY = posY;


        WindowMoveEvent event(posX, posY);
        data.EventCallback(event);
    });

    glfwSetWindowPos(m_Window, props.PosX, props.PosY);
    glfwSetWindowAttrib(m_Window, GLFW_FLOATING, GLFW_TRUE);
}

void Window::Shutdown()
{
    glfwDestroyWindow(m_Window);
}
