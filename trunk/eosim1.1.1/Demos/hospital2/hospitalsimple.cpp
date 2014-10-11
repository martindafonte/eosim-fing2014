#include "hospitalsimple.hpp"
#include <eosim/core/entity.hpp>
#include <eosim/dist/numbergenerator.hpp>
#include <iostream>

using namespace eosim::core;
using namespace eosim::dist;

using namespace std;

HospitalSimple::HospitalSimple(unsigned int cantCamas, double tasaArribos, double tiempoEstadia):
// se contruyen los eventos B, los eventos C, las distribuciones, los recursos y los histogramas
								tasaArribos(tasaArribos),
								tiempoEstadia(tiempoEstadia),
								pF(*this),
								sP(*this),
								pPond(*this),
								arribos(MT19937,tasaArribos,20),
								estadia(MT19937, tiempoEstadia),
								camas(cantCamas, cantCamas),
								tEspera("Tiempos de Espera"),
								lCola("Largos Medios de Colas", *this) {
stream_archivo.open("salida_promedio.txt", ofstream::out);
tiempoEntremedidas = 500.0;
}

HospitalSimple::~HospitalSimple() {
	stream_archivo.flush();
	stream_archivo.close();
	stream_archivo;
}

void HospitalSimple::init() {
	// registro los eventos B
	registerBEvent(&pF);
	registerBEvent(&sP);
	registerBEvent(&pPond);

	// registro las distribuciones
	registerDist(&arribos);
	registerDist(&estadia);
}

void HospitalSimple::doInitialSchedules() {
	// agendo el primer paciente
	schedule(0.0, new Entity(), pacienteF);
	schedule(0.0, new Entity(),tomarMedida);
}

