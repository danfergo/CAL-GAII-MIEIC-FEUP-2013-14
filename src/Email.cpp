/*
 * Email.cpp
 *
 *  Created on: 14/05/2014
 *      Author: Diogo
 */

#include "Email.h"

Email::Email(std::string title, std::string text, std::string date):title(title), text(text),date(date),label(NULL) {
	nWords = 0;
	bool word = true;
	for(int i = 0; i< text.size(); i++){
		if(isalnum(text[i]) || (text[i] > 128 && text[i] < 154))
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

void Email::setLabel(Label* label){
	this->label = label;
}

Label * Email::getLabel(){
	return label;
}

void Email::clearLabel(){
	label = NULL;
}

std::string Email::getText() const{
	return text;
}

unsigned int Email::getNWords() const{
	return nWords;
}

std::string Email::getDate() const{
	return date;
}

std::vector<Email> Email::importEmailsFolder(std::string dirname){
	std::vector<Email> res;
	std::string filename;
	DIR *dir;
	Email email("","","");
	struct dirent *ent;
	unsigned x;
	std::string fname;
	if ((dir = opendir (dirname.c_str())) != NULL) {
		while ((ent = readdir (dir)) != NULL) {
			fname = ent->d_name;
			x = (((int)fname.size()-4) < 0) ? 0 : (fname.size()-4);
			if(fname.substr(x) == ".txt"){
				filename = dirname + "\\" + ent->d_name;
				res.push_back(email.addDataFromFile(filename));
			}

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
	std::cout << title << "|" << date << "|" << text;
	Email email(title,text,date);
	return email;
}
