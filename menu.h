#include "header.h"

void welcome(){
    color(1);
    cout<<"\n\n\t\t\t\t\t\t****************************"<<endl;
    cout<<"\t\t\t\t\t\t** WELCOME TO QUIZ SYSTEM **"<<endl;
    cout<<"\t\t\t\t\t\t****************************"<<endl<<endl;
    color(11);
}
void returnMenu(string msg){
  //system("clear");
  system("cls");
  cout<<msg<<endl;
  Sleep(500);
  // sleep(500);
}

inline void invalidOpt(){
  system("cls");
  //system("clear");
  // Sleep(500);
  welcome();
  cout<<"\n\n\n\t\t\t\t\t\t   Invalid option!";
  Sleep(500);
}
void loadingBar()
{
    cout<<"\t\t\t\t\t\t****************************"<<endl;
    cout<<"\t\t\t\t\t\t** WELCOME TO QUIZ SYSTEM **"<<endl;
    cout<<"\t\t\t\t\t\t****************************"<<endl<<endl;

	color(11);

	char a = 177, b = 219;

	cout<<"\n\n\n\n\t\t\t\t\t"
		"Loading...\n\n";
	cout<<"\t\t\t\t\t";

	for (int i = 0; i < 50; i++){
		cout<<a;
  }
	cout<<"\r";
	cout<<"\t\t\t\t\t";

	for (int i = 0; i < 50; i++) {
		cout<<b;
  
    Sleep(100);
		// sleep(1000);
	}
  cout<<"\n\n\n\n\t\t\t\t\t""\n\n";
	cout<<"\t\t\t\t\t";
  system("Pause");
}

void mainMenu(){
  system("cls");
  welcome();
  color(9);
  cout<<"\t\t\t***Select your role"<<endl<<endl;
  color(11);
  cout<<"\t\t1. Admin"<<endl;
  cout<<"\t\t2. Student"<<endl;
  cout<<"\t\t3. Exit"<<endl;
}

inline void testTakerMenu(){
  system("cls");
  welcome();
  color(9);
  cout<<"\t\t\t***Welcome Student!!*"<<endl<<endl;
  color(11);
  cout<<"\t\t1. Sign up"<<endl;
  cout<<"\t\t2. Already have an account? ==> Proceed to test"<<endl;
  cout<<"\t\t3. Back to main page"<<endl;
}
 void adminMenu(){
  system("cls");
  welcome();
  cout<<"\t\t\t***Welcome Admin!!*"<<endl<<endl;
  cout<<"\t\t1. Add questions"<<endl;
  cout<<"\t\t2. Display Current question"<<endl;
  cout<<"\t\t3. Remove questions"<<endl;
  cout<<"\t\t4. Edit questions"<<endl;
  cout<<"\t\t5. View Test taker login info"<<endl;
  cout<<"\t\t6. View Test Taker Score"<<endl;
  cout<<"\t\t7. Change question size"<<endl;
  cout<<"\t\t8. View activity History"<<endl;
  cout<<"\t\t9. Back to menu"<<endl;
}

inline void studentMenu(){
  system("cls");
  welcome();
  color(9);
  cout<<"\t\t\t***Welcome Student!!*"<<endl<<endl;
  color(11);
  cout<<"\t\t1. Take Test"<<endl;
  // cout<<"\t\t2. Display Result"<<endl;
  cout<<"\t\t2. Back to menu"<<endl;
  cout<<"\t\tYour choice : ";
}

