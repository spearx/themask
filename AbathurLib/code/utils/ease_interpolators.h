////////////////////////////////////////////////////////////////////////////////////////////
// HOW TO USE: 
//------------------------------------------------------------------------------------------
//	MANUAL SINGLE INTERPOLATION: 
//------------------------------------------------------------------------------------------
//	//float interpolation
//	//50% interpolation in a Cubic InOut curve between 0.0f and 10.0f
//	float fResult = Interpolations::EaseInOutCubicInterpolation::Compute(0.0f,10.f,0.5f);
//
//	//Vec3 interpolation
//	//30% interpolation in a Bounce Out curve between Origin and 10.0f on the X axis
//	Vec3 vResult = Interpolations::EaseOutBounceInterpolation::Compute(Vec3(ZERO),Vec3(10.0f,0.0f,0.0f),0.3f);
//
//------------------------------------------------------------------------------------------
//	AUTOMATIC INTERPOLATION WITH 'INTERPOLABLE' HELPER
//------------------------------------------------------------------------------------------
//
//	//declaration
//	Interpolations::Interpolable<float> foo; // Native type
//
//	//Value Set
//	void TriggerFoo()
//	{
//		foo.Reset(0.0f); //Initial Value (if we do not reset the inital value will be the last interpolated value computed in order to avoid jumps on the signal)
//
//		//Set new value option 1 (expanded)
//		foo.SetMethod<Interpolations::SEaseInOutCubicInterpolation>(); // use a Cubic InOut Easing when interpolating the value ( compile time method assignment )
//		foo.SetMethod(Methods::CubicInOut);                            // use a Cubic InOut Easing when interpolating the value ( run-time method assignment, useful for data driven parameters )
//		foo.SetTotalTime(2.0f);                                        // consume 2 seconds to reach the target value
//		foo.SetValue(10.0f);                                           // start interpolating to 10
//
//		//Set new value option 2 (compact)
//		foo.SetValue<SEaseInOutCubicInterpolation>(10.0f,2.0f);        // Start a Cubic InOut Easing and reach 10.0 in 2 seconds ( compile time method assignment )
//		foo.SetValue(10.0f,2.0f,Methods::CubicInOut);                  // Start a Cubic InOut Easing and reach 10.0 in 2 seconds ( run time method assignment, useful for data driven parameters )
//	}
//
//	//Update
//	void Update(float deltaTime)
//	{
//		//update the value
//		if (foo.Update(deltaTime))
//		{
//			//INTERPOLATION FINISHED...
//		}
//
//		//Retrieve Info
//		const float currentValue   = foo.GetValue();            // current Interpolated value
//		const float targetValue    = foo.GetTarget();           // value that we want to reach
//		const float currentTime    = foo.GetCurrentTime();      // total time for the whole interpolation
//		const float totalTime      = foo.GetTotalTime();        // total time for the whole interpolation
//		const float currentPercent = foo.GetCurrentFactor();    // percent in the range [0-1] of interpolation done
//		const bool hasFinished     = foo.HasFinished();         // is interpolating or not.
//	}
//
//	//custom type usage ( inner method or external method )
//	struct Fred 
//	{ 
//		//... 
//		void Interpolate(const Fred& from, const Fred& to, const float factor)
//		{
//			//... implement something like 'data = from.data*factor + to.data*(1.0f-factor);'
//		}
//		//...
//	};
//	
//	void Interpolate(Fred& output, const Fred& from, const Fred& to, const float factor)
//	{
//		//... implement something like 'output = from*factor + to*(1.0f-factor);'
//	}
//
//	//declaration remains the same
//	Interpolations::Interpolable<Fred> fred; // Custom type ( custom types need a way to define how they lerp)
//
////////////////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "Callbacks.h"
#include "compileTime/compile_time_utils.h"
#include "math/math.h"

namespace Interpolations
{
	/////////////////////////////
	// METHODS ENUM DEFINITION //
	/////////////////////////////

	namespace Methods
	{
		enum EValue
		{
			Linear = 0, 

			QuadIn,
			QuadOut,
			QuadInOut,

			CubicIn,
			CubicOut,
			CubicInOut,

			QuartIn,
			QuartOut,
			QuartInOut,

			QuintIn,
			QuintOut,
			QuintInOut,

