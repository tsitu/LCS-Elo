//NALCS Elo Ranking
#include <iostream>
#include <sstream>
#include <fstream>
#include <map>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

//Prototypes
void calculateElo(string winner, string loser);
map<string, int> sorted(map<string, int> & orig);
void dump(ostream& ofile);

//Implementations
void calculateElo(string winner, string loser, map<string, int> & orig) {
	//scan for positions to winner and loser
	//grab their it->second to int elo's
	/*int diff = elo1 - elo2 + 100;
	int 1_expected = 1 / (1+10**(-diff/400));
	int 2_expected = 1 / (1+10**(diff/400));
	int 1_return = 32 * (result - blue_expected);
	int 2_return = 32 * (1 - result - red_expected);*/
}

map<string, int> sorted(map<string, int> & orig) {
	map<string, int> sortedMap;
	map<string, int>::iterator it;
	vector<int> eloSort;
	for (it = orig.begin(); it != orig.end(); it++) {
		eloSort.push_back(it->second);
	}
	sort(eloSort.begin(), eloSort.end());
	for (unsigned int i=0; i<eloSort.size(); i++) {
		for (it = orig.begin(); it != orig.end(); it++) {
			if (it->second == eloSort[i]) {
				sortedMap.insert(pair<string, int>(it->first, it->second));
			}
		}
	}
	return sortedMap;
}

void dump(map<string, int> & orig, ostream& ofile) {
	ofile << "NALCS Elo Rankings" << endl;
	ofile << "Format: Team Name / ELO" << endl << endl;
	map<string, int>::iterator it;
	for (it = orig.begin(); it != orig.end(); it++) {
		ofile << it->first << ": " << it->second << endl;
	}
}

int main(int argc, char* argv[]) {
	if (argc != 3) {
		cout << "Usage: ./main input.txt output.txt" << endl;
	}
	else {
		//Opens database file
		ifstream infile;
		infile.open(argv[1], ifstream::in);
		if (infile.fail()) {
			cerr << "Error opening file: " << argv[1];
		}
		//Opens output file
		ofstream outfile;
		outfile.open(argv[2]);
		if (outfile.fail()) {
			cerr << "Error opening file: " << argv[2];
		}
		//Reads data from database
		map<string, int> inputMap;
		string text;
		while (getline(infile, text)) {
			istringstream iss;
			if (iss.fail()) {
				cout << "Error reading line" << endl;
			}
			else {
				//search map for winner/loser keys
				//if there then nothing, if not insert key into map with elo = 1200
				string winner;
				string loser;
				iss >> winner;
				iss >> loser;
				map<string, int>::iterator it;
				it = inputMap.find(winner);
				if (it == inputMap.end()) {
					inputMap.insert(pair<string, int>(winner, 1200));
				}
				it = inputMap.find(loser);
				if (it == inputMap.end()) {
					inputMap.insert(pair<string, int>(loser, 1200));
				}

				//calculateElo(winner, loser) using the ints?

			}
		}
		map<string, int> sortedMap;
		sortedMap = sorted(inputMap);
		dump(sortedMap, outfile);
	}

	return 1;
}