/*
 * Label.h
 *
 *  Created on: 14/05/2014
 *      Author: Daniel
 */

#ifndef LABEL_H_
#define LABEL_H_

#include <vector>
#include <string>

/**
 *  This class represents a label/category of e-mails.
 */
class Label {
private:
	std::string title;
	std::vector<std::string> keywords;
public:
	Label(std::string title);
	bool addKey(std::string key);
	bool deleteKey(std::string key);
	bool replaceKey(std::string key, std::string newkeytitle);
	void setTitle(std::string title);
};

#endif /* LABEL_H_ */
