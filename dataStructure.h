#include "general.h"
#include "header.h"
#include "menu.h"

// #include <curses.h>
using namespace std;

// for adding questions
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

// Global Variable to sign in
string fname;
string lname;
string email;
string password;
string rpassword;

// Global variable
int inputInt;
string inputStr;

struct Node {
  struct personInfo {
    string email;
    string fname;
    string lname;
    string password;
    string rpassword;
  } l;
  Node *next;
};

struct loginList {
  int n;
  Node *head, *tail;
};

loginList *createEmptyLoginList() {
  loginList *ls;
  ls = new loginList;

  ls->n = 0;
  ls->head = NULL;
  ls->tail = NULL;

  return ls;
}

struct Element {
  struct question {
    string questionName;
    string questionID;
    int questionIndex;
    string correctAns;
    string studentAns;
    int studentScore;
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

bool checkQuestionID(List *ls, string questionID, bool found) {
  Element *tmp;
  tmp = ls->head;
  while (tmp != NULL) {
    if (tmp->q.questionID == questionID) {
      found = true;
      return found;
    }
    tmp = tmp->next;
  }
  return found;
}

Element *findQuestionPos(List *ls, string id) {

  Element *temp;
  temp = ls->head;

  while (temp != NULL) {
    if (temp->q.questionID == id) {
      return temp;
    } else {
      temp = temp->next;
    }
  }
  return NULL;
}

void AddQuestion(List *ls, string questionID, int questionIndex,
                 string questionName, string a1, string a2, string a3,
                 string correctAns) {
  Element *e;
  e = new Element;
  e->q.questionID = questionID;
  e->q.questionIndex = questionIndex;
  e->q.questionName = questionName;
  e->q.a.a1 = a1;
  e->q.a.a2 = a2;
  e->q.a.a3 = a3;
  e->q.correctAns = correctAns;

  if (ls->n == 0) {
    e->next = NULL;
    e->previous = NULL;
    ls->head = e;
    ls->tail = e;
  } else if (ls->n != 0) {
    e->next = ls->head;
    e->previous = NULL;
    ls->head->previous = e;
    ls->head = e;
  }
  ls->n++;
}

void addMoreQ(List *ls) {
  // need to write to file
  bool found = false;
  int count = 1;
  while (1) {
    inputString("Enter q ID: ", &q.questionID);
    if (checkQuestionID(ls, q.questionID, found)) {
      cout << "Id already exists" << endl;
      cout << "Please try again" << endl;
      addMoreQ(ls);
    } else {
      cout << "Enter question index: ";
      cin >> q.questionIndex;
      inputString("Enter q name: ", &q.questionName);
      inputString("Enter q a1: ", &q.a.a1);
      inputString("Enter q a2: ", &q.a.a2);
      inputString("Enter q a3: ", &q.a.a3);
      inputString("Enter the correct answer: ", &q.correctAns);
    }
    AddQuestion(ls, q.questionID, q.questionIndex, q.questionName, q.a.a1,
                q.a.a2, q.a.a3, q.correctAns);
    cout << "<<< Successfully added the question to the list >>>" << endl;
    count++;
    cout << "Add more (1 - Continue), (0 - Finish)? >>>>> ";
    cin >> inputInt;
    if (inputInt == 0) {
      cout << "<<< You have added " << count << " question(s) to the list >>>"
           << endl;
      cout << "Press any key to continue";
      _getch();
      break;
    } else if (inputInt == 1) {
      addMoreQ(ls);
    }
    break;
  }
}

void deleteNode(List *ls, Element *tmp, bool *remove) {
  // list empty or no node
  if (ls->head == NULL || tmp == NULL) {
    *remove = false;
    return;
  }
  // head = input element
  if (ls->head == tmp) {
    ls->head = tmp->next;
    *remove = true;
  }
  if (tmp->next != NULL) {
    tmp->next->previous = tmp->previous; // need explanation :/
    *remove = true;
  }
  if (tmp->previous != NULL) {
    tmp->previous->next = tmp->next; // same shit
    *remove = true;
  }
  delete tmp;
}

void deleteQuestion(List *ls) {
  bool remove = false;
  Element *e;
  e = ls->head;
  // list empty
  if (ls->head == NULL) {
    cout << "There's no question in the list, maybe add some? (1 - Continue), "
            "(0 - Menu) >>>>> ";
    cin >> inputInt;
    if (inputInt == 1) {
      addMoreQ(ls);
    } else if (inputInt == 0) {
      return;
    }
  }
  cout << "What question do you want to remove? >>>>> ";
  cin >> inputStr;
  e = findQuestionPos(ls, inputStr);
  // no id
  if (e == NULL) {
    cout << "The question ID: " << inputStr
         << " doesn't seem to exist (1 - Continue), (0 - Menu) >>>>> ";
    cin >> inputInt;
    if (inputInt == 1) {
      deleteQuestion(ls);
    } else if (inputInt == 0) {
      return;
    }
  }
  deleteNode(ls, e, &remove);
  if (!remove) {
    cout << "No such question" << endl;
  } else if (remove) {
    cout << "Successfully removed question from the list (1 - Continue), (0 - "
            "Menu) >>>>> ";
    cin >> inputInt;
    if (inputInt == 1) {
      deleteQuestion(ls);
    } else if (inputInt == 0) {
      return;
    }
  } else {
    cout << "Invalid input - ..." << endl;
    _sleep(500);
    deleteQuestion(ls);
  }
}

void editQuestion(List *ls) {
  Element *tmp;
  bool success = false;
  cout << "Which question do you wish to edit? >>>>> ";
  cin >> inputStr;
  tmp = findQuestionPos(ls, inputStr);
  cout<<"This is the question you have selected "<<endl<<endl;
  cout << tmp->q.questionIndex << " - " << tmp->q.questionName << endl;
    cout << "a. " << tmp->q.a.a1 << endl;
    cout << "b. " << tmp->q.a.a2 << endl;
    cout << "c. " << tmp->q.a.a3 << endl << endl;
  if(tmp != NULL){
    cout<<"Which part do you want to edit? -"<<endl;
    cout<<"0 - Back to Menu"<<endl;
    cout<<"1 - Everything"<<endl;
    cout<<"2 - Question Name"<<endl;
    cout<<"3 - Answers"<<endl;
    cout<<"4 - Correct Answer"<<endl;
    cout<<" >>>>> ";
    cin>>inputInt;
    switch(inputInt){
      case 0:
      exit("Going back to menu");
      break;
      case 1:
      inputString("Rename question: ", &q.questionName);
      tmp->q.questionName = q.questionName;
      inputString("Edit answer 1: ", &q.a.a1);
      tmp->q.a.a1 = q.a.a1;
      inputString("Edit answer 1: ", &q.a.a2);
      tmp->q.a.a2 = q.a.a2;
      inputString("Edit answer 1: ", &q.a.a3);
      tmp->q.a.a3 = q.a.a3;
      inputString("Enter the correct answer: ", &q.correctAns);
      tmp->q.correctAns = q.correctAns;
      success = true;
      break;
      case 2:
      inputString("Rename question: ", &q.questionName);
      tmp->q.questionName = q.questionName;
      success = true;
      break;
      case 3: 
      inputString("Edit answer 1: ", &q.a.a1);
      tmp->q.a.a1 = q.a.a1;
      inputString("Edit answer 1: ", &q.a.a2);
      tmp->q.a.a2 = q.a.a2;
      inputString("Edit answer 1: ", &q.a.a3);
      tmp->q.a.a3 = q.a.a3;
      success = true;
      break;
      case 4:
      inputString("Enter the correct answer: ", &q.correctAns);
      tmp->q.correctAns = q.correctAns;
      success = true;
      break;
      default:
      invalidOpt();
      break;
    }
  }else if(ls->head == NULL || tmp == NULL){
    cout<<"No such question in the list - Press any key to try again"<<endl;
    _getch();
    editQuestion(ls);
  }
  if(success){
    cout<<"The question now looks like >>>>> "<<endl;
    cout << tmp->q.questionIndex << " - " << tmp->q.questionName << endl;
    cout << "a. " << tmp->q.a.a1 << endl;
    cout << "b. " << tmp->q.a.a2 << endl;
    cout << "c. " << tmp->q.a.a3 << endl << endl;
    _getch();
  }
}

void displayQuestion(List *ls) {
  Element *tmp;
  tmp = ls->head;
  while (tmp != NULL) {
    cout << tmp->q.questionIndex << " - " << tmp->q.questionName << endl;
    cout << "a. " << tmp->q.a.a1 << endl;
    cout << "b. " << tmp->q.a.a2 << endl;
    cout << "c. " << tmp->q.a.a3 << endl << endl;
    tmp = tmp->next;
  }
}

void CSQuestion(List *ls) {
  AddQuestion(ls, "10", 10,
              "What year was the first computer virus created in?", "1993",
              "1965", "1986", "c"); // 1986
  AddQuestion(ls, "11", 11, "One megabyte is equal to how many bytes?",
              "1000 byte", "1000000 byte", "1048576 bytes", "c"); // c
  AddQuestion(ls, "12", 12, "Apple was created in which country?", "America",
              "China", "Korea", "a");
  AddQuestion(ls, "13", 13,
              "Which is the correct syntax to output “hello world” in c++?",
              "system.out.println(“Hello world”);", "print(“hello world”);",
              "cout<<”hello world”;", "c");
  AddQuestion(ls, "14", 14, "How do you insert COMMENTs in C++ code?",
              "# this is a comment", "// this is  comment",
              "--this is a comment.", "b");
  AddQuestion(ls, "15", 15, " How do you create a function in c++?",
              "Functionname{}", "Functionname[]", "Functionname()", "c");
  AddQuestion(ls, "16", 16,
              "Which operator is used to add together two values?",
              "The + sign ", "The & sign", "The * sign", "a");
  AddQuestion(ls, "17", 17,
              " Which header file lets us work with input and output objects?",
              "#include <iostream>", "#include <inputstr>", "#include <stream>",
              "a");
  AddQuestion(ls, "18", 18,
              " Which method can be used to find the highest value of x and y?",
              "largest(x,y)", "maximum(x,y)", "max(x,y) ", "c"); // max
  AddQuestion(ls, "19", 19, "Which operator is used to multiply numbers?", "%",
              "/", "*", "c"); // c
  AddQuestion(ls, "20", 20, "What does HTML stand for?",
              "Hyperlinks and Text Markup Language",
              "Hyper Text Markup Language ", "Home Tool Markup Language", "b");
  AddQuestion(ls, "21", 21,
              "Choose the correct HTML element for the largest heading:",
              "<h1>", "<h6>", "<heading>", "a");
  AddQuestion(ls, "22", 22,
              "What is the most common operation system across all devices? "
              "(tablet, phone, laptop)?",
              "ios ", " Google android os", "Htl", "b");
  AddQuestion(ls, "23", 23, "One byte is equal to how many bits?", "5 bits",
              "7 bits", "8 bits", "b"); // c
  AddQuestion(ls, "24", 24,
              "How can you create a variable with the numeric value 5?",
              "num = 5;", "num = 5 int;", "int num = 5", "c");
  AddQuestion(ls, "27", 27, "Which statement is used to stop a loop?", "exit;",
              "break;", "void", "b");
  AddQuestion(ls, "25", 25,
              "How can you create a variable with the floating number 2.8?",
              "num = 2.8 double;", "float num = 2.8;", "num = 2.8 double;",
              "b");
  AddQuestion(
      ls, "26", 26,
      "Which function is often used to output values and print text in c?",
      "printword();", "output();", "printf();", "c");
  AddQuestion(ls, "28", 28, "Which keyword is used to create a structure?",
              "Struct", "Structs", "Structure", "a");
  AddQuestion(ls, "41", 41, "The two kinds of main memory are", "CDs and DVDs",
              "RAM and ROM", "Primary and secondary", "b");
  AddQuestion(ls, "42", 42, " _____ has the shortest access times.",
              "Virtual Memory", "Secondary Memory", "Cache Memory", "c");
  AddQuestion(
      ls, "43", 43,
      "Which parts of the computer were is used for calculating and comparing?",
      "ALU", "Modem", "Control Unit", "a");
  AddQuestion(ls, "44", 44, "The following is not an operating system ______",
              "MS OFFICE", "Window XP", "UNIX", "a");
  AddQuestion(ls, "45", 45, "A computer programmer is a person who _____",
              "sells program", "Use program", "writes program", "c");
  AddQuestion(ls, "46", 46, "The quality of the display is better if _____",
              "Resolution is least", "Resolution the moderate",
              "Resolution is higher", "c");
}

void tmpQuestion(List *ls) {
  AddQuestion(ls, "1", 1,
              "Cambodia academy of digital technology is located in :",
              "Prek Leap ", "Wat Phnom ", "Jomkadoung", "a");
  AddQuestion(ls, "2", 2, "What is the boiling point of water?", " 120 celcius",
              " 100 celcius ", " 95 celcius ", "a");
  AddQuestion(ls, "3", 3, "The coldest continent in the world is.",
              "Antarctica", "Greenland", "Alaska", "a");
  AddQuestion(ls, "4", 4,
              "Techo scholarship provides monthly pay for the scholarship "
              "student, how much does each student receive for generation 8? ",
              "70$", " 80$", "90$", "a");
  AddQuestion(ls, "5", 5, "What is the name of CADT before it was changed? ",
              "NIPTICT", " ITC", "NPIC", "a");
  AddQuestion(ls, "6", 6, "What is the national flower of cambodia?", "Lotus",
              "Wild lilly", "Romdoul", "a");
  AddQuestion(ls, "7", 7, "Which city host the 2002 olympic?", "Beijing",
              "Sydney", "Tokyo", "a"); // it's sydney
  AddQuestion(ls, "8", 8, " Where was tea invented?", "England", "USA", "China",
              "a");
  AddQuestion(ls, "9", 9, "What language does the Cambodian speak?",
              "Cambodese", "Khmer", "Khmeir", "a");

  // AddQuestion(ls, "29" ,29, "What is the largest organ in the human body?",
  // "Skin",
  //             "Muscle", "The veins","a");
  // AddQuestion(ls, "30" ,30, "Which planet is known as the red planet?",
  // "Venus",
  //             "Mercury", "mars","a");
  // AddQuestion(ls, "31" ,31, "How many continents are there in the world?",
  // "6", "7",
  //             "8","b");
  // AddQuestion(ls, "32" ,32, "The periodic table has how many elements?",
  // "90", "110",
  //             "118","c");
  // AddQuestion(ls, "33" ,33, "How many are there in a dozen?", "4", "10",
  // "12","c"); AddQuestion(ls, "34" ,34, "The ocean covers how much of the
  // earth's surface?",
  //             "75%", "70%", "80%","b");
  // AddQuestion(ls, "35" ,35, "What is the largest religious structure in the
  // world?",
  //             "Angkor wat", "Vishnu statue", "Mangal mahadev","a");
  // AddQuestion(ls, "36" ,36, "Which living mammal cannot jump?", "Elephant",
  // "Giraffe",
  //             "Pig","a");
  // AddQuestion(ls, "37" ,37, "What is the population of Cambodia in 2022?",
  //             "15 millions", "16 millions", "17 millions","c");
  // AddQuestion(ls, "38" ,38, "Who is the Prime Minister of Cambodia?", "Hun
  // Sen",
  //             "Elon Musk", "Pov SomNoun","a");
  // AddQuestion(ls, "39" ,39, "Cadt is an academy specialized in :", "Digital
  // major ",
  //             "Cooking major", "Agriculture major","a");
  // AddQuestion(ls, "40" ,40, "What is the smallest country among the ASEAN
  // country?",
  //             "Singapore", "Brunei", "Malaysia","b");

  // AddQuestion(ls, "47" ,47, "What is the largest planet in  the solar
  // system?",
  //             "Jupiter", "Saturn", "Neptune","a");
  // AddQuestion(ls, "48" ,48, "Which country won the fifa world cup 2018?",
  // "Croatia",
  //             "France", "Brazil","a");
  // AddQuestion(ls, "49" ,49, " What is the longest river in the world?",
  //             "The nile river", "The yangtze river", "The amazon river","a");
  // AddQuestion(ls, "50" ,50, "What is the highest mountain in the world?",
  //             "Mount Kanchenjunga", "Mount K2", "Mount Everest","c");
}

void createQuestions(List *ls) {
  tmpQuestion(ls);
  // CSQuestion(ls);
}

void adminOpt(List *ls, loginList *loginLs) {
  adminMenu();
  cout << "Enter your choice >>>>> ";
  cin >> inputInt;
  if (inputInt) {
    switch (inputInt) {
    case 1:
      system("cls");
      // cout<<"How many questions do you want to add? "; cin>>input;
      addMoreQ(ls);
      // back to menu
      adminOpt(ls, loginLs);
      break;
    case 2:
      // Display q
      system("cls");
      displayQuestion(ls);
      _getch();
      adminOpt(ls, loginLs);
      break;
    case 3:
      // Remove q
      system("cls");
      deleteQuestion(ls);
      adminOpt(ls, loginLs);
      break;
    case 4:
      // Edit q
      system("cls");
      editQuestion(ls);
      // _getch();
      adminOpt(ls, loginLs);
      // cout << "WIP" << endl;
      break;
    case 5:
      system("cls");
      // View Test take login info
      cout << "WIP" << endl;
      break;
    case 6:
      system("cls");
      // View Test Taker history
      cout << "WIP" << endl;
      break;
    case 7:
      // Exit
      exit("Back to menu");
      _sleep(500);
      break;
    default:
      system("cls");
      cout << "Invalid option" << endl;
      break;
    }
  }
}

int finalScore;

void addAccuracy(List *ls, string questionName, string a1, string a2, string a3,
                 string inputAns, string correctAns) {
  Element *e = new Element();
  e->q.questionName = questionName;
  e->q.a.a1 = a1;
  e->q.a.a2 = a2;
  e->q.a.a3 = a3;
  e->q.correctAns = correctAns;
  e->q.studentAns = inputAns;
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

void displayAccuracy(List *ls) {
  Element *tmp = ls->tail;
  int count = 1;
  finalScore = 0;
  while (tmp != NULL) {
    cout << count << "- " << tmp->q.questionName << endl;
    cout << "a. " << tmp->q.a.a1 << endl;
    cout << "b. " << tmp->q.a.a2 << endl;
    cout << "c. " << tmp->q.a.a3 << endl;
    cout << endl << "Your input answer: " << tmp->q.studentAns << endl;
    cout << "Correct answer: " << tmp->q.correctAns << endl;
    if (tmp->q.studentAns == tmp->q.correctAns) {
      cout << "Correct" << endl;
      cout << "----------------------------------------------------------------"
              "-------------------"
           << endl;
      finalScore += 3;
    } else {
      cout << "Incorrect" << endl;
      finalScore -= 1;
      cout << "----------------------------------------------------------------"
              "-------------------"
           << endl;
    }
    tmp = tmp->previous;
    count++;
    cout << endl;
  }
  cout << "Your final point is: " << finalScore << endl;
  cout << " -----------------------------";
}

void takeTest(List *ls, List *ls1) {
  Element *tmp = ls->tail;
  while (tmp != NULL) {
    for (int i = 0; i < 10; i++) {
      system("cls");
    Top:
      cout << i + 1 << "- " << tmp->q.questionName << endl;
      cout << "a. " << tmp->q.a.a1 << endl;
      cout << "b. " << tmp->q.a.a2 << endl;
      cout << "c. " << tmp->q.a.a3 << endl;
      cout << "Enter answer: ";
      fflush(stdin);
      getline(cin, inputStr);

      if (inputStr == "a" || inputStr == "b" || inputStr == "c") {
        addAccuracy(ls1, tmp->q.questionName, tmp->q.a.a1, tmp->q.a.a2,
                    tmp->q.a.a3, inputStr, tmp->q.correctAns);
        cout << endl;
      } else {
        cout << "Invalid Input, please enter again" << endl;
        cout << " -----------------------------";
        getch();
        goto Top;
      }
      tmp = tmp->previous;
    }
    break;
  }

  getch();
}

void studentOpt(List *ls) {
  List *accuracyList;
  accuracyList = createEmptyList();
Menu:
  system("cls");
  studentMenu();
  cin >> inputInt;
  switch (inputInt) {
  case 1:
    system("cls");
    takeTest(ls, accuracyList);
    goto Menu;
  case 2:
    system("cls");
    displayAccuracy(accuracyList);
    break;
  default:
    break;
  }
}