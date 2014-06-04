/*
 * MailSystem.cpp
 *
 *  Created on: 14/05/2014
 *      Author: Daniel
 */

#include "MailSystem.h"
#include <algorithm>    // std::find
#include <sstream>
#include "matcher.h"

MailSystem::MailSystem(){
	searchTolerance = 0;
};

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
	try{
		Label::exportLabelsFile(filename,labels);
		return true;
	}catch(FileNotFound & e){
		return false;
	}
}

bool MailSystem::ImportEmailsFolder(std::string folderpath){
	std::vector<Email> e;
	try{
		e = Email::importEmailsFolder(folderpath);
		emails.insert(emails.end(), e.begin(), e.end());
		return true;
	}catch(FileNotFound & e){
		return false;
	}
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

bool MailSystem::LabeRelativeFreq::operator < (const LabeRelativeFreq &le2) const{
	return freq > le2.freq;
}

void MailSystem::assingLabelToEmail(Email & email){
	email.clearLabel();

	if(labels.size() == 0) return;

	std::vector<LabelEmail> relativefreq;
	for(unsigned i = 0 ; i < labels.size(); i++){
		LabelEmail le = {&labels[i],0};
		relativefreq.push_back(le);
		relativefreq[i].freq = calculateRelativeFrequency(labels[i],email);
	}

	if(labels.size() == 1){
		if(relativefreq[0].freq > searchTolerance)
			email.setLabel(relativefreq[0].label);
	}else{
		std::sort (relativefreq.begin(), relativefreq.end());
		if(relativefreq[0].freq - relativefreq[1].freq > searchTolerance)
			email.setLabel(relativefreq[0].label);
	}
}


void MailSystem::assingLabelsToEmails(){
	for(std::vector<Email>::iterator it = emails.begin(); it != emails.end(); it++){
		assingLabelToEmail(*it);
	}
}


float MailSystem::calculateRelativeFrequency(const Label & label,const Email & email) const{
	float x = 0;
	std::vector<std::string> gkeys = label.getKeys();

	for(std::vector<std::string>::const_iterator it = gkeys.begin(); it != gkeys.end();it++){
		x += numStringMatchingText(email.text,*it);
	}
	unsigned y = email.getNWords();
	return y == 0 ? 0 : x/(float)y;
}


