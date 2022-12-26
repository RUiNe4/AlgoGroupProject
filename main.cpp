#include "login.h"

void startTest(List *mainList, loginList *loginList) {
  int inputInt;
  testTakerMenu();
  cout << "Enter your choice >>>>> ";
  cin >> inputInt;
  switch (inputInt) {
  case 1:
    // Register
    signUp(loginList);
    saveLoginFile(loginList);
    break;
  case 2:
    // Login
    Login(loginList);
    // studentOpt(mainList);
    startTest(mainList, loginList);
    break;
  case 3:
    exit("Going back to menu");
    break;
  default:
    invalidOpt();
    startTest(mainList, loginList);
    break;
  }
}

void home(List *mainList, loginList *loginList) {
  int inputInt;
  mainMenu();
  cout << "Enter your choice >>>>> ";
  cin >> inputInt;
  switch (inputInt) {
  case 1:
    adminOpt(mainList, loginList);
    home(mainList, loginList);
    break;
  case 2:
    startTest(mainList, loginList);
    home(mainList, loginList);
    break;
  case 3:
    saveFile(mainList);
    exit("You have successfully exit the program");
    exit(0);
    break;
  default:
    invalidOpt();
    //_getch();
    home(mainList, loginList);
    break;
  }
}

int main() {

  List *mainList;
  mainList = createEmptyList();

  loginList *loginList;
  loginList = createEmptyLoginList();
 //  loadingBar();
  readLoginInfo(loginList);
  createQuestions(mainList);
  loadingBar();
  home(mainList, loginList);
  
  return 0;
}
