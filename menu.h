#include "header.h"

void color1(int color_code){
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(console,color_code);
}

void welcome(){
    color1(1);
    cout<<"\n\n\t\t\t\t\t\t****************************"<<endl;
    cout<<"\t\t\t\t\t\t** WELCOME TO QUIZ SYSTEM **"<<endl;
    cout<<"\t\t\t\t\t\t****************************"<<endl<<endl;
    color1(11);
}
inline void exit(string msg){
  system("cls");
  welcome();
  cout<<msg<<endl;
  _sleep(1000);
}

inline void invalidOpt(){
  system("cls");
  welcome();
  cout<<"\n\n\n\t\t\t\t\t\t   Invalid option!";
  _sleep(1000);
}

void mainMenu(){
  system("cls");
  welcome();
  color1(9);
  cout<<"\t\t\t***Select your role"<<endl<<endl;
  color1(11);
  cout<<"\t\t1. Admin"<<endl;
  cout<<"\t\t2. Student"<<endl;
  cout<<"\t\t3. Exit"<<endl;
}

inline void testTakerMenu(){
  system("cls");
  welcome();
  color1(9);
  cout<<"\t\t\t***Welcome Student!!*"<<endl<<endl;
  color1(11);
  cout<<"\t\t1. Sign up"<<endl;
  cout<<"\t\t2. Sign in"<<endl;
  cout<<"\t\t3. Back to main page"<<endl;
}

inline void adminMenu(){
  system("cls");
  welcome();
  cout<<"\t\t\t***Welcome Admin!!*"<<endl<<endl;
  cout<<"\t\t1. Add questions"<<endl;
  cout<<"\t\t2. Display Current question"<<endl;
  cout<<"\t\t3. Remove questions"<<endl;
  cout<<"\t\t4. Edit questions"<<endl;
  cout<<"\t\t5. View Test taker login info"<<endl;
  cout<<"\t\t6. View Test Taker Score"<<endl;
  cout<<"\t\t7. Back to menu"<<endl;
}

inline void studentMenu(){
  system("cls");
  welcome();
  color1(9);
  cout<<"\t\t\t***Welcome Student!!*"<<endl<<endl;
  color1(11);
  cout<<"\t\t1. Take test"<<endl;
  cout<<"\t\t2. Display Result"<<endl;
  cout<<"\t\t3. Back to menu"<<endl;
  cout<<"\t\tYour choice : ";
}
