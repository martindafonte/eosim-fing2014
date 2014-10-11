#ifndef MACHINE_HPP_
#define MACHINE_HPP_

#include <eosim/core/entity.hpp>
#include "constantes.hpp"


class Vehiculo: public eosim::core::Entity{
private:
    Carriles carril;
public:
	Vehiculo(){}
	Vehiculo(Carriles number): carril(number) {}
	Carriles getCarril() {return carril; }
	void setCarril(Carriles pCarril){ carril = pCarril;}
	~Vehiculo() {}
};

#endif

