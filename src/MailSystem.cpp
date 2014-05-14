/*
 * MailSystem.cpp
 *
 *  Created on: 14/05/2014
 *      Author: Daniel
 */

#include "MailSystem.h"



MailSystem::MailSystem(){};

bool MailSystem::ImportLabelsFile(std::string filename){};
bool MailSystem::ExportLabelsFile(std::string filename){};
bool MailSystem::ImportEmailsFolder(std::string folderpath){};

bool MailSystem::addLabel(std::string label){
};
std::vector<Label> MailSystem::getLabelList() const{};

Label * MailSystem::getLabel(std::string){};

std::vector<Email> getEmailList() const{};

void MailSystem::clearLabels(){};
void MailSystem::clearEmails(){};
void MailSystem::clearAll(){};
