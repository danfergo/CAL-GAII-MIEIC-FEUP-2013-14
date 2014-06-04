/*
 * Label.cpp
 *
 *  Created on: 14/05/2014
 *      Author: Daniel
 */

#include "Label.h"
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>    // std::find#include <fstream>
Label::Label(std::string t) :
		title(t) {
}

bool Label::addKey(std::string k) {
	std::vector<std::string>::iterator it = find(keywords.begin(),
			keywords.end(), k);
	if (it != keywords.end())
		return false;
	keywords.push_back(k);
	return true;
}

void Label::deleteKey(unsigned i) {
	keywords.erase(keywords.begin()+i);
}


void Label::setTitle(std::string t) {
	title = t;
}

std::string Label::getTitle() const {
	return title;
}

bool Label::operator==(const Label & l) const {
	return l.title == title;
}

std::vector<Label> Label::importLabelsFile(std::string filename)
		throw (FileNotFound) {
	std::string line, word;
	std::stringstream ssline;
	std::ifstream myfile(filename.c_str());
	std::vector<Label> retlabels;
	Label temp1(word);

	bool first;
	if (myfile.is_open()) {
		while (getline(myfile, line)) {

			ssline.str(line);
			first = true;
			while (getline(ssline, word, ' ')) {
				if (first) {
					temp1 = Label(word);
					first = false;
					continue;
				}
				temp1.addKey(word);
			}
			ssline.clear();
			retlabels.push_back(temp1);
		}
		myfile.close();
	} else {
		throw FileNotFound();
	}
	return retlabels;
}

void Label::exportLabelsFile(std::string filename, std::vector<Label> labels) throw(FileNotFound){
	std::ofstream myfile(filename.c_str());
	if (myfile.is_open()) {
		std::vector<std::string> keys;
		for (std::vector<Label>::iterator it = labels.begin();
				it != labels.end(); it++) {
			keys = it->getKeys();
			myfile << it->getTitle();
			for (std::vector<std::string>::iterator itt = keys.begin();
					itt != keys.end(); itt++) {
				myfile << " " << (*itt) ;
			}
			myfile << std::endl;
		}
		myfile.close();
	} else {
		throw FileNotFound();
	}
}

std::vector<std::string> Label::getKeys() const {
	return keywords;
}

