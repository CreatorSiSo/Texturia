#pragma once

#include "txpch.hpp"

#include "Input.hpp"

namespace Texturia {

class WindowsInput : public Input {
protected:
  virtual bool IsKeyDownImpl(int keycode) override;
  virtual bool IsMouseButtonDownImpl(int button) override;
  virtual std::pair<float, float> GetMousePosImpl() override;
  virtual float GetMouseXImpl() override;
  virtual float GetMouseYImpl() override;
};

} // namespace Texturia
