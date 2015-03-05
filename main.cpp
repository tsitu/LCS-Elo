//LCS Elo Ranking by tsitu
#include <iostream>
#include <sstream>
#include <fstream>
#include <map>
#include <vector>
#include <algorithm>
#include <string>
#include <cmath>

using namespace std;

//Prototypes
void calculateElo(string winner, string loser, map<string, int> & orig); //ELO algorithm
void dump(map<string, int> & orig, ostream& ofile); //Raw dump
void dumpSorted(map<string, int> & orig, ostream& ofile); //Dumps sorted by highest ELO

//Implementations
void calculateElo(string winner, string loser, map<string, int> & orig) {
	int elo1, elo2, diff, return1, return2;
	double expected1, expected2;

	map<string, int>::iterator it;
	it = orig.find(winner);
	if (it != orig.end()) {
		elo1 = it->second;
	}

	map<string, int>::iterator it2;
	it2 = orig.find(loser);
	if (it2 != orig.end()) {
		elo2 = it2->second;
	}

	diff = elo1 - elo2 + 100;
	expected1 = 1 / (1 + pow(10, -diff/400));
	expected2 = 1 / (1 + pow(10, diff/400));
	return1 = (int) 32 * (1 - expected1);
	return2 = (int) 32 * (0 - expected2);

	it->second = elo1 + return1;
	it2->second = elo2 + return2;
}

void dump(map<string, int> & orig, ostream& ofile) {
	ofile << "LCS Elo Rankings" << endl;
	ofile << "Format: Team Name - ELO" << endl << endl;
	map<string, int>::iterator it;
	for (it = orig.begin(); it != orig.end(); it++) {
		ofile << it->first << ": " << it->second << endl;
	}
}

void dumpSorted(map<string, int> & orig, ostream& ofile) {
	ofile << "LCS Elo Rankings" << endl;
	ofile << "Format: Team Name - ELO" << endl << endl;
	vector<int> eloSort;
	map<string, int>::iterator it;
	for (it = orig.begin(); it != orig.end(); it++) {
		if (find(eloSort.begin(), eloSort.end(), it->second) == eloSort.end()) {
			eloSort.push_back(it->second);
		}
	}
	sort(eloSort.begin(), eloSort.end());

	//Output corresponding mapped keys, highest to lowest ELO
	for (unsigned int i=0; i<eloSort.size(); i++) {
		for (it = orig.begin(); it != orig.end(); it++) {
			if (it->second == eloSort[eloSort.size()-i-1]) {
				ofile << it->first << ": " << it->second << endl;
			}
		}
	}
}

int main(int argc, char* argv[]) {
	if (argc != 3) {
		cout << "Usage: ./main input.txt output.txt" << endl;
	}
	else {
		//Opens database file
		ifstream infile(argv[1]);
		if (infile.fail()) {
			cerr << "Error opening file: " << argv[1];
		}

		//Reads data from database
		map<string, int> inputMap;
		string text;
		while (getline(infile, text)) {
			istringstream iss(text);
			//Search map for keys that match winner/loser strings
			//If not found, insert key into map with base ELO = 1200
			string winner;
			string loser;
			iss >> winner;
			iss >> loser;
			if (iss.fail()) {
				cout << "Error reading line" << endl;
			}
			map<string, int>::iterator it;
			it = inputMap.find(winner);
			if (it == inputMap.end()) {
				inputMap.insert(pair<string, int>(winner, 1200));
			}
			map<string, int>::iterator it2;
			it2 = inputMap.find(loser);
			if (it2 == inputMap.end()) {
				inputMap.insert(pair<string, int>(loser, 1200));
			}

			calculateElo(winner, loser, inputMap);
			//Add counter for how many games a team has played in total
		}

		//Opens output file
		ofstream outfile(argv[2]);
		if (outfile.fail()) {
			cerr << "Error opening file: " << argv[2];
		}

		//dump(inputMap, outfile);
		dumpSorted(inputMap, outfile);
		outfile.close();
	}

	return 1;
}