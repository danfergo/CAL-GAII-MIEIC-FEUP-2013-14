#include "cute.h"
#include "ide_listener.h"
#include "cute_runner.h"

#include "Label.h"
#include <vector>
#include <string>

void test_import_labels() {
	std::vector<Label> labels = Label::importLabelsFile("labels.txt");
	std::vector<std::string> keys;
	for(unsigned i = 0; i < labels.size(); i++){
		keys = labels[i].getKeys();
		std::cout << labels[i].getTitle() << std::endl;
		for(unsigned j = 0 ; j < keys.size(); j++)
			std::cout << "\t" << keys[j] << std::endl;
	}
}


void text_export_labels(){
	std::vector<Label> labels = Label::importLabelsFile("labels.txt");
	Label::exportLabelsFile("labelsoutput.txt",labels);

}

void runSuite(){
	cute::suite s;
	//TODO add your test here
	s.push_back(CUTE(test_import_labels));
	s.push_back(CUTE(text_export_labels));

	cute::ide_listener lis;
	cute::makeRunner(lis)(s, "The Suite");
}

int main(){
    runSuite();
    return 0;
}



