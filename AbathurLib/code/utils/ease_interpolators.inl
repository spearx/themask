#pragma once

namespace Interpolations
{
	//////////////////////////////////
	// INTERPOLATORS IMPLEMENTATION //
	//////////////////////////////////

	////////////
	// LINEAR //
	////////////

	//------------------------------------------------------------------------
	template< typename T > inline const T LerpInterpolation::Compute(const T& begin, const T& end, const float factor)
	{
		return end*factor + begin*(1.0f-factor);
	}

	/////////////////
	/// QUADRATIC ///
	/////////////////

	//------------------------------------------------------------------------
	template< typename T > inline const T EaseInQuadInterpolation::Compute(const T& begin, const T& end, const float factor)
	{
		const T range = end - begin;
		return range*factor*factor + begin;
	}

	//------------------------------------------------------------------------
	template< typename T > inline const T EaseOutQuadInterpolation::Compute(const T& begin, const T& end, const float factor)
	{
		const T range = end - begin;
		return -range * factor * (factor-2.0f) + begin;
	}

	//------------------------------------------------------------------------
	template< typename T > inline const T EaseInOutQuadInterpolation::Compute(const T& begin, const T& end, const float factor)
	{
		const T range = end - begin;
		float factorTmp = factor * 2.0f;
		return ( factorTmp < 1.f )? (0.5f*range*factorTmp*factorTmp) + begin : -range*0.5f*(((factorTmp-3.0f)*(factorTmp-1.0f))-1.0f) + begin;
	}

	/////////////
	/// CUBIC ///
	/////////////

	//------------------------------------------------------------------------
	template< typename T > inline const T EaseInCubicInterpolation::Compute(const T& begin, const T& end, const float factor)
	{
		const T range = end - begin;
		return range*factor*factor*factor + begin;
	}
	
	//------------------------------------------------------------------------
	template< typename T > inline const T EaseOutCubicInterpolation::Compute(const T& begin, const T& end, const float factor)
	{
		const T range = end - begin; 
		const float factorTmp = factor - 1;
		return range*(factorTmp*factorTmp*factorTmp + 1) + begin;
	}

	//------------------------------------------------------------------------
	template< typename T > inline const T EaseInOutCubicInterpolation::Compute(const T& begin, const T& end, const float factor)
	{
		const T range = end - begin;
		float factorTmp = factor;
		if ((factorTmp*=2.0f) < 1)
		{
			return range/2*factorTmp*factorTmp*factorTmp + begin;
		}
		factorTmp-=2.0f;
		return range/2*(factorTmp*factorTmp*factorTmp + 2) + begin;
	}


	/////////////
	/// QUART ///
	/////////////

	//------------------------------------------------------------------------
	template< typename T > inline const T EaseInQuartInterpolation::Compute(const T& begin, const T& end, const float factor)
	{
		const T range = end - begin;
		const float factor2 = factor*factor; 
		return range*factor2*factor2 + begin;
	}


	//------------------------------------------------------------------------
	template< typename T > inline const T EaseOutQuartInterpolation::Compute(const T& begin, const T& end, const float factor)
	{
		const T range = end - begin;
		const float factorTmp = factor - 1.0f;
		const float factorTmpSqr = factorTmp*factorTmp;
		return -range * (factorTmpSqr*factorTmpSqr - 1.f) + begin;
	}

	//------------------------------------------------------------------------
	template< typename T > inline const T EaseInOutQuartInterpolation::Compute(const T& begin, const T& end, const float factor)
	{
		const T c = end - begin;
		float factorTmp = factor * 2.f;
		if (factorTmp < 1.f)
		{
			return c * 0.5f *factorTmp*factorTmp*factorTmp*factorTmp + begin;
		}
		factorTmp -= 2.0f;
		return -c*0.5f * (factorTmp*factorTmp*factorTmp*factorTmp - 2.0f) + begin;
	}


	/////////////
	/// QUINT ///
	/////////////

	//------------------------------------------------------------------------
	template< typename T > inline const T EaseInQuintInterpolation::Compute(const T& begin, const T& end, const float factor)
	{
		const T range = end - begin;
		const float factorSqr = factor*factor; 
		return range*factorSqr*factorSqr*factor + begin;
	}

	//------------------------------------------------------------------------
	template< typename T > inline const T EaseOutQuintInterpolation::Compute(const T& begin, const T& end, const float factor)
	{
		const T range = end - begin;
		const float factorTmp = factor - 1.0f;
		const float factorTmpSqr = factorTmp*factorTmp;
		return range*(factorTmpSqr*factorTmpSqr*factorTmp + 1.f) + begin;
	}


