#include <iostream>
#include <string>

using namespace std;

void inputString(string msg, string *str){
  cout<<msg;
  fflush(stdin); 
  getline(cin, *str);
}
