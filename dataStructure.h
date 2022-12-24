#include "header.h"
#include "menu.h"
#include "general.h"
// #include <curses.h>
using namespace std;
string questionList = "question.txt";
// for adding questions
struct question {
  int questionIndex;
  string questionName;
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

inline loginList *createEmptyLoginList() {
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

inline List *createEmptyList() {
  List *ls;
  ls = new List;

  ls->n = 0;
  ls->head = NULL;
  ls->tail = NULL;

  return ls;
}

// inline bool checkQuestionID(List *ls, int questionIndex, bool found) {
//   Element *tmp;
//   tmp = ls->head;
//   while (tmp != NULL) {
//     if (tmp->q.questionIndex == questionID) {
//       found = true;
//       return found;
//     }
//     tmp = tmp->next;
//   }
//   return found;
// }

inline Element *findQuestionPos(List *ls, int index) {

  Element *temp;
  temp = ls->head;
  
  while (temp != NULL) {
    if (temp->q.questionIndex == index) {
      return temp;
    } else {
      temp = temp->next;
    }
  }
  return NULL;
}

inline void AddQuestion(List *ls, int questionIndex,
                 string questionName, string a1, string a2, string a3,
                 string correctAns) {
  Element *e;
  e = new Element;
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

// inline void addMoreQ(List *ls) {
//   // need to write to file
//   bool found = false;
//   int count = 0;
//   while (1) {
//     inputString("Enter q ID: ", &q.questionID);
//     if (checkQuestionID(ls, q.questionID, found)) {
//       cout << "Id already exists" << endl;
//       cout << "Please try again" << endl;
//       addMoreQ(ls);
//     } else {
//       cout << "Enter question index: ";
//       cin >> q.questionIndex;
//       inputString("Enter q name: ", &q.questionName);
//       inputString("Enter q a1: ", &q.a.a1);
//       inputString("Enter q a2: ", &q.a.a2);
//       inputString("Enter q a3: ", &q.a.a3);
//       inputString("Enter the correct answer: ", &q.correctAns);
//     }
//     AddQuestion(ls, q.questionID, q.questionIndex, q.questionName, q.a.a1,
//                 q.a.a2, q.a.a3, q.correctAns);
//     cout << "<<< Successfully added the question to the list >>>" << endl;
//     count++;
//     cout << "Add more (1 - Continue), (0 - Finish)? >>>>> ";
//     cin >> inputInt;
//     if (inputInt == 0) {
//       cout << "<<< You have added " << count << " question(s) to the list >>>"
//            << endl;
//       cout << "Press any key to continue";
//       _getch();
//       break;
//     } else if (inputInt == 1) {
//       addMoreQ(ls);
//     }
//     break;
//   }
// }

// inline void deleteNode(List *ls, Element *tmp, bool *remove) {
//   // list empty or no node
//   if (ls->head == NULL || tmp == NULL) {
//     *remove = false;
//     return;
//   }
//   // head = input element
//   if (ls->head == tmp) {
//     ls->head = tmp->next;
//     *remove = true;
//   }
//   if (tmp->next != NULL) {
//     tmp->next->previous = tmp->previous; // need explanation :/
//     *remove = true;
//   }
//   if (tmp->previous != NULL) {
//     tmp->previous->next = tmp->next; // same shit
//     *remove = true;
//   }
//   delete tmp;
// }

// inline void deleteQuestion(List *ls) {
//   bool remove = false;
//   Element *e;
//   e = ls->head;
//   // list empty
//   if (ls->head == NULL) {
//     cout << "There's no question in the list, maybe add some? (1 - Continue), "
//             "(0 - Menu) >>>>> ";
//     cin >> inputInt;
//     if (inputInt == 1) {
//       addMoreQ(ls);
//     } else if (inputInt == 0) {
//       return;
//     }
//   }
//   cout << "What question do you want to remove? >>>>> ";
//   cin >> inputInt;
//   e = findQuestionPos(ls, inputInt);
//   // no id
//   if (e == NULL) {
//     cout << "The question ID: " << inputStr
//          << " doesn't seem to exist (1 - Continue), (0 - Menu) >>>>> ";
//     cin >> inputInt;
//     if (inputInt == 1) {
//       deleteQuestion(ls);
//     } else if (inputInt == 0) {
//       return;
//     }
//   }
//   deleteNode(ls, e, &remove);
//   if (!remove) {
//     cout << "No such question" << endl;
//   } else if (remove) {
//     cout << "Successfully removed question from the list (1 - Continue), (0 - "
//             "Menu) >>>>> ";
//     cin >> inputInt;
//     if (inputInt == 1) {
//       deleteQuestion(ls);
//     } else if (inputInt == 0) {
//       return;
//     }
//   } else {
//     cout << "Invalid input - ..." << endl;
//     _sleep(500);
//     deleteQuestion(ls);
//   }
// }

// inline void editQuestion(List *ls) {
//   Element *tmp;
//   bool success = false;
//   cout << "Which question do you wish to edit? >>>>> ";
//   cin >> inputInt;
//   tmp = findQuestionPos(ls, inputInt);
//   if(tmp != NULL){
//     cout<<"This is the question you have selected "<<endl<<endl;
//     cout << tmp->q.questionIndex << " - " << tmp->q.questionName << endl;
//     cout << "a. " << tmp->q.a.a1 << endl;
//     cout << "b. " << tmp->q.a.a2 << endl;
//     cout << "c. " << tmp->q.a.a3 << endl << endl;
//     cout<<"Which part do you want to edit? -"<<endl;
//     cout<<"0 - Back to Menu"<<endl;
//     cout<<"1 - Everything"<<endl;
//     cout<<"2 - Question Name"<<endl;
//     cout<<"3 - Answers"<<endl;
//     cout<<"4 - Correct Answer"<<endl;
//     cout<<" >>>>> ";
//     cin>>inputInt;
//     switch(inputInt){
//       case 0:
//       exit("Going back to menu");
//       break;
//       case 1:
//       inputString("Rename question: ", &q.questionName);
//       tmp->q.questionName = q.questionName;
//       inputString("Edit answer 1: ", &q.a.a1);
//       tmp->q.a.a1 = q.a.a1;
//       inputString("Edit answer 1: ", &q.a.a2);
//       tmp->q.a.a2 = q.a.a2;
//       inputString("Edit answer 1: ", &q.a.a3);
//       tmp->q.a.a3 = q.a.a3;
//       inputString("Enter the correct answer: ", &q.correctAns);
//       tmp->q.correctAns = q.correctAns;
//       success = true;
//       break;
//       case 2:
//       inputString("Rename question: ", &q.questionName);
//       tmp->q.questionName = q.questionName;
//       success = true;
//       break;
//       case 3: 
//       inputString("Edit answer 1: ", &q.a.a1);
//       tmp->q.a.a1 = q.a.a1;
//       inputString("Edit answer 1: ", &q.a.a2);
//       tmp->q.a.a2 = q.a.a2;
//       inputString("Edit answer 1: ", &q.a.a3);
//       tmp->q.a.a3 = q.a.a3;
//       success = true;
//       break;
//       case 4:
//       inputString("Enter the correct answer: ", &q.correctAns);
//       tmp->q.correctAns = q.correctAns;
//       success = true;
//       break;
//       default:
//       invalidOpt();
//       break;
//     }
//   }else if(ls->head == NULL || tmp == NULL){
//     cout<<"No such question in the list - Press any key to try again"<<endl;
//     editQuestion(ls);
//   }
//   if(success){
//     cout<<"The question now looks like >>>>> "<<endl;
//     cout << tmp->q.questionIndex << " - " << tmp->q.questionName << endl;
//     cout << "a. " << tmp->q.a.a1 << endl;
//     cout << "b. " << tmp->q.a.a2 << endl;
//     cout << "c. " << tmp->q.a.a3 << endl << endl;
//   }
// }

inline void displayQuestion(List *ls) {
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

inline void createQuestions(List *ls) {  
  fstream question;
  question.open(questionList, ios::in);
  //check if file is empty
  if(!question.is_open()){
    cout<<"Cannot open file"<<endl;
  }
  else if(question.peek() == EOF){
    cout<<"No Content in file"<<endl;
  }else{
    while(!question.eof()){
      
      question>>q.questionIndex;
      question>>q.questionName;
      question>>q.a.a1;
      question>>q.a.a2;
      question>>q.a.a3;
      question>>q.correctAns;
    
      AddQuestion(ls,q.questionIndex,q.questionName, q.a.a1,q.a.a2,q.a.a3,q.correctAns);
    }
  
  }
  question.close();
}
inline void adminOpt(List *ls, loginList *loginLs) {
  adminMenu();
  cout << "Enter your choice >>>>> ";
  cin >> inputInt;
  if (inputInt) {
    switch (inputInt) {
    case 1:
      system("cls");
      // cout<<"How many questions do you want to add? "; cin>>input;
      // addMoreQ(ls);
      // back to menu
      adminOpt(ls, loginLs);
      break;
    case 2:
      // Display q
      system("cls");
      displayQuestion(ls);
      // _getch();
      adminOpt(ls, loginLs);
      break;
    case 3:
      // Remove q
      system("cls");
      // deleteQuestion(ls);
      adminOpt(ls, loginLs);
      break;
    case 4:
      // Edit q
      system("cls");
      // editQuestion(ls);
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
      // _sleep(500);
      break;
    default:
      system("cls");
      cout << "Invalid option" << endl;
      break;
    }
  }
}

int finalScore;

inline void addAccuracy(List *ls, string questionName, string a1, string a2, string a3,
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

inline void displayAccuracy(List *ls) {
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


inline void takeTest(List *ls, List *ls1) {
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
        // getch();
        goto Top;
      }
      tmp = tmp->previous;
    }
    break;
  }

  // _getch();
}

inline void studentOpt(List *ls) {
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

void saveFile(List *ls){
  fstream file;
  file.open(questionList, ios::out);
  Element *tmp;
  tmp = ls->head;
    while(tmp != NULL){
    file<<"\n"<<tmp->q.questionIndex<<endl;
    file<<tmp->q.questionName<<endl;
    file<<tmp->q.a.a1<<endl;
    file<<tmp->q.a.a2<<endl;
    file<<tmp->q.a.a3<<endl;
    file<<tmp->q.correctAns;
    tmp = tmp->next;
    }
  
  file.close();
}


// inline void AddQuestion(List *ls, int questionIndex,
//                  string questionName, string a1, string a2, string a3,
//                  string correctAns) {