	//------------------------------------------------------------------------
	template< typename T > inline const T EaseInOutQuintInterpolation::Compute(const T& begin, const T& end, const float factor)
	{
		const T range = end - begin;
		float factorTmp = factor * 2.0f;
		if (factorTmp < 1.0f)
		{
			return range * 0.5f*factorTmp*factorTmp*factorTmp*factorTmp*factorTmp + begin;
		}
		factorTmp -= 2.0f;
		return range*0.5f*(factorTmp*factorTmp*factorTmp*factorTmp*factorTmp + 2.0f) + begin;
	}


	////////////
	/// BACK ///
	////////////

	//------------------------------------------------------------------------
	template< typename T > inline const T EaseInBackInterpolation::Compute(const T& begin, const T& end, const float factor)
	{
		static const float spring = 1.70158f;
		const T range = end - begin;
		return range*(factor)*factor*((spring+1.0f)*factor - spring) + begin;
	}

	//------------------------------------------------------------------------
	template< typename T > inline const T EaseOutBackInterpolation::Compute(const T& begin, const T& end, const float factor)
	{
		static const float spring = 1.70158f;
		const T range = end - begin;
		const float factorTmp = factor-1.0f;
		return range*(factorTmp*factorTmp*((spring+1.0f)*factorTmp + spring) + 1.0f) + begin;
	}

	//------------------------------------------------------------------------
	template< typename T > inline const T EaseInOutBackInterpolation::Compute(const T& begin, const T& end, const float factor)
	{
		static const float spring = 2.5949095f; 
		const T range = end - begin;
		float factorTmp = factor;
		if ((factorTmp*=2) < 1) 
		{
			return range/2*(factorTmp*factorTmp*(((spring)+1)*factorTmp - spring)) + begin;
		}
		factorTmp-=2.0f;
		return range/2*(factorTmp*factorTmp*((spring+1.0f)*factorTmp + spring) + 2.0f) + begin;
	}

	///////////////
	/// ELASTIC ///
	///////////////

	//------------------------------------------------------------------------
	template< typename T > inline const T EaseInElasticInterpolation::Compute(const T& begin, const T& end, const float factor)
	{
		if (fcmp(factor,0.0f)) 
			return begin;

		if (fcmp(factor,1.0f))
			return end;

		static const float spring = 0.3f;
		const T range = end - begin;
		const float t = factor - 1.0f;
		return -(range*pow(2.0f,10.0f*(t)) * sinf((t-spring*0.25f)*(gf_PI2)/spring )) + begin;
	}


	//------------------------------------------------------------------------
	template< typename T > inline const T EaseOutElasticInterpolation::Compute(const T& begin, const T& end, const float factor)
	{
		if (factor <= 0.0f)
			return begin;

		if (factor >= 1.0f)
			return end;

		const float spring = 0.3f;
		const T range = end - begin;
		return (range*powf(2.0f,-10.0f*factor) * sinf( (factor-(spring*0.25f))*(gfPI2)/spring ) + range + begin);
	}


	//------------------------------------------------------------------------
	template< typename T > inline const T EaseInOutElasticInterpolation::Compute(const T& begin, const T& end, const float factor)
	{
		if (fcmp(factor,0.0f)) 
			return begin;

		if (fcmp(factor,1.0f))
			return end;

		static const float spring = 0.45f; 
		static const float subSpring = spring*0.25f;
		const T range = end - begin;
		const float t = (factor*2.0f) - 1.0f;
		return (t < 0.0f)? -0.5f*(range*powf(2.0f,10.0f*(t)) * sinf( (t-subSpring)*(gf_PI2)/spring )) + begin : range*powf(2.0f,-10.0f*(t)) * sinf( (t-subSpring)*(gf_PI2)/spring )*.5f + range + begin;
	}

	//////////////
	/// BOUNCE ///
	//////////////

	//------------------------------------------------------------------------
	template< typename T > inline const T EaseOutBounceInterpolation::Compute(const T& begin, const T& end, const float factor)
	{
		const T range = end - begin;
		static const float inv275 = 1.0f / 2.75f; 

		if ( factor < inv275 ) 
		{
			return range * ( 7.5625f * factor * factor ) + begin;
		}
		if ( factor < (2.0f*inv275) ) 
		{
			const float factorTmp = factor - (1.5f*inv275);
			return range*(7.5625f*factorTmp*factorTmp + .75f) + begin;
		}
		if ( factor < (2.5f * inv275) ) 
		{
			const float factorTmp = factor - (2.25f * inv275);
			return range*(7.5625f*factorTmp*factorTmp + 0.9375f) + begin;
		}

		const float factorTmp = factor - (2.625f * inv275);
		return range*(7.5625f*factorTmp*factorTmp + 0.984375f) + begin;
	}

