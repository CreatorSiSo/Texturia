#pragma once

#include <sstream>

#include "Event.hpp"

namespace Texturia {

class MouseMovedEvent : public Event {
  public:
    MouseMovedEvent(float x, float y)
      : m_MouseX(x), m_MouseY(y) {}

    inline float GetX() const { return m_MouseX; }
    inline float GetY() const { return m_MouseY; }

    std::string ToString() const override {
      std::stringstream ss;
      ss << "MouseMovedEvent: " << GetX() << ", " << GetY();
      return ss.str();
    }

    EVENT_CLASS_TYPE(MouseMoved)
    EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)

  private:
    float m_MouseX, m_MouseY;
};

class MouseScrollEvent : public Event {
  public:
    MouseScrollEvent(float offsetX, float offsetY)
      : m_OffsetX(offsetX), m_OffsetY(offsetX) {}

    inline float GetOffsetY() const { return m_OffsetY; }
    inline float GetOffsetX() const { return m_OffsetX; }

    std::string ToString() const override {
      std::stringstream ss;
      ss << "MouseScrollEvent: " << GetOffsetX() << ", " << GetOffsetY();
      return ss.str();
    }

    EVENT_CLASS_TYPE(MouseScrolled)
    EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)

  private:
    float m_OffsetX, m_OffsetY;
};

class MouseButtonEvent : public Event {
  public:
    inline int GetMouseButton() const { return m_Button; }

    EVENT_CLASS_CATEGORY(EventCategoryMouseButton | EventCategoryInput)

  protected:
    MouseButtonEvent(int button)
      : m_Button(button) {}

    int m_Button;
};

class MouseButtonDownEvent : public MouseButtonEvent {
  public:
    MouseButtonDownEvent(int button, int repeatCount)
      : MouseButtonEvent(button) {}

    std::string ToString() const override {
      std::stringstream ss;
      ss << "MouseButtonDownEvent: " << m_Button;
      return ss.str();
    }

    EVENT_CLASS_TYPE(MouseButtonDown)
};

class MouseButtonUpEvent : public MouseButtonEvent {
  public:
    MouseButtonUpEvent(int button)
      : MouseButtonEvent(button) {}

    std::string ToString() const override {
      std::stringstream ss;
      ss << "MouseButtonUpEvent: " << m_Button;
      return ss.str();
    }

    EVENT_CLASS_TYPE(MouseButtonUp)
};

}