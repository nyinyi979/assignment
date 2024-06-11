#include<iostream>
#include<iomanip>
#include<conio.h>
using namespace std;
struct Book{
	string name;
	string author;
	string producedDate;
	string rating;
	int counts;
};
class Books{
	int currentCount = 0;
	Book books[100];
	public:
		Books(){
			cout<<"Library management system initialized";
		}
		void addABook(){
			string n_,pd,a,r;
			int c;
			cout<<"Enter the name of the book : ";
			cin>>n_;
			cout<<"Enter the name of the author : ";
			cin>>a;
			cout<<"Enter the produced date of the book : ";
			cin>>pd;
			cout<<"Enter rating : ";
			cin>>r;
			cout<<"Enter total counts : ";
			cin>>c;
			books[currentCount] = {n_,a,pd,r,c};
			currentCount++;
			cout<<"\nSuccessfully added, Press Enter to Contine";
			getch();
			system("cls");
		}
		void showBooks(){
			cout<<setw(5)<<"No"<<setw(20)<<"Name"<<setw(20)<<"Author"<<setw(20)
				<<"Produced date"<<setw(10)<<"Rating"<<setw(10)<<"Counts"<<endl;
			for(int i=0; i<currentCount; i++){
				cout<<setw(5)<<i+1<<setw(20)<<books[i].name<<setw(20)<<books[i].author<<setw(20)
					<<books[i].producedDate<<setw(10)<<books[i].rating<<setw(10)<<books[i].counts<<endl;
			}
			cout<<"\n";
			getch();
		 	system("cls");
		}
		void searchABook(){
			string bName;
			float found = false;
			cout<<"Enter book name to search : ";
			cin>>bName;
			for(int i=0; i<currentCount; i++){
				if(books[i].name == bName&& found == false){
					cout<<"\nName of the book :"<<books[i].name;
					cout<<"\nAuthor of the book :"<<books[i].author;
					cout<<"\nProduced date of the book : "<<books[i].producedDate;
					cout<<"\nRating of the book : "<<books[i].rating;
					cout<<"\nTotal book counts : "<<books[i].counts;
					found = true;
				}
				else i++;
			}
			getch();
			system("cls");
		}
		void updateABook(){
			cout<<setw(5)<<"No"<<setw(20)<<"Name"<<setw(20)<<"Author"<<setw(20)
				<<"Produced date"<<setw(10)<<"Rating"<<setw(10)<<"Counts"<<endl;
			for(int i=0; i<currentCount; i++){
				cout<<setw(5)<<i+1<<setw(20)<<books[i].name<<setw(20)<<books[i].author<<setw(20)
					<<books[i].producedDate<<setw(10)<<books[i].rating<<setw(10)<<books[i].counts<<endl;
			}
			updateLabel:
			int index;char y_n;
			cout<<"\nEnter the number : ";
			cin>>index;
			index--;
			if(index < 0 || index > currentCount) {
				cout<<"\nBook not found";
				getch();
				system("cls");
				goto updateLabel;
			}
			cout<<"You are about to edit this book "<<books[index].name<<" \n";
			cout<<"Are you sure?(y/n) :";
			cin>>y_n;
			if(y_n=='y'){
				cout<<"\nEnter the name of the book(\""<<books[index].name<<"\") : ";
				cin>>books[index].name;
				cout<<"Enter the name of the author(\""<<books[index].author<<"\") : ";
				cin>>books[index].author;
				cout<<"Enter the produced date of the book(\""<<books[index].producedDate<<"\") : ";
				cin>>books[index].producedDate;
				cout<<"Enter the rating of the books(\""<<books[index].rating<<"\") : ";
				cin>>books[index].rating;
				cout<<"Enter the counts of the books(\""<<books[index].counts<<"\") : ";
				cin>>books[index].counts;
			}
			cout<<"\n\nUpdated book:";
			cout<<"\nName of the book : "<<books[index].name;
			cout<<"\nAuthor of the book : "<<books[index].author;
			cout<<"\nProduced date of the book : "<<books[index].producedDate;
			cout<<"\nRating of the book : "<<books[index].rating;
			cout<<"\nCounts of the book : "<<books[index].counts;
			cout<<"\n\nClick Enter to Continue...";
			getch();
			system("cls");
		}
		void deleteABook(){
			cout<<setw(5)<<"No"<<setw(20)<<"Name"<<setw(20)<<"Author"<<setw(20)
				<<"Produced date"<<setw(10)<<"Rating"<<setw(10)<<"Counts"<<endl;
			for(int i=0; i<currentCount; i++){
				cout<<setw(5)<<i+1<<setw(20)<<books[i].name<<setw(20)<<books[i].author<<setw(20)
					<<books[i].producedDate<<setw(10)<<books[i].rating<<setw(10)<<books[i].counts<<endl;
			}
			deleteLabel:
			int index;
			char y_n;
			cout<<"Enter index to delete : ";
			cin>>index;
			index--;
			if(index < 0 || index > currentCount) {
				cout<<"\nBook not found";
				getch();
				system("cls");
				goto deleteLabel;
			}
			cout<<"You are about to edit this book "<<books[index].name<<" \n";
			cout<<"Are you sure?(y/n) :";
			cin>>y_n;
			if(y_n=='y') {
				for(int i=index; i<currentCount; i++){
					books[i] = books[i+1];
				}
				currentCount--;
				cout<<"Deleted";
			}
			else {
				cout<<"Not deleted";
			}
			getch();
			system("cls");
		}
};
int main(){
	int menuCode = 0;
	Books bookSystem;
	menulabel:
	cout<<"Welcome from books management system\n\n";
	cout<<"1. Show all the books\n\n";
	cout<<"2. Add a new book\n\n";
	cout<<"3. Update a book\n\n";
	cout<<"0. Quit the system\n\n";
	cin>>menuCode; 
	system("cls");
	if(menuCode == 0) {
		cout<<"Thank you for using the system!";
		return 0;
	}
	else if(menuCode == 1) bookSystem.showBooks();
	else if(menuCode == 2) bookSystem.addABook();
	else if(menuCode == 3) bookSystem.updateABook();
	goto menulabel;
}
