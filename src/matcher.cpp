#include "matcher.h"

#include <iostream>
#include <fstream>

void computePrefixFuncion(std::string pattern, int pref[]) {

	pref[0] = 0;

	unsigned k = 0;
	for (unsigned i = 1; i < pattern.size(); i++) {
		while (k > 0 && pattern[k] != pattern[i]) {
			k = pref[k-1];
		}
		if (pattern[k] == pattern[i]) {
			k++;
		}
		pref[i] = k;
	}

}


int numStringMatching(std::string filename, std::string toSearch) {
	std::string line;
	std::ifstream myfile(filename.c_str());
	unsigned nrMatches = 0;


	// calcular funcao prefixo
	unsigned m = toSearch.size();
	int pref[m];
	computePrefixFuncion(toSearch, pref);

	unsigned q;

	if (myfile.is_open()) {
		while (getline(myfile, line)) {


		// procurar na linha
		q = 0;

		 for (unsigned i = 0; i < line.size(); i++) {
				while (q > 0 && toSearch[q] != line[i]) {
					q = pref[q-1];
				}
				if (toSearch[q] == line[i]) {
					q++;
				}
				if (q == m) {
					nrMatches++;
					q = pref[q-1];
				}

			}

		}
		myfile.close();
		return nrMatches;
	}

	return -1;
}



float numApproximateStringMatching(std::string filename, std::string toSearch) {
	std::string line;
	std::ifstream myfile(filename.c_str());
	float averageDistance = 0;
	unsigned nrMatches = 0;

	// calcular funcao prefixo
	unsigned m = toSearch.size();
	int pref[m];
	computePrefixFuncion(toSearch, pref);

	unsigned q;

	if (myfile.is_open()) {
		while (getline(myfile, line)) {


		// procurar na linha
		q = 0;

		 for (unsigned i = 0; i < line.size(); i++) {
				while (q > 0 && toSearch[q] != line[i]) {
					q = pref[q-1];
				}
				if (toSearch[q] == line[i]) {
					q++;
				}
				if (q == m) {
					averageDistance += (i + 1 - m);
					nrMatches++;
					q = pref[q-1];
				}

			}

		}
		myfile.close();
		return nrMatches == 0 ? 0 : averageDistance/nrMatches;
	}

	return -1;
}


unsigned numStringMatchingText(std::string txt, std::string toSearch) {

	unsigned nrMatches = 0;

	// calcular funcao prefixo
	unsigned m = toSearch.size();
	int pref[m];
	computePrefixFuncion(toSearch, pref);

	// procurar na linha
	unsigned  q = 0;

	 for (unsigned i = 0; i < txt.size(); i++) {
			while (q > 0 && toSearch[q] != txt[i]) {
				q = pref[q-1];
			}
			if (toSearch[q] == txt[i]) {
				q++;
			}
			if (q == m) {
				nrMatches++;
				q = pref[q-1];
			}

		}
	 return  nrMatches;
}
