#include "../Definitions/Application.hh"

Application *app = 0;

Application::Application() : _menu() {
  app = this;
}

Application::~Application() {}

void Application::run() {
  _menu.run();
}

void Application::stop() {
  _menu.quit();
}
