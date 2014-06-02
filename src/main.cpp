#include "tui/TextUserInterface.h"
#include "MailSystem.h"
#include "tests/Test.h"

#include <sstream>

TextUserInterface * tui = new TextUserInterface("");
MailSystem * ms = new MailSystem();





void manageLabels(){
	std::vector<Label> ll;
	std::string output = "";
	std::stringstream ss;//create a stringstream

	switch(tui->printMenu("Show Labels\nAdd Label \nEdit Label \nGo back")){
		case 1:
			ll = ms->getLabels();
			if(ll.size() == 0)
				tui->print("Oops. You must import or add labels to the system before you try to display them. \n\n\n"
						"Please, go to:\n"
						"1.Import or Export data -> 1. Import e-mails from folder \n"
						"OR \n"
						"2. Manage Labels -> 2. Add Label \n"
						"and import your labels.");
			else{
				output += TextUserInterface::processText("LABEL", TextUserInterface::CENTER,10) + "|";
				output += TextUserInterface::processText("N.Keys", TextUserInterface::CENTER,6) + "|" + "\n";
			//	output += TextUserInterface::processText("DATE", TextUserInterface::CENTER,13) + '\n';

				for(std::vector<Label>::iterator it = ll.begin() ; it != ll.end(); it++){
					ss.str("");
					ss << it->getKeys().size();
					output += TextUserInterface::processText(it->getTitle(), TextUserInterface::LEFT,10) + "|";
					output += TextUserInterface::processText(ss.str(), TextUserInterface::LEFT,6) + "|" + "\n";
				//	output += TextUserInterface::processText(it->date, TextUserInterface::LEFT,13) + '\n';
				}
				tui->print(output);
			}
			break;
		case 2:
			break;
		case 3:
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
	tui->print("\n\n\n\n\nHi! Welcome to the Mail Manager.\n",TextUserInterface::CENTER);
	tui->setHeader("E-mail manager");
	mainMenu();
	tui->setHeader("");
	tui->printEnd("\n\n\n\n\nGoodbye!\n\nI hope to see you soon.",TextUserInterface::CENTER);
	return 0;
}
