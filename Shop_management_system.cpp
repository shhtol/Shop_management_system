#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>

using namespace std;

class Item {
   
   private:
   int ID;
   string name;
   float price;
   int amount;
   
   
   public:
   void getdata(){
	   cout << "Enter item ID: " << endl;
	   cin >> ID;
	   cout << "Enter item name: " << endl;
	   cin >> name;
	   cout << "Enter item price: " << endl;
	   cin >> price;
	   cout << "Enter amount: " << endl;
	   cin >> amount;
	   cout << endl;
   }		
   void showdata() const {
	   cout << "Item " << ID << "information" << endl;
	   cout << "Name: " << name << endl;
	   cout << "Price: " << price << endl;
	   cout << "Amount: " << amount << endl;
	   cout << endl;
   }	
   int return_id() const{
	   return ID;
   }
   void showTable() const{
	   cout << ID << setw(6) << " " << name << setw(10) << price << setw(4) << amount << setw(4) << endl;
   }
};

class Staff {
	private:
	string s_name;
	int number;
	string position;
	double salary;

	
	
	
	public:
	void getStaff() {
	   cout << "Enter staff name: " << endl;
	   cin >> s_name;
	   cout << "Enter staff number: " << endl;
	   cin >> number;
	   cout << "Enter staff position: " << endl;
	   cin >> position;
	   cout << "Enter staff salary: " << endl;
	   cin >> salary;
	   cout << endl;
	}
	void showStaff() const {
	   cout << "Name: " << s_name << endl;
	   cout << "Number: " << number << endl;
	   cout << "Position: " << position << endl;
	   cout << "Salary: " << salary << endl;
	   cout << endl;
	}
	int return_no() const {
		return number;
	}
	void showStaffTable() const {
		cout << s_name << setw(10) <<  number << setw(5) << position << setw(10) << salary << setw(5) << endl;
	}
};

void addStaff() { //FIXME
	Staff s;
	ofstream outFile;
	outFile.open("staff.txt", ios::binary|ios::app);
	
	s.getStaff();
	outFile.write(reinterpret_cast<char *> (&s), sizeof(Staff));
	outFile.close();
    	cout<<"\n\nData about person was written successfully" << endl;
	cin.ignore();
	cin.get();
}

void changeStaff(int num) { //FIXME
	Staff s;
	bool found = false; 
	fstream File;
	File.open("staff.txt", ios::binary|ios::in|ios::out);
	
	if(!File)
	{
		cout<<"Error! File is not opened. Please, press any key to continue.";
		cin.ignore();
		cin.get();
		return;
	}
	
	while(!File.eof() && found == false) 
	{

		File.read(reinterpret_cast<char *> (&s), sizeof(Staff));
		
		if(s.return_no() == num)
		{
			s.showStaff();
			cout<<"\n\nEnter the information you want to edit in this data" << endl;
			s.getStaff();
		    	int pos=(-1)*static_cast<int>(sizeof(s));
		    	File.seekp(pos,ios::cur); 
		    	File.write(reinterpret_cast<char *> (&s), sizeof(Staff));
		    	cout<<"\n\n\t Infomation was edited successfully";
		    	found = true;
		}
	}
	
	
	File.close();
    	cout<<"\n\nData about person was written successfully" << endl;
		
		
	if(found == false)
		cout<<"\n\n Error! Information was not found!" << endl;
		
	cin.ignore();
	cin.get();
}

void deleteStaff(int num){
	Staff s;;
	ifstream inFile;
	inFile.open("staff.txt",ios::binary);
	
	if(!inFile)
	{
		cout<<"Error! File is not opened. Please, press any key to continue.";
		cin.ignore();
		cin.get();
		return;
	}
	
	ofstream outFile;
	outFile.open("Temp.txt",ios::out);
	
	inFile.seekg(0,ios::beg); 
	
	while(inFile.read(reinterpret_cast<char *> (&s), sizeof(Staff)))
	{
		if(s.return_no() != num)
		{
			outFile.write(reinterpret_cast<char *> (&s), sizeof(Staff));
		}
	}
	
	outFile.close();
	inFile.close();
	
	remove("staff.txt");
	rename("Temp.dat","staff.txt");
	
	cout<<"\n\n\tInformation about person was successfully deleted" << endl;
	
	cin.ignore();
	cin.get();
}

