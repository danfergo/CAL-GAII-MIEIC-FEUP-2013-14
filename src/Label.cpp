/*
 * Label.cpp
 *
 *  Created on: 14/05/2014
 *      Author: Daniel
 */

#include "Label.h"



Label::Label(std::string t):title(t){
};


bool Label::addKey(std::string k){
	std::vector<std::string>::iterator it = find (keywords.begin(), keywords.end(), k);
	if(it!=keywords.end())
		return false;
	keywords.push_back(k);
	return true;
};

bool Label::deleteKey(std::string k){
	std::vector<std::string>::iterator it = find (keywords.begin(), keywords.end(), k);
	if(it!=keywords.end())
		return false;
	keywords.erase(it);
	return true;
};
bool Label::replaceKey(std::string k, std::string nkt){
	std::vector<std::string>::iterator it = find (keywords.begin(), keywords.end(), k);
	if(it!=keywords.end())
		return false;
	keywords.erase(it);
	return addKey(nkt);
};

void Label::setTitle(std::string t):title(t) {
};

