/*
 * Email.haaa
 *
 *  Created on: 14/05/2014
 *      Author: Diogo
 */

#ifndef EMAIL_H_
#define EMAIL_H_
#include <dirent.h>
#include "Label.h"
#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <cstring>

class Email {
public:

	Email(std::string title, std::string text, std::string date);
	virtual ~Email();
	bool addLabel(Label* label);
	Label* getLabel(Label* label);
	bool clearLabel(Label* label);
	static std::vector<Email> importEmailsFolder(std::string dirname);
	Email Email::addDataFromFile(std::string filename);
private:
	std::string title;
	std::string text;
	unsigned long date;
	std::vector<Label *> labels;
	std::vector<Label *>::iterator findLabel(Label* label);
};


#endif /* EMAIL_H_ */
