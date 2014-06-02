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
	bool setLabel(Label* label);
	Label* getLabel();
	bool clearLabel();
	std::string getText() const;
	unsigned int getNWords() const;
	std::string getDate() const;
	static std::vector<Email> importEmailsFolder(std::string dirname);
	Email addDataFromFile(std::string filename);
	std::string title;
	std::string text;
	std::string date;
private:
	unsigned int nWords;
	Label * label;
	// std::vector<Label *>::iterator findLabel(Label* label);
};


#endif /* EMAIL_H_ */
