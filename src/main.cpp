#include "tui/TextUserInterface.h"
#include "MailSystem.h"
#include "tests/Test.h"
#include <stdlib.h>

#include <fstream>
#include <sstream>

TextUserInterface * tui = new TextUserInterface("");
MailSystem * ms = new MailSystem();

void editLabel(unsigned i){
	std::stringstream words,temp,t;
	std::string keyword,safeword;
	std::vector<std::string> keys = ms->getLabels()[i].getKeys();
	unsigned count = 0,pos;
	switch(tui->printMenu("Show Label keywords \nAdd Keyword(s)\nRemove Keyword \nDelete label \nGo back")){
	case 1:
		temp.str("");
		temp << "Label:" << ms->getLabels()[i].getTitle() << "\nKeywords:\n";
		for(std::vector<std::string>::iterator it = keys.begin(); it != keys.end();it++){
			if((count+1) % 4 == 0)
				temp << TextUserInterface::processText(*it, TextUserInterface::LEFT,15) << "\n";
			else
				temp << TextUserInterface::processText(*it, TextUserInterface::LEFT,15) << "| ";
			count++;
		}
		tui->print(temp.str());
		break;
	case 2:
		words.str(tui->print("Insert the keyword(s) you pretend to add to the label " + ms->getLabels()[i].getTitle() + ".\n"
				"For multiple keywords separate them width a single space.", TextUserInterface::LEFT,"Insert the keywords(s)"));
		while(getline(words,keyword,' ')){
			if(keyword != ""){
				if(ms->getLabels()[i].addKey(keyword)){
					count++;
				}
			}
		}
		temp.str("");
		temp << count << " new keywords inserted with sucess to the \nlabel " <<  ms->getLabels()[i].getTitle() << ".";
		tui->print(temp.str());
		break;
	case 3:
		temp.str("");
		temp << "Label:" << ms->getLabels()[i].getTitle() << "\nKeywords:\n";
		for(std::vector<std::string>::iterator it = keys.begin(); it != keys.end();it++){
			t.str("");
			t << (count+1) << " - "<< *it;
			if((count+1) % 4 == 0)
				temp << TextUserInterface::processText(t.str(), TextUserInterface::LEFT,17) << "\n";
			else
				temp << TextUserInterface::processText(t.str(), TextUserInterface::LEFT,17) << "| ";
			count++;
		}
		t.str("");
		t << "Insert the position of the keyword to delete (1 to " << keys.size() << "), 0 to go back:";
		pos = tui->printInt(temp.str(),t.str(),0,keys.size());
		if(pos != 0){
			ms->getLabels()[i].deleteKey(pos-1);
			tui->print("Keyword removed with success.");
		}else{
			tui->print("No one keyword was removed.");
		}
		break;
	case 4:
		temp.str("");
		temp << "Label:" << ms->getLabels()[i].getTitle() << "\nKeywords:\n";
		for(std::vector<std::string>::iterator it = keys.begin(); it != keys.end();it++){
			if((count+1) % 4 == 0)
				temp << TextUserInterface::processText(*it, TextUserInterface::LEFT,15) << "\n";
			else
				temp << TextUserInterface::processText(*it, TextUserInterface::LEFT,15) << "| ";
			count++;
		}
		safeword = tui->print(temp.str(),TextUserInterface::LEFT,"Insert «delete» to delete the label:");
		if(safeword == "delete"){
			ms->getLabels().erase(ms->getLabels().begin()+i);
			tui->print("Label removed with success.");
			return;
		}else
			tui->print("The label was not removed.");
		break;
	case 0:
		return;
	}
	editLabel(i);
}

