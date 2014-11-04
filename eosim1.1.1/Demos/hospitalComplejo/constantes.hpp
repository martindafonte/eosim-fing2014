#ifndef CONSTANTES_HPP_
#define CONSTANTES_HPP_

// constantes del modelo del hospital complejo
//seeds
const int seed_paciente1 = 1;
const int seed_paciente2 = 2;
const int seed_hostpitalstay = 3;
const int seed_preop_stay = 4;
const int seed_operation = 5;
const int seed_postop_stay = 6;

const double runTime = 500000.0;

//Variables del problema
const int theater_open_time = 4;
const int theather_close_time = 20;
const unsigned int cantCamas = 20;

//valores distribución
const double tasaArribosHospital = 12;
const double tasaArribosOperacion = 6;
const double tiempoEstadiaHospital = 2.5*24;
const double tiempoPreOperEstadia= 24;
const double tiempoPostOperEstadia= 24*3;
const double tiempoOperacion= 0.75;
const double tiempoOperacionSD = 0.25;


#endif
