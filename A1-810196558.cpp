#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>
using namespace std;


struct contact { 
	string email;
	string phone;
	string fname;
	string lname;
	int id;
};

void addcontact (vector <contact> &list, int &idnum);
void deletecontact (vector <contact> &list, int idnum);
void searchcontact (vector <contact> list);
void updatecontact (vector <contact> &list, int idnum);


int main () {
	int idnum, tempn = 0, tempid, fflag = 0, dflag = 0;
	string temp;
	string tempnum;
	vector <contact> list;
	fstream file;
	file.open("contacts.csv");
	while (file >> tempid) {
		fflag = 1;
		contact nc;
		nc.id = tempid;
		file >> temp;
		nc.fname = temp;
		file >> temp;
		nc.lname = temp;
		file >> temp;
		nc.email = temp;
		file >> temp;
		nc.phone = temp;
		list.push_back(nc);
	}
	if (!fflag)
		idnum = 0;
	else 
		idnum = list[list.size() - 1].id + 1;
	file.close();
	while (cin >> temp) {
		if (temp == "add") {
			addcontact (list, idnum) ;
		}
		else if (temp == "delete") {
			dflag = 0;
			cin >> temp;
			for (int i = 0 ; i < temp.size() ; i++) {
				if (!isdigit(temp[i])) {
					cout << "Command Failed." << endl;
					dflag = 1;
				}
				}
				if (!dflag) {
			stringstream t (temp);
			t >> tempn;
			deletecontact (list, tempn);
		}
				
		}
		else if (temp == "search") {
			searchcontact(list);
		}
		else if (temp == "update") {
			cin >> temp;
			for (int i = 0 ; i < temp.size() ; i++)
				if (!isdigit(temp[i])) {
					cout << "Command Failed." << endl;
					continue;
				}
				stringstream t (temp);
				t >> tempn;
				updatecontact(list, tempn);
		}
		else
			cout << "Command Failed." << endl;
		

	}
	file.open("contacts.csv", fstream::trunc | fstream::out);
	for (int i = 0 ; i < list.size() ; i++) {
		file << list[i].id << " " << list[i].fname << " " << list[i].lname << " " << list[i].email << " " << list[i].phone << endl;
	}
	file.close();
	return 0;
}

void addcontact (vector <contact> &list, int &idnum) {
	string line;
	string temp;
	contact nc;
	int fstatus = 1, lstatus = 1, estatus = 1, pstatus = 1;
	getline (cin, line);
	stringstream lstream (line);
	while (fstatus != 0 || lstatus != 0 || pstatus != 0 || estatus != 0) {
		if (!(lstream >> temp)) {
			cout << "Command Failed." << endl;
			return ;
		}
		if (temp == "-f") {
			lstream >> temp;
			for (int i = 0 ; i < temp.size() ; i++) {
				if (!isalpha(temp[i])) {
					cout << "Command Failed." << endl;
					return;
				}
			}
			nc.fname = temp;
			fstatus = 0;
		}
		else if (temp == "-l") {
			lstream >> temp;
			for (int i = 0 ; i < temp.size() ; i++) {
				if (!isalpha(temp[i])) {
					cout << "Command Failed." << endl;
					return;
				}
			}
			nc.lname = temp;
			lstatus = 0;
		}
		else if (temp == "-e") {
			lstream >> temp;
			int pos = temp.find_first_of("@");
			if (pos == -1) {
				cout << "Command Failed." << endl;
				return ;
			}
			else {
				if (temp.find_first_of(".",pos+1) == -1 || temp.find_first_of("@",pos+1) != -1 || temp.find_first_of(".",pos+1) == pos+1 || temp.find_first_of(".",pos+1) == temp.size()-1) {
			cout << "Command Failed." << endl;
			return ;
			}
		}
			nc.email = temp;
			estatus = 0;
		}
		else if (temp == "-p") {
			lstream >> temp;
			if (temp.size() != 11 || temp[0] != '0' || temp[1] != '9') {
				cout << "Command Failed." << endl;
				return ;
			}
			for (int i = 0 ; i < temp.size() ; i++) {
				if (!isdigit(temp[i])) {
					cout << "Command Failed." << endl;
					return;
				}
			}
			nc.phone = temp;
			pstatus = 0;
		}
		else {
			cout << "Command Failed." << endl;
			return  ;
		}
	}
	for (int i = 0 ; i < list.size(); i++) {
		if ((nc.fname == list[i].fname && nc.lname == list[i].lname) || nc.phone == list[i].phone || nc.email == list[i].email) {
			cout << "Command Failed." << endl;
			return ;
		}
	}
	nc.id = idnum;
	idnum++;
	list.push_back (nc);
	cout << "Command OK." << endl;
	return ;
}

