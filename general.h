#include "header.h"

void inputString(string msg, string *str){
  cout<<msg;
  fflush(stdin); 
  getline(cin, *str);
}
