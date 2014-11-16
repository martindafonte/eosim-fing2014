#include "hospitalsimple.hpp"
#include <eosim/core/entity.hpp>
#include <eosim/dist/numbergenerator.hpp>
#include <iostream>
#include<math.h>
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
								mP(*this),
								dis_muertes(MT19937,73),
								arribos(MT19937,tasaArribos),
								estadia(MT19937,tiempoEstadia,20),
								camas(cantCamas, cantCamas),
								tEspera("Tiempos de Espera"),
								r(*this),
								prob_muerte(MT19937,0,100),
								lCola("Largos Medios de Colas", *this),
								tsCola("Time Series",*this){
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
	registerBEvent(&r);
	if(!aviso_muerte_tardio)		registerBEvent(&mP);
	if(!aviso_muerte_tardio)		registerDist(&dis_muertes);
	// registro las distribuciones
	registerDist(&arribos);
	registerDist(&estadia);
	registerDist(&prob_muerte);
}

void HospitalSimple::doInitialSchedules() {
	// agendo el primer paciente
	schedule(0.0, new Entity(), pacienteF);
	schedule(0.0, new Entity(),tomarMedida);
	schedule(0.0, new Entity(),timeSeries);		
	if(!aviso_muerte_tardio) schedule(dis_muertes.sample(), new Entity(),muertePaciente);
	schedule(200000.0,new Entity(),reset);
}

