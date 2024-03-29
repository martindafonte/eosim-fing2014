#ifndef PACIENTE_HPP_
#define PACIENTE_HPP_

#include <eosim/core/bevent.hpp>
#include <eosim/core/entity.hpp>
#include <string>

// identificador del evento fijo PacienteFeeder
const std::string pacienteF = "PacienteFeeder";
const std::string tomarMedida = "TomarMedida";
const std::string timeSeries = "TimeSeries";
const std::string reset = "Reset";
const std::string muertePaciente = "MuertePaciente";


class PacienteFeeder: public eosim::core::BEvent {
public:
	// constructor
	PacienteFeeder(eosim::core::Model& model);
	// destructor
	~PacienteFeeder();
	// rutina del evento fijo
	void eventRoutine(eosim::core::Entity* who);
};

// identificador del evento fijo SalidaPaciente
const std::string salidaP = "SalidaPaciente";


class SalidaPaciente: public eosim::core::BEvent {
public:
	// constructor
	SalidaPaciente(eosim::core::Model& model);
	// destructor
	~SalidaPaciente();
	// rutina del evento fijo
	void eventRoutine(eosim::core::Entity* who);
};

class PromPonderado: public eosim::core::BEvent {
public:
	// constructor
	PromPonderado(eosim::core::Model& model);
	// destructor
	~PromPonderado();
	// rutina del evento fijo
	void eventRoutine(eosim::core::Entity* who);
};

class TimeSeries: public eosim::core::BEvent {
public:
	// constructor
	TimeSeries(eosim::core::Model& model);
	// destructor
	~TimeSeries();
	// rutina del evento fijo
	void eventRoutine(eosim::core::Entity* who);
};

class Reset: public eosim::core::BEvent {
public:
	// constructor
	Reset(eosim::core::Model& model);
	// destructor
	~Reset();
	// rutina del evento fijo
	void eventRoutine(eosim::core::Entity* who);
};

class MuertePaciente: public eosim::core::BEvent {
public:
	// constructor
	MuertePaciente(eosim::core::Model& model);
	// destructor
	~MuertePaciente();
	// rutina del evento fijo
	void eventRoutine(eosim::core::Entity* who);
};
#endif

