#include "menu.h"
// Files for questions
string indexList = "index.txt";
string questionList = "question.txt";
string answerList = "normalAns.txt";
string correctAnsList = "correctAns.txt";
// Files for students
string ScoreList = "sb.txt";
// Files for admin
string actHistory = "history.txt";
// Files for Login
string loginEmailFile = "loginEmail.txt";
string loginNameFile = "loginName.txt";
string passwordFile = "password.txt";
// for adding questions
struct question {
  int questionIndex;
  string questionName;
  string correctAns;
  string normalAns;
  int studentScore;
  string studentName;
  double duration;
  string date;
} q;

struct personInfo {
  string username;
  string email;
  string password;
  string rpassword;
} l;

// Global variable
// string studentName;

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
    double duration;
    string date;
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

void insert(loginList *ls, string password, string email, string name) {
  Node *e;
  e = new Node;
  e->l.email = email;
  e->l.username = name;
  e->l.password = password;
  e->previous = ls->head;
  e->next = NULL;
  if (ls->n == 0) {
    ls->head = e;
    ls->tail = e;
  } else {
    ls->tail->next = e;
    e->previous = ls->tail;
    ls->tail = e;
    ls->tail->next = NULL;
  }
  ls->n = ls->n + 1;
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
    ls->head = e;
    ls->tail = e;
  } else if (ls->n != 0) {
    ls->tail->next = e;
    e->previous = ls->tail;
    ls->tail = e;
    ls->tail->next = NULL;
  }
  ls->n++;
}

