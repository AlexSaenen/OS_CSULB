#include "Application.hh"

Application *app = 0;

Application::Application() : messages(IPC_PRIVATE) {
  app = this; // Initialize our global singleton instance pointer
}

Application::~Application() {}

void Application::run() {
}

void Application::stop() {
}
