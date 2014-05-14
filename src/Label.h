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

class FileNotFound{

};

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
	std::string getTitle() const;

	bool operator==(const Label & l) const;

	static std::vector<Label> importLabelsFile(std::string filename) throw(FileNotFound);
	static void exportLabelsFile(std::string filename) throw(FileNotFound);
};

#endif /* LABEL_H_ */