int checkExistUser(loginList *ls, string email, string userName, bool found) {
  Node *tmp;
  tmp = ls->head;
  while (tmp != NULL) {
    if (tmp->l.email == email || tmp->l.username == userName) {
      found = true;
      return found;
    }
    tmp = tmp->next;
  }
  return found;
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

void displayFromFile() {
  fstream scoreFile;
  scoreFile.open(ScoreList, ios::in);
  if (scoreFile.peek() == EOF) {
    cout << "No One has taken the Test yet" << endl;
  }
  if (scoreFile.is_open()) {
    string tp;
    while (getline(scoreFile, tp)) {
      cout << tp << "\n";
    }
    scoreFile.close();
  }
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

void saveLoginFile(loginList *ls) {
  fstream emailFile;
  fstream nameFile;
  fstream passFile;
  emailFile.open(loginEmailFile, ios::out);
  nameFile.open(loginNameFile, ios::out);
  passFile.open(passwordFile, ios::out);

  Node *tmp;
  tmp = ls->head;

  while (tmp != NULL) {
    emailFile << tmp->l.email << endl;
    nameFile << tmp->l.username << endl;
    passFile << tmp->l.password << endl;
    tmp = tmp->next;
  }

  emailFile.close();
  nameFile.close();
  passFile.close();
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
  fstream act;
  act.open(actHistory, ios::app);
  auto start = std::chrono::system_clock::now();
  std::time_t start_time = std::chrono::system_clock::to_time_t(start);
  int inputInt;
  bool found = false;
  bool done = false;
  cout << "Enter question index (0 - back to menu): ";
  cin >> q.questionIndex;
  if (q.questionIndex == 0) {
    if(countQ == 0){
      act << "\nDate: " << ctime(&start_time)
          << "Admin has used"
            " Add More questions function - nothing changed in the list"
          << endl;
    }
    returnMenu("Going back to menu");
    act.close();
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
    confirmChange("Save changes? (1 - Yes), "
                  "(0 - No) >>>>> ",
                  ls, &done);
    if (done) {
      countQ++;
      AddQuestion(ls, q.questionIndex, q.questionName, q.normalAns,
                  q.correctAns);
      saveFile(ls);
      cout << "<<< Successfully added the question to the list >>>" << endl;
      cout << "Add more (1 - Continue), (0 - Finish)? >>>>> ";
      cin >> inputInt;
      if (inputInt == 0) {
        act << "\nDate: " << ctime(&start_time) << "Admin has added " << countQ
            << " question(s) to the list." << endl;
        cout << "<<< You have added " << countQ
             << " question(s) to the list >>>" << endl;
        Sleep(500);
      } else if (inputInt == 1) {
        addMoreQ(ls);
      } else {
        invalidOpt();
        addMoreQ(ls);
      }
    } else if (!done) {
      cout << "No question added ..." << endl;
      Sleep(500);
      addMoreQ(ls);
    }
  }
  act.close();
}

inline void deleteNode(List *ls, Element *tmp) {
  if (ls->head == NULL || tmp == NULL) {
    return;
  }
  if (ls->head == tmp) {
    ls->head = tmp->next;
  }
  if (tmp->next != NULL) {
    tmp->next->previous = tmp->previous;
  }
  if (tmp->previous != NULL) {
    tmp->previous->next = tmp->next;
  }
  delete tmp;
}

int countD = 0;
inline void deleteQuestion(List *ls) {
  fstream act;
  act.open(actHistory, ios::app);
  auto start = std::chrono::system_clock::now();
  std::time_t start_time = std::chrono::system_clock::to_time_t(start);

  int inputInt;
  bool remove = false;
  Element *e;
  e = ls->head;
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
  if (inputInt == 0 ) {
    if(countD == 0){
    act << "\nDate: " << ctime(&start_time)
        << "Admin has used the "
           "delete function - nothing changed in the list"
        << endl;
    }
    returnMenu("Going back to menu");
    act.close();
    return;
  }
  e = findQuestionPos(ls, inputInt);
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
    if (remove) {
      countD++;
      act << "\nDate: " << ctime(&start_time) << "Admin has deleted "
      << "question "<<inputInt<<" from the list" << endl;
      deleteNode(ls, e);
      saveFile(ls);
      cout << "\nSuccessfully removed question from the list (1 - Continue), "
              "(0 - "
              "Menu) >>>>> ";
      cin >> inputInt;
      if (inputInt == 1) {
        deleteQuestion(ls);
        
      } else if (inputInt == 0) {
        returnMenu("Going back to menu");
        Sleep(500);
      }
    } else if (!remove) {
      cout << "\nQuestion Untouched ..." << endl;
      Sleep(500);
      deleteQuestion(ls);
    } else {
      cout << "Invalid input" << endl;
      Sleep(500);
      deleteQuestion(ls);
    }
  }
  act.close();
}

int countE = 0;
inline void editQuestion(List *ls) {
  fstream act;
  act.open(actHistory, ios::app);
  auto start = std::chrono::system_clock::now();
  std::time_t start_time = std::chrono::system_clock::to_time_t(start);
  int inputInt;
  int input;
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
      Sleep(500);
    }
  }
  cout << "\nWhich question do you wish to edit? (0 - Menu) >>>>> ";
  cin >> inputInt;
  if (inputInt == 0) {
    if(countE == 0){
      act << "\nDate: " << ctime(&start_time)
          << "Admin has used the Edit"
            " Question Function - no question has been edited"
          << endl;
    }
    returnMenu("Going back to Menu");
    act.close();
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
    cin >> input;
    switch (input) {
    case 0:
      returnMenu("Going back to menu");
      break;
    case 1:
      inputString("Rename question: ", &q.questionName);
      inputString("Edit answer: ", &q.normalAns);
      inputString("Enter the correct answer: ", &q.correctAns);
      confirmChange("\nDo you want to save changes? (1 - Yes), (0 - No) >>>>> ",
                    ls, &success);
      if (success) {
        countE++;
        act << "\nDate: " << ctime(&start_time)
            << "Everything of"
               " question "
            << inputInt
            << " has been edited by admin to the "
               "following: "
            << endl;
        act << "Question Name: " << q.questionName << endl;
        act << "Multiple Choices: " << q.normalAns << endl;
        act << "Correct Answer: " << q.correctAns << endl;
        tmp->q.questionName = q.questionName;
        tmp->q.normalAnswer = q.normalAns;
        tmp->q.correctAns = q.correctAns;
        saveFile(ls);
      } else if (!success) {
        cout << "Question is untouched";
        Sleep(500);
        editQuestion(ls);
      }
      break;
    case 2:
      inputString("Rename question: ", &q.questionName);
      fflush(stdin);
      confirmChange("\nDo you want to save changes? (1 - Yes), (0 - No) >>>>> ",
                    ls, &success);
      if (success) {
        countE++;
        act << "\nDate: " << ctime(&start_time)
            << "Admin has "
               "renamed question "
            << inputInt << " to " << q.questionName << endl;
        tmp->q.questionName = q.questionName;
        saveFile(ls);
      } else if (!success) {
        cout << "Question is untouched";
        Sleep(500);
        editQuestion(ls);
      }
      break;
    case 3:
      inputString("Edit answer: ", &q.normalAns);
      confirmChange("\nDo you want to save changes? (1 - Yes), (0 - No) >>>>> ",
                    ls, &success);
      if (success) {
        countE++;
        act << "\nDate: " << ctime(&start_time)
            << "Admin has "
               " edited the answer of question "
            << inputInt << " to " << q.normalAns << endl;
        tmp->q.normalAnswer = q.normalAns;
        saveFile(ls);
      } else if (!success) {
        cout << "Question is untouched";
        Sleep(500);
        editQuestion(ls);
      }
      break;
    case 4:
      inputString("Enter the correct answer: ", &q.correctAns);
      confirmChange("\nDo you want to save changes? (1 - Yes), (0 - No) >>>>> ",
                    ls, &success);
      if (success) {
        countE++;
        act << "\nDate: " << ctime(&start_time)
            << "Admin has changed "
               "the correct answer of question "
            << inputInt << " to " << q.correctAns << endl;
        tmp->q.correctAns = q.correctAns;
        saveFile(ls);
      } else if (!success) {
        cout << "\nQuestion is untouched" << endl;
        Sleep(500);
        editQuestion(ls);
      }
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
    cout << "Edit More questions? (1 - Continue), (0 - Finish) >>>>> ";
    cin >> inputInt;
    if (inputInt == 0) {
      returnMenu("Going back to menu");
    } else if (inputInt == 1) {
      editQuestion(ls);
    } else {
      invalidOpt();
    }
  }
  act.close();
}

