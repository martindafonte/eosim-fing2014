#ifndef EMPIRICDIST_HPP_
#define EMPIRICDIST_HPP_

#include <eosim/dist/distribution.hpp>

namespace eosim {
	
namespace dist {

	class EmpiricDist: public Distribution {
	private:
		int size;
		double* f_x;
	public:
		
		EmpiricDist (GenType gen, double* f_x, int size);
		
		~EmpiricDist ();
		
		double sample ();
	};

}

}

/**
 * \@}
*/

#endif