	//------------------------------------------------------------------------
	template< typename T > inline const T EaseInBounceInterpolation::Compute(const T& begin, const T& end, const float factor)
	{
		return EaseOutBounceInterpolation::Compute<T>(end,begin,1.0f - factor);
	}

	//------------------------------------------------------------------------
	template< typename T > inline const T EaseInOutBounceInterpolation::Compute(const T& begin, const T& end, const float factor)
	{
		const T middle = (begin + end) * 0.5f;
		if (factor < 0.5f) 
		{
			return EaseInBounceInterpolation::Compute<T>(begin,middle,factor*2.0f);
		}
		return EaseOutBounceInterpolation::Compute<T>(middle,end,factor*2.0f - 1.0f);
	}

	////////////////
	/// CIRCULAR ///
	////////////////

	//------------------------------------------------------------------------
	template< typename T > inline const T EaseInCircInterpolation::Compute(const T& begin, const T& end, const float factor)
	{
		const T range = end - begin;
		return -range * (sqrtf(1.f - factor * factor) - 1.f) + begin;
	}


	//------------------------------------------------------------------------
	template< typename T > inline const T EaseOutCircInterpolation::Compute(const T& begin, const T& end, const float factor)
	{
		const T range = end - begin;
		const float factorTmp = factor - 1.f;
		return range * sqrtf(1.f - factorTmp*factorTmp) + begin;
	}


	//------------------------------------------------------------------------
	template< typename T > inline const T EaseInOutCircInterpolation::Compute(const T& begin, const T& end, const float factor)
	{
		const T range = end - begin;
		float t = factor * 2.f;
		return (t < 1.f)? -range*0.5f * (sqrtf(1.0f - t*t) - 1.f) + begin : range*0.5f * (sqrtf(1.0f - (t-2.0f)*(t-2.0f)) + 1.0f) + begin;
	}


	////////////
	/// EXPO ///
	////////////

	//------------------------------------------------------------------------
	template< typename T > inline const T EaseInExpoInterpolation::Compute(const T& begin, const T& end, const float factor)
	{
		const T range = end - begin;
		return (fcmp(factor,0.0f))? begin : range * powf(2.0f,10.0f * (factor - 1.0f)) + begin;
	}

	//------------------------------------------------------------------------
	template< typename T > inline const T EaseOutExpoInterpolation::Compute(const T& begin, const T& end, const float factor)
	{
		const T range = end - begin;
		return (fcmp(factor,1.0f))? end : range * (-powf(2.0f, -10.0f * factor) + 1.0f) + begin;
	}

	//------------------------------------------------------------------------
	template< typename T > inline const T EaseInOutExpoInterpolation::Compute(const T& begin, const T& end, const float factor)
	{
		if (fcmp(factor,0.0f)) 
			return begin;

		if (fcmp(factor,1.0f))
			return end;

		const T range = end - begin;
		const float factorTmp = (factor * 2.f) - 1.0f;
		return (factorTmp < 0.0f)? range * 0.5f * powf(2.0f, 10.0f * factorTmp) + begin : range*0.5f * (-powf(2.0f, -10.0f * factorTmp) + 2) + begin;
	}


	////////////
	/// SINE ///
	////////////

	//------------------------------------------------------------------------
	template< typename T > inline const T EaseInSineInterpolation::Compute(const T& begin, const T& end, const float factor)
	{
		const T range = end - begin;
		return -range * cosf( factor * gf_PI * 0.5f ) + range + begin;
	}

	//------------------------------------------------------------------------
	template< typename T > inline const T EaseOutSineInterpolation::Compute(const T& begin, const T& end, const float factor)
	{
		const T range = end - begin;
		return range * sinf(factor * gf_PI * 0.5f) + begin;
	}

