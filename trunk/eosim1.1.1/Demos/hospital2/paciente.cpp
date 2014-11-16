#include "paciente.hpp"
#include "hospitalsimple.hpp"
#include "constantes.hpp"
#include <iostream>
#include <math.h>
using namespace eosim::core;


// en el constructor se utiliza el identificador definido en paciente.hpp
// en el constructor se utiliza el identificador definido en pacientefeeder.hpp
PacienteFeeder::PacienteFeeder(Model& model): BEvent(pacienteF, model) {}

PacienteFeeder::~PacienteFeeder() {}

void PacienteFeeder::eventRoutine(Entity* who) {
	// se anuncia la llegada del paciente
	//std::cout << "llego un paciente en " << who->getClock() << "\n";
	// se castea owner a un HospitalSimple
	HospitalSimple& h= dynamic_cast<HospitalSimple&>(owner);
	if(aviso_muerte_tardio && (h.prob_muerte.sample() > 95)){
	//significa que el paciente no llegó
		delete who;
	}else{
		if (h.camas.isAvailable(1)) {
			h.camas.acquire(1);
			//std::cout << "un paciente fue aceptado en una cama " << h.getSimTime() << "\n";
			h.tEspera.log(h.getSimTime() - who->getClock());
			h.schedule(h.estadia.sample(), who, salidaP);
		}
		else {
		 // se acumulan datos en los histogramas
		 h.lCola.log(h.cola.size());
			// se pone al paciente recien llegado en la cola
			h.cola.push(who);
		}
	}
    // se agenda el arribo del un nuevo paciente
	h.schedule(std::max(h.arribos.sample(),0.0), new Entity(), pacienteF);
}

// en el constructor se utiliza el identificador definido en paciente.hpp
SalidaPaciente::SalidaPaciente(Model& model): BEvent(salidaP, model) {}

SalidaPaciente::~SalidaPaciente() {}

void SalidaPaciente::eventRoutine(Entity* who) {
	// se informa la salida de un paciente
	//std::cout << "un paciente se retira en " << who->getClock() << "\n";
	// se castea owner a un HospitalSimple
	HospitalSimple& h = dynamic_cast<HospitalSimple&>(owner);
	// se retorna la cama que el paciente ocupaba
	h.camas.returnBin(1);
	if (!h.cola.empty()) {
		h.camas.acquire(1);
		//std::cout << "un paciente fue aceptado en una cama " << h.getSimTime() << "\n";
        h.lCola.log(h.cola.size());
		Entity* ent = h.cola.pop();
		h.tEspera.log(h.getSimTime() - ent->getClock());
		h.schedule(h.estadia.sample(), ent, salidaP);
	}
	// se elimina al paciente del sistema
	delete who;
}

// en el constructor se utiliza el identificador definido en paciente.hpp
PromPonderado::PromPonderado(Model& model): BEvent(tomarMedida, model) {}

PromPonderado::~PromPonderado() {}

void PromPonderado::eventRoutine(Entity* who) {
	HospitalSimple& m = dynamic_cast<HospitalSimple&>(owner);
	m.stream_archivo <<m.getSimTime()<<"\t"<<m.lCola.getMean()<<std::endl;
	m.schedule(100,who,tomarMedida);
}

// en el constructor se utiliza el identificador definido en paciente.hpp
TimeSeries::TimeSeries(Model& model): BEvent(timeSeries, model) {}

TimeSeries::~TimeSeries() {}

void TimeSeries::eventRoutine(Entity* who) {
	HospitalSimple& m = dynamic_cast<HospitalSimple&>(owner);
	m.tsCola.log(m.cola.size());
	m.schedule(m.tiempoEntremedidas,who,timeSeries);
}

// en el constructor se utiliza el identificador definido en paciente.hpp
Reset::Reset(Model& model): BEvent(reset, model) {}

Reset::~Reset() {}

void Reset::eventRoutine(Entity* who) {
	HospitalSimple& m = dynamic_cast<HospitalSimple&>(owner);
	m.lCola.reset();
	m.tEspera.reset();
	m.tsCola.reset();
}

MuertePaciente::MuertePaciente(Model& model): BEvent(muertePaciente, model) {}

MuertePaciente::~MuertePaciente() {}

void MuertePaciente::eventRoutine(Entity* who) {
	HospitalSimple& m = dynamic_cast<HospitalSimple&>(owner);
	//desagendar un paciente
	Entity * es;
	if(( es = m.removeRandomBEvent(pacienteF)) == nullptr ){
		std::cout<<"No se encontraron pacientes para desagendar"<<std::endl;
	}else{
		std::cout<<"paciente eliminado con éxito"<<std::endl;
		delete es;
	}
	//agendar siguiente evento de muerte
	m.schedule(m.dis_muertes.sample(),who,muertePaciente);
}