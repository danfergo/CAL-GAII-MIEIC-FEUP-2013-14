/*
 * TextUserInterface.h
 *
 *  Created on: 04/11/2013
 *      author: Daniel Gomes
 *      e-mail: up201306839@fe.up.pt
 *
 */

#ifndef TEXTUSERINTERFACE_H_
#define TEXTUSERINTERFACE_H_

#include <string>
#include <sstream>
#include <iostream>
#include <vector>



class TextUserInterface {
private:
	unsigned int width;
	unsigned int height;
	std::string header;
	std::string prompt;
	std::string messageToContinue;
	bool allowBackslashCommands;
	static std::string generateString(int size, char c);

public:
	class Panel{
		unsigned panelWidth;
		unsigned panelHeight;
		bool visibleBorder;
		Panel(unsigned width ,unsigned height,bool visibleBorder);

		void draw(std::string content) const;
	};



	enum TextAlignment {LEFT, CENTER, RIGHT, JUSTIFY};

	TextUserInterface(std::string Header = "", unsigned InterfaceWidth = 70, unsigned InterfaceHeight = 15);
	void setHeader(std::string header);
	void setWidth(unsigned width);
	void setHeight(unsigned width);
	void setPrompt(std::string prompt);
	void setMsgToContinue(std::string message);
	void clearScreen();



	static std::vector<std::string> strsplit(std::string str, std::string sep);
	static std::string processText(std::string text, TextAlignment align, unsigned size);

	std::string print(std::string output, TextAlignment align = LEFT, std::string msg = "", bool menu = false);
	int printInt(std::string output, std::string msg, int min, int max, TextAlignment align = LEFT);
	float printFloat(std::string output, std::string msg, float min, float max, TextAlignment align = LEFT);
	void printEnd(std::string output, TextAlignment align = LEFT);
	int printMenu(std::string menu, bool err = false);
	std::string printPrompt(std::string msg);
	std::string printPrompt();

};


#endif /* TEXTUSERINTERFACE_H_ */
