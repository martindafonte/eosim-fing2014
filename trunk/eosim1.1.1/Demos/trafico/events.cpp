#include "events.hpp"
#include "traffic.hpp"
#include "vehiculo.hpp"

#include <iostream>

using namespace eosim::core;

Llega_v::Llega_v(eosim::core::Model& model):BEvent(llega_v,model){};
Llega_v::~Llega_v(){};
void Llega_v::eventRoutine(eosim::core::Entity* who){
	Traffic& t = dynamic_cast<Traffic&>(owner);
	double direccion = t.dis_direccion.sample();
	Carriles c;
	if(direccion <= t.media_izq){
		//dobla izquierda
		t.lCola_di.log(t.cruza_DI.size());
		t.cruza_DI.push(who);
		c = dobla_izq;
	}else if (direccion <= (t.media_der + t.media_izq)){
		//dobla derecha
		t.lCola_dd.log(t.cruza_DD.size());
		t.cruza_DD.push(who);
		c= dobla_der;
	}else{
		//sigue derecho
		double carril = t.dis_carriles.sample();
		if(carril< 1){
		//carril izquierda
			t.lCola_ci.log(t.cruza_CI.size());
			t.cruza_CI.push(who);
			c = centro_izq;
		}else if (carril<2){
		//carril derecha
			t.lCola_cd.log(t.cruza_CD.size());
			t.cruza_CD.push(who);
			c = centro_der;
		}else{
		//carril central
			t.lCola_cc.log(t.cruza_CC.size());
			t.cruza_CC.push(who);
			c = centro_centro;
		}
	}
	((Vehiculo*)who)->setCarril(c);
    // se agenda el arribo del proximo vehiculo
	//std::cout << "Ingresó un vehículo al carril "<<c<<" en " << who->getClock() << "\n";
	t.schedule(t.dis_llegada.sample(), new Vehiculo(), llega_v);
};

Fin_cruzar::Fin_cruzar(eosim::core::Model& model):BEvent(fin_cruzar,model){};
Fin_cruzar::~Fin_cruzar(){};
void Fin_cruzar::eventRoutine(eosim::core::Entity* who){
	Traffic& t = dynamic_cast<Traffic&>(owner);
	if(t.semaforo->verde){
		switch (((Vehiculo*)who)->getCarril())
		{
		case dobla_der:
			t.r_doblar_der.returnBin(1);
			break;
		case dobla_izq:
			t.r_doblar_izq.returnBin(1);
			break;
		case centro_centro:
			t.r_cruzar_centro.returnBin(1);
			break;
		case centro_izq:
			t.r_cruzar_izq.returnBin(1);
			break;
		case centro_der:
			t.r_cruzar_der.returnBin(1);
			break;
		}
	}
	//std::cout << "Salió un vehículo del carril "<<((Vehiculo*)who)->getCarril()<<" en "<< who->getClock() << "\n";
	delete who;
};

Luz_verde::Luz_verde(eosim::core::Model& model):BEvent(luz_verde,model){};
Luz_verde::~Luz_verde(){};
void Luz_verde::eventRoutine(eosim::core::Entity* who){
	Traffic& t = dynamic_cast<Traffic&>(owner);
	t.r_doblar_der.returnBin(t.r_doblar_der.getMax()-t.r_doblar_der.getQuantity());
	t.r_doblar_izq.returnBin(t.r_doblar_izq.getMax()-t.r_doblar_izq.getQuantity());
	t.r_cruzar_centro.returnBin(t.r_cruzar_centro.getMax() -t.r_cruzar_centro.getQuantity());
	t.r_cruzar_izq.returnBin(t.r_cruzar_izq.getMax() -t.r_cruzar_izq.getQuantity());
	t.r_cruzar_der.returnBin(t.r_cruzar_der.getMax()-t.r_cruzar_der.getQuantity());
	t.semaforo->verde=true;
	//Agendo cambio de luz
	t.schedule(t.tiempo_Verde,who,luz_roja);
	//std::cout<< "LUZ VERDE"<<"\n";
};

