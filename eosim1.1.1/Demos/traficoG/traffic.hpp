#ifndef REPAIR_HPP
#define	REPAIR_HPP

#include "events.hpp"
#include "vehiculo.hpp"
#include "Semaforo.hpp"
#include <vector>
#include <eosim/core/model.hpp>
#include <eosim/core/renewable.hpp>
#include <eosim/dist/uniformdist.hpp>
#include <eosim/utils/entityqueuefifo.hpp>
#include <eosim/dist/poissondist.hpp>
#include <eosim/dist/negexpdist.hpp>
#include <eosim/statics/observation.hpp>
#include <eosim/statics/timeweighted.hpp>

/*
Este es el modelo de simulacion del ejemplo de la fabrica presentado en el libro
Simulation Modelling with Pascal - Ruth Davies, Robert O'Keefe

Este modelo esta construido en 3 fases
*/


class Traffic: public eosim::core::Model {
private:
	//B Events
	Llega_v eLLeggaVehiculo;
	Fin_cruzar eFinCruzar;
	Luz_verde eLuzVerde;
	Luz_roja eLuzRoja;
	//C events
	Ini_cruzar_di eIniCruzarDI;
	Ini_cruzar_dd eIniCruzarDD;
	Ini_cruzar_ci eIniCruzarCI;
	Ini_cruzar_cc eIniCruzarCC;
	Ini_cruzar_cd eIniCruzarCD;
public:
    // Doblar a la izquierda
    eosim::core::Renewable r_doblar_izq;
	// Doblar a la derecha
    eosim::core::Renewable r_doblar_der;
	// Cruzar carril izq
    eosim::core::Renewable r_cruzar_izq;
	// Cruzar carril der
    eosim::core::Renewable r_cruzar_der;
	// Cruzar carril centro
    eosim::core::Renewable r_cruzar_centro;

	Semaforo* semaforo;

    // disbribucion poisson de llegada de autos
	eosim::dist::NegexpDist dis_llegada;
    // disbribucion uniforme de los carriles 
	eosim::dist::UniformDist dis_carriles;
	// disbribucion uniforme de los carriles 
	eosim::dist::UniformDist dis_direccion;
	
	// acumulador de datos sobre los tiempos de espera en las colas
	eosim::statics::Observation tEspera_dd;
	eosim::statics::Observation tEspera_di;
	eosim::statics::Observation tEspera_ci;
	eosim::statics::Observation tEspera_cc;
	eosim::statics::Observation tEspera_cd;
	// acumulador de datos sobre el largo medio de la cola
	eosim::statics::TimeWeighted lCola_dd;
	eosim::statics::TimeWeighted lCola_di;
	eosim::statics::TimeWeighted lCola_cc;
	eosim::statics::TimeWeighted lCola_ci;
	eosim::statics::TimeWeighted lCola_cd;

	double media_izq;
	double media_der;
	double media_central;
	double tiempo_Verde;
	double tiempo_Roja;
    // cola de vehículos creados esperando elegir un carril
	eosim::utils::EntityQueueFifo llegada;
    // cola de vehículos en los carriles
	eosim::utils::EntityQueueFifo cruza_DI;
	eosim::utils::EntityQueueFifo cruza_DD;
	eosim::utils::EntityQueueFifo cruza_CI;
	eosim::utils::EntityQueueFifo cruza_CC;
	eosim::utils::EntityQueueFifo cruza_CD;

	// constructor del modelo
	Traffic(double media_vehiculos, double media_izq, double media_der, double media_central, double tiempo_verde, double tiempo_roja);
    // destructor del modelo
	~Traffic();
    // inicializa y registra los atributos del modelo, operacion abstracta de eosim::core::Model
    void init();
    // lleva al modelo a su estado inicial, operacion abstracta de eosim::core::Model
    void doInitialSchedules();
};


#endif



