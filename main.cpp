#include "dataStructure.h"

void startTest(List *mainList, loginList *loginList) {
  int inputInt;
  testTakerMenu();
  cout<<endl<<endl;
  cout << "Enter your choice >>>>> ";
  cin >> inputInt;
  switch (inputInt) {
  case 1:
    // Register
    system("cls");
    signUp(loginList);
    _getch();
    startTest(mainList, loginList);
    break; 
  case 2:
    studentOpt(mainList, loginList);
    startTest(mainList, loginList);
    break;
  case 3:
    returnMenu("Going back to menu");
    break;
  default:
    invalidOpt();
    startTest(mainList, loginList);
    break;
  }
}

void home(List *mainList, loginList *loginList, List *scoreList) {
  bool adm = false;
  int inputInt;
  mainMenu();
  cout<<"\t\tEnter Your choice : ";
  cin >> inputInt;
  switch (inputInt) {
  case 1:
    system("cls");
    loginAdmin(&adm);
    if(adm){
      adminOpt(mainList, loginList, scoreList);
    }
    home(mainList, loginList, scoreList);
    break;
  case 2:
    system("cls");
    startTest(mainList, loginList);
    home(mainList, loginList, scoreList);
    break;
  case 3:
    welcome();
    returnMenu("\n\n\n\t\t\t\t\tYou have successfully exit the program");
    exit(0);
    break;
  default:
    welcome();
    invalidOpt();

    _getch();
    home(mainList, loginList, scoreList);

    break;
  }
}

int main() {
  color(11);  
  // loadingBar();
  List *mainList;
  mainList = createEmptyList();

  loginList *loginList;
  loginList = createEmptyLoginList();

  List *scoreList;
  scoreList = createEmptyList();

  readLoginInfo(loginList);
  readQuestionFromFile(mainList);
  
  home(mainList, loginList, scoreList);

  return 0;
}