			BackIn,
			BackOut,
			BackInOut,

			ElasticIn,
			ElasticOut,
			ElasticInOut,

			BounceIn,
			BounceOut,
			BounceInOut,

			CircularIn,
			CircularOut,
			CircularInOut,

			ExpoIn,
			ExpoOut,
			ExpoInOut,

			SineIn,
			SineOut,
			SineInOut
		};
	}

	///////////////////
	// INTERPOLATORS //
	///////////////////

	struct BaseInterpolation{};

	////////////
	// LINEAR //
	////////////

	//------------------------------------------------------------------------
	struct LerpInterpolation : public BaseInterpolation
	{
		template< typename T > inline static const T Compute(const T& begin, const T& end, const float factor);
	};

	/////////////////
	/// QUADRATIC ///
	/////////////////

	//------------------------------------------------------------------------
	struct EaseInQuadInterpolation : public BaseInterpolation
	{
		template< typename T > inline static const T Compute(const T& begin, const T& end, const float factor);
	};

	//------------------------------------------------------------------------
	struct EaseOutQuadInterpolation : public BaseInterpolation 
	{
		template< typename T > inline static const T Compute(const T& begin, const T& end, const float factor);
	};

	//------------------------------------------------------------------------
	struct EaseInOutQuadInterpolation : public BaseInterpolation 
	{
		template< typename T > inline static const T Compute(const T& begin, const T& end, const float factor);
	};

	/////////////
	/// CUBIC ///
	/////////////

	//------------------------------------------------------------------------
	struct EaseInCubicInterpolation : public BaseInterpolation 
	{
		template< typename T > inline static const T Compute(const T& begin, const T& end, const float factor);
	};

	//------------------------------------------------------------------------
	struct EaseOutCubicInterpolation : public BaseInterpolation 
	{
		template< typename T > inline static const T Compute(const T& begin, const T& end, const float factor);
	};

	//------------------------------------------------------------------------
	struct EaseInOutCubicInterpolation : public BaseInterpolation 
	{
		template< typename T > inline static const T Compute(const T& begin, const T& end, const float factor);
	};

	/////////////
	/// QUART ///
	/////////////

	//------------------------------------------------------------------------
	struct EaseInQuartInterpolation : public BaseInterpolation 
	{
		template< typename T > inline static const T Compute(const T& begin, const T& end, const float factor);
	};

	//------------------------------------------------------------------------
	struct EaseOutQuartInterpolation : public BaseInterpolation 
	{
		template< typename T > inline static const T Compute(const T& begin, const T& end, const float factor);
	};

	//------------------------------------------------------------------------
	struct EaseInOutQuartInterpolation : public BaseInterpolation 
	{
		template< typename T > inline static const T Compute(const T& begin, const T& end, const float factor);
	};

	/////////////
	/// QUINT ///
	/////////////

	//------------------------------------------------------------------------
	struct EaseInQuintInterpolation : public BaseInterpolation 
	{
		template< typename T > inline static const T Compute(const T& begin, const T& end, const float factor);
	};

	//------------------------------------------------------------------------
	struct EaseOutQuintInterpolation : public BaseInterpolation 
	{
		template< typename T > inline static const T Compute(const T& begin, const T& end, const float factor);
	};

	//------------------------------------------------------------------------
	struct EaseInOutQuintInterpolation : public BaseInterpolation 
	{
		template< typename T > inline static const T Compute(const T& begin, const T& end, const float factor);
	};

	////////////
	/// BACK ///
	////////////

	//------------------------------------------------------------------------
	struct EaseInBackInterpolation : public BaseInterpolation 
	{
		template< typename T > inline static const T Compute(const T& begin, const T& end, const float factor);
	};

	//------------------------------------------------------------------------
	struct EaseOutBackInterpolation : public BaseInterpolation 
	{
		template< typename T > inline static const T Compute(const T& begin, const T& end, const float factor);
	};

	//------------------------------------------------------------------------
	struct EaseInOutBackInterpolation : public BaseInterpolation 
	{
		template< typename T > inline static const T Compute(const T& begin, const T& end, const float factor);
	};

	///////////////
	/// ELASTIC ///
	///////////////

	//------------------------------------------------------------------------
	struct EaseInElasticInterpolation : public BaseInterpolation 
	{
		template< typename T > inline static const T Compute(const T& begin, const T& end, const float factor);
	};

