/*
 * MailSystem.cpp
 *
 *  Created on: 14/05/2014
 *      Author: Daniel
 */

#include "MailSystem.h"
#include <algorithm>    // std::find
#include <sstream>

MailSystem::MailSystem(){};

bool MailSystem::ImportLabelsFile(std::string filename){
	std::vector<Label > v;
	try{
		v = Label::importLabelsFile(filename);
		labels.insert(labels.end(), v.begin(), v.end());
		return true;
	}catch(FileNotFound & e){
		return false;
	}
}
bool MailSystem::ExportLabelsFile(std::string filename){
	return Label::exportLabelsFile(filename,labels);
}

bool MailSystem::ImportEmailsFolder(std::string folderpath){
	return false;
}

bool MailSystem::addLabel(std::string label){
	std::vector<Label>::iterator it = find(labels.begin(), labels.end(), label);
	if(it!=labels.end())
		return false;
	labels.push_back(label);
	return true;
}

std::vector<Label> & MailSystem::getLabels(){
	return labels;
}

std::vector<Email> & MailSystem::getEmails(){
	return emails;
}

void MailSystem::clearLabels(){
	labels.clear();
}
void MailSystem::clearEmails(){
	emails.clear();
}
void MailSystem::clearAll(){
	clearLabels();clearEmails();
}

bool MailSystem::LabelEmail::operator < (const LabelEmail &le2){
	return freq > le2;
}

void MailSystem::assingLabelToEmail(Email & email,unsigned k){
	if(labels.size == 0) return;

	std::vector<LabelEmail> relativefreq;
	for(unsigned i = 0 ; i < labels.size(); i++){
		relativefreq.push_back({k,labels[i],0});
		relativefreq[i].freq = calculateRelativeFrequency(labels[i],email);
	}


	if(labels.size() == 1){
		if(relativefreq[0].freq > searchTolerance); //???
		//email.setLabel(relativefreq[0].email);
	}else{
		std::sort (relativefreq.begin(), relativefreq.end());
		if(relativefreq[1].freq/relativefreq[0].freq > searchTolerance){ //???
			//email.setLabel(relativefreq[0].email);
		}
	}
}


float MailSystem::calculateRelativeFrequency(const Label & label,const Email & email) const{
	float wordCounter=0, matchesCounter=0;
	std::string word, bigger, smaller;
	std::stringstream wordsStream/* = email.getWordStream()*/;
	while(getline(wordsStream, word, ' ')){

		for(std::vector<std::string>::iterator it = label.getKeys().begin(); it != label.getKeys().end();it++){
			bigger = word.size() >= (*it).size() ? word : (*it);
			smaller = bigger == word ? (*it) : word;
			if(bigger.substr(0,smaller.size()) == smaller){
				matchesCounter++;
			}
		}
		wordCounter++;
	}
	return (matchesCounter/wordCounter);
}