Luz_roja::Luz_roja(eosim::core::Model& model):BEvent(luz_roja,model){};
Luz_roja::~Luz_roja(){};
void Luz_roja::eventRoutine(eosim::core::Entity* who){
	Traffic& t = dynamic_cast<Traffic&>(owner);
	t.r_doblar_der.acquire(t.r_doblar_der.getQuantity());
	t.r_doblar_izq.acquire(t.r_doblar_izq.getQuantity());
	t.r_cruzar_centro.acquire(t.r_cruzar_centro.getQuantity());
	t.r_cruzar_izq.acquire(t.r_cruzar_izq.getQuantity());
	t.r_cruzar_der.acquire(t.r_cruzar_der.getQuantity());
	t.semaforo->verde=false;
	//Agendo cambio de luz
	t.schedule(t.tiempo_Roja,who,luz_verde);
	//std::cout<< "LUZ ROJA"<<"\n";
};

Ini_cruzar_di::Ini_cruzar_di(eosim::core::Model& model):CEvent(model){};
Ini_cruzar_di::~Ini_cruzar_di(){};
void Ini_cruzar_di::eventRoutine(){
	Traffic& t = dynamic_cast<Traffic&>(owner);
	if (t.cruza_DI.size() > 0 && t.r_doblar_izq.isAvailable(1)){
		t.r_doblar_izq.acquire(1);
		t.lCola_di.log(t.cruza_DI.size());
		Entity* e =t.cruza_DI.pop();
		t.tEspera_di.log(t.getSimTime()-e->getClock());
		t.schedule(2,e,fin_cruzar);
	}
};

Ini_cruzar_dd::Ini_cruzar_dd(eosim::core::Model& model):CEvent(model){};
Ini_cruzar_dd::~Ini_cruzar_dd(){};
void Ini_cruzar_dd::eventRoutine(){
	Traffic& t = dynamic_cast<Traffic&>(owner);
	if (t.cruza_DD.size() > 0 && t.r_doblar_der.isAvailable(1)){
		t.r_doblar_der.acquire(1);
		t.lCola_dd.log(t.cruza_DD.size());
		Entity* e =t.cruza_DD.pop();
		t.tEspera_dd.log(t.getSimTime()-e->getClock());
		t.schedule(2,e,fin_cruzar);
	}
};

Ini_cruzar_cc::Ini_cruzar_cc(eosim::core::Model& model):CEvent(model){};
Ini_cruzar_cc::~Ini_cruzar_cc(){};
void Ini_cruzar_cc::eventRoutine(){
	Traffic& t = dynamic_cast<Traffic&>(owner);
	if (t.cruza_CC.size() > 0 && t.r_cruzar_centro.isAvailable(1)){
		t.r_cruzar_centro.acquire(1);
		t.lCola_cc.log(t.cruza_CC.size());
		Entity* e =t.cruza_CC.pop();
		t.tEspera_cc.log(t.getSimTime()-e->getClock());
		t.schedule(2,e,fin_cruzar);
	}
};

Ini_cruzar_ci::Ini_cruzar_ci(eosim::core::Model& model):CEvent(model){};
Ini_cruzar_ci::~Ini_cruzar_ci(){};
void Ini_cruzar_ci::eventRoutine(){
	Traffic& t = dynamic_cast<Traffic&>(owner);
	if (t.cruza_CI.size() > 0 && t.r_cruzar_izq.isAvailable(1)){
		t.r_cruzar_izq.acquire(1);
		t.lCola_ci.log(t.cruza_CI.size());
		Entity* e =t.cruza_CI.pop();
		t.tEspera_ci.log(t.getSimTime()-e->getClock());
		t.schedule(2,e,fin_cruzar);
	}
};

Ini_cruzar_cd::Ini_cruzar_cd(eosim::core::Model& model):CEvent(model){};
Ini_cruzar_cd::~Ini_cruzar_cd(){};
void Ini_cruzar_cd::eventRoutine(){
	Traffic& t = dynamic_cast<Traffic&>(owner);
	if (t.cruza_CD.size() > 0 && t.r_cruzar_der.isAvailable(1)){
		t.r_cruzar_der.acquire(1);
		t.lCola_cd.log(t.cruza_CD.size());
		Entity* e =t.cruza_CD.pop();
		t.tEspera_cd.log(t.getSimTime()-e->getClock());
		t.schedule(2,e,fin_cruzar);
	}
};
