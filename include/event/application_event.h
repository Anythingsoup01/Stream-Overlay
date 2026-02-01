#pragma once

#include "event.h"

// Window Close Event
class WindowCloseEvent : public Event {
public:
    WindowCloseEvent() {}
    EVENT_CLASS_TYPE(WindowClose)
    EVENT_CLASS_CATEGORY(CategoryApplicationEvent)
};

// Window Resize Event
class WindowResizeEvent : public Event {
public:
    WindowResizeEvent(unsigned int width, unsigned int height)
    : m_Width(width), m_Height(height) {}

    inline unsigned int GetWidth() const { return m_Width; }
    inline unsigned int GetHeight() const { return m_Height; }

    std::string ToString() const override {
        std::stringstream ss;
        ss << "Window Resize Event: " << m_Width << ", " << m_Height;
        return ss.str();
    }

    EVENT_CLASS_TYPE(WindowResize)
    EVENT_CLASS_CATEGORY(CategoryApplicationEvent)
private:
    unsigned int m_Width, m_Height;
};

// Window Moved Event
class WindowMoveEvent : public Event {
public:
    WindowMoveEvent(int posX, int posY)
        : m_PosX(posX), m_PosY(posY) {}

    inline unsigned int GetPosX() const { return m_PosX; }
    inline unsigned int GetPosY() const { return m_PosY; }

    std::string ToString() const override {
        std::stringstream ss;
        ss << "Window Move Event: " << m_PosX << ", " << m_PosY;
        return ss.str();
    }

    EVENT_CLASS_TYPE(WindowMove)
    EVENT_CLASS_CATEGORY(CategoryApplicationEvent)
private:
    int m_PosX, m_PosY;
};

// Window Maximized
class WindowMaximizedEvent : public Event {
public:
    WindowMaximizedEvent() {}
    EVENT_CLASS_TYPE(WindowMaximize)
    EVENT_CLASS_CATEGORY(CategoryApplicationEvent)
};

