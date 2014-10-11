#include <eosim/dist/empiricdist.hpp>
#include <cmath>

using namespace eosim::dist;


EmpiricDist::EmpiricDist(GenType gen, double* f_x, int size):
	Distribution(gen), f_x(f_x), size(size) {} 


EmpiricDist::~EmpiricDist() {}

double EmpiricDist::sample() {

    return 0.0;
}

