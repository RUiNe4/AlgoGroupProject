#include "header.h"
#include "general.h"
#include "menu.h"
// #include <curses.h>
using namespace std;

//Global Variable to sign in
string fname;
string lname;
string email ;
string password;
string rpassword;

//Global variable
int input;

string inputAns;

struct Node{
  struct personInfo{
    string email;
	  string fname;
	  string lname;
	  string password;
	  string rpassword;
  }l;
  Node *next;
};

struct Element {
  struct question {
    string questionName;
    string questionID;
    int questionIndex;
    string correctAns;
    struct answer {
      string a1;
      string a2;
      string a3;
    } a;
  } q;
  Element *next, *previous;
};

struct List {
  int n;
  Element *head, *tail;
};

List *createEmptyList() {
  List *ls;
  ls = new List;

  ls->n = 0;
  ls->head = NULL;
  ls->tail = NULL;

  return ls;
}

bool checkQuestionsID(List *ls, int id) {

  Element *temp;
  bool found = false;

  temp = ls->head;

  while (temp != NULL) {
    if (temp->q.questionIndex == id) {

      cout << "\nThis question already existed!\n\n";
      cout << temp->q.questionIndex;
      found = true;
      break;
    } else {
      temp = temp->next;
      found = false;
    }
  }
  return found;
}

void deleteQuestion(List *ls){
  string ip;
  bool remove = false;
  Element *e; 
  
  e = ls->head;
  ls->head = ls->head->previous;
  cout<<e->q.questionName;
  cout<<"What question do you want to remove? >>>>>"; cin>>ip;
  while(e!=NULL){
  if(e->q.questionID == ip){
    remove = true;
    delete e;
  }
  e = e->next;
  }
  if(remove)
  ls->n = ls->n - 1;
}

void AddQuestion(List *ls, string questionID, int questionIndex, string questionName, string a1,
                 string a2, string a3,string correctAns) {
  Element *e;
  e = new Element;
  e->q.questionID = questionID;
  e->q.questionIndex = questionIndex;
  e->q.questionName = questionName;
  e->q.a.a1 = a1;
  e->q.a.a2 = a2;
  e->q.a.a3 = a3;
  e->q.correctAns = correctAns;
  e->next = ls->head;
  e->previous = NULL;
  if (ls->n == 0) {
    // e->next=NULL;
    ls->head = e;
    ls->tail = e;
  } else if (ls->n != 0) {
    ls->head->previous = e;
    ls->head = e;
  }
  ls->n++;
}

void addMoreQ(List *ls){
  // need to write to file
  int count = 0;
  // int i=0;
  Element *tmp;
  tmp = ls->head;
  while(true){
    cout<<"Enter question index: "; cin>>tmp->q.questionIndex;
    inputString("Enter q name: ", &tmp->q.questionName);
    inputString("Enter q ID: ", &tmp->q.questionID);
    inputString("Enter q a1: ", &tmp->q.a.a1);
    inputString("Enter q a2: ", &tmp->q.a.a2);
    inputString("Enter q a3: ", &tmp->q.a.a3);
    cout<<"<<< Successfully added the question to the list >>>"<<endl;
    cout<<"Add more (1 - Continue), (0 - Finish)? >>>>> "; cin>>input;
    if(input == 0)
    break;
    else if(input == 1){
      addMoreQ(ls);
    }
  }
//   AddQuestion(ls, tmp->q.questionID, tmp->q.questionIndex, tmp->q.questionName, tmp->q.a.a1, tmp->q.a.a2
// ,tmp->q.a.a3);
  
}

void displayQuestion(List *ls) {
  Element *tmp;
  tmp = ls->tail;
  while (tmp != NULL) {
    // system("clear");
    cout << tmp->q.questionIndex << "- " << tmp->q.questionName << endl;
    cout << "a. " << tmp->q.a.a1 << endl;
    cout << "b. " << tmp->q.a.a2 << endl;
    cout << "c. " << tmp->q.a.a3 << endl;
    tmp = tmp->previous;
  }
}

