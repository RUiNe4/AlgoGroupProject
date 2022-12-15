#include <iostream>
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
        cout<<">>>>> Input answer: ";
        cin>>tmp->q.answer;
        cout<<tmp->q.answer<<endl;
        tmp = tmp->previous;
    }
}

void createQuestions(){
    List* ls;
    ls = createEmptyList();
    AddtoList(ls, 1 ,"question :"," answer1: "," answer2: "," answer3: ");

    displayList(ls);
}

int main(){
    createQuestions();
    return 0;
}