inline void displayQuestion(List *ls) {
  Element *tmp;
  tmp = ls->head;
  if (ls->head == NULL) {
    cout << "There is no data in the list" << endl;
  } else {
    while (tmp != NULL) {

      cout << tmp->q.questionIndex << " - " << tmp->q.questionName << endl;
      cout << tmp->q.normalAnswer << endl << endl;
      tmp = tmp->next;
    }
  }
}

void readLoginInfo(loginList *ls) {
  fstream emailFile;
  fstream nameFile;
  fstream passFile;
  emailFile.open(loginEmailFile, ios::in);
  nameFile.open(loginNameFile, ios::in);
  passFile.open(passwordFile, ios::in);

  if (!emailFile.is_open() || !nameFile.is_open() || !passFile.is_open()) {
    cout << "Can't open File" << endl;
  } else if (emailFile.peek() == EOF || nameFile.peek() == EOF ||
             passFile.peek() == EOF) {
    cout << "No one has registered into the system" << endl;
  } else {
    while (getline(passFile, l.password) && getline(emailFile, l.email) &&
           getline(nameFile, l.username)) {
      insert(ls, l.password, l.email, l.username);
    }
  }

  emailFile.close();
  nameFile.close();
  passFile.close();
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
  if (!indexFile.is_open() || !questionFile.is_open() ||
      !answerFile.is_open() || !correctAnsFile.is_open()) {
    cout << "Can't Open file" << endl;
  } else if (indexFile.peek() == EOF || questionFile.peek() == EOF ||
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
void loginAdmin(bool *adm) {
  string inputUser;
  string inputPass;
  inputString("Enter Username: ", &inputUser);
  inputString("Enter Password: ", &inputPass);
  if ((inputUser == "admin") && (inputPass == "123@admin")) {
    cout << "Welcome to Admin Mode";
    *adm = true;
  } else {
    cout << "Incorrect Password or Username" << endl;
    cout << "Please try again" << endl << endl;
    Sleep(500);
    countAdm++;
    if (countAdm == 3) {
      for (int i = 3; i >= 0; i--) {
        *adm = false;
        system("cls");
        cout << "Too many failed attempts" << endl;
        cout << "Returning to menu in " << i << endl;
        Sleep(1000);
      }
      return;
    }
    loginAdmin(adm);
  }
}

void displayLoginInfo(loginList *ls) {
  Node *tm;
  tm = ls->head;
  if (tm == NULL) {
    cout << "No one has registered into the system yet" << endl;
  }
  while (tm != NULL) {
    cout << tm->l.username << endl;
    cout << tm->l.email << endl;
    cout << tm->l.password << endl << endl;
    tm = tm->next;
  }
}

void displayScore(List *ls) {
  Element *tmp = ls->head;
  if (ls->n == 0) {
    cout << "No one has taken the test yet" << endl;
  }
  while (tmp != NULL) {
    cout << tmp->q.date << "\t" << tmp->q.studentName << "\t"
         << tmp->q.studentScore << "\t" << tmp->q.duration << endl;
    tmp = tmp->next;
  }
}

void addToScoreList(List *ls, string studentName, int studentScore,
                    double duration, string date) {
  Element *e;
  e = new Element;
  e->q.studentName = studentName;
  e->q.studentScore = studentScore;
  e->q.duration = duration;
  e->q.date = date;
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
      scoreFile >> q.date;
      scoreFile >> q.duration;
      scoreFile >> q.studentName;
      scoreFile >> q.studentScore;
      addToScoreList(ls, q.studentName, q.studentScore, q.duration, q.date);
    }
  }
  scoreFile.close();
}

