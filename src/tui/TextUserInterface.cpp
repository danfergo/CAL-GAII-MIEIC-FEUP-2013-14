/*
 * TextUserInterface.h
 *
 *  Created on: 04/11/2013
 *      author: Daniel Gomes
 *      e-mail: up201306839@fe.up.pt
 *
 */

#include "TextUserInterface.h"


TextUserInterface::Panel::Panel(unsigned w, unsigned h, bool vb){
//	panelWidth = TextUserInterface::width;
	//panelHeight = h;
//	visibleBorder = vb;


};


void TextUserInterface::Panel::draw(std::string content) const{

}

void TextUserInterface::setHeader(std::string header){
	this->header = header;
}


std::vector<std::string> TextUserInterface::strsplit(std::string str, std::string sep){
	std::vector<std::string> ret;
	if(sep.size() ==0){
		for(unsigned int i = 0; i < str.size(); i++){
			ret.push_back(str.substr(i,1));
		}
		return ret;
	}

	bool isSep = false;
	unsigned int lastIndex = 0;

	for(unsigned int i = 0; i < str.size(); i++){
		if(str[i] == sep[0]){
			isSep = true;
			for(unsigned j = 1; j < sep.size(); j++){
				if(str[i + j] != sep[j]){
					isSep = false;
					break;
				}
			}
			if(isSep){
				ret.push_back(str.substr(lastIndex, i - lastIndex));
				lastIndex = i + sep.size();
				i = i + sep.size() - 1;
			}
		}
	}
	ret.push_back(str.substr(lastIndex, str.size() - lastIndex));
	return ret;
}


static int verifOp(std::string str){
	if(str.size() > 2 || str.size() == 0){
		return -1;
	}
	int b = 1, n = 0;
	for(int i = str.size() - 1; i >= 0; i--){
		if(str[i] >= 48 || str[i] <= 57){
			n += (str[i] - 48)*b;
			b = b * 10;
		}else {
			return -1;
		}
	}
	return n;
}


std::string TextUserInterface::generateString(int size, char c){
	std::string ret;
	for(int i = 0; i < size ; i++)
		ret += c;
	return ret;
}

std::string TextUserInterface::processText(std::string text, TextAlignment align, unsigned size){
	std::string ttext = text; text = "";
	if(ttext.size() > size){
		text = ttext.substr(size);
		return ttext.substr(0,size);
	}else switch(align) {
		case CENTER:{
			std::string sepace = generateString(size/2 - ttext.size()/2, ' ');
			std::string line = sepace + ttext + sepace;
			if(size % 2 != 0) line = ' ' + line;
			if(ttext.size() % 2 != 0) line = line.substr(1);
			return line;
		}
		case RIGHT:
			return generateString(size - ttext.size(), ' ')+ ttext;
		case LEFT:
			return ttext + generateString(size - ttext.size(), ' ');
		case JUSTIFY:
			return ttext;
	}
}








TextUserInterface::TextUserInterface(std::string title, unsigned int w, unsigned int h): width(w),height(h), header(title){
	prompt = ">";
	messageToContinue = "Press enter to continue...";
}

std::string TextUserInterface::print(std::string o, TextAlignment align, std::string msg, bool menu){
	clearScreen();
	std::vector<std::string> toPrint = strsplit(o, "\n");

	if(header != ""){
		std::string h = header;
		std::cout << "+"<< generateString(width, '-') << "+"<< std::endl;
		std::cout << "|" + processText(h, CENTER, width) + "|" << std::endl;
		std::cout << "+"<< generateString(width, '-') << "+"<< std::endl;
	}else{
		std::cout << "+"<< generateString(width, '-') << "+"<< std::endl;
		std::cout << "|"<< generateString(width, ' ') << "|"<< std::endl;
		std::cout << "|"<< generateString(width, ' ') << "|"<< std::endl;
	}

	/* drawing middle box */

	for(unsigned int i = 0; i < toPrint.size(); i++){
		if(menu){
			std::cout << "|" << ((i + 1) == toPrint.size()? 0 : i+1) << " - " + processText(toPrint[i], LEFT, i > 9 ? width - 5 : width - 4) + "|" << std::endl;
		}else{
			std::cout << "|" + processText(toPrint[i], align, width) + "|" << std::endl;
		}
	}
	for(unsigned int i = toPrint.size(); i < height; i++){
		std::cout << "|" + generateString(width, ' ') + "|" << std::endl;
	}

	/* end draw middle box */

	if(msg != "%%END%%"){
		return printPrompt(msg == "" ? messageToContinue : msg);
	}else{
		std::cout << "+"<< generateString(width, '-') << "+"<< std::endl;
		std::cout << std::endl;
		return "";
	}
}

int TextUserInterface::printInt(std::string output, std::string msg, int min, int max, TextAlignment align){
	std::string s = print(output, align, msg, false);
	int n;
	std::stringstream str(s);
	str >> n;
	while(!(std::stringstream(s) >> n) || n < min || n > max){
		s = print(output, align,  "ERRO! Valor inválido. "+msg, false);
		std::stringstream str(s);
		str >> n;
	}
	return n;
}


float TextUserInterface::printFloat(std::string output, std::string msg, float min, float max, TextAlignment align){
	std::string s = print(output, align, msg, false);
	float n;
	std::stringstream str(s);
	str >> n;
	while(!(std::stringstream(s) >> n) || n < min || n > max){
		s = print(output, align,  "ERRO! Valor inválido. "+msg, false);
		std::stringstream str(s);
		str >> n;
	}
	return n;
}


int TextUserInterface::printMenu(std::string menu, bool err){
	std::string msg = err ? "ERRO! Opção inválida. Insira a opção:" : "Insira a opção:";

	std::string str = print(menu, LEFT, msg, true);

	unsigned int n = verifOp(str);
	if(n < 0 || n >   strsplit(menu, "\n").size() -1 ){
		return printMenu(menu,true);
	}
	return n;
};
std::string TextUserInterface::printPrompt(std::string msg){
	std::string inp;

	std::cout << "+"<< generateString(width, '-') << "+"<< std::endl;
	std::cout  << msg << std::endl;
	std::cout << prompt;

	getline(std::cin, inp);
	return inp;
}

void TextUserInterface::clearScreen(){
	std::cout << generateString(height*5,'\n');
}

void TextUserInterface::printEnd(std::string o, TextAlignment align){
	std::string str = print(o, align, "%%END%%");
}

std::string TextUserInterface::printPrompt(){
	return printPrompt(messageToContinue);
}

