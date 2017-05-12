#include <iostream>
#include <fstream>
#include <vector>
#include <assert.h>
#include <time.h>



class evolutiv {
	int nr_thread;
	int nr_procese;
	int nr_colonie;
	std::vector<std::vector<int>> colonie;
public:
	evolutiv() {
		srand(time(NULL));
		citire_date();
	}

	void citire_date() {
		std::ifstream f("inp.txt");
		f >> nr_thread;
		f >> nr_procese;
		f >> nr_colonie;
		f.close();
	}


	//incrucisare cu n pct de taietura

	void taietura(std::vector<int> &cromA, std::vector<int> &cromB) {
		int taietura = rand() % cromA.size();

		for (int i = 0; i < taietura; i++) {
			int aux = cromA[i];
			cromA[i] = cromB[cromB.size() + i];
			cromB[cromB.size() + i] = aux;
		}

		for (int i = cromA.size()- taietura; i < cromA.size(); i++) {
			int aux = cromA[i];
			cromA[i] = cromB[cromB.size() - i];
			cromB[cromB.size() - i] = aux;
		}
	}

	

	

};