	//------------------------------------------------------------------------
	struct EaseOutElasticInterpolation : public BaseInterpolation 
	{
		template< typename T > inline static const T Compute(const T& begin, const T& end, const float factor);
	};

	//------------------------------------------------------------------------
	struct EaseInOutElasticInterpolation : public BaseInterpolation 
	{
		template< typename T > inline static const T Compute(const T& begin, const T& end, const float factor);
	};

	//////////////
	/// BOUNCE ///
	//////////////

	//------------------------------------------------------------------------
	struct EaseOutBounceInterpolation : public BaseInterpolation
	{
		template< typename T > inline static const T Compute(const T& begin, const T& end, const float factor);
	};

	//------------------------------------------------------------------------
	struct EaseInBounceInterpolation : public BaseInterpolation 
	{
		template< typename T > inline static const T Compute(const T& begin, const T& end, const float factor);
	};

	//------------------------------------------------------------------------
	struct EaseInOutBounceInterpolation : public BaseInterpolation 
	{
		template< typename T > inline static const T Compute(const T& begin, const T& end, const float factor);
	};

	////////////////
	/// CIRCULAR ///
	////////////////

	//------------------------------------------------------------------------
	struct EaseInCircInterpolation : public BaseInterpolation 
	{
		template< typename T > inline static const T Compute(const T& begin, const T& end, const float factor);
	};

	//------------------------------------------------------------------------
	struct EaseOutCircInterpolation : public BaseInterpolation 
	{
		template< typename T > inline static const T Compute(const T& begin, const T& end, const float factor);
	};

	//------------------------------------------------------------------------
	struct EaseInOutCircInterpolation : public BaseInterpolation 
	{
		template< typename T > inline static const T Compute(const T& begin, const T& end, const float factor);
	};

	////////////
	/// EXPO ///
	////////////

	//------------------------------------------------------------------------
	struct EaseInExpoInterpolation : public BaseInterpolation 
	{
		template< typename T > inline static const T Compute(const T& begin, const T& end, const float factor);
	};

	//------------------------------------------------------------------------
	struct EaseOutExpoInterpolation : public BaseInterpolation 
	{
		template< typename T > inline static const T Compute(const T& begin, const T& end, const float factor);
	};

	//------------------------------------------------------------------------
	struct EaseInOutExpoInterpolation : public BaseInterpolation 
	{
		template< typename T > inline static const T Compute(const T& begin, const T& end, const float factor);
	};

	////////////
	/// SINE ///
	////////////

	//------------------------------------------------------------------------
	struct EaseInSineInterpolation : public BaseInterpolation 
	{
		template< typename T > inline static const T Compute(const T& begin, const T& end, const float factor);
	};

	//------------------------------------------------------------------------
	struct EaseOutSineInterpolation : public BaseInterpolation 
	{
		template< typename T > inline static const T Compute(const T& begin, const T& end, const float factor);
	};

	//------------------------------------------------------------------------
	struct EaseInOutSineInterpolation : public BaseInterpolation 
	{
		template< typename T > inline static const T Compute(const T& begin, const T& end, const float factor);
	};

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// DEFAULT INTERPOLATE FUNCTION FOR CUSTOM TYPES
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	template<typename T> void Interpolate(T& output, const T& from, const T& to, const float factor)
	{
		//Defaults to call the inner method of the given object. 
		//If the code fails on compiling here make sure the the given object has the method and knows how to Linear Interpolate between 2 instances. 
		output.Interpolate(from,to,factor); 
	}

