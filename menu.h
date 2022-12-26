#include "header.h"

inline void exit(string msg){
  system("clear");
  cout<<msg<<endl;
  //_sleep(500);
  sleep(500);
}

inline void invalidOpt(){
  //system("cls");
  system("clear");
  cout<<"Invalid option - Press any key to continue";
  // _sleep(500);
}
void loadingBar()
{
  
    cout<<"\t\t\t\t\t\t****************************"<<endl;
    cout<<"\t\t\t\t\t\t** WELCOME TO QUIZ SYSTEM **"<<endl;
    cout<<"\t\t\t\t\t\t****************************"<<endl<<endl;
	// 0 - black background,
	// A - Green Foreground
	system("color 0D");

	// Initialize char for printing
	// loading bar
	char a = 177, b = 219;

	cout<<"\n\n\n\n";
	cout<<"\n\n\n\n\t\t\t\t\t"
		"Loading...\n\n";
	cout<<"\t\t\t\t\t";

	// Print initial loading bar
	for (int i = 0; i < 26; i++){
		cout<<"%c", a;
  }
	// Set the cursor again starting
	// point of loading bar
	cout<<"\r";
	cout<<"\t\t\t\t\t";

	// Print loading bar progress
	for (int i = 0; i < 26; i++) {
		cout<<("%c", b);

		// Sleep for 1 second
  
    //_sleep(1000);
		sleep(1000);
	}
}

void mainMenu(){
  //system("cls");
  system("clear");
  cout<<"Who are you?"<<endl;
  cout<<"1 - Admin"<<endl;
  cout<<"2 - Take Test"<<endl;
  cout<<"3 - Exit"<<endl;
}

inline void testTakerMenu(){
  //system("cls");
  system("clear");
  cout<<"1 - Sign up"<<endl;
  cout<<"2 - Already have an account? ==> Take test"<<endl;
  cout<<"3 - Back to menu"<<endl;
}
 void adminMenu(){
  //system("cls");
  system("clear");
  cout<<"1. Add questions"<<endl;
  cout<<"2. Display Current question"<<endl;
  cout<<"3. Remove questions"<<endl;
  cout<<"4. Edit questions"<<endl;
  cout<<"5. View Test take login info"<<endl;
  cout<<"6. View Test Taker history"<<endl;
  cout<<"7. Back to menu"<<endl;
}

inline void studentMenu(){
  //system("cls");
  system("clear");
  cout<<"1. Take test"<<endl;
  cout<<"2. Display Result"<<endl;
  cout<<"3. Back to menu"<<endl;
  cout<<"Please select an option: ";
}
