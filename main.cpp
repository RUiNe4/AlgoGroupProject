#include "login.h"
using namespace std;

void home(List *mainList, loginList *loginList){
  mainMenu();
  cout<<"Enter your choice >>>>> "; cin>>inputInt;
  switch(inputInt){
    case 1:
    //Login admin
    system("cls");
    adminOpt(mainList);
    break;                                                                                                        
    case 2:
    signUp(&fname, &lname, &email, &password, &rpassword);
    if(checkExistEmailInFile(email)==0){
        cout<<"User already exist"<<endl;
    }else if(checkExistEmailInFile(email)==1){
        cout<<"You have successfully registered"<<endl;
        insert(loginList,fname,lname,email,password);
        writeNameEmail(loginList);
        writeEmail(loginList);
        writePass(loginList);
    }
    home(mainList, loginList);
    //Sign up 
    break;
    case 3:
    //Login student
    Login();
    studentOpt(mainList);
    // cout<<"WIP"<<endl;
    break;
    case 4:
    cout<<"You have exit the program"<<endl;
    // cout<<"WIP"<<endl;
    //Exit
    break;
    default:
    cout<<"Invalid option"<<endl;
    break;
  }
}

// int input;
int main(){
  Element *tmp;
  List *mainList;
  mainList = createEmptyList();
  
  loginList *loginList;
  loginList = createEmptyLoginList();
  
  createQuestions(mainList);
  home(mainList, loginList);
  return 0;
}
