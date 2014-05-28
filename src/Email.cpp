/*
 * Email.cpp
 *
 *  Created on: 14/05/2014
 *      Author: Diogo
 */

#include "Email.h"

Email::Email(std::string title, std::string text, std::string date):title(title), text(text),date(date) {
	nWords = 0;
	bool word = true;
	for(int i = 0;i<text.size();i++){
		if(isalnum(text[i]))
			word = true;
		else if(word == false)
			continue;
		else {
			word = false;
			nWords++;
		}
	}
}

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

std::string Email::getText() const{
	return text;
}

unsigned int Email::getNWords() const{
	return nWords;
}

std::vector<Email> Email::importEmailsFolder(std::string dirname){
	std::vector<Email> res;
	std::string filename;
	DIR *dir;
	Email email("","","");
	struct dirent *ent;
	if ((dir = opendir (dirname.c_str())) != NULL) {
		while ((ent = readdir (dir)) != NULL) {
			//std::cout <<"%s\n" << ent->d_name;
			filename = dirname + "\\" + ent->d_name;
			email.addDataFromFile(filename);
			res.push_back(email);
		}
		closedir (dir);
	}
	else throw FileNotFound();
	return res;
}

Email Email::addDataFromFile(std::string filename) {
	//clearData();
	std::string line, title, date, text;
	unsigned state = 0;
	std::ifstream myfile(filename.c_str());

	if (myfile.is_open()) {
		while (getline(myfile, line)) {
			if (line.substr(0, 7) == "-Title-") {
				state = 1;
			} else if (line.substr(0, 6) == "-Date-") {
				state = 2;
			} else if (line.substr(0, 6) == "-Text-") {
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
