#include "dataStructure.h"
using namespace std;

// int input;
int main(){
  List *mainList;
  mainList = createEmptyList();
  createQuestions(mainList);
  mainMenu();
  cout<<"Input: ";
  cin>>input;
  switch(input){
    case 1:
    //Login admin
    adminOpt(mainList);
    break;                                                                                                        
    case 2:
    cout<<"WIP"<<endl;
    //Sign up 
    break;
    case 3:
    //Login student
    cout<<"WIP"<<endl;
    break;
    case 4:
    cout<<"WIP"<<endl;
    //Exit
    break;
    default:
    cout<<"Invalid option"<<endl;
    break;
  }

  return 0;
}