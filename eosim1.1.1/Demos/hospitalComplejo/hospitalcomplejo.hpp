#ifndef HOSPITAL_COMPLEJO_HPP_
#define HOSPITAL_COMPLEJO_HPP_

#include <eosim/core/model.hpp>
#include <eosim/core/entity.hpp>
#include <eosim/utils/entityqueuefifo.hpp>
#include <eosim/core/renewable.hpp>
#include <eosim/dist/lognormaldist.hpp>
#include <eosim/dist/normaldist.hpp>
#include <eosim/dist/poissondist.hpp>
#include <eosim/dist/empiricdist.hpp>
#include <eosim/dist/negexpdist.hpp>
#include <eosim/dist/uniformdist.hpp>
#include <eosim/statics/timeweighted.hpp>
#include <eosim/statics/observation.hpp>
#include <eosim/statics/timeseries.hpp>
#include "paciente.hpp"
#include <iostream>
#include <fstream>

/*
Este es el modelo de simulacion del ejemplo del hospital simple presentado en el libro
Simulation Modelling with Pascal - Ruth Davies, Robert O'Keefe

Este modelo esta construido en 2 fases
*/
class Theater : public eosim::core::Entity{
public:
	bool open, available;
};

class Patient : public eosim::core::Entity{
public:
	int priority;
	bool operacion;
};

class HospitalComplejo: public eosim::core::Model {
private:
	Paciente b1;
	EndHospitalStay b3;
	EndPreOperativeStay b4;
	EndOperation b5;
	EndPostOperativeStay b6;
	OpenTheater b7;
	CloseTheater b8;
	//Al definir c1 primero que c2 se le da prioridad a los pacientes que no tienen que operarse
	StartHospitalStay c1;
	StartPreOperativeStay c2;
	StartOperation c3;
	StartPostOperativeStay c4;

public:
	// camas del hospital
	eosim::core::Renewable camas;
	// colas de espera
	eosim::utils::EntityQueueFifo cola_1;
	eosim::utils::EntityQueueFifo cola_2;
	eosim::utils::EntityQueueFifo cola_3;
	eosim::utils::EntityQueueFifo cola_4;

	
    double tiempoEntremedidas;
	// distribucion aleatoria de arribos de pacientes (exponencial negativa)
	//eosim::dist::NegexpDist dis_arribos_hospital;
	eosim::dist::UniformDist dis_tipo_paciente;
	eosim::dist::NegexpDist dis_arribos_opercion;
	eosim::dist::NegexpDist dis_hospital_stay;
	eosim::dist::NegexpDist dis_pre_operative_stay;
	eosim::dist::NegexpDist dis_post_operative_stay;
	eosim::dist::NormalDist dis_tiempo_operacion;

	Theater  * sala_operaciones;

	
	// histogramas de la soluci�n
	eosim::statics::Observation hist_cola1,hist_cola2,hist_camas,hist_op_espera;

	//Metodos
	// constructor del modelo
	HospitalComplejo();
	// destructor del modelo
	~HospitalComplejo();
	// inicializa y registra los atributos del modelo, operacion abstracta de eosim::core::Model
	void init();
	// lleva al modelo a su estado inicial, operacion abstracta de eosim::core::Model
	void doInitialSchedules();
};

#endif

