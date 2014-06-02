#include "Test.h"

#include "../cute/cute.h"
#include "../cute/ide_listener.h"
#include "../cute/cute_runner.h"

#include "../Label.h"
#include <vector>
#include <string>
#include <stdio.h>
#include <sstream>


namespace mailsystem_tests {
	void test_import_labels() {
		std::vector<Label> labels = Label::importLabelsFile("labels.txt");
		std::vector<std::string> keys;
		for(unsigned i = 0; i < labels.size(); i++){
			keys = labels[i].getKeys();
			std::cout << labels[i].getTitle() << std::endl;
			for(unsigned j = 0 ; j < keys.size(); j++)
				std::cout << "\t" << keys[j] << std::endl;\
		}
	}


	void text_export_labels(){
		std::vector<Label> labels = Label::importLabelsFile("labels.txt");
		Label::exportLabelsFile("labelsoutput.txt",labels);
	}

	void runCuteTests(){
		cute::suite s;
		s.push_back(CUTE(test_import_labels));
		s.push_back(CUTE(text_export_labels));

		cute::ide_listener lis;
		cute::makeRunner(lis)(s, "Gestor de Emails - Testes Unitários");
	}

};


