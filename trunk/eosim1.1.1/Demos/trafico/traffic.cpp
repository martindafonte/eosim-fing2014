#include "traffic.hpp"
#include <eosim/dist/numbergenerator.hpp>
#include <iostream>

using namespace eosim::core;
using namespace eosim::dist;

Traffic::Traffic(double p_media_vehiculos, double p_media_izq, double p_media_der, double p_media_central, double p_tiempo_verde, double p_tiempo_roja):
	eLLeggaVehiculo(*this),
	eFinCruzar(*this),
	eLuzVerde(*this),
	eLuzRoja(*this),
	eIniCruzarDI(*this),
	eIniCruzarDD(*this),
	eIniCruzarCC(*this),
	eIniCruzarCI(*this),
	eIniCruzarCD(*this),
	eTs(*this),
	eRs(*this),
	dis_llegada(MT19937,(50/p_media_vehiculos)),//Se puse 50 para permitir variar los tiempos de luz
	dis_carriles(MT19937,0,3),
	dis_direccion(MT19937,1,1000),
	r_doblar_der(1,1),
	r_doblar_izq(1,1),
	r_cruzar_centro(1,1),
	r_cruzar_der(1,1),
	r_cruzar_izq(1,1),
	media_izq(10*p_media_izq),
	media_der(10*p_media_der),
	media_central(10*p_media_central),
	tiempo_Roja(p_tiempo_roja),
	tiempo_Verde(p_tiempo_verde),
	tEspera_dd("Tiempo Espera DD"),
	tEspera_di("Tiempo Espera DI"),
	tEspera_cc("Tiempo Espera CC"),
	tEspera_ci("Tiempo Espera CI"),
	tEspera_cd("Tiempo Espera CD"),
	lCola_dd("Largo Cola DD",*this),
	lCola_di("Largo Cola DI",*this),
	lCola_cc("Largo Cola CC",*this),
	lCola_cd("Largo Cola CD",*this),
	lCola_ci("Largo Cola CI",*this),
	ts_colacc("TimeSeries CC",*this),
	ts_colaci("TimeSeries CI",*this),
	ts_colacd("TimeSeries CD",*this),
	ts_coladd("TimeSeries DD",*this),
	ts_coladi("TimeSeries DI",*this)
{
	stream_archivo.open("salida_promedio.txt", std::ofstream::out);
	semaforo = new Semaforo();
	tiempo_llegada = 0;
	cant_vehiculos = 0;
}

	Traffic::~Traffic() {
		stream_archivo.flush();
		stream_archivo.close();
		stream_archivo;
	}

void Traffic::init() {

	registerBEvent(&eLLeggaVehiculo);
	registerBEvent(&eFinCruzar);
	registerBEvent(&eLuzVerde);
	registerBEvent(&eLuzRoja);
	registerBEvent(&eTs);
	registerBEvent(&eRs);

	registerCEvent(&eIniCruzarCC);
	registerCEvent(&eIniCruzarCI);
	registerCEvent(&eIniCruzarCD);
	registerCEvent(&eIniCruzarDI);
	registerCEvent(&eIniCruzarDD);
	
	registerDist(&dis_carriles);
	registerDist(&dis_llegada);
}

void Traffic::doInitialSchedules() {
	schedule(0.0, semaforo, luz_verde);
	schedule(0.0,new Vehiculo(),llega_v);
	schedule(ts_time,new Entity(),"TomarTS");
	schedule(10000,new Entity(),"Reset");
}

