#include "header.h"
#include "general.h"
// #include <curses.h>
using namespace std;

struct Element {
  struct question {
    string questionName;
    string questionID;
    int questionIndex;
    struct answer {
      string a1;
      string a2;
      string a3;
      string correctAns;
    } a;
    double point;
    char answer;
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
  Element *tmp;
  tmp = ls->head;
  cout<<"Enter question index: ";
  cin>>tmp->q.questionIndex;
  inputString("Enter q name: ", &tmp->q.questionName);
  inputString("Enter q ID: ", &tmp->q.questionID);
  inputString("Enter q a1: ", &tmp->q.a.a1);
  inputString("Enter q a2: ", &tmp->q.a.a2);
  inputString("Enter q a3: ", &tmp->q.a.a3);
  inputString("Enter q Correct Answer: ", &tmp->q.a.correctAns);
//   AddQuestion(ls, tmp->q.questionID, tmp->q.questionIndex, tmp->q.questionName, tmp->q.a.a1, tmp->q.a.a2
// ,tmp->q.a.a3);
}

void displayQuestion(List *ls) {
  Element *tmp;
  tmp = ls->tail;
  while (tmp != NULL) {
    // system("clear");
    cout << "- " << tmp->q.questionName << endl;
    cout << "a. " << tmp->q.a.a1 << endl;
    cout << "b. " << tmp->q.a.a2 << endl;
    cout << "c. " << tmp->q.a.a3 << endl;
    tmp = tmp->previous;
  // cout << ">>>>> Input answer (0 - to previous), (1 - skip): ";
  //   cin >> tmp->q.answer;
  //   switch (tmp->q.answer) {
  //   case 'a':
  //     cout << tmp->q.answer;
  //     tmp = tmp->previous;
  //     break;
  //   case 'b':
  //     cout << tmp->q.answer;
  //     tmp = tmp->previous;
  //     break;
  //   case 'c':
  //     cout << tmp->q.answer;
  //     tmp = tmp->previous;
  //     break;
  //   case '0':
  //     if (tmp == NULL) {
  //       cout << "Cannot go to previous question";
  //     } else {
  //       tmp = tmp->next;
  //     }
  //     break;
  //   case '1':
  //     if (tmp == NULL) {
  //       cout << "No more next";
  //     } else {
  //       tmp = tmp->previous;
  //     }
  //     break;
  //   }
  }
}

void createQuestions() {
  List *ls;
  ls = createEmptyList();
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
  AddQuestion(ls, "10" ,10, "What year was the first computer virus created in?",
              "1993", "1965", "1986","c"); // 1986
  AddQuestion(ls, "11" ,11, "One megabyte is equal to how many bytes?", "1000 byte",
              "1000000 byte", "1048576 bytes"); // c
  AddQuestion(ls, "" ,12, "Apple was created in which country?", "America", "China",
              "Korea");
  AddQuestion(ls, "" ,13,
              "Which is the correct syntax to output “hello world” in c++?",
              "system.out.println(“Hello world”);", "print(“hello world”);",
              "cout<<”hello world”;");
  AddQuestion(ls, "" ,14, "How do you insert COMMENTs in C++ code?",
              "# this is a comment", "// this is  comment",
              "this is a comment.");
  AddQuestion(ls, "" ,15, " How do you create a function in c++?", "Functionname{}",
              "Functionname[]", "Functionname()");
  AddQuestion(ls, "" ,16, "Which operator is used to add together two values?",
              "The + sign ", "The & sign", "The * sign");
  AddQuestion(
      ls,"" ,17, " Which header file lets us work with input and output objects?",
      "#include <iostream>", "#include <inputstr>", "#include <stream>");
  AddQuestion(ls, "" ,18,
              " Which method can be used to find the highest value of x and y?",
              "largest(x,y)", "maximum(x,y)", "max(x,y)  "); // max
  AddQuestion(ls, "" ,19, "Which operator is used to multiply numbers?", "%", "/",
              "*"); // c
  AddQuestion(ls, "" ,20, "What does HTML stand for?",
              "Hyperlinks and Text Markup Language",
              "Hyper Text Markup Language ", "Home Tool Markup Language");
  AddQuestion(ls, "" ,21,
              "Choose the correct HTML element for the largest heading:",
              "<h1>", "<h6>", "<heading>");
  AddQuestion(ls, "" ,22,
              "What is the most common operation system across all devices? "
              "(tablet, phone, laptop)?",
              "ios ", " Google android os", "Htl");
  AddQuestion(ls, "" ,23, "One byte is equal to how many bits?", "5 bits", "7 bits",
              "8 bits"); // c
  AddQuestion(ls, "" ,24, "How can you create a variable with the numeric value 5?",
              "num = 5;", "num = 5 int;", "int num = 5");
  AddQuestion(ls, "" ,27, "Which statement is used to stop a loop?", "exit;",
              "break;", "void");
  AddQuestion(ls, "" ,25,
              "How can you create a variable with the floating number 2.8?",
              "num = 2.8 double;", "float num = 2.8;", "num = 2.8 double;");
  AddQuestion(
      ls, "", 26,
      "Which function is often used to output values and print text in c?",
      "printword();", "output();", "printf();");
  AddQuestion(ls, "" ,28, "Which keyword is used to create a structure?", "Struct",
              "Structs", "Structure");
  AddQuestion(ls, "" ,29, "What is the largest organ in the human body?", "Skin",
              "Muscle", "The veins");
  AddQuestion(ls, "" ,30, "Which planet is known as the red planet?", "Venus",
              "Mercury", "mars");
  AddQuestion(ls, "" ,31, "How many continents are there in the world?", "6", "7",
              "8");
  AddQuestion(ls, "" ,32, "The periodic table has how many elements?", "90", "110",
              "118");
  AddQuestion(ls, "" ,33, "How many are there in a dozen?", "4", "10", "12");
  AddQuestion(ls, "" ,34, "The ocean covers how much of the earth's surface?",
              "75%", "70%", "80%");
  AddQuestion(ls, "" ,35, "What is the largest religious structure in the world?",
              "Angkor wat", "Vishnu statue", "Mangal mahadev");
  AddQuestion(ls, "" ,36, "Which living mammal cannot jump?", "Elephant", "Giraffe",
              "Pig");
  AddQuestion(ls, "" ,37, "What is the population of Cambodia in 2022?",
              "15 millions", "16 millions", "17 millions");
  AddQuestion(ls, "" ,38, "Who is the Prime Minister of Cambodia?", "Hun Sen",
              "Elon Musk", "Pov SomNoun");
  AddQuestion(ls, "" ,39, "Cadt is an academy specialized in :", "Digital major ",
              "Cooking major", "Agriculture major");
  AddQuestion(ls, "" ,40, "What is the smallest country among the ASEAN country?",
              "Singapore", "Brunei", "Malaysia");
  AddQuestion(ls, "" ,41, "The two kinds of main memory are", "CDs and DVDs",
              "RAM and ROM", "Primary and secondary");
  AddQuestion(ls, "" ,42, " _____ has the shortest access times.", "Virtual Memory",
              "Secondary Memory", "Cache Memory");
  AddQuestion(
      ls, "", 43,
      "Which parts of the computer were is used for calculating and comparing?",
      "ALU", "Modem", "Control Unit");
  AddQuestion(ls, "" ,44, "The following is not an operating system ______",
              "MS OFFICE", "Window XP", "UNIX");
  AddQuestion(ls, "" ,45, "A computer programmer is a person who _____",
              "sells program", "Use program", "writes program");
  AddQuestion(ls, "" ,46, "The quality of the display is better if _____",
              "Resolution is least", "Resolution the moderate",
              "Resolution is higher");
  AddQuestion(ls, "" ,47, "What is the largest planet in  the solar system?",
              "Jupiter", "Saturn", "Neptune");
  AddQuestion(ls, "" ,48, "Which country won the fifa world cup 2018?", "Croatia",
              "France", "Brazil");
  AddQuestion(ls, "" ,49, " What is the longest river in the world?",
              "The nile river", "The yangtze river", "The amazon river");
  AddQuestion(ls, "" ,50, "What is the highest mountain in the world?",
              "Mount Kanchenjunga", "Mount K2", "Mount Everest");

  addMoreQ(ls);
  
  displayQuestion(ls);
}
