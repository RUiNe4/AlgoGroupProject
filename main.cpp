#include "login.h"
using namespace std;

void home(List *mainList){
  mainMenu();
  cout<<"Enter your choice >>>>> "; cin>>input;
  switch(input){
    case 1:
    //Login admin
    adminOpt(mainList);
    break;                                                                                                        
    case 2:
    signUp(&fname, &lname, &email, &password, &rpassword);
    if(checkExistEmailInFile(email)==0){
        cout<<"User already exist"<<endl;
    }else if(checkExistEmailInFile(email)==1){
        cout<<"You have successfully registered"<<endl;
        insert(mainList,fname,lname,email,password);
    }
    home(mainList);
    //Sign up 
    break;
    case 3:
    //Login student
    Login();
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
  List *mainList;
  mainList = createEmptyList();
  createQuestions(mainList);
  home(mainList);
  return 0;
}