#include "login.h"
using namespace std;

void takeTest(List *mainList, loginList *loginList){
  testTakerMenu();
  cout<<"Enter your choice >>>>> "; cin>>inputInt;
  switch(inputInt){
    case 1:
    //Register
    signUp(&fname, &lname, &email, &password, &rpassword);
    if(checkExistEmailInFile(email)==0){
        cout<<"User already exists"<<endl;
    }else if(checkExistEmailInFile(email)==1){
        cout<<"You have successfully registered"<<endl;
        insert(loginList,fname,lname,email,password);
        writeNameEmail(loginList);
        writeEmail(loginList);
        writePass(loginList);
    }
    break;
    case 2:
    //Login
    Login();
    studentOpt(mainList);
    break;
    case 3:
    exit("Going back to menu");
    break;
    default: 
    invalidOpt();
    takeTest(mainList, loginList);
    break;
  }
}

void home(List *mainList, loginList *loginList){
  mainMenu();
  cout<<"Enter your choice >>>>> "; cin>>inputInt;
  switch(inputInt){
    case 1:
    adminOpt(mainList);
    home(mainList, loginList);
    break;                                                                                                        
    case 2:
    takeTest(mainList, loginList);
    home(mainList, loginList);
    break;
    case 3:
    exit("You have successfully exit the program");
    exit(0);
    break;
    default:
    invalidOpt();
    home(mainList, loginList);
    break;
  }
}

int main(){
  List *mainList;
  mainList = createEmptyList();
  
  loginList *loginList;
  loginList = createEmptyLoginList();
  
  createQuestions(mainList);
  home(mainList, loginList);
  return 0;
}
