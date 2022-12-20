#include <iostream>
#include <conio.h>
using namespace std;

inline void exit(string msg){
  system("cls");
  cout<<msg<<endl;
  _sleep(500);
}

inline void invalidOpt(){
  system("cls");
  cout<<"Invalid option - Press any key to continue";
  _getch();
}

inline void mainMenu(){
  system("cls");
  cout<<"Who are you?"<<endl;
  cout<<"1 - Admin"<<endl;
  cout<<"2 - Take Test"<<endl;
  cout<<"3 - Exit"<<endl;
}

inline void testTakerMenu(){
  system("cls");
  cout<<"1 - Sign up"<<endl;
  cout<<"2 - Already have an account? ==> Take test"<<endl;
  cout<<"3 - Back to menu"<<endl;
}

inline void adminMenu(){
  system("cls");
  cout<<"1. Add questions"<<endl;
  cout<<"2. Display Current question"<<endl;
  cout<<"3. Remove questions"<<endl;
  cout<<"4. Edit questions"<<endl;
  cout<<"5. View Test take login info"<<endl;
  cout<<"6. View Test Taker history"<<endl;
  cout<<"7. Back to menu"<<endl;
}

inline void studentMenu(){
  system("cls");
  cout<<"1. Take test"<<endl;
  cout<<"2. Display Result"<<endl;
  cout<<"3. Back to menu"<<endl;
  cout<<"Please select an option: ";
}