string questionFile = "questionSize.txt";
int readQuestionSize() {
  int questionSize;
  fstream sizeFile;
  sizeFile.open(questionFile, ios::in);
  if (!sizeFile.is_open()) {
    cout << "Can't Open File" << endl;
  } else if (sizeFile.peek() == EOF) {
    cout << "No content in file" << endl;
  } else {
    while (!sizeFile.eof()) {
      sizeFile >> questionSize;
    }
  }
  sizeFile.close();
  return questionSize;
}

void changeQuestionSize(int qSize) {
  fstream sizeFile;
  sizeFile.open(questionFile, ios::out);

  sizeFile << qSize;
  sizeFile.close();
}

void randomQuestion(List *mainList, List *randomQuestionList) {
  Element *tmp = mainList->head;
  int count = 0;
  while (tmp != NULL) {
    tmp = findQuestionPos(mainList, 1 + rand() % mainList->n);
    if (tmp == NULL) {
      continue;
    } else {
      AddQuestion(randomQuestionList, tmp->q.questionIndex, tmp->q.questionName,
                  tmp->q.normalAnswer, tmp->q.correctAns);
      count++;
    }
    if (count == readQuestionSize()) {
      break;
    }
  }
}

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

void signUp(loginList *ls) {
  bool found = false;
  cout << "Please input your information :\n";
  inputString("Enter username: ", &l.username);
  inputString("Enter email: ", &l.email);
  if (checkExistUser(ls, l.email, l.username, found)) {
    cout << "User Already exist" << endl;
    cout << "Please try a different username or email" << endl << endl;
    signUp(ls);
  } else {
  again:
    inputString("Enter Password: ", &l.password);
    inputString("Re-enter Password: ", &l.rpassword);
    if (l.password != l.rpassword) {
      cout << "WRONG PASSWORD !Please input again\n";
      goto again;
    }
    insert(ls, l.rpassword, l.email, l.username);
    cout << l.username << " has successfully registered" << endl;
  }
  saveLoginFile(ls);
}

inline Node *findUserPos(loginList *ls, string inputStr) {
  Node *tmp;
  tmp = ls->head;
  while (tmp != NULL) {
    if (tmp->l.email == inputStr) {
      return tmp;
    } else if (tmp->l.username == inputStr) {
      return tmp;
    } else {
      tmp = tmp->next;
    }
  }

  return NULL;
}

int countLog = 0;
void Login(loginList *ls, string *name, bool *log) {
  string inputStr;
  Node *tmp;
  bool exist = true;
  system("cls");
  inputString("Enter username: ", &inputStr);
  tmp = findUserPos(ls, inputStr);
  if (tmp == NULL) {
    exist = false;
  }
  inputString("Enter password: ", &l.password);
  if (exist) {
    if ((inputStr == tmp->l.username || inputStr == tmp->l.email) &&
        (l.password == tmp->l.password)) {
      cout << "Welcome back " << tmp->l.username << endl;
      *name = tmp->l.username;
      *log = true;
      Sleep(500);
    } else {
      cout << "Incorrect Credentials" << endl;
      cout << "Please try again" << endl;
      Sleep(500);
      countLog++;
      if (countLog == 3) {
        for (int i = 3; i >= 0; i--) {
          system("cls");
          cout << "Too many failed attempts" << endl;
          cout << "Returning to menu in " << i << endl;
          Sleep(1000);
        }
        return;
      }
      Login(ls, name, log);
    }
  } else if (!exist) {
    cout << "User Doesn't seem to exist";
    _getch();
    Login(ls, name, log);
  }
}

int finalScore;
int correctQuestion;
int wrongQuestion;

