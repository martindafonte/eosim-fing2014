#ifndef PACIENTE_HPP_
#define PACIENTE_HPP_

#include <eosim/core/bevent.hpp>
#include <eosim/core/cevent.hpp>
#include <eosim/core/entity.hpp>
#include <string>

const std::string pacienteOperacion = "PacienteOperacion";
class PacienteOperacion: public eosim::core::BEvent {
public:
	PacienteOperacion(eosim::core::Model& model);
	~PacienteOperacion();
	void eventRoutine(eosim::core::Entity* who);
};

const std::string pacienteHospital = "PacienteHospital";
class PacienteHospital: public eosim::core::BEvent {
public:
	PacienteHospital(eosim::core::Model& model);
	~PacienteHospital();
	void eventRoutine(eosim::core::Entity* who);
};

const std::string endHospitalStay = "EndHospitalStay";
//end_hospital_stay
class EndHospitalStay: public eosim::core::BEvent {
public:
	EndHospitalStay(eosim::core::Model& model);
	~EndHospitalStay();
	void eventRoutine(eosim::core::Entity* who);
};

const std::string endPreOperativeStay = "EndPreOperativeStay";
//end_pre_operative_stay
class EndPreOperativeStay: public eosim::core::BEvent {
public:
	EndPreOperativeStay(eosim::core::Model& model);
	~EndPreOperativeStay();
	void eventRoutine(eosim::core::Entity* who);
};

const std::string endOperation = "EndOperation";
//end_operation
class EndOperation: public eosim::core::BEvent {
public:
	EndOperation(eosim::core::Model& model);
	~EndOperation();
	void eventRoutine(eosim::core::Entity* who);
};

const std::string endPostOperativeStay = "EndPostOperativeStay";
//end_post_operative_stay
class EndPostOperativeStay: public eosim::core::BEvent {
public:
	EndPostOperativeStay(eosim::core::Model& model);
	~EndPostOperativeStay();
	void eventRoutine(eosim::core::Entity* who);
};

const std::string openTheater = "OpenTheater";
//open_theater
class OpenTheater: public eosim::core::BEvent {
public:
	OpenTheater(eosim::core::Model& model);
	~OpenTheater();
	void eventRoutine(eosim::core::Entity* who);
};

const std::string closeTheater = "CloseTheater";
//close_theater
class CloseTheater: public eosim::core::BEvent {
public:
	CloseTheater(eosim::core::Model& model);
	~CloseTheater();
	void eventRoutine(eosim::core::Entity* who);
};

const std::string startHospitalStay = "StartHospitalStay";
//start_hospital_stay
class StartHospitalStay: public eosim::core::CEvent {
public:
	StartHospitalStay(eosim::core::Model& model);
	~StartHospitalStay();
	void eventRoutine();
};

const std::string startPreOperativeStay = "StartPreOperativeStay";
//start_pre_operative_stay
class StartPreOperativeStay: public eosim::core::CEvent {
public:
	StartPreOperativeStay(eosim::core::Model& model);
	~StartPreOperativeStay();
	void eventRoutine();
};

const std::string startOperation = "StartOperation";
//start_operation
class StartOperation: public eosim::core::CEvent {
public:
	StartOperation(eosim::core::Model& model);
	~StartOperation();
	void eventRoutine();
};

const std::string startPostOperativeStay = "StartPostOperativeStay";
//start_post_operative_stay
class StartPostOperativeStay: public eosim::core::CEvent {
public:
	StartPostOperativeStay(eosim::core::Model& model);
	~StartPostOperativeStay();
	void eventRoutine();
};
#endif

