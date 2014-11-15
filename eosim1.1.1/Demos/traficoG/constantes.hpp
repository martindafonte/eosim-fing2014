#ifndef CONSTANTES_HPP_
#define CONSTANTES_HPP_

// constantes del modelo de la fabrica
const double media_vehiculos = 26.08;
const double media_izq = 2;
const double media_der = 24.4;
const double media_central= 73.6;
const double tiempo_verde = 29;
const double tiempo_roja = 21;
//const char * imagen_rojo = "../Images/roja.png";
//const char * imagen_verde_l = "../Images/verde_l.png";
//const char * imagen_verde_r = "../Images/verde_r.png";
//const char * imagen_auto_1 = "../Images/car1.png";
//const char * imagen_auto_2 = "../Images/car2.png";
//const char * imagen_fondo = "../Images/Fondo.jpg";


enum Carriles
{
	dobla_izq =0,
	dobla_der=1,
	centro_izq =2,
	centro_der = 3,
	centro_centro=4
};
#endif