void chooseLabelToEdit(){
	std::stringstream ss,tout;
	std::string output;
	std::vector<Label> ll = ms->getLabels();
	if(ll.size() == 0){
		tui->print("Oops. You must import or add labels to the system before \nyou try to edit them. \n\n\n"
				"Please, go to:\n"
				"1.Import or Export data -> 1. Import e-mails from folder \n"
				"OR \n"
				"2. Manage Labels -> 2. Add Label \n"
				"and import your labels.");
		return;
	}

	unsigned i = 1;
	output += "What label you want to explore/edit? \n";
	for(std::vector<Label>::iterator it = ll.begin() ; it != ll.end(); it++){
		ss.str("");
		ss << i << " - " << it->getTitle();
		output += TextUserInterface::processText(ss.str(), TextUserInterface::LEFT,70) + " \n";
		i++;
	}
	tout << "Insert the position of the label to edit (1 to " << ll.size() << "), 0 to go back:";

	unsigned pos = tui->printInt(output,tout.str(), 0 , ll.size());
	if(pos != 0)
		editLabel(pos-1);
}




void manageLabels(){
	std::vector<Label> ll;
	std::string output = "";
	std::stringstream ss;//create a stringstream
	std::string labletitle;
	switch(tui->printMenu("Show Labels\nAdd Label \nExplore/Edit Label \nGo back")){
		case 1:
			ll = ms->getLabels();
			if(ll.size() == 0)
				tui->print("Oops. You must import or add labels to the system before \nyou try to display them. \n\n\n"
						"Please, go to:\n"
						"1.Import or Export data -> 1. Import e-mails from folder \n"
						"OR \n"
						"2. Manage Labels -> 2. Add Label \n"
						"and import your labels.");
			else{
				output += TextUserInterface::processText("LABEL", TextUserInterface::CENTER,10) + "|";
				output += TextUserInterface::processText("N.Keys", TextUserInterface::CENTER,6) + "|" + "\n";

				for(std::vector<Label>::iterator it = ll.begin() ; it != ll.end(); it++){
					ss.str("");
					ss << it->getKeys().size();
					output += TextUserInterface::processText(it->getTitle(), TextUserInterface::LEFT,10) + "|";
					output += TextUserInterface::processText(ss.str(), TextUserInterface::LEFT,6) + "|" + "\n";
				}
				tui->print(output);
			}
			break;
		case 2:
			labletitle = tui->print("Insert the title of the new lable or nothing to continue.", TextUserInterface::LEFT, "Insert the title:");
			if(labletitle == "")
				tui->print("No label was created.");
			else {
				if(ms->addLabel(labletitle))
					tui->print("Label created with success.");
				else
					tui->print("It was not possible to create this lable. \nProbably this lable already exists.");
			}
			break;
		case 3:
			chooseLabelToEdit();
			break;
		case 0:
			return;
	}
	manageLabels();
}


void importExportFiles(){
	std::string path;
	switch(tui->printMenu("Import e-mails from folder \nImport label's file  \nExport Labels to file \nGo back")){
		case 1:
			path = tui->print("Insert the email's folder location path.\n"
					"Each file should have the following format: \n"
					"-Title- \n"
					"The title of the e-mail\n"
					"-Date- \n"
					"dd-mm-yy hh:mm::ss \n"
					"-Text- \n"
					"Email's body." ,TextUserInterface::LEFT, "Insert the email's location folder:");
			if(ms->ImportEmailsFolder(path))
				tui->print("Emails successfully imported!");
			else
				tui->print("Oops. It was not possible to import your emails!");
			break;
		case 2:
			path = tui->print("Insert the path and the file name of the label's file:\n"
								,TextUserInterface::LEFT, "Insert the path and file name:");
			if(ms->ImportLabelsFile(path))
				tui->print("Labels successfully imported!");
			else
				tui->print("Oops. It was not possible to import your label's file!");
			break;
		case 3:
			path = tui->print("Insert the path and filename whither you pretend to export the Labels\n"
											,TextUserInterface::LEFT, "Insert the path and file name:");
			if(ms->ExportLabelsFile(path))
				tui->print("Labels successfully exported!");
			else
				tui->print("Oops. It was not possible to export your label's file!");
			break;
		case 0:
			return;
	}
	importExportFiles();
}

