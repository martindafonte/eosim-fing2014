#include "paciente.hpp"
#include "hospitalcomplejo.hpp"
#include <iostream>
#include <math.h>
using namespace eosim::core;

//comienzo eventos complejos
//comienzo eventos complejos
PacienteOperacion::	PacienteOperacion(eosim::core::Model& model):BEvent(pacienteOperacion, model){};
PacienteOperacion::	~PacienteOperacion(){};
void PacienteOperacion::eventRoutine(eosim::core::Entity* who){
	HospitalComplejo hc = (HospitalComplejo &) this->owner;
	hc.hist_cola1.log(hc.cola_1.size);
	hc.cola_1.push(who);
	hc.schedule(hc.dis_arribos_opercion.sample(),new Entity(),pacienteOperacion);
};

PacienteHospital::	PacienteHospital(eosim::core::Model& model):BEvent(pacienteHospital, model){};
PacienteHospital::	~PacienteHospital(){};
void PacienteHospital::	eventRoutine(eosim::core::Entity* who){
HospitalComplejo hc = (HospitalComplejo &) this->owner;
	hc.hist_cola2.log(hc.cola_2.size);
	hc.cola_2.push(who);
	hc.schedule(hc.dis_arribos_hospital.sample(),new Entity(),pacienteHospital);
};


//end_hospital_stay
EndHospitalStay::	EndHospitalStay(eosim::core::Model& model):BEvent(endHospitalStay, model){};
EndHospitalStay::	~EndHospitalStay(){};
void EndHospitalStay::	eventRoutine(eosim::core::Entity* who){};

//end_pre_operative_stay
EndPreOperativeStay::	EndPreOperativeStay(eosim::core::Model& model):BEvent(endPreOperativeStay, model){};
EndPreOperativeStay::	~EndPreOperativeStay(){};
void EndPreOperativeStay::	eventRoutine(eosim::core::Entity* who){};


//end_operation
EndOperation::	EndOperation(eosim::core::Model& model):BEvent(endOperation, model){};
EndOperation::	~EndOperation(){};
void EndOperation::	eventRoutine(eosim::core::Entity* who){};


//end_post_operative_stay
EndPostOperativeStay::	EndPostOperativeStay(eosim::core::Model& model):BEvent(endPostOperativeStay, model){};
EndPostOperativeStay::	~EndPostOperativeStay(){};
void EndPostOperativeStay::	eventRoutine(eosim::core::Entity* who){};

//open_theater
OpenTheater::	OpenTheater(eosim::core::Model& model):BEvent(openTheater, model){};
OpenTheater::	~OpenTheater(){};
void OpenTheater::	eventRoutine(eosim::core::Entity* who){};

//close_theater
CloseTheater::	CloseTheater(eosim::core::Model& model):BEvent(closeTheater, model){};
CloseTheater::	~CloseTheater(){};
void CloseTheater::	eventRoutine(eosim::core::Entity* who){};

//start_hospital_stay
StartHospitalStay::	StartHospitalStay(eosim::core::Model& model):CEvent(model){};
StartHospitalStay::	~StartHospitalStay(){};
void StartHospitalStay:: eventRoutine(){};

//start_pre_operative_stay
StartPreOperativeStay::	StartPreOperativeStay(eosim::core::Model& model):CEvent(model){};
StartPreOperativeStay::	~StartPreOperativeStay(){};
void StartPreOperativeStay:: eventRoutine(){};

//start_operation
StartOperation::	StartOperation(eosim::core::Model& model):CEvent(model){};
StartOperation::	~StartOperation(){};
void StartOperation::	eventRoutine(){};

//start_post_operative_stay
StartPostOperativeStay::	StartPostOperativeStay(eosim::core::Model& model):CEvent(model){};
StartPostOperativeStay::	~StartPostOperativeStay(){};
void StartPostOperativeStay::	eventRoutine(){};
//Fin eventos complejos