inline void displayAccuracy(List *ls) {

  Element *tmp = ls->tail;
  int count = 1;
  // welcome();
  while (tmp != NULL) {
    color(6);
    cout << count << "- " << tmp->q.questionName << endl;
    color(14);
    cout << tmp->q.normalAnswer << endl;
    color(11);
    cout << endl << "Your input answer: ";
    color(9);
    cout << tmp->q.studentAns << endl;
    color(11);
    cout << "Correct answer: ";
    color(10);
    cout << tmp->q.correctAns << endl;
    color(11);
    tmp = tmp->previous;
    count++;
    cout << endl;
  }
  color(12);
  cout << "\n\n\n\t\t\t\t\t\t-----------------------------------";
  color(11);
  if (finalScore < 0) {
    cout << "\t\t\t\t\t\tSorry, You failed the test :(";
  } else if (finalScore > 0 && finalScore < 15) {
    cout << "\t\t\t\t\t\tSorry, You failed the test :(" << endl << endl;
    cout << "\t\t\t\t\t\t   ======================" << endl;
    cout << "\t\t\t\t\t\t   ==  Your Score: " << finalScore;
    cout << "  ==" << endl;
    cout << "\t\t\t\t\t\t   ======================" << endl;
  } else if (finalScore >= 15) {
    cout << "\t\t\t\t\t\tYou passed the test :)" << endl << endl;
    cout << "\t\t\t\t\t\t   ======================" << endl;
    cout << "\t\t\t\t\t\t   ==  Your Score: " << finalScore;
    cout << "  ==" << endl;
    cout << "\t\t\t\t\t\t   ======================" << endl;
  }
  color(11);
  cout << "\t\t\t\t\t\tCorrect Question: ";
  color(10);
  cout << correctQuestion << endl << endl;
  color(11);
  cout << "\t\t\t\t\t\tIncorrect Question: ";
  color(12);
  cout << wrongQuestion << endl;
  cout << " -----------------------------";
  cout << endl;
}

void disclaimer() {
  cout << "IMPORTANT NOTES" << endl;
  cout << "1 - This is a general Knowledge Test" << endl;
  cout << "2 - You will doing a total of " << readQuestionSize() << endl;
  cout << "3 - The total score of this quiz is " << readQuestionSize() * 3
       << endl;
  cout << "4 - You will earn 3 pts for each correct answer done" << endl;
  cout << "5 - But for each incorrect question, 1 pt will be deducted from "
          "your score"
       << endl;
  cout << "6 - You have a total of 1 minute to answer all the questions"
       << endl;
  cout << "7 - If you Submit your answers over the time limit, it will not be "
          "saved into"
          " the system"
       << endl;
  cout << "Your Exam Report/History can only be seen once and will not be "
          "printed for you"
          " in a hard copy"
       << endl;
  cout << "Goodluck With Your quiz" << endl;
}

inline void takeTest(List *randomQuestionList, List *accuracyList,
                     loginList *loginls, string *name) {
  fstream scoreFile, act;
  act.open(actHistory, ios::app);
  scoreFile.open(ScoreList, ios::app);
  Element *tmp = randomQuestionList->head;
  auto start = std::chrono::system_clock::now();
  std::time_t start_time = std::chrono::system_clock::to_time_t(start);
  string inputStr;
  finalScore = 0;
  correctQuestion = 0;
  wrongQuestion = 0;
  system("cls");
  disclaimer();
  cout << "Press any Key to start the test" << endl;
  _getch();
  int i = 0;
  while (tmp != NULL) {
  Top:
    system("cls");
    color(9);
    // welcome();
    color(12);
    cout << i + 1 << "- " << tmp->q.questionName << endl;
    color(14);
    cout << tmp->q.normalAnswer << endl;
    color(6);
    inputString("Enter answer(1 to skip & 0 to previous): ", &inputStr);
    color(11);
    if (inputStr == "1") {
      if (i == readQuestionSize()) {
        cout << "You have reached the end of the test...";
        _getch();
      } else {
        tmp = tmp->next;
        i++;
      }
    } else if (inputStr == "0") {
      if (tmp->previous == NULL) {
        cout << "No more previous";
        _getch();
        goto Top;
      } else {
        tmp = tmp->previous;
        i--;
      }
    } else if (inputStr == "a" || inputStr == "b" || inputStr == "c") {
      if (inputStr == tmp->q.correctAns) {
        finalScore += 3;
        correctQuestion++;
      } else {
        finalScore -= 1;
        wrongQuestion++;
      }
      addAccuracy(accuracyList, tmp->q.questionName, tmp->q.normalAnswer,
                  inputStr, tmp->q.correctAns);
      tmp = tmp->next;
      i++;
    } else {
      cout << "\t\t\t\t\t\tInvalid Input, please enter again" << endl;
      cout << "\t\t\t\t\t\t---------------------------------" << endl;
      _getch();
      goto Top;
    }
  }
  act << "\nDate: " << ctime(&start_time);
  act << "User: " << name << " has taken a test" << endl;
  act.close();
  scoreFile << "Test Taker Username: " << name << endl;
  scoreFile << "Score: " << finalScore << endl;
  auto end = std::chrono::system_clock::now();
  std::chrono::duration<double> elapsed_seconds = end - start;

  system("cls");
  if (elapsed_seconds.count() > 60.0) {
    cout << "You are too late to submit" << endl;
  } else {
    cout << "Submit Success";
    Sleep(1000);
  }
  system("cls");
  std::time_t end_time = std::chrono::system_clock::to_time_t(end);
  displayAccuracy(accuracyList);
  std::cout << "Duration: " << elapsed_seconds.count() << "s" << std::endl;
  scoreFile << "Duration: " << elapsed_seconds.count() << " s" << endl;
  scoreFile << "Date: " << ctime(&end_time) << endl;
  scoreFile.close();
  _getch();
}