	void Interpolate(Quat& output, const Quat& from, const Quat& to, const float factor);
	void Interpolate(QuatT& output, const QuatT& from, const QuatT& to, const float factor);

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// HELPER CLASSES
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	namespace Internal
	{
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		// INTERPOLATION METHOD EXTRACTION POLICIES
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		////////////////////////////////////////////////////////////////////////////////////////////////////////////
		// Custom split to achieve partial method template specialization
		template<bool IS_CUSTOM> struct InterpolationCompute;
		template<> struct InterpolationCompute<true>
		{
			template<typename T, class InterpolationMethod> static void ComputeInterpolation(T& output, const T& from, const T& to, const float factor){ Interpolate(output,from,to,InterpolationMethod::Compute(0.0f,1.0f,factor)); }
		};
		template<> struct InterpolationCompute<false>
		{
			template<typename T, class InterpolationMethod> static void ComputeInterpolation(T& output, const T& from, const T& to, const float factor){ output = InterpolationMethod::Compute(from,to,factor); }
		};

		////////////////////////////////////////////////////////////////////////////////////////////////////////////

		template<typename T,bool IS_CUSTOM>
		class FunctorBasedInterpolationSelection
		{
		public:
			FunctorBasedInterpolationSelection(){ SetMethod<LerpInterpolation>(); }

			template<class InterpolationMethod> inline void SetMethod()
			{ 
				STATIC_ASSERT( (SConversion<InterpolationMethod,Interpolations::BaseInterpolation>::Exists));
				callBack = Callback::SetFunction< &InterpolationCompute<IS_CUSTOM>::template ComputeInterpolation<T,InterpolationMethod> >();
			}
			
			inline void PerformInterpolation(T& output, const T& from, const T& to, const float factor) const{ ASSERT(callBack); callBack(output,from,to,factor); } 

		private:

			typedef CFunctionCaller4<T&, const T&, const T&, float> Callback;
			Callback callBack;
		};


		////////////////////////////////////////////////////////////////////////////////////////////////////////////

		template<typename T, class InterpolationMethod, bool IS_CUSTOM>
		class FixedInterpolation
		{
		public:
			FixedInterpolation()
			{
				STATIC_ASSERT( (SConversion<InterpolationMethod,Interpolations::BaseInterpolation>::Exists));
			}

			inline void PerformInterpolation(T& output, const T& from, const T& to, const float factor) const{ InterpolationCompute<IS_CUSTOM>::template ComputeInterpolation<T,InterpolationMethod>(output, from, to, factor);  } 
		};

		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		// Value abstraction
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		//interface
		template< typename T, class InterpolationPolicy>
		struct CBaseInterpolValue
		{
		public:

			CBaseInterpolValue():m_timeToInterp(FLT_EPSILON),m_isCompensateTimeScale(false){ Reset(); }

			inline void SetTotalTime(const float totalTime){ m_timeToInterp = (totalTime > 0.0f)? totalTime : m_timeToInterp; }
			inline void Reset(const T& newValue = T(), const bool isFinished = true);
			void CompensateTimeScale(bool compensateTimeScale) { m_isCompensateTimeScale = compensateTimeScale; }

			bool Update(float elapsed);

			inline const T& GetValue() const { return m_interp; }
			inline const T& GetTarget() const { return m_to; }
			inline float GetTotalTime() const { return m_timeToInterp; }
			inline float GetCurrentTime() const { return m_timeToGo; }
			inline float GetCurrentFactor() const { return m_timeToGo / m_timeToInterp;}
			inline bool HasFinished() const { return fcmp(m_timeToGo, m_timeToInterp); }

		protected:

			inline void PerformSetValue(const T& newTarget){ m_from = m_interp; m_to = newTarget; m_timeToGo = 0.0f; }
			inline void PerformSetValue(const T& newTarget, const float time){ SetTotalTime(time); PerformSetValue(newTarget); }
			inline InterpolationPolicy& GetInterpolationPolicy(){ return m_interpolationPolicy; }

		private:
			T m_from;                                   ///< initial value
			T m_to;                                     ///< final value
			T m_interp;                                 ///< current value
			float m_timeToGo;                           ///< current Time
			float m_timeToInterp;                       ///< total time
			InterpolationPolicy m_interpolationPolicy;  ///< interpolation policy
			bool m_isCompensateTimeScale;               ///< correction for t_scale cvar
		};

		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//Generic Class to handle a value giving smooth transition with time control (the interpolation policy is compile-time fixed and will always use the same).
		template< typename T, class InterpolationMethod, bool IS_CUSTOM = false>
		class CFixedInterpolValue : public CBaseInterpolValue<T, FixedInterpolation<T,InterpolationMethod,IS_CUSTOM> >
		{
		private:
			typedef CBaseInterpolValue<T, FixedInterpolation<T,InterpolationMethod, IS_CUSTOM> > TBase;

		public:
			inline void SetValue(const T& newTarget){ TBase::PerformSetValue(newTarget); }
			inline void SetValue(const T& newTarget, const float time){ TBase::PerformSetValue(newTarget, time); }
		};

		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//Generic class to handle a value giving a smooth transition with time control and the ability to choose the interpolation type we want each time.
		template<typename T, bool IS_CUSTOM = false>
		class CInterpolValue : public CBaseInterpolValue<T, FunctorBasedInterpolationSelection<T,IS_CUSTOM> >
		{
		private:
			typedef CBaseInterpolValue<T, FunctorBasedInterpolationSelection<T,IS_CUSTOM> > TBase;

		public:
			CInterpolValue(){}

			template<class InterpolationMethod> inline void SetMethod(){ TBase::GetInterpolationPolicy().template SetMethod<InterpolationMethod>(); }
			inline void SetMethod(const Methods::EValue method);

			template<class InterpolationMethod> inline void SetValue(const T& newTarget){ SetMethod<InterpolationMethod>(); TBase::PerformSetValue(newTarget); }
			template<class InterpolationMethod> inline void SetValue(const T& newTarget, const float time){ SetMethod<InterpolationMethod>(); TBase::PerformSetValue(newTarget, time); }
			inline void SetValue(const T& newTarget, const Methods::EValue method){ SetMethod(method); TBase::PerformSetValue(newTarget); }
			inline void SetValue(const T& newTarget, const float time, const Methods::EValue method){ SetMethod(method); TBase::PerformSetValue(newTarget,time); }
			inline void SetValue(const T& newTarget, const float time){ TBase::PerformSetValue(newTarget, time); } 
			inline void SetValue(const T& newTarget){ TBase::PerformSetValue(newTarget); } 
		};

	}

