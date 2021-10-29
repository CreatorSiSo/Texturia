#include "CoreApp.hpp"

int main(int argc, char **argv) {
  auto app = Texturia::CreateCoreApp();
  app->Run();
  delete app;
  exit(EXIT_SUCCESS);
}
