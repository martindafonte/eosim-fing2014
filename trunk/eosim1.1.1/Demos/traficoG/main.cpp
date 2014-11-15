#include <eosim/core/experiment.hpp>
#include "constantes.hpp"
#include "traffic.hpp"
#include <iostream>
#include <string>

using namespace std;

const unsigned int repeticiones = 10;

int main() {
    std::string s;
    //repito el experimento una cierta cantidad de veces
	double lCola_cc [repeticiones];
	double lCola_ci [repeticiones];
	double lCola_cd [repeticiones];
	double lCola_dd [repeticiones];
	double lCola_di [repeticiones];

	//double lCola_cc_max [repeticiones];
	//double lCola_ci_max [repeticiones];
	//double lCola_cd_max [repeticiones];
	//double lCola_dd_max [repeticiones];
	//double lCola_di_max [repeticiones];

	double tespera_cc [repeticiones];
	double tespera_ci [repeticiones];
	double tespera_cd [repeticiones];
	double tespera_dd [repeticiones];
	double tespera_di [repeticiones];

    for (int i = 0; i < repeticiones; i++) {
		Traffic t(media_vehiculos, media_izq, media_der, media_central, tiempo_verde, tiempo_roja);
		eosim::core::Experiment e;
		//std::cout << "Arranco ...\n";
		t.connectToExp(&e);
		e.setSeed((unsigned long) i * 137);
		e.run(500*50);
        //std::cout << "Termine ...\n\n\n";
		lCola_cc[i]=t.lCola_cc.getMean();
		lCola_ci[i]=t.lCola_cc.getMean();
		lCola_cd[i]=t.lCola_cc.getMean();
		lCola_dd[i]=t.lCola_cc.getMean();
		lCola_di[i]=t.lCola_cc.getMean();
		
		tespera_cc[i] = t.tEspera_cc.getMean();
		tespera_ci[i] = t.tEspera_ci.getMean();
		tespera_cd[i] = t.tEspera_cd.getMean();
		tespera_dd[i] = t.tEspera_dd.getMean();
		tespera_di[i] = t.tEspera_di.getMean();
		//int celdasCola=5;
		//int celdasTiempo = 8;
		//t.lCola_cc.print(celdasCola);
		//t.lCola_ci.print(celdasCola);
		//t.lCola_cd.print(celdasCola);
		//t.lCola_dd.print(celdasCola);
		//t.lCola_di.print(celdasCola);
		//t.tEspera_cc.print(celdasTiempo);
		//t.tEspera_ci.print(celdasTiempo);
		//t.tEspera_cd.print(celdasTiempo);
		//t.tEspera_dd.print(celdasTiempo);
		//t.tEspera_di.print(celdasTiempo);
        //std::cin >> s;
	}
	cout<<"Valores repeticiones"<<endl;
	cout<<"Largo cola(mean)		Tiempo de espera(mean)"<<endl;
	for(int i=0;i<repeticiones;i++){
		cout<<"cc "<<lCola_cc[i]<<"	"<<tespera_cc[i]<<endl;		
		cout<<"ci "<<lCola_ci[i]<<"	"<<tespera_ci[i]<<endl;		
		cout<<"cd "<<lCola_cd[i]<<"	"<<tespera_cd[i]<<endl;		
		cout<<"dd "<<lCola_dd[i]<<"	"<<tespera_dd[i]<<endl;		
		cout<<"di "<<lCola_di[i]<<"	"<<tespera_di[i]<<endl<<endl<<endl;		
	}
	string s;
	cin>>s;
	return 0;
}
