/*
 * Email.h
 *
 *  Created on: 14/05/2014
 *      Author: Diogo
 */

#ifndef EMAIL_H_
#define EMAIL_H_

#include <string>
#include <vector>


class Label;
class Email {
public:

	Email(std::string ti, std::string te, unsigned long d);
	virtual ~Email();
	bool addLabel(Label label);
	bool getLabel(Label label);
	bool clearLabel(Label label);

private:
	std::string title;
	std::string text;
	unsigned long date;
	std::vector<Label *> labels;
};

#endif /* EMAIL_H_ */
