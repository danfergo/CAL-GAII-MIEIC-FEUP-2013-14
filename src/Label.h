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
	bool deleteKey(unsigned i);
	bool replaceKey(std::string key, std::string newkeytitle);
	void setTitle(std::string title);
	std::string getTitle() const;
	std::vector<std::string> getKeys() const;

	bool operator==(const Label & l) const;

	static std::vector<Label> importLabelsFile(std::string filename) throw(FileNotFound);
	static bool exportLabelsFile(std::string filename, std::vector<Label> labels);
};

#endif /* LABEL_H_ */
