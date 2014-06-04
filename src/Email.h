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
	/**
	 * Basic constructor of an email
	 * @param title title of the email
	 * @param text text of the email
	 * @param date date of the email
	 */
	Email(std::string title, std::string text, std::string date);
	virtual ~Email();
	/**
	 * this funcion sets the label of the e-mail
	 * @param label to associate with the email
	 */
	void setLabel(Label* label);
	/**
	 * this funcion return the current label associated to this email
	 * @return the label
	 */
	Label* getLabel();
	/**
	 * this function removes (=NULL) the label of the e-mail
	 */
	void clearLabel();
	/**
	 * this function returns the text of the e-mail
	 * @return the text of the email
	 */
	std::string getText() const;
	/**
	 * this function returns the number of words on the text of the e-mail
	 * @return number of words on the text of the e-mail
	 */
	unsigned int getNWords() const;
	/**
	 * this function returns the date of the e-mail
	 * @return date of the e-mail
	 */
	std::string getDate() const;
	/**
	 *this function imports all the e-mails in text files inside one folder
	 *@param dirname location of the folder
	 *@return vector width the read e-mails
	 */
	static std::vector<Email> importEmailsFolder(std::string dirname);
	/**
	 * This function read an e-mail from a file at «filename»
	 * @param filename name/location of the file to import
	 * @return email read
	 */
	Email addDataFromFile(std::string filename);
	/**
	 * title/header of the e-mail
	 */
	std::string title;
	/**
	 * text/body of the e-mail
	 */
	std::string text;
	/**
	 * string containing the date of the e-mail
	 */
	std::string date;
	/**
	 * pointer to the labels assciated to the e-mail.
	 */
	Label * label;
private:
	unsigned int nWords;
};


#endif /* EMAIL_H_ */
