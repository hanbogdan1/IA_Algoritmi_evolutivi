#include <iostream>
#include <fstream>

class evolutiv {
	int nr_thread;
	int nr_procese;
public:
	evolutiv() {
		citire_date();
	}


	void citire_date() {
		std::ifstream f("inp.txt");
		f >> nr_thread;
		f >> nr_procese;
		f.close();
	}

};