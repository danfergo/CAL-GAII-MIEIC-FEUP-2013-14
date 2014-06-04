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
	/**
	 * title represents the title of the label
	 */
	std::string title;
	/**
	 * keywords this vector contents all the words to search in the e-mail
	 */
	std::vector<std::string> keywords;
public:
	/**
	 *Constructor of the class Label
	 *@param title this is the title of the e-mail
	 */
	Label(std::string title);
	/**
	 * This method adds a new keyword to the label
	 * @param key this should be the word to add
	 * @return this function returns false in case the word already exists
	 */
	bool addKey(std::string key);
	/**
	 *This method delets the keyword at the position i in the vector keywords
	 *@param i position of the key in the vector of keywords
	 */
	void deleteKey(unsigned i);

	/**
	 * This method changes the title of the label
	 * @param title the new title to the label
	 */
	void setTitle(std::string title);
	/**
	 * This function returns the title of the label
	 * @return title of the label
	 */
	std::string getTitle() const;
	/**
	 *  this function returns the keywords of the label
	 */
	std::vector<std::string> getKeys() const;

	/**
	 * Operator equals.
	 * @return returs true in case the title of the labels are equal
	 */
	bool operator==(const Label & l) const;

	/**
	 * This function import labels in a text file and returs them
	 * @param filename the location/name of the file to import the labels
	 * @return vector of labels read
	 */
	static std::vector<Label> importLabelsFile(std::string filename) throw(FileNotFound);
	/**
	 * this function exports the lables passed to the the file at filename
	 * @param filename location/lame of the file to export the labels
	 * @param labels vector of labels to export
	 */
	static void exportLabelsFile(std::string filename, std::vector<Label> labels) throw(FileNotFound);
};

#endif /* LABEL_H_ */
