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

class MailSystem {
private:
	typedef struct LabelEmail {
		  bool operator < (const LabelEmail & le2);
		  Email * email;
		  Label * label;
		  float freq;
	} LabelEmail;

	std::vector<Label> labels;
	std::vector<Email> emails;
	unsigned searchTolerance;
public:
	MailSystem();

	bool ImportLabelsFile(std::string filename);
	bool ExportLabelsFile(std::string filename);
	bool ImportEmailsFolder(std::string folderpath);

	bool addLabel(std::string label);
	std::vector<Label> & getLabels();

	Label * getLabel(std::string);

	std::vector<Email> & getEmails();

	float calculateRelativeFrequency(const Label & label,const Email & email) const;
	void assingLabelToEmail(Email & email, unsigned k);

	void clearLabels();
	void clearEmails();
	void clearAll();

};

#endif /* MAILSYSTEM_H_ */
