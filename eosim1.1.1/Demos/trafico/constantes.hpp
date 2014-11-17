#ifndef CONSTANTES_HPP_
#define CONSTANTES_HPP_

// constantes del modelo de tráfico
const double media_vehiculos = 26.08;
const double media_izq = 2;
const double media_der = 24.4;
const double media_central= 73.6;
const double tiempo_verde = 29;
const double tiempo_roja = 21;
const double runtime = 1000*50;
const double ts_time = 200;
const double ts_celdas = 250;

//ajuste de variable
const double var_a = -0.415694195;
const double var_v = 1.917177914;

enum Carriles
{
	dobla_izq =0,
	dobla_der=1,
	centro_izq =2,
	centro_der = 3,
	centro_centro=4
};
#endif
