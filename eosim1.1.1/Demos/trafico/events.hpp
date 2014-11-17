#ifndef EVENTS_HPP
#define EVENTS_HPP

#include <eosim/core/bevent.hpp>
#include <eosim/core/entity.hpp>
#include <eosim/core/cevent.hpp>
#include <string>

const std::string llega_v = "llega_v";
const std::string fin_cruzar = "fin_cruzar";
const std::string ini_cruzar_di = "cruza_di";
const std::string ini_cruzar_dd = "cruza_dd";
const std::string ini_cruzar_ci = "cruza_ci";
const std::string ini_cruzar_cc = "cruza_cc";
const std::string ini_cruzar_cd = "cruza_cd";
const std::string luz_verde = "luz_verde";
const std::string luz_roja = "luz_roja";



class Llega_v: public eosim::core::BEvent {
public:
	Llega_v(eosim::core::Model& model);
	~Llega_v();
	void eventRoutine(eosim::core::Entity* who);
};

class Fin_cruzar: public eosim::core::BEvent {
public:
	Fin_cruzar(eosim::core::Model& model);
	~Fin_cruzar();
	void eventRoutine(eosim::core::Entity* who);
};

class Luz_verde: public eosim::core::BEvent {
public:
	Luz_verde(eosim::core::Model& model);
	~Luz_verde();
	void eventRoutine(eosim::core::Entity* who);
};

class Luz_roja: public eosim::core::BEvent {
public:
	Luz_roja(eosim::core::Model& model);
	~Luz_roja();
	void eventRoutine(eosim::core::Entity* who);
};

class Ini_cruzar_di: public eosim::core::CEvent {
public:
	Ini_cruzar_di(eosim::core::Model& model);
	~Ini_cruzar_di();
	void eventRoutine();
};

class Ini_cruzar_dd: public eosim::core::CEvent {
public:
	Ini_cruzar_dd(eosim::core::Model& model);
	~Ini_cruzar_dd();
	void eventRoutine();
};
class Ini_cruzar_ci: public eosim::core::CEvent {
public:
	Ini_cruzar_ci(eosim::core::Model& model);
	~Ini_cruzar_ci();
	void eventRoutine();
};
class Ini_cruzar_cd: public eosim::core::CEvent {
public:
	Ini_cruzar_cd(eosim::core::Model& model);
	~Ini_cruzar_cd();
	void eventRoutine();
};
class Ini_cruzar_cc: public eosim::core::CEvent {
public:
	Ini_cruzar_cc(eosim::core::Model& model);
	~Ini_cruzar_cc();
	void eventRoutine();
};

class TomarTS: public eosim::core::BEvent {
public:
	TomarTS(eosim::core::Model& model);
	~TomarTS();
	void eventRoutine(eosim::core::Entity* who);
};

class Reset: public eosim::core::BEvent{
public:
	Reset(eosim::core::Model& model);
	~Reset();
	void eventRoutine(eosim::core::Entity* who);
};

#endif