void CSQuestion(List *ls){
   AddQuestion(ls, "10" ,10, "What year was the first computer virus created in?",
              "1993", "1965", "1986","c"); // 1986
  AddQuestion(ls, "11" ,11, "One megabyte is equal to how many bytes?", "1000 byte",
              "1000000 byte", "1048576 bytes","c"); // c
  AddQuestion(ls, "12" ,12, "Apple was created in which country?", "America", "China",
              "Korea","a");
  AddQuestion(ls, "13" ,13,
              "Which is the correct syntax to output “hello world” in c++?",
              "system.out.println(“Hello world”);", "print(“hello world”);",
              "cout<<”hello world”;","c");
  AddQuestion(ls, "14" ,14, "How do you insert COMMENTs in C++ code?",
              "# this is a comment", "// this is  comment",
              "--this is a comment.","b");
  AddQuestion(ls, "15" ,15, " How do you create a function in c++?", "Functionname{}",
              "Functionname[]", "Functionname()","c");
  AddQuestion(ls, "16" ,16, "Which operator is used to add together two values?",
              "The + sign ", "The & sign", "The * sign","a");
  AddQuestion(
      ls,"17" ,17, " Which header file lets us work with input and output objects?",
      "#include <iostream>", "#include <inputstr>", "#include <stream>","a");
  AddQuestion(ls, "18" ,18,
              " Which method can be used to find the highest value of x and y?",
              "largest(x,y)", "maximum(x,y)", "max(x,y) ","c"); // max
  AddQuestion(ls, "19" ,19, "Which operator is used to multiply numbers?", "%", "/",
              "*","c"); // c
  AddQuestion(ls, "20" ,20, "What does HTML stand for?",
              "Hyperlinks and Text Markup Language",
              "Hyper Text Markup Language ", "Home Tool Markup Language","b");
  AddQuestion(ls, "21" ,21,
              "Choose the correct HTML element for the largest heading:",
              "<h1>", "<h6>", "<heading>","a");
  AddQuestion(ls, "22" ,22,
              "What is the most common operation system across all devices? "
              "(tablet, phone, laptop)?",
              "ios ", " Google android os", "Htl","b");
  AddQuestion(ls, "23" ,23, "One byte is equal to how many bits?", "5 bits", "7 bits",
              "8 bits","b"); // c
  AddQuestion(ls, "24" ,24, "How can you create a variable with the numeric value 5?",
              "num = 5;", "num = 5 int;", "int num = 5","c");
  AddQuestion(ls, "27" ,27, "Which statement is used to stop a loop?", "exit;",
              "break;", "void","b");
  AddQuestion(ls, "25" ,25,
              "How can you create a variable with the floating number 2.8?",
              "num = 2.8 double;", "float num = 2.8;", "num = 2.8 double;","b");
  AddQuestion(
      ls, "26", 26,
      "Which function is often used to output values and print text in c?",
      "printword();", "output();", "printf();","c");
  AddQuestion(ls, "28" ,28, "Which keyword is used to create a structure?", "Struct",
              "Structs", "Structure","a");
              AddQuestion(ls, "41" ,41, "The two kinds of main memory are", "CDs and DVDs",
              "RAM and ROM", "Primary and secondary","b");
  AddQuestion(ls, "42" ,42, " _____ has the shortest access times.", "Virtual Memory",
              "Secondary Memory", "Cache Memory","c");
  AddQuestion(
      ls, "43", 43,
      "Which parts of the computer were is used for calculating and comparing?",
      "ALU", "Modem", "Control Unit","a");
  AddQuestion(ls, "44" ,44, "The following is not an operating system ______",
              "MS OFFICE", "Window XP", "UNIX","a");
  AddQuestion(ls, "45" ,45, "A computer programmer is a person who _____",
              "sells program", "Use program", "writes program","c");
  AddQuestion(ls, "46" ,46, "The quality of the display is better if _____",
              "Resolution is least", "Resolution the moderate",
              "Resolution is higher","c");
  
  // displayQuestion(ls);       

}

