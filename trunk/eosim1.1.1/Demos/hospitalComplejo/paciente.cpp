#include "paciente.hpp"
#include "hospitalcomplejo.hpp"
#include <iostream>
#include <math.h>
#include "constantes.hpp"
using namespace eosim::core;

//comienzo eventos complejos
//comienzo eventos complejos
Paciente::	Paciente(eosim::core::Model& model):BEvent(paciente, model){};
Paciente::	~Paciente(){};
void Paciente::eventRoutine(eosim::core::Entity* who){
	HospitalComplejo& hc = dynamic_cast<HospitalComplejo&>(owner);
	
	if(hc.dis_tipo_paciente.sample() > 2){
	//paciente hospital
		hc.hist_cola2.log(hc.cola_2.size());
		hc.cola_2.push(who);
	}else{
		//paciente operación
		hc.hist_cola1.log(hc.cola_1.size());
		hc.cola_1.push(who);
	}
	double d = hc.dis_arribos_opercion.sample();
	hc.schedule(d>0?d:0,new Entity(),paciente);
};

//end_hospital_stay
EndHospitalStay::	EndHospitalStay(eosim::core::Model& model):BEvent(endHospitalStay, model){};
EndHospitalStay::	~EndHospitalStay(){};
void EndHospitalStay::	eventRoutine(eosim::core::Entity* who){
HospitalComplejo &hc = dynamic_cast<HospitalComplejo&>(owner);
hc.hist_camas.log(hc.camas.getMax() - hc.camas.getQuantity());
hc.camas.returnBin(1);
delete who;
};

//end_pre_operative_stay
EndPreOperativeStay::	EndPreOperativeStay(eosim::core::Model& model):BEvent(endPreOperativeStay, model){};
EndPreOperativeStay::	~EndPreOperativeStay(){};
void EndPreOperativeStay::	eventRoutine(eosim::core::Entity* who){
	HospitalComplejo &hc = dynamic_cast<HospitalComplejo&>(owner);
	hc.cola_3.push(who);
};


//end_operation
EndOperation::	EndOperation(eosim::core::Model& model):BEvent(endOperation, model){};
EndOperation::	~EndOperation(){};
void EndOperation::	eventRoutine(eosim::core::Entity* who){
HospitalComplejo &hc = dynamic_cast<HospitalComplejo&>(owner);
hc.sala_operaciones.available =true;
hc.cola_4.push(who);
};


//end_post_operative_stay
EndPostOperativeStay::	EndPostOperativeStay(eosim::core::Model& model):BEvent(endPostOperativeStay, model){};
EndPostOperativeStay::	~EndPostOperativeStay(){};
void EndPostOperativeStay::	eventRoutine(eosim::core::Entity* who){
HospitalComplejo &hc = dynamic_cast<HospitalComplejo&>(owner);
hc.hist_camas.log(hc.camas.getMax() - hc.camas.getQuantity());
hc.camas.returnBin(1);
delete who;
};

//open_theater
OpenTheater::	OpenTheater(eosim::core::Model& model):BEvent(openTheater, model){};
OpenTheater::	~OpenTheater(){};
void OpenTheater::	eventRoutine(eosim::core::Entity* who){
	HospitalComplejo &hc = dynamic_cast<HospitalComplejo&>(owner);
	hc.sala_operaciones.open = true;
	hc.schedule(theater_open_time,who,closeTheater);
};

//close_theater
CloseTheater::	CloseTheater(eosim::core::Model& model):BEvent(closeTheater, model){};
CloseTheater::	~CloseTheater(){};
void CloseTheater::	eventRoutine(eosim::core::Entity* who){
	HospitalComplejo &hc= dynamic_cast<HospitalComplejo&>(owner);
	hc.sala_operaciones.open = false;
	hc.schedule(theather_close_time,who,openTheater);
};

//start_hospital_stay
StartHospitalStay::	StartHospitalStay(eosim::core::Model& model):CEvent(model){};
StartHospitalStay::	~StartHospitalStay(){};
void StartHospitalStay:: eventRoutine(){
	HospitalComplejo &hc = dynamic_cast<HospitalComplejo&>(owner);
	while(hc.camas.isAvailable(1) && (!hc.cola_1.empty())) {
		hc.hist_camas.log(hc.camas.getMax()-hc.camas.getQuantity());
		hc.camas.acquire(1);
		hc.hist_cola1.log(hc.cola_1.size());
		double d = hc.dis_hospital_stay.sample();
		hc.schedule(d > 0 ?d:0,hc.cola_1.pop(),endHospitalStay);
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
		hc.hist_cola1.log(hc.cola_2.size());
		double d =hc.dis_pre_operative_stay.sample();
		hc.schedule(d > 0 ?d:0,hc.cola_2.pop(),endPreOperativeStay);
	}
};

//start_operation
StartOperation::	StartOperation(eosim::core::Model& model):CEvent(model){};
StartOperation::	~StartOperation(){};
void StartOperation::	eventRoutine(){
	HospitalComplejo &hc = dynamic_cast<HospitalComplejo&>(owner);
	while(hc.sala_operaciones.open && hc.sala_operaciones.available && (!hc.cola_3.empty())) {
		hc.sala_operaciones.available = false;
		Entity * e = hc.cola_3.pop();
		hc.hist_op_espera.log(hc.getSimTime()-e->getClock());
		double d = hc.dis_tiempo_operacion.sample();
		hc.schedule(d >0 ? d:0,&(hc.sala_operaciones),endOperation);
		hc.schedule(d> 0 ?d:0,e,endOperation);
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
	}
};
//Fin eventos complejos