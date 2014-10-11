#include <eosim/core/experiment.hpp>
#include "constantes.hpp"
#include "traffic.hpp"
#include <iostream>
#include <string>

using namespace eosim::core;

const unsigned int repeticiones = 4;

int main() {
    std::string s;
    //repito el experimento una cierta cantidad de veces
    //for (int i = 0; i < repeticiones; i++) {
		Traffic t(media_vehiculos, media_izq, media_der, media_central, tiempo_verde, tiempo_roja);
		Experiment e;
		std::cout << "Arranco ...\n";
		t.connectToExp(&e);
		e.setSeed((unsigned long) /*i +*/ 129);
		e.run(1000*50);
        std::cout << "Termine ...\n\n\n";
		int celdasCola=5;
		int celdasTiempo = 8;
		t.lCola_cc.print(celdasCola);
		t.lCola_ci.print(celdasCola);
		t.lCola_cd.print(celdasCola);
		t.lCola_dd.print(celdasCola);
		t.lCola_di.print(celdasCola);
		t.tEspera_cc.print(celdasTiempo);
		t.tEspera_ci.print(celdasTiempo);
		t.tEspera_cd.print(celdasTiempo);
		t.tEspera_dd.print(celdasTiempo);
		t.tEspera_di.print(celdasTiempo);
        //std::cin >> s;
	//}
	return 0;
}