void mainMenu(){
	std::vector<Email> ee;
	std::string output = "";
	std::stringstream temp;
	switch(tui->printMenu("Import or Export data \nManage Labels\nShow e-mails\nChange Search Tolerance\nAbout \nRun Unit Tests\nExit")){
		case 1:
			importExportFiles();
			break;
		case 2:
			manageLabels();
			break;
		case 3:
			ee = ms->getEmails();
			if(ee.size() == 0)
				tui->print("Oops. You must Import your e-mails to the system before you try to display them. \n\n\n"
						"Please, go to:\n"
						"1.Import or Export data > 1. Import e-mails from folder \n"
						"and import your e-mails.");
			else{
				ms->assingLabelsToEmails();
				ee = ms->getEmails();
				output += TextUserInterface::processText("LABEL", TextUserInterface::CENTER,10) + "|";
				output += TextUserInterface::processText("TITLE ", TextUserInterface::CENTER,40) + "|";
				output += TextUserInterface::processText("DATE", TextUserInterface::CENTER,13) + '\n';

				for(std::vector<Email>::iterator it = ee.begin() ; it != ee.end(); it++){
					output += TextUserInterface::processText((it->getLabel() == NULL ? "" : it->getLabel()->getTitle()), TextUserInterface::LEFT,10) + "|";
					output += TextUserInterface::processText(it->title, TextUserInterface::LEFT,40) + "|";
					output += TextUserInterface::processText(it->date, TextUserInterface::LEFT,13) + '\n';
				}
				tui->print(output);
			}
			break;
		case 4:
			temp << "Search tolerance constant is now: " << ms->getSearchTolerance() << "\nInsert a value to the search tolerance constant.";
			ms->setSearchTolerance(tui->printFloat(temp.str(),"Insert a value between 0 and 1:", 0, 1));
			temp.str("");
			temp << "Search tolerance constant is now: " << ms->getSearchTolerance();
			tui->print(temp.str());
		break;
		case 5:
			tui->print("    This application was developed during the Curricular Unit\n"
					"Concepção e Analise de Algoritmos of the Mestrado Integrado em\n"
					"Engenharia Informática e Computação at the Faculdade de Engenharia da \n"
					"Universidade do Port by Daniel Gomes, Diogo Gomes and Pedro Santiago.\n"
					"\n\n"
					"    At this application the user can load his e-mails from a \n"
					"text file, add his labels manualy or with a text file and, the \n"
					"program will automatically assing the corresponding label \n"
					"to each e-mail.");
			break;
		case 6:
			tui->clearScreen();
			mailsystem_tests::runCuteTests();
			tui->printPrompt();
			break;
		case 0:
			return;
	}
	mainMenu();
}


int main(){
	tui->print(""
			 " ______                 _ _   __  __                                   \n"
			 "|  ____|               (_) | |  \\/  |                                  \n"
			 "| |__   _ __ ___   __ _ _| | | \\  / | __ _ _ __   __ _  __ _  ___ _ __ \n"
			 "|  __| | '_ ` _ \\ / _` | | | | |\\/| |/ _` | '_ \\ / _` |/ _` |/ _ \\ '__|\n"
			 "| |____| | | | | | (_| | | | | |  | | (_| | | | | (_| | (_| |  __/ |   \n"
			 "|______|_| |_| |_|\\__,_|_|_| |_|  |_|\\__,_|_| |_|\\__,_|\\__, |\\___|_|   \n"
			 "                                                        __/ |          \n"
			 "                                                       |___/           \n"
			"\n\n"
			"Hi! Welcome to the Email Manager.\n",TextUserInterface::CENTER);
	tui->setHeader("Email Manager");
	mainMenu();
	tui->setHeader("");
	tui->printEnd("\n\n\n\n\nGoodbye!\n\nI hope to see you soon.",TextUserInterface::CENTER);
	return 0;
}
