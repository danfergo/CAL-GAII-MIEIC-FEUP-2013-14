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
	std::vector<Label> labels;
	std::vector<Email> emails;
public:
	MailSystem();

	bool ImportLabelsFile(std::string filename);
	bool ExportLabelsFile(std::string filename);
	bool ImportEmailsFolder(std::string folderpath);

	bool addLabel(std::string label);
	std::vector<Label> getLabelList() const;

	Label * getLabel(std::string);

	std::vector<Email> getEmailList() const;

	void clearLabels();
	void clearEmails();
	void clearAll();

};

#endif /* MAILSYSTEM_H_ */
