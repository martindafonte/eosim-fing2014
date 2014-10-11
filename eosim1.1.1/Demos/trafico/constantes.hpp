#ifndef CONSTANTES_HPP_
#define CONSTANTES_HPP_

// constantes del modelo de la fabrica
const double media_vehiculos = 26.08;
const double media_izq = 2;
const double media_der = 24.4;
const double media_central= 73.6;
const double tiempo_verde = 29;
const double tiempo_roja = 21;

enum Carriles
{
	dobla_izq =0,
	dobla_der=1,
	centro_izq =2,
	centro_der = 3,
	centro_centro=4
};
#endif