void tmpQuestion(List *ls){
  AddQuestion(ls, "1" ,1, "Cambodia academy of digital technology is located in :",
              "Prek Leap ", "Wat Phnom ", "Jomkadoung","a");
  AddQuestion(ls, "2" ,2, "What is the boiling point of water?", " 120 celcius",
              " 100 celcius ", " 95 celcius ","b");
  AddQuestion(ls, "3" ,3, "The coldest continent in the world is.", "Antarctica",
              "Greenland", "Alaska","a");
  AddQuestion(ls, "4" ,4,
              "Techo scholarship provides monthly pay for the scholarship "
              "student, how much does each student receive for generation 8? ",
              "70$", " 80$", "90$","b");
  AddQuestion(ls, "5" ,5, "What is the name of CADT before it was changed? ",
              "NIPTICT", " ITC", "NPIC","a");
  AddQuestion(ls, "6" ,6, "What is the national flower of cambodia?", "Lotus",
              "Wild lilly", "Romdoul","c");
  AddQuestion(ls, "7" ,7, "Which city host the 2002 olympic?", "Beijing", "Sydney",
              "Tokyo","b"); // it's sydney
  AddQuestion(ls, "8" ,8, " Where was tea invented?", "England", "USA", "China","c");
  AddQuestion(ls, "9" ,9, "What language does the Cambodian speak?", "Cambodese",
              "Khmer", "Khmeir","b");
 
  AddQuestion(ls, "29" ,29, "What is the largest organ in the human body?", "Skin",
              "Muscle", "The veins","a");
  AddQuestion(ls, "30" ,30, "Which planet is known as the red planet?", "Venus",
              "Mercury", "mars","c");
  AddQuestion(ls, "31" ,31, "How many continents are there in the world?", "6", "7",
              "8","b");
  AddQuestion(ls, "32" ,32, "The periodic table has how many elements?", "90", "110",
              "118","c");
  AddQuestion(ls, "33" ,33, "How many are there in a dozen?", "4", "10", "12","c");
  AddQuestion(ls, "34" ,34, "The ocean covers how much of the earth's surface?",
              "75%", "70%", "80%","b");
  AddQuestion(ls, "35" ,35, "What is the largest religious structure in the world?",
              "Angkor wat", "Vishnu statue", "Mangal mahadev","a");
  AddQuestion(ls, "36" ,36, "Which living mammal cannot jump?", "Elephant", "Giraffe",
              "Pig","a");
  AddQuestion(ls, "37" ,37, "What is the population of Cambodia in 2022?",
              "15 millions", "16 millions", "17 millions","c");
  AddQuestion(ls, "38" ,38, "Who is the Prime Minister of Cambodia?", "Hun Sen",
              "Elon Musk", "Pov SomNoun","a");
  AddQuestion(ls, "39" ,39, "Cadt is an academy specialized in :", "Digital major ",
              "Cooking major", "Agriculture major","a");
  AddQuestion(ls, "40" ,40, "What is the smallest country among the ASEAN country?",
              "Singapore", "Brunei", "Malaysia","b");
  
  AddQuestion(ls, "47" ,47, "What is the largest planet in  the solar system?",
              "Jupiter", "Saturn", "Neptune","a");
  AddQuestion(ls, "48" ,48, "Which country won the fifa world cup 2018?", "Croatia",
              "France", "Brazil","a");
  AddQuestion(ls, "49" ,49, " What is the longest river in the world?",
              "The nile river", "The yangtze river", "The amazon river","a");
  AddQuestion(ls, "50" ,50, "What is the highest mountain in the world?",
              "Mount Kanchenjunga", "Mount K2", "Mount Everest","c");
}

void createQuestions(List *ls) {
  tmpQuestion(ls);
  CSQuestion(ls);
  // for(int i=0;i<numQ;i++){
  //   addMoreQ(ls, numQ);
  // }
}

void adminOpt(List *ls){
  system("cls");
  adminMenu();
  cout<<"Enter your choice >>>>>"; cin>>input;
  if(input){
    switch (input)
    {
      case 1:
      system("cls");
      // cout<<"How many questions do you want to add? "; cin>>input;
      addMoreQ(ls);
      //back to menu
      adminOpt(ls);
      break;
      case 2:
        //Display q
        system("cls");
        displayQuestion(ls);
        getch();
        adminOpt(ls);
      break;
      case 3:
        //Remove q
        system("cls");
        deleteQuestion(ls);
        _getch();
        adminOpt(ls);
      break;
      case 4:
        //Edit q
        system("cls");
        cout<<"WIP"<<endl;
      break;
      case 5:
        system("cls");
        // View Test take login info
        cout<<"WIP"<<endl;
      break;
      case 6:
        system("cls");
        //View Test Taker history
        cout<<"WIP"<<endl;
      break;
      case 7:
        system("cls");
        // Exit
        cout<<"WIP"<<endl;
      break;
      default:
        system("cls");
        cout<<"Invalid option"<<endl;
      break;
    }
  }
}

int finalScore;

void takeTest(List *ls){
  Element *tmp = ls->head;
  finalScore = 0;
  while(tmp!=NULL){
    for (int i = 0 ;i<10;i++){
    system("cls");
    Top:
    cout<<tmp->q.questionName<<endl;
    cout<<"a. "<<tmp->q.a.a1<<endl;
    cout<<"b. "<<tmp->q.a.a2<<endl;
    cout<<"c. "<<tmp->q.a.a3<<endl;
    cout<<"Enter answer: ";  
    fflush(stdin);
    getline(cin,inputAns);
    if(inputAns == "a" || inputAns == "b" || inputAns == "c"){
      if (inputAns == tmp->q.correctAns){
        finalScore += 3;
      }else{
        // finalScore -= 1;
      }
      cout<<endl;
    }else{
      cout<<"Invalid Input, please enter again"<<endl;
      cout<<" -----------------------------";
      getch();
      goto Top;
    }
    tmp = tmp->next;
    }
    break;
  }
  cout<<"Your final point is: "<<finalScore;
  cout<<" -----------------------------";
  getch();
}

void studentOpt(List *ls){
  Menu:
  system("cls");
  studentMenu();
  cin>>input;
  switch (input)
  {
  case 1:
    system("cls");
    takeTest(ls);
    goto Menu;
  default:
    break;
  }
}