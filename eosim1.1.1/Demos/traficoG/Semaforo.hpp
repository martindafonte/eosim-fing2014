#ifndef Semaforo_HPP_
#define Semaforo_HPP_

#include <eosim/core/entity.hpp>


class Semaforo: public eosim::core::Entity{
public:
	bool verde;
	Semaforo(){}
	~Semaforo() {}
};

#endif

