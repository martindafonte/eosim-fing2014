#include "paciente.hpp"
#include "hospitalcomplejo.hpp"
#include <iostream>
#include <math.h>
#include "constantes.hpp"
#include <cassert>
#include <eosim/dist/uniformdist.hpp>
using namespace eosim::core;

//comienzo eventos complejos
//comienzo eventos complejos
Paciente::	Paciente(eosim::core::Model& model):BEvent(paciente, model){};
Paciente::	~Paciente(){};
void Paciente::eventRoutine(eosim::core::Entity* who){
	HospitalComplejo& hc = dynamic_cast<HospitalComplejo&>(owner);
	Patient * p = (Patient *) who;
	double prob = hc.dis_tipo_paciente.sample();
	p->operacion =  prob < 2; //paciente operacion si es menor a 2
	p->priority = floor(hc.dis_tipo_paciente.sample()); //probabilidades 0, 1, 2
	if(p->operacion) {
		std::cout << "Arribo de paciente operación "<<who->getClock() <<std::endl;
		hc.hist_cola1.log(hc.cola_1.size());
		hc.cola_1.push(who);
	}
	else {
		std::cout << "Arribo de paciente hospital "<<hc.getSimTime() <<std::endl;
		hc.hist_cola2.log(hc.cola_2.size());
		if(!seleccionRandomFromQueue) hc.cola_2.push(who);
		else{
			//si es selección random uso solo 1 cola
			hc.hist_cola1.log(hc.cola_1.size());
			hc.cola_1.push(who); 
		}
	}
	double d = hc.dis_arribos_opercion.sample();
	hc.schedule(d>0?d:0,new Patient(),paciente);
	
};

//end_hospital_stay
EndHospitalStay::	EndHospitalStay(eosim::core::Model& model):BEvent(endHospitalStay, model){};
EndHospitalStay::	~EndHospitalStay(){};
void EndHospitalStay::	eventRoutine(eosim::core::Entity* who){
HospitalComplejo &hc = dynamic_cast<HospitalComplejo&>(owner);
hc.hist_camas.log(hc.camas.getMax() - hc.camas.getQuantity());
hc.camas.returnBin(1);
std::cout << "Fin estadia hospital "<<hc.getSimTime() <<std::endl;
delete who;
};

//end_pre_operative_stay
EndPreOperativeStay::	EndPreOperativeStay(eosim::core::Model& model):BEvent(endPreOperativeStay, model){};
EndPreOperativeStay::	~EndPreOperativeStay(){};
void EndPreOperativeStay::	eventRoutine(eosim::core::Entity* who){
	HospitalComplejo &hc = dynamic_cast<HospitalComplejo&>(owner);
	hc.cola_3.push(who);
	std::cout << "Fin Estadia Pre Operacion "<<hc.getSimTime() <<std::endl;
};


//end_operation
EndOperation::	EndOperation(eosim::core::Model& model):BEvent(endOperation, model){};
EndOperation::	~EndOperation(){};
void EndOperation::	eventRoutine(eosim::core::Entity* who){
HospitalComplejo &hc = dynamic_cast<HospitalComplejo&>(owner);
hc.sala_operaciones->available =true;
Entity * e =this->owner.removeNextBEvent();
Theater * so = dynamic_cast<Theater *>(e);//estoy sacando la sala de operaciones
Theater * so2 = hc.sala_operaciones;
assert(so == so2 && "La sala de operaciones no coincide con la entidad");
hc.cola_4.push(who);
std::cout << "Fin Operacion "<<hc.getSimTime() <<std::endl;
};


//end_post_operative_stay
EndPostOperativeStay::	EndPostOperativeStay(eosim::core::Model& model):BEvent(endPostOperativeStay, model){};
EndPostOperativeStay::	~EndPostOperativeStay(){};
void EndPostOperativeStay::	eventRoutine(eosim::core::Entity* who){
HospitalComplejo &hc = dynamic_cast<HospitalComplejo&>(owner);
hc.hist_camas.log(hc.camas.getMax() - hc.camas.getQuantity());
hc.camas.returnBin(1);
delete who;
std::cout << "Fin estadia post Operacion "<<hc.getSimTime() <<std::endl;
};

//open_theater
OpenTheater::	OpenTheater(eosim::core::Model& model):BEvent(openTheater, model){};
OpenTheater::	~OpenTheater(){};
void OpenTheater::	eventRoutine(eosim::core::Entity* who){
	HospitalComplejo &hc = dynamic_cast<HospitalComplejo&>(owner);
	hc.sala_operaciones->open = true;
	hc.schedule(theater_open_time,who,closeTheater);
	std::cout << "### Abre sala operaciones "<<hc.getSimTime() <<std::endl;
};

