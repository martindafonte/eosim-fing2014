#include "hospitalsimple.hpp"
#include <eosim/core/entity.hpp>
#include <eosim/dist/numbergenerator.hpp>
#include <iostream>
#include "constantes.hpp"

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
								tS(*this),
								arribos(MT19937,tasaArribos),
								estadia(MT19937,a =new double[3],3),
								camas(cantCamas, cantCamas),
								tEspera("Tiempos de Espera"),
								lCola("Largos Medios de Colas", *this),
								tsCola("Time Series",*this){
									a[0]=0;
									a[1]=0.5;
									a[2]=1;
stream_archivo.open("salida_promedio.txt", ofstream::out);
tiempoEntremedidas = tiempoEntreMedidasConst;
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
	registerBEvent(&tS);
	// registro las distribuciones
	registerDist(&arribos);
	registerDist(&estadia);
}

void HospitalSimple::doInitialSchedules() {
	// agendo el primer paciente
	schedule(0.0, new Entity(), pacienteF);
	schedule(0.0, new Entity(),tomarMedida);
	schedule(0.0, new Entity(),timeSeries);
}

