#include <eosim/dist/mt19937.hpp>
#include <eosim/core/experiment.hpp>
#include "hospitalsimple.hpp"
#include "constantes.hpp"

#include <iostream>
#include <fstream>

const unsigned int repeticiones = 4;

int main () {
	std::string s;
    using namespace eosim::core;
    //repito el experimento una cierta cantidad de veces
    //for (int i = 0; i < repeticiones; i++) {
        HospitalSimple m(cantCamas, tasaArribos, tiempoEstadia);
        Experiment e;
        std::cout << "Arranco ...\n";
        m.connectToExp(&e);
        e.setSeed((unsigned long) 123132);
		e.run(12000);
        std::cout << "Termine ...\n\n\n";
		m.lCola.print(10);
		std::cout << '\n';
		m.tEspera.print(20);
		m.tsCola.print(cantCeldas);
		m.tsCola.print(cantCeldas,"timeSeries.txt");
		std::cin >> s;
    //}
}