//close_theater
CloseTheater::	CloseTheater(eosim::core::Model& model):BEvent(closeTheater, model){};
CloseTheater::	~CloseTheater(){};
void CloseTheater::	eventRoutine(eosim::core::Entity* who){
	HospitalComplejo &hc= dynamic_cast<HospitalComplejo&>(owner);
	hc.sala_operaciones->open = false;
	hc.schedule(theather_close_time,who,openTheater);
	std::cout << "### Cierra sala operaciones "<<hc.getSimTime() <<std::endl;
};

//start_hospital_stay
StartHospitalStay::	StartHospitalStay(eosim::core::Model& model):CEvent(model){};
StartHospitalStay::	~StartHospitalStay(){};
void StartHospitalStay:: eventRoutine(){
	HospitalComplejo &hc = dynamic_cast<HospitalComplejo&>(owner);
	while(hc.camas.isAvailable(1) && (!hc.cola_1.empty())) {
		Patient * p;
		int index = -1;
		if(seleccionRandomFromQueue)
		{
			index = rand() % (hc.cola_1.size());
		}else{
			int max_priority = -1;
		
			for(int i =0;i<hc.cola_1.size();i++){
				if(max_priority < ((Patient *)(hc.cola_1.operator[](i)))->priority){
					index = i;
				}
			}
		}
		p= (Patient *)hc.cola_1.operator[](index);
		hc.cola_1.remove(index);
		hc.hist_camas.log(hc.camas.getMax()-hc.camas.getQuantity());
		hc.camas.acquire(1);
		hc.hist_cola1.log(hc.cola_1.size());

		if(seleccionRandomFromQueue && p->operacion){// Si se selecciona random de 1 sola cola y se es del tipo operación
			double d =hc.dis_pre_operative_stay.sample();
			hc.schedule(d > 0 ?d:0,p,endPreOperativeStay);
			std::cout << "Comienza estadia pre operacion "<<hc.getSimTime() <<std::endl;
		}else{// Si no se selecciona random o es del tipo hospital
		double d = hc.dis_hospital_stay.sample();
		hc.schedule(d > 0 ?d:0,p,endHospitalStay);
		std::cout << "Comienza estadia hospital "<<hc.getSimTime() <<std::endl;
		}
	}
};

//start_pre_operative_stay
StartPreOperativeStay::	StartPreOperativeStay(eosim::core::Model& model):CEvent(model){};
StartPreOperativeStay::	~StartPreOperativeStay(){};
void StartPreOperativeStay:: eventRoutine(){
	HospitalComplejo &hc = dynamic_cast<HospitalComplejo&>(owner);
	while(hc.camas.isAvailable(1) && (!hc.cola_2.empty())) {
		hc.hist_camas.log(hc.camas.getMax()-hc.camas.getQuantity());
		hc.camas.acquire(1);
		hc.hist_cola2.log(hc.cola_2.size());
		double d =hc.dis_pre_operative_stay.sample();
		int max_priority = -1;
		int index = -1;
			for(int i =0;i<hc.cola_2.size();i++){
				if(max_priority < ((Patient *)(hc.cola_2.operator[](i)))->priority){
					index = i;
				}
			}
		Patient * p= (Patient *)hc.cola_2.operator[](index);
		hc.cola_2.remove(index);
		hc.schedule(d > 0 ?d:0,p,endPreOperativeStay);
		std::cout << "Comienza estadia pre operacion "<<hc.getSimTime() <<std::endl;
	}
};

//start_operation
StartOperation::	StartOperation(eosim::core::Model& model):CEvent(model){};
StartOperation::	~StartOperation(){};
void StartOperation::	eventRoutine(){
	HospitalComplejo &hc = dynamic_cast<HospitalComplejo&>(owner);
	while(hc.sala_operaciones->open && hc.sala_operaciones->available && (!hc.cola_3.empty())) {
		hc.sala_operaciones->available = false;
		Entity * e = hc.cola_3.pop();
		hc.hist_op_espera.log(hc.getSimTime()-e->getClock());
		double d = hc.dis_tiempo_operacion.sample();
		hc.schedule(d> 0 ?d:0,e,endOperation);
		hc.schedule(d >0 ? d:0,hc.sala_operaciones,endOperation);//pongo la sala de operaciones segunda así es más facil sacarla
		std::cout << "Comienza operacion "<<hc.getSimTime() <<std::endl;
	}
};


//start_post_operative_stay
StartPostOperativeStay::	StartPostOperativeStay(eosim::core::Model& model):CEvent(model){};
StartPostOperativeStay::	~StartPostOperativeStay(){};
void StartPostOperativeStay::	eventRoutine(){
	HospitalComplejo &hc = dynamic_cast<HospitalComplejo&>(owner);
	while(!hc.cola_4.empty()) {
		double d = hc.dis_post_operative_stay.sample();
		hc.schedule(d > 0?d:0,hc.cola_4.pop(),endPostOperativeStay);
		std::cout << "Comienza estadia post operacion "<<hc.getSimTime() <<std::endl;
	}
};
//Fin eventos complejos