inline void studentOpt(List *mainList, loginList *loginls) {
  bool log = false;
  string name;
  List *accuracyList;
  accuracyList = createEmptyList();
  List *randomQuestionList;
  randomQuestionList = createEmptyList();
  system("cls");
  randomQuestion(mainList, randomQuestionList);
  Login(loginls, &name, &log);
  if (log) {
    takeTest(randomQuestionList, accuracyList, loginls, &name);
  } else {
    return;
  }
}

void displayHistory() {
  system("cls");
  string tmp;
  fstream act;
  act.open(actHistory, ios::in);
  if (!act.is_open()) {
    cout << "Can't Open File" << endl;
  } else if (act.peek() == EOF) {
    cout << "No content in file" << endl;
  } else {
    while (getline(act, tmp)) {
      cout << tmp << endl;
    }
  }
  act.close();
}

inline void adminOpt(List *ls, loginList *loginLs, List *scoreList) {
  int inputInt;
  fstream act;
  act.open(actHistory, ios::app);
  auto start = std::chrono::system_clock::now();
  std::time_t start_time = std::chrono::system_clock::to_time_t(start);
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
      displayFromFile();
      _getch();
      adminOpt(ls, loginLs, scoreList);
      break;
    case 7:
      int input;
      system("cls");
      cout << "This is the current question size: " << readQuestionSize()
           << endl;
      cout << "How many questions do you want the test taker to complete? (0 - "
              "Menu)>>>>> ";
      cin >> inputInt;
      if (inputInt == 0) {
        returnMenu("Going back to menu");
        adminOpt(ls, loginLs, scoreList);
      }
      cout << "Are you sure to commit changes? (1 - Continue), (0 - Discard)";
      cout << " >>>>> ";
      cin >> input;
      if (input == 1) {
        act << "\nDate: " << ctime(&start_time)
          << "Admin has changed the question size from "<<readQuestionSize()
          <<" to "<<inputInt<< endl;
        changeQuestionSize(inputInt);
        cout << "Questions for the test taker is now: " << readQuestionSize()
             << endl;
        _getch();
      } else if (input == 0) {
        cout << "Questions for the test taker remains the same at: "
             << readQuestionSize() << endl;
        _getch();
      }
      adminOpt(ls, loginLs, scoreList);
      break;
    case 8:
      displayHistory();
      _getch();
      adminOpt(ls, loginLs, scoreList);
      break;
    case 9:
      // Exit
      returnMenu("Back to menu");
      Sleep(500);
      break;
    default:
      system("cls");
      returnMenu("Invalid Option");
      adminOpt(ls, loginLs, scoreList);
      break;
    }
  }
}

void saveScoreToFile(List *ls) {
  fstream ScoreFile;
  ScoreFile.open(ScoreList, ios::out);
  Element *tmp;
  tmp = ls->head;
  while (tmp != NULL) {
    ScoreFile << "\n" << tmp->q.date << "\t";
    ScoreFile << tmp->q.duration << "\t";
    ScoreFile << tmp->q.studentName << "\t";
    ScoreFile << tmp->q.studentScore;
    tmp = tmp->next;
  }
  ScoreFile.close();
}