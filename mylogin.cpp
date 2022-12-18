#include<iostream>
#include<fstream>
#include<string.h>
#include <iomanip>
#include<conio.h>
using namespace std;
//structur
string dataOneRow;
struct element{
	string email;
	string fname;
	string lname;
	string password;
	string rpassword;
	element *next;
};
struct list{
	int n;
	element *head;
	element *tail;
};
list *empty(){
	list* ls;
	ls=new list;
	ls->head=NULL;
	ls->tail=NULL;
	ls->n=0;
	return ls;
}
void insert(list* ls,string fname,string lname,string email ,string password){
	element *e;
	e=new element();
	e->email=email;
	e->fname=fname;
	e->lname=lname;
	e->password=password;
	if(ls->n==0){
		ls->head=e;
		ls->tail=e;
	}else{
		ls->tail->next=e;
		ls->tail=e;
	}
	ls->n=ls->n +1;
}
//input
void signUp(string *fname,string *lname,string *email,string *password,string *rpassword){

	cout<<"Please input you information :\n";
	cout<<"FIRST NAME :";cin>>*fname;
	cout<<"LAST NAME:";cin>>*lname;
	cout<<"EMAIL :";cin>>*email;
	cout<<"PASSWORD :";cin>>*password;
	again:
	cout<<"REENTER PASSWORD :";cin>>*rpassword;
	if(*rpassword!=*password){
		cout<<"WRONG PASSWORD !Please input again\n";
		goto again;
	}
}
int checkExistEmailInFile(string email){
    fstream emailf;
    emailf.open("email.txt",ios::in);
    while(emailf.eof()!=true){
        dataOneRow="";
        getline(emailf, dataOneRow);
        if(!dataOneRow.empty()&& email==dataOneRow){
            emailf.close();
            return 0; //email exsit
        }
    }
    emailf.close();
    return 1;
}
int checkExistpassword(string password){
    fstream passf;
    passf.open("password.txt",ios::in);
    while(passf.eof()!=true){
        dataOneRow="";
        getline(passf, dataOneRow);
        if(!dataOneRow.empty()&& password==dataOneRow){
            passf.close();
            return 0; //email exsit
        }
    }
    passf.close();
    return 1;
}
void Login(){
    string email,password;
    cout<<"Email: "; cin>>email;
    cout<<"password:"; cin>>password;
    if(checkExistEmailInFile(email)==0 && checkExistpassword(password)==0){
        cout<<"User exsit"<<endl;
    }else if(checkExistEmailInFile(email)==1 && checkExistpassword(password)==1){
        cout<<"not"<<endl;
    }

}
void display(list* ls){
	element *tm;
	tm=ls->head;
	while(tm!=NULL){
		cout<<tm->fname<<" "<<tm->lname<<endl;
		cout<<tm->email<<endl;
		cout<<tm->password;
		tm=tm->next;
	}
}

void writenameemail(list* ls){
	element *tem;
	element *te;
	string t;
	tem=new element();
	te=new element();
	tem=ls->head;
	te=tem->next;
	fstream file;
	file.open("name.txt",ios::app);
	while(tem->next!=NULL){
		te=tem->next;
		while(tem->next){
			if(tem->fname>te->fname){
				t=tem->fname;
				tem->fname=te->fname;
				te->fname=t;
			}
			tem=tem->next;
		}
	  te=te->next;
	}
		while(tem!=NULL){
			file<<setw(10)<<tem->fname<<setw(5)<<tem->lname<<endl;
			tem=tem->next;
		}
    file.close();
}
void wirteemail(list *ls){
	element *te;
	te=ls->head;
	fstream emailf;
	emailf.open("email.txt",ios::app);
	while(te!=NULL){
		emailf<<te->email;
		te=te->next;
	}
	emailf<<endl;
    emailf.close();

}
void wirtepass(list *ls){
	element *te;
	te=ls->head;
	fstream passf;
	passf.open("password.txt",ios::app);
	while(te!=NULL){
		passf<<te->password;;
		te=te->next;
	}
	passf<<endl;
	passf.close();
}
main(){
	string fname;
	string lname;
	string email ;
	string password;
	string rpassword;
	int opt;
	list* l;
   l=empty();
   cout<<"chose sign up & log in:";cin>>opt;
    if(opt==1){
        signUp(&fname,&lname,&email,&password,&rpassword);
       if(checkExistEmailInFile(email)==0){
        cout<<"User exsit"<<endl;
    }else if(checkExistEmailInFile(email)==1){
        cout<<"not"<<endl;

        insert(l,fname,lname,email,password);
    }
   }else if(opt==2){
        Login();
   }

   display(l);
   writenameemail(l);
   wirteemail(l);
   wirtepass(l);
}
