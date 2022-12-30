#include "dataStructure.h"

string loginEmailFile = "loginEmail.txt";
string loginNameFile = "loginName.txt";
string passwordFile = "password.dat";

// Global Variable to sign in
struct personInfo {
  string username;
  string email;
  string password;
  string rpassword;
} l;

//Global Variable to login

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

// Read login
void readLoginInfo(loginList *ls) {
  fstream emailFile;
  fstream nameFile;
  fstream passFile;
  emailFile.open(loginEmailFile, ios::in);
  nameFile.open(loginNameFile, ios::in);
  passFile.open(passwordFile, ios::in | ios::binary);

  if (!emailFile.is_open() || !nameFile.is_open() || !passFile.is_open()) {
    cout << "Can't open File" << endl;
  }
  if (emailFile.peek() == EOF || nameFile.peek() == EOF ||
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

// checked
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
void Login(loginList *ls) {
  string inputStr;
  Node *tmp;
  fstream scoreFile;
  scoreFile.open(ScoreList, ios::app);
  bool exist = true;
	system("cls");
  inputString("Enter username: ", &inputStr);
  tmp = findUserPos(ls, inputStr);
	if (tmp == NULL) {
    exist = false;
	}
	inputString("Enter password: ", &l.password);
	if(exist){
		if ((inputStr == tmp->l.username || inputStr == tmp->l.email) &&
        (l.password == tmp->l.password)) {
      cout << "Welcome back " << tmp->l.username << endl;
      scoreFile<<"\n"<<tmp->l.username<<"\t";
			_sleep(500);
    } else {
      cout << "Incorrect Credentials" << endl;
			cout<<"Please try again"<<endl;
			_sleep(500);
      countLog++;
      if (countLog == 3) {
        for (int i = 3; i >= 0; i--) {
          system("cls");
          cout << "Too many failed attempts" << endl;
          cout << "Returning to menu in " << i << endl;
          _sleep(1000);
        }
        	return;
      }
				Login(ls);
    }
	}
	else if(!exist){
		cout << "User Doesn't seem to exist";
		_getch();
		Login(ls);
	}
  } 

// checked

void saveLoginFile(loginList *ls) {
  fstream emailFile;
  fstream nameFile;
  fstream passFile;
  emailFile.open(loginEmailFile, ios::out);
  nameFile.open(loginNameFile, ios::out);
  passFile.open(passwordFile, ios::binary | ios::out);

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
