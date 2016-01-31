#include "ease_interpolators.h"

namespace Interpolations
{
	// ----------------------------------------------------------------------------------------
	void Interpolate(Quat& output, const Quat& from, const Quat& to, const float factor)
	{
		output.SetNlerp(from,to,factor);
	}
	
	// ----------------------------------------------------------------------------------------
	void Interpolate(QuatT& output, const QuatT& from, const QuatT& to, const float factor)
	{
		Interpolate(output.q,from.q,to.q,factor);
		output.t = Interpolations::LerpInterpolation::Compute(from.t,to.t,factor);
	}
	
}