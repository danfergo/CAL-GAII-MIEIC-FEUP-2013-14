/*
 * Email.cpp
 *
 *  Created on: 14/05/2014
 *      Author: Diogo
 */

#include "Email.h"

Email::Email(std::string title, std::string text, std::string date):title(title), text(text),date(date) {}

Email::~Email() {
	// TODO Auto-generated destructor stuba
}

std::vector<Label *>::iterator Email::findLabel(Label* label){
	std::vector<Label *>::iterator it = labels.begin();
	std::vector<Label *>::iterator ite = labels.end();
	for (;it!=ite;it++){
		if(*(*it) == *label) return it;
	}
	return ite;
}

bool Email::addLabel(Label* label){
	std::vector<Label *>::iterator it = findLabel(label);
	if (**it == *label) return false;
	labels.push_back(label);
	return true;
}
Label* Email::getLabel(Label* label){
	std::vector<Label *>::iterator it = findLabel(label);
	if (**it == *label) return label;
	return *it;
}
bool Email::clearLabel(Label* label){
	labels.clear();
	return true;
}

static std::vector<Email> Email::importEmailsFolder(std::string dirname){
	std::vector<Email> res;
	std::string filename;
	DIR *dir;
	struct dirent *ent;
	if ((dir = opendir (dirname.c_str())) != NULL) {
		while ((ent = readdir (dir)) != NULL) {
			//std::cout <<"%s\n" << ent->d_name;
			filename = dirname + "\\" + ent->d_name;
			Email email = addDataFromFile(filename);
			res.push_back(email);
		}
		closedir (dir);
	}
	throw FileNotFound();
}

Email Email::addDataFromFile(std::string filename) {
	//clearData();
	std::string line, title, date, text;
	unsigned state = 0;
	std::ifstream myfile(filename.c_str());

	if (myfile.is_open()) {
		while (getline(myfile, line)) {
			if (line.substr(0, 5) == "Title") {
				state = 1;
			} else if (line.substr(0, 4) == "Date") {
				state = 2;
			} else if (line.substr(0, 4) == "Text") {
				state = 3;
			} else {
				switch(state){
				case 1: //Title
					title = line;
					break;
				case 2: //Date
					date = line;
					break;
				case 3: //Text
					text += line + "\n";
					break;
				}
			}

		}
		myfile.close();
	}
	Email email(title,text,date);
	return email;
}