void showStaffTable(){
	Staff s;
	ifstream inFile;
	inFile.open("staff.txt",ios::binary);
	
	if(!inFile)
	{
		cout<<"Error! File is not opened. Please, press any key to continue." << endl;
		cin.ignore();
		cin.get();
		return;
	}
	
	cout<<"\n\n\n\t\tSTAFF TABLE\n\n" << endl;
	cout<<"##########################################################\n";
	cout<<"Name      Number     Position     Salary"<<endl;
	cout<<"##########################################################\n";
	while(inFile.read(reinterpret_cast<char *> (&s), sizeof(Staff)))
	{
		s.showStaffTable();
		
	}
	
	inFile.close();
	cin.ignore();
	cin.get();
}

void searchStaff(int num) {
	Staff s;
	ifstream inFile;
	inFile.open("staff.txt",ios::binary);
	
	if(!inFile)
	{
		cout<<"Error! File is not opened. Please, press any key to continue." << endl;
		cin.ignore();
		cin.get();
		return;
	}
	
	bool found = false; 
	
	while(inFile.read(reinterpret_cast<char *> (&s), sizeof(Staff)))
	{
		if(s.return_no() == num)
		{
	  		 s.showStaff();
			 found = true;
		}
	}
	
	inFile.close();
	
	if(found == false)
		cout << "\n\nInformation does not exist" << endl;
		
	cin.ignore();
	cin.get();
}
void menu();
void staff () {
	int n;
	int num;
	cout << "################################################" << endl;
	cout << "\t STAFF MANAGEMENT MENU " << endl;
	cout << "################################################" << endl;
	cout << "\n 1. ADD PERSON" << endl;
	cout << "2. CHANGE PERSON" << endl;
	cout << "3. DELETE PERSON" << endl;
	cout << "4. SHOW STAFF TABLE" << endl;
	cout << "5. SEARCH PERSON" << endl;
	cout << "6. BACK TO MAIN MENU" << endl;
	cout << "\nChoose your option (1-6): ";
	cin >> n;
	switch(n){
		case 1: addStaff();
				break;
		case 2: cout << "Enter the number: " << endl;;
	            cin >> num;
				changeStaff(num);
				break;
		case 3: cout << "Enter the number: " << endl;;
	            cin >> num;
				deleteStaff(num);
				break;
		case 4: showStaffTable(); //FIXME
				break;
		case 5: cout << "Enter the number: " << endl;;
	            cin >> num;
				searchStaff(num);
				break;
		case 6: menu();
				break;
		default: staff();
	}
	
	
}

void addItem() { //FIXME
	Item i;
	ofstream outFile;
	outFile.open("item.txt", ios::binary|ios::app);
	
	i.getdata();
	outFile.write(reinterpret_cast<char *> (&i), sizeof(Item));
	outFile.close();
    	cout<<"\n\nData about item was written successfully" << endl;
	cin.ignore();
	cin.get();
}

void changeItem(int id) { //FIXME
	Item i;
	bool found = false; 
	fstream File;
	File.open("item.txt", ios::binary|ios::in|ios::out);
	
	if(!File)
	{
		cout<<"Error! File is not opened. Please, press any key to continue.";
		cin.ignore();
		cin.get();
		return;
	}
	
	while(!File.eof() && found == false) 
	{

		File.read(reinterpret_cast<char *> (&i), sizeof(Item));
		
		if(i.return_id() == id)
		{
			i.showdata();
			cout<<"\n\nEnter the information you want to edit in this data" << endl;
			i.getdata();
		    	int pos=(-1)*static_cast<int>(sizeof(i));
		    	File.seekp(pos,ios::cur); 
		    	File.write(reinterpret_cast<char *> (&i), sizeof(Item));
		    	cout<<"\n\n\t Infomation was edited successfully";
		    	found = true;
		}
	}
	
	
	File.close();
    	cout<<"\n\nData about item was written successfully" << endl;
		
		
	if(found == false)
		cout<<"\n\n Error! Information was not found!" << endl;
		
	cin.ignore();
	cin.get();
}

