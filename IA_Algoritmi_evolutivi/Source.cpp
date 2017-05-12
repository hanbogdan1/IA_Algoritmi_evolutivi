#include <iostream>
#include <fstream>
#include <vector>
#include <assert.h>
#include <time.h>

typedef std::vector<int> cromozom;

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


	void generare_matrice() {

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

	//mutatia random resetting
	void mutatia_tare(cromozom& crom) {
		int probabilitate = rand() % 101;
		for (auto &x : crom) {
			int prob = rand() % 101;
			if (prob < probabilitate)
				x = rand() % nr_thread;
		}
	}


	

};


int main() {
	
	return 0;
}