#include <eosim/dist/mt19937.hpp>
#include <eosim/core/experiment.hpp>
#include "hospitalcomplejo.hpp"
#include "constantes.hpp"

#include <iostream>
#include <fstream>

const unsigned int repeticiones = 4;

int main () {
	std::string s;
    using namespace eosim::core;
    //repito el experimento una cierta cantidad de veces
    //for (int i = 0; i < repeticiones; i++) {
	HospitalComplejo * m = new HospitalComplejo();
        Experiment e;
        std::cout << "Arranco ...\n";
		m->connectToExp(&e);
        e.setSeed((unsigned long) 9123832);
		e.run(runTime);
    //}
}