void deleteItem(int id){
	Item i;
	ifstream inFile;
	inFile.open("item.txt",ios::binary);
	
	if(!inFile)
	{
		cout<<"Error! File is not opened. Please, press any key to continue.";
		cin.ignore();
		cin.get();
		return;
	}
	
	ofstream outFile;
	outFile.open("Temp.txt",ios::out);
	
	inFile.seekg(0,ios::beg); 
	
	while(inFile.read(reinterpret_cast<char *> (&i), sizeof(Item)))
	{
		if(i.return_id() != id)
		{
			outFile.write(reinterpret_cast<char *> (&i), sizeof(Item));
		}
	}
	
	outFile.close();
	inFile.close();
	
	remove("item.txt");
	rename("Temp.dat","item.txt");
	
	cout<<"\n\n\tInformation about item was successfully deleted" << endl;
	
	cin.ignore();
	cin.get();
}

void showItemTable(){
	Item i;
	ifstream inFile;
	inFile.open("item.txt",ios::binary);
	
	if(!inFile)
	{
		cout<<"Error! File is not opened. Please, press any key to continue." << endl;
		cin.ignore();
		cin.get();
		return;
	}
	
	cout<<"\n\n\n\t\tAVAILABLE ITEMS\n\n" << endl;
	cout<<"##########################################################\n";
	cout<<"ID      Name        Price     Amount"<<endl;
	cout<<"##########################################################\n";
	while(inFile.read(reinterpret_cast<char *> (&i), sizeof(Item)))
	{
		i.showTable();
		
	}
	
	inFile.close();
	cin.ignore();
	cin.get();
}

void searchItem(int id) {
	Item i;
	ifstream inFile;
	inFile.open("item.txt",ios::binary);
	
	if(!inFile)
	{
		cout<<"Error! File is not opened. Please, press any key to continue." << endl;
		cin.ignore();
		cin.get();
		return;
	}
	
	bool found = false; 
	
	while(inFile.read(reinterpret_cast<char *> (&i), sizeof(Item)))
	{
		if(i.return_id() == id)
		{
	  		 i.showdata();
			 found = true;
		}
	}
	
	inFile.close();
	
	if(found == false)
		cout << "\n\nInformation does not exist" << endl;
		
	cin.ignore();
	cin.get();
}
void item () {
	int n;
	int id;
	cout << "################################################" << endl;
	cout << "\t ITEM MANAGEMENT MENU " << endl;
	cout << "################################################" << endl;
	cout << "\n 1. ADD ITEM" << endl;
	cout << "2. CHANGE ITEM" << endl;
	cout << "3. DELETE ITEM" << endl;
	cout << "4. SHOW ITEM TABLE" << endl;
	cout << "5. SEARCH ITEM" << endl;
	cout << "6. BACK TO MAIN MENU" << endl;
	cout << "\nChoose your option (1-6): ";
	cin >> n;
	switch(n){
		case 1: addItem();
				break;
		case 2: cout << "Enter the id: " << endl;;
	            cin >> id;
				changeItem(id);
				break;
		case 3: cout << "Enter the id: " << endl;;
	            cin >> id;
				deleteItem(id);
				break;
		case 4: showItemTable(); //FIXME
				break;
		case 5: cout << "Enter the id: " << endl;;
	            cin >> id;
				searchItem(id);
				break;
		case 6: menu();
				break;
		default: item();
	}
	
	
}
void entry();
void menu () {
	int n;
	cout << "################################################" << endl;
	cout << "\t MAIN MENU " << endl;
	cout << "################################################" << endl;
	cout << "\n 1. ITEM MANAGMENT" << endl;
	cout << "2. STAFF MANAGEMENT" << endl;
	cout << "3. BACK TO MAIN MENU" << endl;
	cout << "\nChoose your option (1-3): ";
	cin >> n;
	switch(n){
		case 1: item(); //FIXME
				break;
		case 2: staff(); //FIXME
				break;
		case 3: entry();
				break;
		default: menu();
		
	}
}

void entry () {
	int n;
	cout << "################################################" << endl;
	cout << "\t WELCOME TO SHOP MANAGEMENT SYSTEM " << endl;
	cout << "################################################" << endl;
	cout << "\n 1. MAIN MENU" << endl;
	cout << " 2. EXIT" << endl;
	cout << "\nChoose your option (1, 2): ";
	cin >> n;
	switch(n){
		case 1: menu();
				break;
		case 2: exit(0);
		default: entry();
		
	}

}
int main () {
	entry();
	return 0;
}
