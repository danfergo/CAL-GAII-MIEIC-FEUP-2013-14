/*
 * MailSystem.h
 *
 *  Created on: 14/05/2014
 *      Author: Daniel
 */

#ifndef MAILSYSTEM_H_
#define MAILSYSTEM_H_

#include "Email.h"
#include "Label.h"


#include <vector>
#include <string>
/**
 * This class encapsulates all the needed functions to manage the Program Mail Manager
 */
class MailSystem {
private:
	/**
	 * this struct associates a frequency to a label
	 */
	typedef struct LabeRelativeFreq{
		  bool operator < (const LabeRelativeFreq & le2) const;
		  Label * label;
		  float freq;
	} LabelEmail;

	/**
	 * vector of labels of the program
	 */
	std::vector<Label> labels;
	/**
	 * vector of emails of the program
	 */
	std::vector<Email> emails;
	/**
	 * constant searchTolerance
	 */
	float searchTolerance;
public:
	/**
	 * default constructor of the class MailSystem
	 */
	MailSystem();

	/**
	 * this method calls the respective method at the class Label
	 * @param filename name/location of the file to read
	 * @return this method returns false in case of failure
	 */
	bool ImportLabelsFile(std::string filename);
	/**
	 * this method calls the respective method at the class Label
	 * @param filename name/location of the file to export to
	 * @return this method returns false in case of failure
	 */
	bool ExportLabelsFile(std::string filename);
	/**
	 * this method calls the respective method at the class Email
	 * @param filename name/location of the file to read
	 * @return this method returns false in case of failure
	 */
	bool ImportEmailsFolder(std::string folderpath);

	/**
	 * this function add a lable to the program
	 * @param label title of the new label
	 * @return this function returns false in case of the label already exists
	 */
	bool addLabel(std::string label);
	/**
	 * this function returns the vector of labels in the program
	 * @return the vector of the labels
	 */
	std::vector<Label> & getLabels();

	/**
	 * this function searchs a label in the program
	 * @returns a pointer to the label found.
	 */
	Label * getLabel(std::string);

	/**
	 * this function returns the vector of emails on the program
	 * @return the vector of the emails
	 */
	std::vector<Email> & getEmails();

	/**
	 * this is method calculates the relative frequency of all words of a label on a e-mail. It uses the Knuth–Morris–Pratt search algorithm
	 * @param label label to calculate the frequency
	 * @param email to search the label on
	 * @return the frequency
	 */
	float calculateRelativeFrequency(const Label & label,const Email & email) const;
	/**
	 * this function assings a label to a email if the diference between the most frequent label and the second one is bigger than the searchtolerance
	 * @param email to assing a label
	 */
	void assingLabelToEmail(Email & email);
	/**
	 * this function assigns , when under conditions, the program labels to the emails.
	 */
	void assingLabelsToEmails();
	/**
	 * this function clears all labels
	 */
	void clearLabels();
	/**
	 * this function clears all e-mails
	 */
	void clearEmails();
	/**
	 * this function clears all data of the program
	 */
	void clearAll();

	/**
	 * this function returns the searchTolerance constant.
	 * @return the search tolerance
	 */
	float getSearchTolerance() const{
		return searchTolerance;
	}

	/**
	 * this function sets the searchTolerance constant
	 * @param st searchTolerance
	 */
	void setSearchTolerance(float st){
		searchTolerance = st;
	}

};

#endif /* MAILSYSTEM_H_ */
