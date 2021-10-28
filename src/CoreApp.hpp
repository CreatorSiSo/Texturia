#pragma once

namespace Texturia {

  class CoreApp {
  public:
    CoreApp();
    ~CoreApp();

    void Run();
  };

  CoreApp* CreateCoreApp();

}