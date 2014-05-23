/*
 * MailSystem.cpp
 *
 *  Created on: 14/05/2014
 *      Author: Daniel
 */

#include "MailSystem.h"
#include <algorithm>    // std::find

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
