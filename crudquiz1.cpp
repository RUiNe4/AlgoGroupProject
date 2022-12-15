#include <iostream>
#include <conio.h>
using namespace std;

struct Element {
    struct question{
        string questionName;
        int questionID;
        struct answer{
            string a1;
            string a2;
            string a3;
        }a;
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

    ls->n=0;
    ls->head=NULL;
    ls->tail=NULL;

    return ls;
}

void AddtoList(List *ls, int questionID, string questionName, string a1,string a2, string a3) {
    Element *e;
    e = new Element;
    
    e->q.questionID = questionID;
    e->q.questionName = questionName;
    e->q.a.a1= a1;
    e->q.a.a2= a2;
    e->q.a.a3= a3;
    e->next = ls->head;
    e->previous= NULL;
    if (ls->n==0) {
        // e->next=NULL;
        ls->head=e;
        ls->tail=e;
    } else if (ls->n!=0) {
        ls->head->previous = e;
        ls->head=e;

    }
    ls->n++;
}

void displayList(List *ls) {
    Element *tmp;
    tmp = ls->tail;
    while (tmp!=NULL) {
        cout<<tmp->q.questionName<<endl;
        cout<<tmp->q.a.a1<<endl;
        cout<<tmp->q.a.a2<<endl;
        cout<<tmp->q.a.a3<<endl;
        cout<<"<<<<<Previous (0)\t\t\t\t\t\tNext (1)>>>>>"<<endl;
        cout<<">>>>> Input answer: ";
        cin>>tmp->q.answer;
        switch(tmp->q.answer){
            case 'a':
            cout<<tmp->q.answer;
            tmp = tmp->previous;
            break;
            case 'b':
            cout<<tmp->q.answer;
            tmp = tmp->previous;
            break;
            case 'c':
            cout<<tmp->q.answer;
            tmp = tmp->previous;
            break;
            case '0':
            if(tmp == NULL){
                cout<<"Cannot go to previous question";
            }else{
                tmp = tmp->next;
            }
            break;
            case '1':
            if(tmp == NULL){
                cout<<"No more next";
            }else{
                tmp = tmp->previous;
            }
        }
    }
}

void createQuestions(){
    List* ls;
    ls = createEmptyList();
    AddtoList(ls, 1 ,"- Cambodia academy of digital technology is located in :"," a: Prek Leap "," b: Wat Phnom "," c: Jomkadoung");
    AddtoList(ls, 2 ,"- What is the boiling point of water?"," a: 120 celcius"," b: 100 celcius "," c: 95 celcius ");
    AddtoList(ls, 3, "- The coldest continent in the world is.","a: Antarctica","b: Greenland","c: Alaska");
    AddtoList(ls,4,"- Techo scholarship provides monthly pay for the scholarship student, how much does each student receive for generation 8? ","a: 70$","b : 80$","c: 90$");
    AddtoList(ls,5,"- What is the name of CADT before it was changed? ","a: NIPTICT","b : ITC","c: NPIC");
    AddtoList(ls,6,"- What is the national flower of cambodia?","a: Lotus","b : Wild lilly","c: Romdoul");
    AddtoList(ls,7,"- Which city host the 2002 olympic?","a: Beijing","b: Sydney","c: Tokyo");//it's sydney
    AddtoList(ls,8,"-  Where was tea invented?","a: England","b: USA","c: China");
    AddtoList(ls,9,"- What language does the Cambodian speak?","a: Cambodese","b: Khmer","c: Khmeir");
    AddtoList(ls,10,"- What year was the first computer virus created in?","a: 1993","b: 1965","c: 1986");//1986
    AddtoList(ls,11,"- One megabyte is equal to how many bytes?","a: 1000 byte","b: 1000000 byte","c: 1048576 bytes");//c
    AddtoList(ls,12,"- Apple was created in which country?","a: America","b: China" ,"c: Korea");
    AddtoList(ls,13,"- Which is the correct syntax to output “hello world” in c++?","a: system.out.println(“Hello world”);","b: print(“hello world”);","c: cout<<”hello world”;");
    AddtoList(ls,14,"- How do you insert COMMENTs in C++ code?","a: # this is a comment","b: // this is  comment","c: - - this is a comment.");
    AddtoList(ls,15,"-  How do you create a function in c++?","a: Functionname{}","b: Functionname[]","c: Functionname()");
    AddtoList(ls,16,"- Which operator is used to add together two values?","a: The + sign ","b: The & sign","c: The * sign");
    AddtoList(ls,17,"-  Which header file lets us work with input and output objects?","a: #include <iostream>","b: #include <inputstr>","c: #include <stream>");
    AddtoList(ls,18,"-  Which method can be used to find the highest value of x and y?","a: largest(x,y)","b: maximum(x,y)","c: max(x,y)  ");//max
    AddtoList(ls,19,"- Which operator is used to multiply numbers?","a: %","b: /","c: *");//c
    AddtoList(ls,20,"- What does HTML stand for?","a: Hyperlinks and Text Markup Language","b: Hyper Text Markup Language ","c: Home Tool Markup Language");
    AddtoList(ls,21,"- Choose the correct HTML element for the largest heading:","a: <h1>","b: <h6>","c: <heading>");
    AddtoList(ls,22,"- What is the most common operation system across all devices? (tablet, phone, laptop)?","a: ios ","b:  Google android os","c: Htl");
    AddtoList(ls,23,"- One byte is equal to how many bits?","a: 5 bits","b: 7 bits","c: 8 bits");//c
    AddtoList(ls,24,"- How can you create a variable with the numeric value 5?","a: num = 5;","b: num = 5 int;","c: int num = 5");
    AddtoList(ls,26,"- Which statement is used to stop a loop?","a: exit;","b: break;","c: void");

    displayList(ls);
}
int main(){
    createQuestions();
    return 0;
}