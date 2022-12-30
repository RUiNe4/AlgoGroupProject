#include "general.h"
#include "header.h"
#include "menu.h"

string indexList = "index.txt";
string questionList = "question.txt";
string answerList = "normalAns.txt";
string correctAnsList = "correctAns.txt";
string ScoreList = "sb.txt";
// for adding questions
struct question {
  int questionIndex;
  string questionName;
  string correctAns;
  string normalAns;
  int studentScore;
  string studentName;
} q;

// Global variable
string studentName;

struct Node {
  struct personInfo {
    string email;
    string username;
    string password;
    string rpassword;
  } l;
  Node *next, *previous;
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
    string studentName;
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

inline void AddQuestion(List *ls, int questionIndex, string questionName,
                        string normalAns, string correctAns) {
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

void saveFile(List *ls) {
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
  while (tmp != NULL) {
    indexFile << tmp->q.questionIndex << endl;
    questionFile << tmp->q.questionName << endl;
    answerFile << tmp->q.normalAnswer << endl;
    correctAnsFile << tmp->q.correctAns << endl;
    tmp = tmp->next;
  }
  indexFile.close();
  questionFile.close();
  answerFile.close();
  correctAnsFile.close();
}

bool confirmChange(string msg, List *ls, bool *remove) {
  int input;
  cout << msg;
  cin >> input;
  if (input == 0) {
    *remove = false;
    return *remove;
  } else if (input == 1) {
    *remove = true;
    return *remove;
  } else {
    return -1;
  }
}

int countQ = 0;
inline void addMoreQ(List *ls) {
  int inputInt;
  bool found = false;
  bool done = false;
  // while (!done) {
    cout << "Enter question index (0 - back to menu): ";
    cin >> q.questionIndex;
    if (q.questionIndex == 0) {
      exit("Going back to menu");
      return;
    }
    if (checkQuestionID(ls, q.questionIndex, found)) {
      cout << "\nId already exists" << endl;
      cout << "Please try again" << endl << endl;
      addMoreQ(ls);
    } else {
        inputString("Enter q name: ", &q.questionName);
        inputString("Enter normal answer: ", &q.normalAns);
        inputString("Enter the correct answer: ", &q.correctAns);
        confirmChange("Save changes? (1 - Yes), (0 - No) >>>>> ", ls, &done);
        cout<<"Done: "<<done<<endl;
        if(done){
        countQ++;
        AddQuestion(ls, q.questionIndex, q.questionName, q.normalAns,
                    q.correctAns);
        saveFile(ls);
        cout << "<<< Successfully added the question to the list >>>" << endl;
        cout << "Add more (1 - Continue), (0 - Finish)? >>>>> ";
        cin >> inputInt;
        if (inputInt == 0) {
          cout << "<<< You have added " << countQ << " question(s) to the list >>>"
              << endl;
          _sleep(500);
          // add Loading animation
        } else if (inputInt == 1) {
          addMoreQ(ls);
        } else{
          invalidOpt();
          addMoreQ(ls);
        }
        }else if(!done){
          cout<<"No question added ..."<<endl;
          _sleep(500);
          addMoreQ(ls);
        }
    }
  //   break;
  // }
}

inline void deleteNode(List *ls, Element *tmp) {
  // list empty or no node
  if (ls->head == NULL || tmp == NULL) {
    return;
  }
  // head = input element
  if (ls->head == tmp) {
    ls->head = tmp->next;
  }
  if (tmp->next != NULL) {
    tmp->next->previous = tmp->previous; // need explanation :/
  }
  if (tmp->previous != NULL) {
    tmp->previous->next = tmp->next; // same shit
  }
  delete tmp;
}

inline void deleteQuestion(List *ls) {
  int inputInt;
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
  cout << "\nWhat question do you want to remove? (0 - Back to Menu) >>>>> ";
  cin >> inputInt;
  if (inputInt == 0) {
    exit("Going back to menu");
    return;
  }
  e = findQuestionPos(ls, inputInt);
  // no id
  if (e == NULL) {
    cout << "\nThe question ID: " << inputInt << " doesn't seem to exist :/"
         << endl;
    cout << "Press any key to try again" << endl;
    _getch();
    deleteQuestion(ls);
  } else {
    cout << "\nThis is the question you have selected: " << endl << endl;
    cout << e->q.questionIndex << " - " << e->q.questionName << endl;
    cout << e->q.normalAnswer << endl;
    confirmChange("\nAre you sure to delete this question from the list? (1 - "
                  "Yes), (0 - No) >>>>> ",
                  ls, &remove);
    cout << "Remove: " << remove << endl;
    if (remove) {
      deleteNode(ls, e);
      saveFile(ls);
      cout << "\nSuccessfully removed question from the list (1 - Continue), "
              "(0 - "
              "Menu) >>>>> ";
      cin >> inputInt;
      if (inputInt == 1) {
        deleteQuestion(ls);
      } else if (inputInt == 0) {
        return;
      }
    } else if (!remove) {
      cout << "\nQuestion Untouched ..." << endl;
      _sleep(500);
      deleteQuestion(ls);
    } else {
      cout << "Invalid input" << endl;
      _sleep(500);
      deleteQuestion(ls);
    }
  }
}

inline void editQuestion(List *ls) {
  int inputInt;
  Element *tmp;
  bool success = false;

  if (ls->head == NULL) {
    cout << "There is no question to edit" << endl;
    cout << "Maybe add some (1 - add question), (0 - Menu) ? >>>>> ";
    cin >> inputInt;
    if (inputInt == 1) {
      addMoreQ(ls);
    } else if (inputInt == 0) {
      cout << "Going back to menu - Press any key to continue" << endl;
      _sleep(500);
    }
  } 
    cout << "\nWhich question do you wish to edit? (0 - Menu) >>>>> ";
    cin >> inputInt;
    if(inputInt == 0){
      exit("Going back to Menu");
      return;
    }
    tmp = findQuestionPos(ls, inputInt);
    
    if (tmp == NULL) {
      cout << "\nThat question doesn't seem to exist :/" << endl;
      cout << "Press any key to try again" << endl;
      _getch();
      editQuestion(ls);
    } else {
      cout << "\nThis is the question you have selected " << endl << endl;
      cout << tmp->q.questionIndex << " - " << tmp->q.questionName << endl;
      cout << tmp->q.normalAnswer << endl;
      cout << "\nWhich part do you want to edit? -" << endl;
      cout << "0 - Back to Menu" << endl;
      cout << "1 - Everything" << endl;
      cout << "2 - Question Name" << endl;
      cout << "3 - Answers" << endl;
      cout << "4 - Correct Answer" << endl;
      cout << " >>>>> ";
      cin >> inputInt;
      switch (inputInt) {
      case 0:
        exit("Going back to menu");
        break;
      case 1:
        inputString("Rename question: ", &q.questionName);
        inputString("Edit answer: ", &q.normalAns);
        inputString("Enter the correct answer: ", &q.correctAns);
        confirmChange("\nDo you want to save changes? (1 - Yes), (0 - No) >>>>> ",
                      ls, &success);
        if (success) {
          tmp->q.questionName = q.questionName;
          tmp->q.normalAnswer = q.normalAns;
          tmp->q.correctAns = q.correctAns;
          saveFile(ls);
        } else if (!success) {
          cout << "Question is untouched";
          _sleep(500);
          editQuestion(ls);
        }
        // success = true;
        break;
      case 2:
        inputString("Rename question: ", &q.questionName);
        confirmChange("\nDo you want to save changes? (1 - Yes), (0 - No) >>>>> ",
                      ls, &success);
        if (success) {
          tmp->q.questionName = q.questionName;
          saveFile(ls);
        } else if (!success) {
          cout << "Question is untouched";
          _sleep(500);
          editQuestion(ls);
        }
        // success = true;
        break;
      case 3:
        inputString("Edit answer: ", &q.normalAns);
        confirmChange("\nDo you want to save changes? (1 - Yes), (0 - No) >>>>> ",
                      ls, &success);
        if (success) {
          tmp->q.normalAnswer = q.normalAns;
          saveFile(ls);
        } else if (!success) {
          cout << "Question is untouched";
          _sleep(500);
          editQuestion(ls);
        }
        // success = true;
        break;
      case 4:
        inputString("Enter the correct answer: ", &q.correctAns);
        confirmChange("\nDo you want to save changes? (1 - Yes), (0 - No) >>>>> ",
                      ls, &success);
        if (success) {
          tmp->q.correctAns = q.correctAns;
          saveFile(ls);
        } else if (!success) {
          cout << "\nQuestion is untouched"<<endl;
          _sleep(500);
          editQuestion(ls);
        }
        // success = true;
        break;
      default:
        invalidOpt();
        break;
      }
    }
  
  if (success) {
    cout << "The question now looks like >>>>> " << endl;
    cout << tmp->q.questionIndex << " - " << tmp->q.questionName << endl;
    cout << tmp->q.normalAnswer << endl;
    _getch();
  }
}

inline void displayQuestion(List *ls) {

  Element *tmp;
  tmp = ls->tail;
  if (ls->head == NULL) {
    cout << "There is no data in the list" << endl;
  } else {
    while (tmp != NULL) {

      cout << tmp->q.questionIndex << " - " << tmp->q.questionName << endl;
      cout << tmp->q.normalAnswer << endl << endl;
      tmp = tmp->previous;
    }
  }
}

void readQuestionFromFile(List *ls) {
  fstream indexFile;
  fstream questionFile;
  fstream answerFile;
  fstream correctAnsFile;

  indexFile.open(indexList, ios::in);
  questionFile.open(questionList, ios::in);
  answerFile.open(answerList, ios::in);
  correctAnsFile.open(correctAnsList, ios::in);
  // check if file is empty
  if (!indexFile.is_open() || !questionFile.is_open() ||
      !answerFile.is_open() || !correctAnsFile.is_open()) {
    cout << "Can't Open file" << endl;
  }
  if (indexFile.peek() == EOF || questionFile.peek() == EOF ||
      answerFile.peek() == EOF || correctAnsFile.peek() == EOF) {
    cout << "No Content in file" << endl;
  } else {
    while (!indexFile.eof() && getline(questionFile, q.questionName) &&
           getline(answerFile, q.normalAns) && !correctAnsFile.eof()) {
      indexFile >> q.questionIndex;
      correctAnsFile >> q.correctAns;

      AddQuestion(ls, q.questionIndex, q.questionName, q.normalAns,
                  q.correctAns);
    }
  }
  indexFile.close();
  questionFile.close();
  answerFile.close();
  correctAnsFile.close();
}

int countAdm = 0;
void loginAdmin() {
  string inputUser;
  string inputPass;
  inputString("Enter Username: ", &inputUser);
  inputString("Enter Password: ", &inputPass);
  if ((inputUser == "admin") && (inputPass == "123@admin")) {
    cout << "Welcome to Admin Mode";
  } else {
    cout << "Incorrect Password or Username" << endl;
    cout << "Please try again" << endl << endl;
    _sleep(500);
    countAdm++;
    if (countAdm == 3) {
      for (int i = 3; i >= 0; i--) {
        system("cls");
        cout << "Too many failed attempts" << endl;
        cout << "Returning to menu in " << i << endl;
        _sleep(1000);
      }
      return;
    }
    loginAdmin();
  }
}

void displayLoginInfo(loginList *ls) {
  Node *tm;
  tm = ls->head;
  while (tm != NULL) {
    cout << tm->l.username << endl;
    cout << tm->l.email << endl;
    cout << tm->l.password << endl<<endl;
    tm = tm->next;
  }
}

void displayScore(List *ls) {
  Element *tmp = ls->head;
  if (ls->n == 0) {
    cout << "No one has taken the test yet" << endl;
  }
  while (tmp != NULL) {
    cout << tmp->q.studentName << "\t" << tmp->q.studentScore << endl;
    tmp = tmp->next;
  }
}

void addToScoreList(List *ls, string studentName, int studentScore) {
  Element *e;
  e = new Element;
  e->q.studentName = studentName;
  e->q.studentScore = studentScore;
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

void sortList(List *ls) {
  Element *current = ls->head, *index = NULL;
  Element *temp;
  string name;
  int score;
  if (ls->head == NULL) {
    return;
  } else {
    while (current != NULL) {
      index = current->next;
      while (index != NULL) {
        if (current->q.studentScore < index->q.studentScore) {
          name = current->q.studentName;
          score = current->q.studentScore;
          current->q.studentScore = index->q.studentScore;
          current->q.studentName = index->q.studentName;
          index->q.studentScore = score;
          index->q.studentName = name;
        }
        index = index->next;
      }
      current = current->next;
    }
  }
}

void saveScoreFromFile(List *ls) {
  fstream scoreFile;
  scoreFile.open(ScoreList, ios::in);
  Element *tmp = ls->head;
  if (!scoreFile.is_open()) {
    cout << "Can't Open File" << endl;
  }
  if (scoreFile.peek() == EOF) {
    cout << "No content in File" << endl;
  } else {
    while (!scoreFile.eof()) {
      scoreFile >> q.studentName;
      scoreFile >> q.studentScore;
      addToScoreList(ls, q.studentName, q.studentScore);
    }
  }
  scoreFile.close();
}

void saveScoreToFile(List *ls) {
  fstream ScoreFile;
  ScoreFile.open(ScoreList, ios::out);
  Element *tmp;
  tmp = ls->head;
  while (tmp != NULL) {
    ScoreFile << "\n" << tmp->q.studentName << "\t";
    ScoreFile << tmp->q.studentScore;
    tmp = tmp->next;
  }
  ScoreFile.close();
}

inline void adminOpt(List *ls, loginList *loginLs, List *scoreList) {
  int inputInt;

  system("cls");

  adminMenu();
  cout << "Enter your choice >>>>> ";
  cin >> inputInt;
  if (inputInt) {
    switch (inputInt) {
    case 1:
      // Add q
      system("cls");
      addMoreQ(ls);
      adminOpt(ls, loginLs, scoreList);
      break;
    case 2:
      // Display q
      system("cls");
      displayQuestion(ls);
      _getch();
      adminOpt(ls, loginLs, scoreList);
      break;
    case 3:
      // Remove q
      system("cls");
      deleteQuestion(ls);
      adminOpt(ls, loginLs, scoreList);
      break;
    case 4:
      // Edit q
      system("cls");
      editQuestion(ls);
      // _getch();
      adminOpt(ls, loginLs, scoreList);
      break;
    case 5:
      // View Test taker login info
      system("cls");
      displayLoginInfo(loginLs);
      _getch();
      adminOpt(ls, loginLs, scoreList);
      break;
    case 6:
      system("cls");
      saveScoreFromFile(scoreList);
      sortList(scoreList);
      displayScore(scoreList);
      saveScoreToFile(scoreList);
      _getch();
      adminOpt(ls, loginLs, scoreList);
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

inline void takeTest(List *mainList, List *accuracyList) {
  Element *tmp;
  tmp = mainList->head;
  fstream scoreFile;
  scoreFile.open(ScoreList, ios::app);
  string inputStr;
  // int i = 0;
  finalScore = 0;
  int i = 0;
  while (i < 10) {
    // Problem pel display jom index delete, stop program
    tmp = findQuestionPos(mainList, 1 + rand() % mainList->n);
    system("cls");
  Top:
    cout << i + 1 << "- " << tmp->q.questionName << endl;
    cout << tmp->q.normalAnswer << endl;
    inputString("Enter answer: ", &inputStr);
    if (inputStr == "a" || inputStr == "b" || inputStr == "c") {
      if (inputStr == tmp->q.correctAns) {
        finalScore += 3;
      } else {
        finalScore -= 1;
      }
      addAccuracy(accuracyList, tmp->q.questionName, tmp->q.normalAnswer,
                  inputStr, tmp->q.correctAns);
    } else {
      cout << "Invalid Input, please enter again" << endl;
      cout << " -----------------------------";
      getch();
      goto Top;
    }
    tmp = tmp->next;

    i++;
  }
  if (finalScore < 0) {
    cout << "Sorry, You failed the test.";
  } else if (finalScore > 0 && finalScore < 15) {
    cout << "Sorry, You failed the test" << endl;
    cout << "Your Score: " << finalScore;
  } else if (finalScore >= 15) {
    cout << "You pass the test" << endl;
    cout << "Your Score: " << finalScore;
  }
  scoreFile << finalScore;
  scoreFile.close();
  _getch();
}

inline void studentOpt(List *mainList) {
  List *accuracyList;
  accuracyList = createEmptyList();
  int inputInt;
Top:
  system("cls");
  studentMenu();
  cin >> inputInt;
  switch (inputInt) {
  case 1:
    system("cls");
    takeTest(mainList, accuracyList);
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
    cout << "Invalid Option..";
    goto Top;
    break;
  }
}
