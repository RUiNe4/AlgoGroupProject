#include <iostream>
#include <string>
#include <string.h>
#include <fstream>
#include <iomanip>
#include <conio.h>
#include <stdlib.h>
#include <windows.h>
#include <chrono>
#include <ctime>
// #include <conio.h>
// #include <curse.h>
using namespace std;

void inputString(string msg, string *str){
  cout<<msg;
  fflush(stdin); 
  getline(cin, *str);
}

void color(int color_code){
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(console,color_code);
}