	////////////////////
	// PUBLIC HELPERS //
	////////////////////
	
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Polymorphic interpolable value ( this can handle different interpolation policies per each value modification )

	//Default Custom structure
	template<typename T> class Interpolable : public Internal::CInterpolValue<T,true>{};

	//Basic types use direct interpolation
	template<> class Interpolable<int32>   : public Internal::CInterpolValue<int32>{};
	template<> class Interpolable<uint32>  : public Internal::CInterpolValue<uint32>{};
	template<> class Interpolable<float>   : public Internal::CInterpolValue<float>{};
	template<> class Interpolable<double>  : public Internal::CInterpolValue<double>{};
	template<> class Interpolable<Vector2> : public Internal::CInterpolValue<Vector2>{};
	template<> class Interpolable<Vector3> : public Internal::CInterpolValue<Vector3>{};
	template<> class Interpolable<Vector4> : public Internal::CInterpolValue<Vector4>{};


	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Polymorphic fixed interpolable value ( this will stick to a single interpolation method )

	//Default Custom structure
	template<typename T, class InterpolationPolicy> class InterpolableFixed : public Internal::CFixedInterpolValue<T,InterpolationPolicy,true>{}; 
	
	//Basic types use direct interpolation
	template<class InterpolationPolicy> class InterpolableFixed<int32,   InterpolationPolicy> : public Internal::CFixedInterpolValue<int32,   InterpolationPolicy>{};
	template<class InterpolationPolicy> class InterpolableFixed<uint32,  InterpolationPolicy> : public Internal::CFixedInterpolValue<uint32,  InterpolationPolicy>{};
	template<class InterpolationPolicy> class InterpolableFixed<float,   InterpolationPolicy> : public Internal::CFixedInterpolValue<float,   InterpolationPolicy>{};
	template<class InterpolationPolicy> class InterpolableFixed<double,  InterpolationPolicy> : public Internal::CFixedInterpolValue<double,  InterpolationPolicy>{};
	template<class InterpolationPolicy> class InterpolableFixed<Vector2, InterpolationPolicy> : public Internal::CFixedInterpolValue<Vector2, InterpolationPolicy>{};
	template<class InterpolationPolicy> class InterpolableFixed<Vector3, InterpolationPolicy> : public Internal::CFixedInterpolValue<Vector3, InterpolationPolicy>{};
	template<class InterpolationPolicy> class InterpolableFixed<Vector4, InterpolationPolicy> : public Internal::CFixedInterpolValue<Vector4, InterpolationPolicy>{};
}

#include "ease_interpolators.inl"

