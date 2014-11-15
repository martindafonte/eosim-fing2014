#ifndef Semaforo_HPP_
#define Semaforo_HPP_

#include <eosim/core/entity.hpp>
#include <eosim/graphic/display.hpp>

class Semaforo: public eosim::core::Entity{
public:
	eosim::graphic::Sprite spr_l;
	eosim::graphic::Sprite spr_r;
	bool verde;
	Semaforo(eosim::graphic::Display& disp, double posx_l, double posy_l, double posx_r, double posy_r) : spr_l(disp,"../images/roja.png", posx_l, posy_l),spr_r(disp,"../images/roja.png", posx_r, posy_r)  {}
	~Semaforo() {}
};

#endif

