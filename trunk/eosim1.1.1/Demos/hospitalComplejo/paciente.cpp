#include "paciente.hpp"
#include "hospitalcomplejo.hpp"
#include <iostream>
#include <math.h>
using namespace eosim::core;

//comienzo eventos complejos
//comienzo eventos complejos
PacienteFeeder1::	PacienteFeeder1(eosim::core::Model& model):BEvent(pacienteFeeder1, model){};
PacienteFeeder1::	~PacienteFeeder1(){};
void PacienteFeeder1::eventRoutine(eosim::core::Entity* who)
	{};

PacienteFeeder2::	PacienteFeeder2(eosim::core::Model& model):BEvent(pacienteFeeder2, model){};
PacienteFeeder2::	~PacienteFeeder2(){};
void PacienteFeeder2::	eventRoutine(eosim::core::Entity* who){};


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