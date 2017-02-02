#include <limits>

#include "../Definitions/Menu.hh"
#include "../Definitions/Interrupts.hh"

Menu::Menu() {
  _interruptVector[0] = new Initiate();
  _interruptVector[1] = new Print();
  _interruptVector[2] = new Terminate();
  _interruptVector[3] = new Exit();
  _isRunning = false;
}

Menu::~Menu() {
  for (int index = 0; index < 4; index++) {
    delete _interruptVector[index];
  }
}

void Menu::run() {
  int currentSelection;

  _isRunning = true;

  while (_isRunning) {
    this->displayMain();
    currentSelection = this->getSelection();
    if (currentSelection < 1 || currentSelection > 4) {
      this->displayError();
    } else {
      _interruptVector[currentSelection - 1]->handle();
    }
  }
}

void Menu::quit() {
  _isRunning = false;
}

void Menu::displayMain() const {
  cout << "Welcome to the Memory Management System" << endl;
  cout << "Please choose one of the following options by entering the corresponding number" << endl;
  cout << "1 - Initiate Process" << endl;
  cout << "2 - Print Processes" << endl;
  cout << "3 - Terminate Process" << endl;
  cout << "4 - Exit" << endl;
}

void Menu::displayError() const {
  cout << "Error: Please enter a valid number" << endl;
}

int Menu::getSelection() const {
  int selection = 0;
  cin >> selection;
  cin.clear();
  cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  return selection;
}
