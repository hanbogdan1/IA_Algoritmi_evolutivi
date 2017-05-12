#include <iostream>
#include <fstream>
#include <vector>
#include <assert.h>
#include <time.h>

typedef std::vector<int> cromozom;

class evolutiv {

public:
	int nr_thread;
	int nr_procese;
	int nr_colonie;
	std::vector<std::vector<int>> matrice;
	std::vector<std::vector<int>> colonie;
	std::ofstream g;
	evolutiv() {
		g.open("putput.txt");
		srand(1);
		citire_date();
		generare_matrice();
		generare_colonie();
	}

	~evolutiv() {
		g.close();
	}
	void citire_date() {
		std::ifstream f("inp.txt");
		f >> nr_thread;
		f >> nr_procese;
		f >> nr_colonie;
		f.close();

	}

	void generare_matrice() {
		for (auto proces = 0; proces < nr_procese; proces++) {
			std::vector<int> timp_linie;
			for (auto procesor = 0; procesor < nr_thread; procesor++) {
				timp_linie.push_back(rand() % 101);
			}
			matrice.push_back(timp_linie);
		}

	}


	void generare_cromozom(cromozom &x ) {
		x.clear();
		for (auto procesor = 0; procesor < nr_procese; procesor++) {
				x.push_back(rand() % nr_thread);
			}
	}

	//incrucisare cu n pct de taietura
	void incrucisare(std::vector<int> &cromA, std::vector<int> &cromB) {
		int taietura = rand() % cromA.size();

		for (int i = 0; i < taietura; i++) {
			int aux = cromA[i];
			cromA[i] = cromB[cromB.size() -taietura+ i];
			cromB[cromB.size() -taietura + i] = aux;
		}

		for (int i = cromA.size() - taietura; i < cromA.size(); i++) {
			int aux = cromA[i];
			cromA[i] = cromB[cromB.size() - i];
			cromB[cromB.size() - i] = aux;
		}
	}

	int fitness(cromozom&x) {
		int suma = 0;
		for (int i = 0; i < x.size(); i++) {
			suma += matrice[i][x[i]];
		}
		return suma;
	}

	//mutatia random resetting
	void mutatie(cromozom& crom) {
		cromozom aux = crom;

		int dead_lock = rand() % 10; // poate cromozomul are fitness-ul foarte mic si atunci nu se mai face iesirea din while

		do {
			dead_lock--;
			int probabilitate = rand() % 101;
			for (auto &x : aux) {
				int prob = rand() % 101;
				if (prob < probabilitate)
					x = rand() % nr_thread;
			}
		} while (fitness(aux) > fitness(crom) && dead_lock);
			crom = aux;
	}

	bool comp(std::vector<int> &a,std::vector<int> &b)
	{
		return cmp_vect(a, b);
	}


	bool cmp_vect(std::vector<int> &a, std::vector<int>& b)
	{

		if (fitness(a) < fitness(b))
			return false;
		return true;
	}

	void inserare_colonie(cromozom vect) {
			int i = 0;
			for (;i < colonie.size(); i++) {
				if (comp(colonie[i], vect))
					break;
			}
			colonie.insert(colonie.begin() + i, vect);
	}


	void generare_colonie() {
		for (auto i = 0; i < nr_colonie; i++) {
			cromozom x;
			generare_cromozom(x);
			inserare_colonie(x);
		}
	}

	void afisare_fitness_colonie() {
		g << "\n";
		for (auto &x : colonie) {
			g << fitness(x) << " ";
		}
	}

	void rezolvare() {

		int loop = rand() % 500;
		
		//cromozom FIRST_LOCAL_BEST = colonie[0];

		afisare_fitness_colonie();
		for (; loop > 0; loop--) {
			cromozom First_best = colonie[0];
			cromozom Second_best = colonie[1];

			incrucisare(First_best, Second_best);
			
			mutatie(First_best);
			mutatie(Second_best);

			colonie.pop_back();
			colonie.pop_back();

			inserare_colonie(First_best);
			inserare_colonie(Second_best);
			afisare_fitness_colonie();
		}

	}
};


void test() {
	evolutiv x;
	srand(1);
	cromozom y;
	x.generare_cromozom(y);
	assert(x.fitness(y) == 11979);
	x.generare_cromozom(y);
	assert(x.fitness(y) == 11842);
	x.generare_cromozom(y);
	assert(x.fitness(y) == 12465);
	x.generare_cromozom(y);
	assert(x.fitness(y) == 13375);
	x.generare_cromozom(y);
	assert(x.fitness(y) == 13231);

}

int main() {
	evolutiv a;
	a.rezolvare();
	//test();
	return 0;
}