void deletecontact (vector <contact> &list, int idnum) {
	int counter = 0, flag = 0;
	for (int i = 0 ; i < list.size() ; i++) {
		if (list[i].id == idnum) {
			flag = 1;
			break;
		}
		counter++;
	}
	if (flag) {
		list.erase(list.begin() + counter);
		cout << "Command Ok." << endl;
		return ; 
	}
	else {
		cout << "Command Failed." << endl;
		return ;
	}

}

void searchcontact (vector <contact> list) {
	string temp, line;
	getline(cin,line);
	stringstream lstream (line);
	lstream >> temp;
	for (int i = 0 ; i < list.size() ; i++) {
		if (list[i].fname.find(temp) != -1 ||  list[i].lname.find(temp) != -1 || list[i].phone.find(temp) != -1 || list[i].email.find(temp) != -1)
			cout << list[i].id << " " << list[i].fname << " " << list[i].lname << " " << list[i].email << " " << list[i].phone << endl;
	}
}

void updatecontact (vector <contact> &list, int idnum) {
	string email,fname,lname,phone, line, temp;
	int index = -1,fflag = 0,lflag = 0,eflag = 0,pflag = 0;
	getline (cin, line);
	stringstream lstream (line);
	for (int i = 0 ; i < list.size() ; i++) {
		if (list[i].id == idnum) {
			index = i;
			break;
		}
	}
	if (index == -1) {
		cout << "Command Failed." << endl;
		return;
	}
	if (!(lstream >> temp)) {
			cout << "Command Failed." << endl;
			return ;
		}
		do {
		if (temp == "-f") {
			lstream >> temp;
			for (int i = 0 ; i < temp.size() ; i++) {
				if (!isalpha(temp[i])) {
					cout << "Command Failed." << endl;
					return;
				}
			}
			fname = temp;
			fflag = 1;
		}
		else if (temp == "-l") {
			lstream >> temp;
			for (int i = 0 ; i < temp.size() ; i++) {
				if (!isalpha(temp[i])) {
					cout << "Command Failed." << endl;
					return;
				}
			}
			lname = temp;
			lflag = 1;
		}
		else if (temp == "-e") {
			lstream >> temp;
			int pos = temp.find_first_of("@");
			if (pos == -1) {
				cout << "Command Failed." << endl;
				return ;
			}
			else {
				if (temp.find_first_of(".",pos+1) == -1 || temp.find_first_of(".",pos+1) == pos+1 || temp.find_first_of(".",pos+1) == temp.size()-1) {
			cout << "Command Failed." << endl;
			return ;
			}
		}
			email = temp;
			eflag = 1;
		}
		else if (temp == "-p") {
			lstream >> temp;
			for (int i = 0 ; i < temp.size() ; i++) {
				if (!isdigit(temp[i])) {
					cout << "Command Failed." << endl;
					return;
				}
			}
			phone = temp;
			pflag = 1;
		}
		else {
			cout << "Command Failed." << endl;
			return  ;
		}
	} while (lstream >> temp);
	if (!fflag) fname = list[index].fname;
	if (!lflag) lname = list[index].lname;
	if (!pflag) phone = list[index].phone;
	if (!eflag) email = list[index].email;
	for (int i = 0 ; i < list.size(); i++) {
		if ((fname == list[i].fname && lname == list[i].lname) || phone == list[i].phone || email == list[i].email) {
			cout << "Command Failed." << endl;
			return ;
		}
	}
	if (fflag) list[index].fname = fname;
	if (lflag) list[index].lname = lname;
	if (pflag) list[index].phone = phone;
	if (eflag) list[index].email = email;
	cout << "Command OK." << endl;
	return ;
}



