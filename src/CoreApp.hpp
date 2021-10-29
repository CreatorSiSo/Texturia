#pragma once

#include "txpch.hpp"

namespace Texturia {

class CoreApp {
public:
  CoreApp();
  ~CoreApp();

  void Run();
};

CoreApp *CreateCoreApp();

} // namespace Texturia
