#pragma once

#include "common/common_api.h"


namespace rk9 {

	struct COMMON_API BoundingBox {
		double 
			Xmin = -100.0,
			Xmax = +100.0, 
			Ymin = -100.0, 
			Ymax = +100.0, 
			Zmin = -100.0, 
			Zmax = +100.0;
	};

}
