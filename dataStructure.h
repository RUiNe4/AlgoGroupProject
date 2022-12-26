#include "header.h"
#include "menu.h"
#include "general.h"
// #include <curses.h>
using namespace std;
string indexList = "index.txt";
string questionList = "question.txt";
string answerList = "normalAns.txt";
string correctAnsList = "correctAns.txt";
string ScoreList = "Scoreboard.txt";
// for adding questions
struct question {
  int questionIndex;
  string questionName;
  string correctAns;
  string normalAns;
  int studentScore;
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
    string normalAnswer;
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

inline bool checkQuestionID(List *ls, int questionIndex, bool found) {
  Element *tmp;
  tmp = ls->head;
  while (tmp != NULL) {
    if (tmp->q.questionIndex == questionIndex) {
      found = true;
      return found;
    }
    tmp = tmp->next;
  }
  return found;
}

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
                 string questionName, string normalAns, string correctAns) {
  Element *e;
  e = new Element;
  e->q.questionIndex = questionIndex;
  e->q.questionName = questionName;
  e->q.normalAnswer = normalAns;
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

void saveFile(List *ls){
  fstream indexFile;
  fstream questionFile;
  fstream answerFile;
  fstream correctAnsFile;

  indexFile.open(indexList, ios::out);
  questionFile.open(questionList, ios::out);
  answerFile.open(answerList, ios::out);
  correctAnsFile.open(correctAnsList, ios::out);

  Element *tmp;
  tmp = ls->head;
    while(tmp != NULL){
    indexFile<<tmp->q.questionIndex<<endl;
    questionFile<<tmp->q.questionName<<endl;
    answerFile<<tmp->q.normalAnswer<<endl;
    correctAnsFile<<tmp->q.correctAns<<endl;
    tmp = tmp->next;
    }
  indexFile.close();
  questionFile.close();
  answerFile.close();
  correctAnsFile.close();
}

inline void addMoreQ(List *ls) {
  bool found = false;
  int count = 1;
  while (1) {
    cout<<"Enter question index: ";
    cin>>q.questionIndex;
    if (checkQuestionID(ls, q.questionIndex, found)) {
      cout << "Id already exists" << endl;
      cout << "Please try again" << endl;
      addMoreQ(ls);
    } else {
      inputString("Enter q name: ", &q.questionName);
      inputString("Enter normal answer: ", &q.normalAns);
      inputString("Enter the correct answer: ", &q.correctAns);
    }
    AddQuestion(ls, q.questionIndex, q.questionName, q.normalAns ,q.correctAns);
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

inline void deleteNode(List *ls, Element *tmp, bool *remove) {
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

inline void deleteQuestion(List *ls) {
  bool remove = false;
  Element *e;
  e = ls->head;
  // list empty
  if (ls->head == NULL) {
    cout << "There's no question in the list, maybe add some? (1 - Continue), "
            "(0 - Menu) >>>>> ";
    cin >> inputInt;
    if (inputInt == 1) {
      // addMoreQ(ls);
    } else if (inputInt == 0) {
      return;
    }
  }
  cout << "What question do you want to remove? >>>>> ";
  cin >> inputInt;
  e = findQuestionPos(ls, inputInt);
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

inline void editQuestion(List *ls) {
  Element *tmp;
  bool success = false;
  cout << "Which question do you wish to edit? >>>>> ";
  cin >> inputInt;
  tmp = findQuestionPos(ls, inputInt);
  if(tmp != NULL){
    cout<<"This is the question you have selected "<<endl<<endl;
    cout << tmp->q.questionIndex << " - " << tmp->q.questionName << endl;
    cout << tmp->q.normalAnswer << endl;
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
      inputString("Edit answer 1: ", &q.normalAns);
      tmp->q.normalAnswer = q.normalAns;
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
      inputString("Edit answer 1: ", &q.normalAns);
      tmp->q.normalAnswer = q.normalAns;
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
    editQuestion(ls);
  }
  if(success){
    cout<<"The question now looks like >>>>> "<<endl;
    cout << tmp->q.questionIndex << " - " << tmp->q.questionName << endl;
    cout << tmp->q.normalAnswer << endl;
  }
}

inline void displayQuestion(List *ls) {
  Element *tmp;
  tmp = ls->tail;
  while (tmp != NULL) {
    cout << tmp->q.questionIndex << " - " << tmp->q.questionName << endl;
    cout << tmp->q.normalAnswer << endl;
    cout<< endl;
    tmp = tmp->previous;
  }
  _getch();
}

void createQuestions(List *ls) {  
  fstream indexFile;
  fstream questionFile;
  fstream answerFile;
  fstream correctAnsFile;

  indexFile.open(indexList, ios::in);
  questionFile.open(questionList, ios::in);
  answerFile.open(answerList, ios::in);
  correctAnsFile.open(correctAnsList, ios::in);
  //check if file is empty
  if(!indexFile.is_open() || !questionFile.is_open() || !answerFile.is_open() || !correctAnsFile.is_open()){
    cout<<"Can't Open file"<<endl;
  }
  if(indexFile.peek() == EOF || questionFile.peek() == EOF || answerFile.peek() == EOF || correctAnsFile.peek() == EOF){
    cout<<"No Content in file"<<endl;
  }else{
    while(!indexFile.eof() && getline(questionFile, q.questionName) && getline(answerFile, q.normalAns) && !correctAnsFile.eof()){
      indexFile>>q.questionIndex;
      correctAnsFile>>q.correctAns;
    
      AddQuestion(ls ,q.questionIndex,q.questionName, q.normalAns, q.correctAns);
    }
  
  }
  indexFile.close();
  questionFile.close();
  answerFile.close();
  correctAnsFile.close();
}
inline void adminOpt(List *ls, loginList *loginLs) {
  adminMenu();
  cout << "Enter your choice >>>>> ";
  cin >> inputInt;
  if (inputInt) {
    switch (inputInt) {
    case 1:
      system("cls");
      addMoreQ(ls);
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
      deleteQuestion(ls);
      adminOpt(ls, loginLs);
      break;
    case 4:
      // Edit q
      system("cls");
      editQuestion(ls);
      _getch();
      adminOpt(ls, loginLs);
      // cout << "WIP" << endl;
      break;
    case 5:
      system("cls");
      // View Test taker login info
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

inline void addAccuracy(List *ls, string questionName, string normalAns,
                 string inputAns, string correctAns) {
  Element *e = new Element();
  e->q.questionName = questionName;
  e->q.normalAnswer = normalAns;
  e->q.correctAns = correctAns;
  e->q.studentAns = inputAns;
  e->next = ls->head;
  e->previous = NULL;
  if (ls->n == 0) {
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
  while (tmp != NULL) {
    cout << count << "- " << tmp->q.questionName << endl;
    cout << tmp->q.normalAnswer << endl;
    cout << endl << "Your input answer: " << tmp->q.studentAns << endl;
    cout << "Correct answer: " << tmp->q.correctAns << endl;
    tmp = tmp->previous;
    count++;
    cout << endl;
  }
  cout << " -----------------------------";
  _getch();
}

inline void takeTest(List *ls, List *ls1) {
  Element *tmp = ls->tail;
  finalScore = 0;
  fstream scoreFile;
  scoreFile.open(ScoreList, ios::app);
  while (tmp != NULL) {
    for (int i = 0; i < 10; i++) {
      system("cls");
      Top:
      tmp = findQuestionPos(ls,1 + rand()%ls->n);
      cout << i + 1 << "- " << tmp->q.questionName << endl;
      cout << tmp->q.normalAnswer <<endl;
      cout << "Enter answer: ";
      fflush(stdin);
      getline(cin, inputStr);
      if (inputStr == "a" || inputStr == "b" || inputStr == "c") {
        if (inputStr == tmp->q.correctAns) {
          finalScore += 3;
        } else {
          finalScore -= 1;
        }
        addAccuracy(ls1, tmp->q.questionName, tmp->q.normalAnswer
                    ,inputStr, tmp->q.correctAns);
      } else {
        cout << "Invalid Input, please enter again" << endl;
        cout << " -----------------------------";
        getch();
        goto Top;
      }
      tmp = tmp->previous;
    }
    scoreFile<<"\n"<<finalScore;
    scoreFile.close();
    break;
  }

  _getch();
}

inline void studentOpt(List *ls) {
  List *accuracyList;
  accuracyList = createEmptyList();
  Top:
  system("cls");
  studentMenu();
  cin >> inputInt;
  switch (inputInt) {
  case 1:
    system("cls");
    takeTest(ls, accuracyList);
    goto Top;
    break;
  case 2:
    system("cls");
    displayAccuracy(accuracyList);
    goto Top;
    break;
  case 3:
    testTakerMenu();
    break;
  default:
    cout<<"Invalid Option..";
    goto Top;
    break;
  }
}

void displayScore(List *ls){
  Element *tmp = ls->head;
  while(tmp!=NULL){
    cout<<tmp->q.studentScore<<endl;
    tmp = tmp->next;
  }
}

void addToScoreList(List *ls, int studentScore){
  Element *e;
  e = new Element;
  e->q.studentScore = studentScore;
  if (ls->n == 0){
    e->next = NULL;
    e->previous = NULL;
    ls->head = e;
    ls->tail = e;
  }else if (ls->n != 0){
    e->next = ls->head;
    e->previous = NULL;
    ls->head->previous = e;
    ls->head = e;
  }
  ls->n++;
}

void saveScoreFromFile(List *ls){
  fstream scoreFile;
  scoreFile.open(ScoreList, ios::in);
  Element *tmp = ls->head;
  if(!scoreFile.is_open()){
    cout<<"Can't Open File"<<endl;
  }
  if (scoreFile.peek() == EOF){
    cout<<"No content in File"<< endl;
  }else{
    while(!scoreFile.eof()){
      scoreFile>>q.studentScore;
      addToScoreList(ls, q.studentScore);
    }
  }
  scoreFile.close();
}

void saveScoreToFile(List *ls){
  fstream ScoreFile;
  ScoreFile.open(ScoreList, ios::out);
  Element *tmp;
  tmp = ls->head;
  while(tmp!=NULL){
    ScoreFile<<"\n"<<tmp->q.studentScore;
    tmp = tmp->next;
  }
  ScoreFile.close();
}

void sortList(List *ls){
    Element *current = ls->head, *index = NULL;
    Element *temp;
    int score;
    if(ls->head == NULL){
        return;
    }else{
        while(current!=NULL){
            index = current->next;
            while(index!=NULL){
                if (current->q.studentScore > index->q.studentScore){
                score = current->q.studentScore;
                current->q.studentScore = index->q.studentScore;
                index->q.studentScore   = score;
            }
        index = index->next;
        }
        current = current->next;
      }
    }
}