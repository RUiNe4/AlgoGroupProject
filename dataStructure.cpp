#include <iostream>
#include <curses.h>
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

bool checkQuestionsID(List *ls, int id){
    
    Element *temp;
    bool found = false ;
    
    temp = ls->head;

    while (temp!=NULL) {
        if (temp->q.questionID =id) {
            
           cout<<"\nThis question already existed!\n\n";
           cout<<temp->q.questionID;
            found=true;
            break;
        } else {
            temp = temp->next;
            found= false;
        }
    }
    return found;
}


void displayList(List *ls) {
    Element *tmp;
    tmp = ls->tail;
    while (tmp!=NULL) {
        system("clear");
        cout<<"- "<<tmp->q.questionName<<endl;
        cout<<"a. "<<tmp->q.a.a1<<endl;
        cout<<"b. "<<tmp->q.a.a2<<endl;
        cout<<"c. "<<tmp->q.a.a3<<endl;
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
    AddtoList(ls, 1 ,"Cambodia academy of digital technology is located in :","Prek Leap ","Wat Phnom ","Jomkadoung");
    AddtoList(ls, 2 ,"What is the boiling point of water?"," 120 celcius"," 100 celcius "," 95 celcius ");
    AddtoList(ls, 3, "The coldest continent in the world is.","Antarctica","Greenland","Alaska");
    AddtoList(ls,4,"Techo scholarship provides monthly pay for the scholarship student, how much does each student receive for generation 8? ","70$","b : 80$","90$");
    AddtoList(ls,5,"What is the name of CADT before it was changed? ","NIPTICT","b : ITC","NPIC");
    AddtoList(ls,6,"What is the national flower of cambodia?","Lotus","Wild lilly","Romdoul");
    AddtoList(ls,7,"Which city host the 2002 olympic?","Beijing","Sydney","Tokyo");//it's sydney
    AddtoList(ls,8," Where was tea invented?","England","USA","China");
    AddtoList(ls,9,"What language does the Cambodian speak?","Cambodese","Khmer","Khmeir");
    AddtoList(ls,10,"What year was the first computer virus created in?","1993","1965","1986");//1986
    AddtoList(ls,11,"One megabyte is equal to how many bytes?","1000 byte","1000000 byte","1048576 bytes");//c
    AddtoList(ls,12,"Apple was created in which country?","America","China" ,"Korea");
    AddtoList(ls,13,"Which is the correct syntax to output “hello world” in c++?","system.out.println(“Hello world”);","print(“hello world”);","cout<<”hello world”;");
    AddtoList(ls,14,"How do you insert COMMENTs in C++ code?","# this is a comment","// this is  comment","this is a comment.");
    AddtoList(ls,15," How do you create a function in c++?","Functionname{}","Functionname[]","Functionname()");
    AddtoList(ls,16,"Which operator is used to add together two values?","The + sign ","The & sign","The * sign");
    AddtoList(ls,17," Which header file lets us work with input and output objects?","#include <iostream>","#include <inputstr>","#include <stream>");
    AddtoList(ls,18," Which method can be used to find the highest value of x and y?","largest(x,y)","maximum(x,y)","max(x,y)  ");//max
    AddtoList(ls,19,"Which operator is used to multiply numbers?","%","/","*");//c
    AddtoList(ls,20,"What does HTML stand for?","Hyperlinks and Text Markup Language","Hyper Text Markup Language ","Home Tool Markup Language");
    AddtoList(ls,21,"Choose the correct HTML element for the largest heading:","<h1>","<h6>","<heading>");
    AddtoList(ls,22,"What is the most common operation system across all devices? (tablet, phone, laptop)?","ios "," Google android os","Htl");
    AddtoList(ls,23,"One byte is equal to how many bits?","5 bits","7 bits","8 bits");//c
    AddtoList(ls,24,"How can you create a variable with the numeric value 5?","num = 5;","num = 5 int;","int num = 5");
    AddtoList(ls,27,"Which statement is used to stop a loop?","exit;","break;","void");
    AddtoList(ls,25,"How can you create a variable with the floating number 2.8?","num = 2.8 double;","float num = 2.8;","num = 2.8 double;");
    AddtoList(ls,26,"Which function is often used to output values and print text in c?","printword();","output();","printf();");
    AddtoList(ls,28,"Which keyword is used to create a structure?","Struct","Structs","Structure");
    AddtoList(ls,29,"What is the largest organ in the human body?","Skin","Muscle","The veins");
    AddtoList(ls,30,"Which planet is known as the red planet?","Venus","Mercury","mars");
    AddtoList(ls,31,"How many continents are there in the world?","6","7","8");
    AddtoList(ls,32,"The periodic table has how many elements?","90","110","118");
    AddtoList(ls,33,"How many are there in a dozen?","4","10","12");
    AddtoList(ls,34,"The ocean covers how much of the earth's surface?","75%","70%","80%");
    AddtoList(ls,35,"What is the largest religious structure in the world?","Angkor wat","Vishnu statue","Mangal mahadev");
    AddtoList(ls,36,"Which living mammal cannot jump?","Elephant","Giraffe","Pig");
    AddtoList(ls,37,"What is the population of Cambodia in 2022?","15 millions","16 millions","17 millions");
    AddtoList(ls,38,"Who is the Prime Minister of Cambodia?","Hun Sen","Elon Musk","Pov SomNoun");
    AddtoList(ls,39,"Cadt is an academy specialized in :","Digital major ","Cooking major","Agriculture major");
    AddtoList(ls,40,"What is the smallest country among the ASEAN country?","Singapore","Brunei","Malaysia");
    AddtoList(ls,41,"The two kinds of main memory are","CDs and DVDs","RAM and ROM","Primary and secondary");
    AddtoList(ls,42," _____ has the shortest access times.","Virtual Memory","Secondary Memory","Cache Memory");
    AddtoList(ls,43,"Which parts of the computer were is used for calculating and comparing?","ALU","Modem","Control Unit");
    AddtoList(ls,44,"The following is not an operating system ______","MS OFFICE","Window XP","UNIX");
    AddtoList(ls,45,"A computer programmer is a person who _____","sells program","Use program","writes program");
    AddtoList(ls,46,"The quality of the display is better if _____","Resolution is least","Resolution the moderate","Resolution is higher");
    AddtoList(ls,47,"What is the largest planet in  the solar system?","Jupiter","Saturn","Neptune");
    AddtoList(ls,48,"Which country won the fifa world cup 2018?","Croatia","France","Brazil");
    AddtoList(ls,49," What is the longest river in the world?","The nile river","The yangtze river","The amazon river");
    AddtoList(ls,50,"What is the highest mountain in the world?","Mount Kanchenjunga","Mount K2","Mount Everest");
    

    




    displayList(ls);
}
int main(){
    createQuestions();
    return 0;
}