#include <iostream>
#include <fstream>
#include <vector>
#include <assert.h>
#include <time.h>

typedef std::vector<int> ant;

class aco {

public:
	int ant_number;
	int nr_thread;
	int nr_procese;

	std::vector<std::vector<int>> matrice;
	std::vector<std::vector<int>> matrice_feromon;
	std::vector<std::vector<int>> colonie;

	std::ofstream g;
	
	aco() {
		g.open("putput.txt");
		srand(1);
		citire_date();
		generare_matrice();
		generare_colonie();
	}

	~aco() {
		g.close();
	}
	void citire_date() {
		std::ifstream f("inp.txt");
		f >> nr_thread;
		f >> nr_procese;
		f >> ant_number;
		f.close();
	}

	void generare_matrice() {
		for (auto proces = 0; proces < nr_procese; proces++) {
			std::vector<int> feromon_linie;
			std::vector<int> timp_linie;
			for (auto procesor = 0; procesor < nr_thread; procesor++) {
				timp_linie.push_back(rand() % 101);
				feromon_linie.push_back(0);
			}
			matrice.push_back(timp_linie);
			matrice_feromon.push_back(feromon_linie);
		}

	}


	void generare_ant(ant &x) {
		x.clear();
		for (auto proces = 0; proces < nr_procese; proces++) {
			x.push_back(rand() % nr_thread);
		}
	}

	int fitness(ant&x) {
		int suma = 0;
		for (int i = 0; i < x.size(); i++) {
			suma += matrice[i][x[i]];
		}
		return suma;
	}

	bool comp(std::vector<int> &a, std::vector<int> &b)
	{
		return cmp_vect(a, b);
	}


	bool cmp_vect(std::vector<int> &a, std::vector<int>& b)
	{

		if (fitness(a) < fitness(b))
			return false;
		return true;
	}

	void inserare_colonie(ant vect) {
		int i = 0;
		for (; i < colonie.size(); i++) {
			if (comp(colonie[i], vect))
				break;
		}
		colonie.insert(colonie.begin() + i, vect);
	}


	void generare_colonie() {
		for (auto i = 0; i < ant_number; i++) {
			ant x;
			generare_ant(x);
			inserare_colonie(x);
		}
	}

	void afisare_fitness_colonie() {
		g << "\n";
		for (auto &x : colonie) {
			g << fitness(x) << " ";
		}
	}

	void aco_rez() {
		generare_colonie();
		int loop;
		loop = rand() % 100;
		for (; loop > 0; loop--) {
			colonie.clear();
			for (auto i = 0; i < ant_number; i++) {
				ant x;
				generare_ant(x);
				inserare_colonie(x);
				for (int i = 0; i < x.size(); i++) {
					matrice_feromon[i][x[i]]++;
				}
			}

		}
	}

};


int main() {
	return 1;
}