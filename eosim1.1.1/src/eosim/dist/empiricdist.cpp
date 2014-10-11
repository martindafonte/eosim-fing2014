#include <eosim/dist/empiricdist.hpp>
#include <cmath>

using namespace eosim::dist;


EmpiricDist::EmpiricDist(GenType gen, double* f_x, int size):
	Distribution(gen), f_x(f_x), size(size) {} 


EmpiricDist::~EmpiricDist() {}

double EmpiricDist::sample() {
	if (size > 1){
		double u = this->generator->nextDouble();
		int x = 1;

		while (u > f_x[x]){
			x++;
		}

		return x - 1 + ((u - f_x[x-1])/(f_x[x] - f_x[x-1]));
	}

    return 0.0;
}

