#include "hospitalcomplejo.hpp"
#include <eosim/core/entity.hpp>
#include <eosim/dist/numbergenerator.hpp>
#include <iostream>
#include<math.h>
#include "constantes.hpp"

using namespace eosim::core;
using namespace eosim::dist;

using namespace std;

HospitalComplejo::HospitalComplejo():
								//B events
								b1(*this),
								b3(*this),
								b4(*this),
								b5(*this),
								b6(*this),
								b7(*this),
								b8(*this),
								//C events
								c1(*this),
								c2(*this),
								c3(*this),
								c4(*this),
								//bed bin
								camas(cantCamas, cantCamas),
								//histogramas
								hist_cola1("Largo Cola 1"),
								hist_cola2("Largo Cola 2"),
								hist_camas("Utilización de camas"),
								hist_op_espera("Espera sala operaciónes"),
								//distribuciones
								//dis_arribos_hospital(MT19937,tasaArribosHospital),
								dis_arribos_opercion(MT19937,tasaArribos),
								dis_hospital_stay(MT19937,tiempoEstadiaHospital),
								dis_pre_operative_stay(MT19937,tiempoPreOperEstadia),
								dis_post_operative_stay(MT19937,tiempoPostOperEstadia),
								dis_tiempo_operacion(MT19937,tiempoOperacion,tiempoOperacionSD),
								dis_tipo_paciente(MT19937,0,3)
								{
									sala_operaciones = new Theater();
}

HospitalComplejo::~HospitalComplejo() {
}

void HospitalComplejo::init() {
	sala_operaciones->open = true;
	sala_operaciones->available = true;
	// registro los eventos B
	registerBEvent(&b1);
	registerBEvent(&b3);
	registerBEvent(&b4);
	registerBEvent(&b5);
	registerBEvent(&b6);
	registerBEvent(&b7);
	registerBEvent(&b8);

	//registro los eventos C
	registerCEvent(&c1);
	registerCEvent(&c2);
	registerCEvent(&c3);
	registerCEvent(&c4);
	
	// registro las distribuciones
	//registerDist(&dis_arribos_hospital);
	registerDist(&dis_arribos_opercion);
	registerDist(&dis_hospital_stay);
	registerDist(&dis_post_operative_stay);
	registerDist(&dis_pre_operative_stay);
	registerDist(&dis_tiempo_operacion);
}

void HospitalComplejo::doInitialSchedules() {
	//represento a la sala operaciones como 2 entidades, 1 para abrir y cerrar y otra para los pacientes
	schedule(0.0,new Entity(),openTheater);
	// agendo el primer paciente
	schedule(0.0, new Entity(), paciente);
}