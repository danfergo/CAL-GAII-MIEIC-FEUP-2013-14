/*
 * matcher.h
 *
 *  Created on: 01/06/2014
 *      Author: Daniel
 */

#ifndef MATCHER_H_
#define MATCHER_H_

#include "Email.h"
#include <string>

void computePrefixFuncion(std::string pattern, int pref[]);
int numStringMatching(std::string filename, std::string toSearch);
float numApproximateStringMatching(std::string filename, std::string toSearch);
unsigned numStringMatchingText(std::string txt, std::string toSearch);


#endif /* MATCHER_H_ */
