#include <eosim/core/experiment.hpp>
#include "constantes.hpp"
#include "traffic.hpp"
#include <iostream>
#include <string>

using namespace std;

const unsigned int repeticiones = 1;

int main() {
    std::string s;
    //repito el experimento una cierta cantidad de veces
	double lCola_cc [repeticiones];
	double lCola_ci [repeticiones];
	double lCola_cd [repeticiones];
	double lCola_dd [repeticiones];
	double lCola_di [repeticiones];
	double prom_llegada[repeticiones];
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

	//double s_tiempo_verde[3] ={29,39,19};
	//double s_tiempo_roja[3] = {21,11,31};
	//double s_media_vehiculos [2] = {media_vehiculos, media_vehiculos*1.05*1.05};

    for (int i = 0; i < repeticiones; i++) {
		Traffic t(media_vehiculos, media_izq, media_der, media_central,tiempo_verde /*s_tiempo_verde[i]*/, tiempo_roja /* s_tiempo_roja[i]*/);
		eosim::core::Experiment e;
		std::cout << "Arranco ...\n";
		t.connectToExp(&e);
		e.setSeed((unsigned long) i * 13289);
		e.run(runtime);
        std::cout << "Termine ...\n\n\n";
		lCola_cc[i]=t.lCola_cc.getMean();
		lCola_ci[i]=t.lCola_ci.getMean();
		lCola_cd[i]=t.lCola_cd.getMean();
		lCola_dd[i]=t.lCola_dd.getMean();
		lCola_di[i]=t.lCola_di.getMean();
		
		tespera_cc[i] = t.tEspera_cc.getMean();
		tespera_ci[i] = t.tEspera_ci.getMean();
		tespera_cd[i] = t.tEspera_cd.getMean();
		tespera_dd[i] = t.tEspera_dd.getMean();
		tespera_di[i] = t.tEspera_di.getMean();

		t.ts_colacc.print(ts_celdas,"salida_cc.sal");
		t.ts_colaci.print(ts_celdas,"salida_ci.sal");
		t.ts_colacd.print(ts_celdas,"salida_cd.sal");
		t.ts_coladd.print(ts_celdas,"salida_dd.sal");
		t.ts_coladi.print(ts_celdas,"salida_di.sal");
		prom_llegada[i] = t.tiempo_llegada / t.cant_vehiculos;
		int celdasCola=5;
		int celdasTiempo = 8;
		t.lCola_cc.print(celdasCola);
		t.lCola_ci.print(celdasCola);
		t.lCola_cd.print(celdasCola);
		t.lCola_dd.print(celdasCola);
		t.lCola_di.print(celdasCola);
		t.tEspera_cc.print(celdasTiempo);
		t.tEspera_ci.print(celdasTiempo);
		t.tEspera_cd.print(celdasTiempo);
		t.tEspera_dd.print(celdasTiempo);
		t.tEspera_di.print(celdasTiempo);
        //std::cin >> s;
	}
	//cout<<"Valores repeticiones"<<endl;
	cout<<"\tLargo cola(mean)\t\tTiempo de espera(mean)"<<endl;
	for(int i=0;i<repeticiones;i++){
		/*cout<<"Valor verde "<<s_tiempo_verde[i]<<" valor tiempo roja "<< s_tiempo_roja[i]<<endl;*/
		//cout<< "Media vehículos "<< s_media_vehiculos[i]<<endl;
		cout<<"cc\t"<<lCola_cc[i]<<"\t\t"<<tespera_cc[i]<<endl;		
		cout<<"ci\t"<<lCola_ci[i]<<"\t\t"<<tespera_ci[i]<<endl;		
		cout<<"cd\t"<<lCola_cd[i]<<"\t\t"<<tespera_cd[i]<<endl;		
		cout<<"dd\t"<<lCola_dd[i]<<"\t\t"<<tespera_dd[i]<<endl;		
		cout<<"di\t"<<lCola_di[i]<<"\t\t"<<tespera_di[i]<<endl<<endl;
		double var_xn = (lCola_cc[i]+lCola_ci[i]+lCola_cd[i]+lCola_dd[i]+lCola_di[i])/5 ;
		cout<<"promedio del promedio de largo colas(X): "<<var_xn<<endl;
		cout<<"promedio del tiempo llegadas de vehiculos (Y): "<<prom_llegada[i] <<endl;	
		cout<<"Valor Xc: "<<var_xn - (var_a*(prom_llegada[i]-var_v))<<endl<<endl<<endl;
	}
	string l;
	cin>>l;
	return 0;
}
