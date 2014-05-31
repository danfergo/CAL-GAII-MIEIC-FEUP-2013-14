/*
 * Email.haaa
 *
 *  Created on: 14/05/2014
 *      Author: Diogo
 */

#ifndef EMAIL_H_
#define EMAIL_H_


#include "Label.h"


#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <cstring>
#include <cctype>
#include <dirent.h>



class Email {
public:

	Email(std::string title, std::string text, std::string date);
	virtual ~Email();
	bool addLabel(Label* label);
	Label* getLabel(Label* label);
	bool clearLabel(Label* label);
	std::string getText() const;
	unsigned int getNWords() const;
	std::string getDate() const;
	static std::vector<Email> importEmailsFolder(std::string dirname);
	Email addDataFromFile(std::string filename);
private:
	std::string title;
	std::string text;
	std::string date;
	unsigned int nWords;
	std::vector<Label *> labels;
	std::vector<Label *>::iterator findLabel(Label* label);
};


#endif /* EMAIL_H_ */
