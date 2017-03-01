#include "Application.hh"

Application *app = 0;

Application::Application() : messages(IPC_PRIVATE, true) {
  app = this; // Initialize our global singleton instance pointer
}

Application::~Application() {}

void Application::execute() {
  Child sender("sender");
  Child receiver("receiver");
}