	//------------------------------------------------------------------------
	template< typename T > inline const T EaseInOutSineInterpolation::Compute(const T& begin, const T& end, const float factor)
	{
		const T range = end - begin;
		return -range * 0.5f * ( cosf(gf_PI * factor) - 1.f ) + begin;
	}


	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// HELPER CLASSES
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	namespace Internal
	{
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		//------------------------------------------------------------------------
		template< typename T, class InterpolationPolicy> inline void CBaseInterpolValue<T,InterpolationPolicy>::Reset(const T& newValue /* = T() */, const bool isFinished /* = false */)
		{ 
			m_from = newValue; 
			m_to = newValue; 
			m_interp = newValue; 
			m_timeToGo = (isFinished)? m_timeToInterp : 0.0f; 
		}

		//------------------------------------------------------------------------
		template< typename T, class InterpolationPolicy> bool CBaseInterpolValue<T,InterpolationPolicy>::Update(float elapsed)
		{
			if (m_isCompensateTimeScale)
			{
				//const float timeScale = gEnv->pTimer->GetTimeScale();
				//elapsed /= (timeScale > FLT_EPSILON) ? timeScale : 1.f;
			}

			m_timeToGo += elapsed;
			bool finished = false; 
			if (m_timeToGo > m_timeToInterp) 
			{ 
				m_timeToGo = m_timeToInterp; 
				finished = true; 
			}
			m_interpolationPolicy.PerformInterpolation(m_interp,m_from,m_to,GetCurrentFactor()); // ask for interpolation
			return finished;
		}

		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		//------------------------------------------------------------------------
		template<typename T,bool IS_CUSTOM> inline void CInterpolValue<T,IS_CUSTOM>::SetMethod(const Methods::EValue method)
		{
			switch (method)
			{
				case Methods::Linear:        SetMethod<LerpInterpolation>(); break;

				case Methods::QuadIn:        SetMethod<EaseInQuadInterpolation>(); break;
				case Methods::QuadOut:       SetMethod<EaseOutQuadInterpolation>(); break;
				case Methods::QuadInOut:     SetMethod<EaseInOutQuadInterpolation>(); break;

				case Methods::CubicIn:       SetMethod<EaseInCubicInterpolation>(); break;
				case Methods::CubicOut:      SetMethod<EaseOutCubicInterpolation>(); break;
				case Methods::CubicInOut:    SetMethod<EaseInOutCubicInterpolation>(); break;

				case Methods::QuartIn:       SetMethod<EaseInQuartInterpolation>(); break;
				case Methods::QuartOut:      SetMethod<EaseOutQuartInterpolation>(); break;
				case Methods::QuartInOut:    SetMethod<EaseInOutQuartInterpolation>(); break;

				case Methods::QuintIn:       SetMethod<EaseInQuintInterpolation>(); break;
				case Methods::QuintOut:      SetMethod<EaseOutQuintInterpolation>(); break;
				case Methods::QuintInOut:    SetMethod<EaseInOutQuintInterpolation>(); break;

				case Methods::BackIn:        SetMethod<EaseInBackInterpolation>(); break;
				case Methods::BackOut:       SetMethod<EaseOutBackInterpolation>(); break;
				case Methods::BackInOut:     SetMethod<EaseInOutBackInterpolation>(); break;

				case Methods::ElasticIn:     SetMethod<EaseInElasticInterpolation>(); break;
				case Methods::ElasticOut:    SetMethod<EaseOutElasticInterpolation>(); break;
				case Methods::ElasticInOut:  SetMethod<EaseInOutElasticInterpolation>(); break;

				case Methods::BounceIn:      SetMethod<EaseInBounceInterpolation>(); break;
				case Methods::BounceOut:     SetMethod<EaseOutBounceInterpolation>(); break;
				case Methods::BounceInOut:   SetMethod<EaseInOutBounceInterpolation>(); break;

				case Methods::CircularIn:    SetMethod<EaseInCircInterpolation>(); break;
				case Methods::CircularOut:   SetMethod<EaseOutCircInterpolation>(); break;
				case Methods::CircularInOut: SetMethod<EaseInOutCircInterpolation>(); break;

				case Methods::ExpoIn:        SetMethod<EaseInExpoInterpolation>(); break;
				case Methods::ExpoOut:       SetMethod<EaseOutExpoInterpolation>(); break;
				case Methods::ExpoInOut:     SetMethod<EaseInOutExpoInterpolation>(); break;

				case Methods::SineIn:        SetMethod<EaseInSineInterpolation>(); break;
				case Methods::SineOut:       SetMethod<EaseOutSineInterpolation>(); break;
				case Methods::SineInOut:     SetMethod<EaseInOutSineInterpolation>(); break;

				default: ASSERT(0); break;
			}
		}
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}
