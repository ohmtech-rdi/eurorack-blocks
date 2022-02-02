/*******************************************************************************************************************
Cycling '74 License for Max-Generated Code for Export
Copyright (c) 2016 Cycling '74
The code that Max generates automatically and that end users are capable of exporting and using, and any
  associated documentation files (the “Software”) is a work of authorship for which Cycling '74 is the author
  and owner for copyright purposes.  A license is hereby granted, free of charge, to any person obtaining a
  copy of the Software (“Licensee”) to use, copy, modify, merge, publish, and distribute copies of the Software,
  and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
The Software is licensed to Licensee only for non-commercial use. Users who wish to make commercial use of the
  Software must contact the copyright owner to determine if a license for commercial use is available, and the
  terms and conditions for same, which may include fees or royalties. For commercial use, please send inquiries
  to licensing@cycling74.com.  The determination of whether a use is commercial use or non-commercial use is based
  upon the use, not the user. The Software may be used by individuals, institutions, governments, corporations, or
  other business whether for-profit or non-profit so long as the use itself is not a commercialization of the
  materials or a use that generates or is intended to generate income, revenue, sales or profit.
The above copyright notice and this license shall be included in all copies or substantial portions of the Software.
THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO
  THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT. IN NO EVENT SHALL
  THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF
  CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
  DEALINGS IN THE SOFTWARE.
*******************************************************************************************************************/

#ifndef GENLIB_OPS_H
#define GENLIB_OPS_H 1

#include "genlib_common.h"
#include "genlib.h"

#ifndef MSP_ON_CLANG
#	include <cmath>
#endif

//////////// genlib_ops.h ////////////

// system constants
#define GENLIB_DBL_EPSILON (__DBL_EPSILON__)
#define GENLIB_FLT_EPSILON (__FLT_EPSILON__)

// denormal numbers cannot occur when hosted in MSP, nor on ARM Cortex processors:
#if defined(MSP_ON_CLANG) || defined(ARM_MATH_CM4) || defined(ARM_MATH_CM7)
#	define GENLIB_NO_DENORM_TEST 1
#endif // defined(MSP_ON_CLANG) || defined(ARM_MATH_CM4) || defined(ARM_MATH_CM7)

// in order to guarantee consistent integer overflow wrapping fixed point phase
// on M1 processors we first must convert to signed int64 and then to uint32
#define FLOAT_TO_UINT32(x) ((uint32_t)((int64_t)(x)))

#ifdef GENLIB_USE_FLOAT32
#	define GENLIB_EPSILON GENLIB_FLT_EPSILON
#else
#	define GENLIB_EPSILON GENLIB_DBL_EPSILON
#endif

#define GENLIB_PI (t_sample(3.14159265358979323846264338327950288))
#define GENLIB_PI_OVER_2 (t_sample(1.57079632679489661923132169163975144))
#define GENLIB_PI_OVER_4 (t_sample(0.785398163397448309615660845819875721))
#define GENLIB_1_OVER_LOG_2 (t_sample(1.442695040888963))

// assumes v is a 64-bit double:
#ifdef GENLIB_USE_FLOAT32
#	define GENLIB_IS_NAN_FLOAT(v)			((v)!=(v))
#	define GENLIB_FIX_NAN_FLOAT(v)			((v)=GENLIB_IS_NAN_FLOAT(v)?0.f:(v))

#	ifdef GENLIB_NO_DENORM_TEST
#		define GENLIB_IS_DENORM_FLOAT(v)	(v)
#		define GENLIB_FIX_DENORM_FLOAT(v)	(v)
#	else
#		ifdef WIN32
#			define __FLT_MIN__	(FLT_MIN)
#		endif
#		define GENLIB_IS_DENORM_FLOAT(v)	((v)!=0.&&fabs(v)<__FLT_MIN__)
#		define GENLIB_FIX_DENORM_FLOAT(v)	((v)=GENLIB_IS_DENORM_FLOAT(v)?0.f:(v))
#	endif // GENLIB_NO_DENORM_TEST

#	define GENLIB_IS_NAN		GENLIB_IS_NAN_FLOAT
#	define GENLIB_FIX_NAN		GENLIB_FIX_NAN_FLOAT
#	define GENLIB_IS_DENORM	GENLIB_IS_DENORM_FLOAT
#	define GENLIB_FIX_DENORM	GENLIB_FIX_DENORM_FLOAT
#else // GENLIB_USE_FLOAT32
#	define GENLIB_IS_NAN_DOUBLE(v)			(((((uint32_t *)&(v))[1])&0x7fe00000)==0x7fe00000)
#	define GENLIB_FIX_NAN_DOUBLE(v)		((v)=GENLIB_IS_NAN_DOUBLE(v)?0.:(v))

#	ifdef GENLIB_NO_DENORM_TEST
#		define GENLIB_IS_DENORM_DOUBLE(v)	(v)
#		define GENLIB_FIX_DENORM_DOUBLE(v)	(v)
#	else // GENLIB_NO_DENORM_TEST
#		define GENLIB_IS_DENORM_DOUBLE(v)	((((((uint32_t *)&(v))[1])&0x7fe00000)==0)&&((v)!=0.))
#		define GENLIB_FIX_DENORM_DOUBLE(v)	((v)=GENLIB_IS_DENORM_DOUBLE(v)?0.f:(v))
#	endif

#	define GENLIB_IS_NAN		GENLIB_IS_NAN_DOUBLE
#	define GENLIB_FIX_NAN		GENLIB_FIX_NAN_DOUBLE
#	define GENLIB_IS_DENORM	GENLIB_IS_DENORM_DOUBLE
#	define GENLIB_FIX_DENORM	GENLIB_FIX_DENORM_DOUBLE
#endif // GENLIB_USE_FLOAT32

#define GENLIB_QUANT(f1,f2)			t_sample(floor((f1)*(f2)+0.5)/(f2))

inline t_sample genlib_isnan(t_sample v) { return GENLIB_IS_NAN(v); }
inline t_sample fixnan(t_sample v) { return GENLIB_FIX_NAN(v); }
inline t_sample fixdenorm(t_sample v) { return GENLIB_FIX_DENORM(v); }
inline t_sample isdenorm(t_sample v) { return GENLIB_IS_DENORM(v); }

inline t_sample fasterpow(t_sample x, t_sample p);
inline t_sample fasterexp(t_sample x);
inline t_sample fastercosfull(t_sample x);
inline t_sample fastersinfull(t_sample x);
inline t_sample fastertanfull(t_sample x);

inline t_sample safemod(t_sample f, t_sample m) {
	if (m > GENLIB_DBL_EPSILON || m < -GENLIB_DBL_EPSILON) {
		if (m<0)
			m = -m; // modulus needs to be absolute value
		if (f>=m) {
			if (f>=(m*2.)) {
				t_sample d = f / m;
				d = d - (long) d;
				f = d * m;
			}
			else {
				f -= m;
			}
		}
		else if (f<=(-m)) {
			if (f<=(-m*2.)) {
				t_sample d = f / m;
				d = d - (long) d;
				f = d * m;
			}
			 else {
				f += m;
			}
		}
	} else {
		f = 0.0; //don't divide by zero
	}
	return f;
}

inline t_sample safediv(t_sample num, t_sample denom) {
	return denom == 0. ? (t_sample)0. : (t_sample)(num/denom);
}

// fixnan for case of negative base and non-integer exponent:
inline t_sample safepow(t_sample base, t_sample exponent) {
	return fixnan(pow(base, exponent));
}

inline t_sample absdiff(t_sample a, t_sample b) { return fabs(a-b); }

#ifndef WIN32
/*
ohmtech-rdi: when 't_sample' is a 'float', this clashes with `math.h` definitions.

inline t_sample exp2(t_sample v) { return pow(2., v); }

inline t_sample trunc(t_sample v) {
	t_sample epsilon = (v<0.0) * -2 * 1E-9 + 1E-9;
	// copy to long so it gets truncated (probably cheaper than floor())
	long val = v + epsilon;
	return val;
}
*/
#endif // WIN32

inline t_sample sign(t_sample v) {
	return v > t_sample(0) ? t_sample(1) : v < t_sample(0) ? t_sample(-1) : t_sample(0);
}

inline long is_poweroftwo(long x) {
	return (x & (x - 1)) == 0;
}

inline uint64_t next_power_of_two(uint64_t v) {
    v--;
    v |= v >> 1;
    v |= v >> 2;
    v |= v >> 4;
    v |= v >> 8;
    v |= v >> 16;
    v |= v >> 32;
    v++;
    return v;
}

inline t_sample fold(t_sample v, t_sample lo1, t_sample hi1){
	t_sample lo;
	t_sample hi;
	if(lo1 == hi1){ return lo1; }
	if (lo1 > hi1) {
		hi = lo1; lo = hi1;
	} else {
		lo = lo1; hi = hi1;
	}
	const t_sample range = hi - lo;
	long numWraps = 0;
	if(v >= hi){
		v -= range;
		if(v >= hi){
			numWraps = (long)((v - lo)/range);
			v -= range * (t_sample)numWraps;
		}
		numWraps++;
	} else if(v < lo){
		v += range;
		if(v < lo){
			numWraps = (long)((v - lo)/range) - 1;
			v -= range * (t_sample)numWraps;
		}
		numWraps--;
	}
	if(numWraps & 1) v = hi + lo - v;	// flip sign for odd folds
	return v;
}

inline t_sample wrap(t_sample v, t_sample lo1, t_sample hi1){
	t_sample lo;
	t_sample hi;
	if(lo1 == hi1) return lo1;
	if (lo1 > hi1) {
		hi = lo1; lo = hi1;
	} else {
		lo = lo1; hi = hi1;
	}
	const t_sample range = hi - lo;
	if (v >= lo && v < hi) return v;
	if (range <= 0.000000001) return lo;	// no point...
	const long numWraps = long((v-lo)/range) - (v < lo);
	const t_sample result = v - range * t_sample(numWraps);
	if (result >= hi) return result - range;
	else return result;
}

// this version gives far better performance when wrapping is relatively rare
// and typically double of wraps is very low (>1%)
// but catastrophic if wraps is high (1000%+)
inline t_sample genlib_wrapfew(t_sample v, t_sample lo, t_sample hi){
	const t_sample range = hi - lo;
	while (v >= hi) v -= range;
	while (v < lo) v += range;
	return v;
}

inline t_sample phasewrap(t_sample val) {
	const t_sample twopi = GENLIB_PI*2.;
	const t_sample oneovertwopi = t_sample(1./twopi);
	if (val>= twopi || val <= twopi) {
		t_sample d = val * oneovertwopi;	//multiply faster
		d = d - (long)d;
		val = d * twopi;
	}
	if (val > GENLIB_PI) val -= twopi;
	if (val < -GENLIB_PI) val += twopi;
	return val;
}

/// 8th order Taylor series approximation to a cosine.
/// r must be in [-pi, pi].
inline t_sample genlib_cosT8(t_sample r) {
	const t_sample t84 = 56.;
	const t_sample t83 = 1680.;
	const t_sample t82 = 20160.;
	const t_sample t81 = t_sample(2.4801587302e-05);
	const t_sample t73 = 42.;
	const t_sample t72 = 840.;
	const t_sample t71 = t_sample(1.9841269841e-04);
	if (r < GENLIB_PI_OVER_4 && r > -GENLIB_PI_OVER_4){
		t_sample rr = r*r;
		return t_sample(1. - rr * t81 * (t82 - rr * (t83 - rr * (t84 - rr))));
	}
	else if (r > 0.){
		r -= GENLIB_PI_OVER_2;
		t_sample rr = r*r;
		return t_sample(-r * (1. - t71 * rr * (t72 - rr * (t73 - rr))));
	}
	else {
		r += GENLIB_PI_OVER_2;
		t_sample rr = r*r;
		return t_sample(r * (1. - t71 * rr * (t72 - rr * (t73 - rr))));
	}
}

//inline double genlib_sin_fast(const double r){
//	const double y = (4./GENLIB_PI) * r + (-4./(GENLIB_PI*GENLIB_PI)) * r * fabs(r);
//	return 0.225 * (y * fabs(y) - y) + y;   // Q * y + P * y * abs(y)
//}
//
//inline t_sample genlib_sinP7(t_sample n){
//	t_sample nn = n*n;
//	return n * (t_sample(3.138982) + nn * (t_sample(-5.133625) + nn * (t_sample(2.428288) - nn * t_sample(0.433645))));
//}
//
//inline t_sample genlib_sinP9(t_sample n){
//	t_sample nn = n*n;
//	return n * (GENLIB_PI + nn * (t_sample(-5.1662729) + nn * (t_sample(2.5422065) + nn * (t_sample(-0.5811243) + nn * t_sample(0.0636716)))));
//}
//
//inline t_sample genlib_sinT7(t_sample r){
//	const t_sample t84 = 56.;
//	const t_sample t83 = 1680.;
//	const t_sample t82 = 20160.;
//	const t_sample t81 = 2.4801587302e-05;
//	const t_sample t73 = 42.;
//	const t_sample t72 = 840.;
//	const t_sample t71 = 1.9841269841e-04;
//	if(r < GENLIB_PI_OVER_4 && r > -GENLIB_PI_OVER_4){
//		t_sample rr = r*r;
//		return r * (1. - t71 * rr * (t72 - rr * (t73 - rr)));
//	}
//	else if(r > 0.){
//		r -= GENLIB_PI_OVER_2;
//		t_sample rr = r*r;
//		return t_sample(1.) - rr * t81 * (t82 - rr * (t83 - rr * (t84 - rr)));
//	}
//	else{
//		r += GENLIB_PI_OVER_2;
//		t_sample rr = r*r;
//		return t_sample(-1.) + rr * t81 * (t82 - rr * (t83 - rr * (t84 - rr)));
//	}
//}

// use these if r is not known to be in [-pi, pi]:
inline t_sample genlib_cosT8_safe(t_sample r) { return genlib_cosT8(phasewrap(r)); }
//inline double genlib_sin_fast_safe(double r) { return genlib_sin_fast(phasewrap(r)); }
//inline t_sample genlib_sinP7_safe(t_sample r) { return genlib_sinP7(phasewrap(r)); }
//inline t_sample genlib_sinP9_safe(t_sample r) { return genlib_sinP9(phasewrap(r)); }
//inline t_sample genlib_sinT7_safe(t_sample r) { return genlib_sinT7(phasewrap(r)); }



/*=====================================================================*
 *                   Copyright (C) 2011 Paul Mineiro                   *
 * All rights reserved.                                                *
 *                                                                     *
 * Redistribution and use in source and binary forms, with             *
 * or without modification, are permitted provided that the            *
 * following conditions are met:                                       *
 *                                                                     *
 *     * Redistributions of source code must retain the                *
 *     above copyright notice, this list of conditions and             *
 *     the following disclaimer.                                       *
 *                                                                     *
 *     * Redistributions in binary form must reproduce the             *
 *     above copyright notice, this list of conditions and             *
 *     the following disclaimer in the documentation and/or            *
 *     other materials provided with the distribution.                 *
 *                                                                     *
 *     * Neither the name of Paul Mineiro nor the names                *
 *     of other contributors may be used to endorse or promote         *
 *     products derived from this software without specific            *
 *     prior written permission.                                       *
 *                                                                     *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND              *
 * CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES,         *
 * INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES               *
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE             *
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER               *
 * OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,                 *
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES            *
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE           *
 * GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR                *
 * BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF          *
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT           *
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY              *
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE             *
 * POSSIBILITY OF SUCH DAMAGE.                                         *
 *                                                                     *
 * Contact: Paul Mineiro <paul@mineiro.com>                            *
 *=====================================================================*/

inline float genlib_fastersin(float x) {
	static const float fouroverpi = 1.2732395447351627f;
	static const float fouroverpisq = 0.40528473456935109f;
	static const float q = 0.77633023248007499f;
	union { float f; uint32_t i; } p = { 0.22308510060189463f };
	union { float f; uint32_t i; } vx = { x };
	uint32_t sign = vx.i & 0x80000000;
	vx.i &= 0x7FFFFFFF;
	float qpprox = fouroverpi * x - fouroverpisq * x * vx.f;
	p.i |= sign;
	return qpprox * (q + p.f * qpprox);
}

inline float genlib_fastercos(float x) {
	static const float twooverpi = 0.63661977236758134f;
	static const float p = 0.54641335845679634f;
	union { float f; uint32_t i; } vx = { x };
	vx.i &= 0x7FFFFFFF;
	float qpprox = 1.0f - twooverpi * vx.f;
	return qpprox + p * qpprox * (1.0f - qpprox * qpprox);
}

inline float genlib_fastersinfull(float x) {
	static const float twopi = 6.2831853071795865f;
	static const float invtwopi = 0.15915494309189534f;
	int k = int(x * invtwopi);
	float half = (x < 0) ? -0.5f : 0.5f;
	return genlib_fastersin ((half + k) * twopi - x);
}

inline float genlib_fastercosfull(float x) {
	static const float halfpi = 1.5707963267948966f;
	return genlib_fastersinfull (x + halfpi);
}

inline float genlib_fastertanfull(float x) {
	static const float twopi = 6.2831853071795865f;
	static const float invtwopi = 0.15915494309189534f;
	int k = int(x * invtwopi);
	float half = (x < 0) ? -0.5f : 0.5f;
	float xnew = x - (half + k) * twopi;
	return genlib_fastersin (xnew) / genlib_fastercos (xnew);
}


#define cast_uint32_t static_cast<uint32_t>
inline float genlib_fasterpow2(float p) {
	float clipp = (p < -126) ? -126.0f : p;
	union { uint32_t i; float f; } v = { cast_uint32_t (FLOAT_TO_UINT32 ( (1 << 23) * (clipp + 126.94269504f) )) };
	return v.f;
}

inline float genlib_fasterexp(float p) {
	return genlib_fasterpow2 (1.442695040f * p);
}

inline float genlib_fasterlog2(float x) {
	union { float f; uint32_t i; } vx = { x };
	float y = float(vx.i);
	y *= 1.1920928955078125e-7f;
	return y - 126.94269504f;
}

inline float genlib_fasterpow(float x, float p) {
	return genlib_fasterpow2(p * genlib_fasterlog2 (x));
}

// from http://dspguru.com/dsp/tricks/fixed-point-atan2-with-self-normalization
inline float genlib_fasteratan2(float y, float x) {
	const float coeff_1 = (float)(GENLIB_PI/4);
	const float coeff_2 = 3 * (float)(GENLIB_PI/4);
	float abs_y = fabs(y) + 1e-10; // kludge to prevent 0/0 condition
	float r, angle;
	if (x >= 0) {
		r = (x - abs_y) / (x + abs_y);
		angle = coeff_1 - coeff_1 * r;
	}
	else {
		r = (x + abs_y) / (abs_y - x);
		angle = coeff_2 - coeff_1 * r;
	}
	if (y < 0) {
		return (-angle); // negate if in quad III or IV
	}
	else {
		return (angle);
	}
}

// http://math.stackexchange.com/questions/107292/rapid-approximation-of-tanhx
inline float genlib_fastertanh(float x) {
	return (-.67436811832e-5 + (.2468149110712040 + (.583691066395175e-1 + .3357335044280075e-1 * x) * x) * x) /
			(.2464845986383725 + (.609347197060491e-1 + (.1086202599228572 + .2874707922475963e-1 * x) * x) * x);
}

////////////////////////////////////////////////////////////////

inline t_sample fastertanfull(t_sample x) {
	return (t_sample)genlib_fastertanfull((float)x);
}

inline t_sample fastersinfull(t_sample x) {
	return (t_sample)genlib_fastersinfull((float)x);
}

inline t_sample fastercosfull(t_sample x) {
	return (t_sample)genlib_fastercosfull((float)x);
}

inline t_sample fasterexp(t_sample x) {
	return (t_sample)genlib_fasterexp((float)x);
}

inline t_sample fasterlog2(t_sample x) {
	return (t_sample)genlib_fasterlog2((float)x);
}

inline t_sample fasterpow(t_sample x, t_sample p) {
	return (t_sample)genlib_fasterpow((float)x, (float)p);
}

inline t_sample fasterpow2(t_sample p) {
	return (t_sample)genlib_fasterpow2((float)p);
}

inline t_sample fasteratan2(t_sample y, t_sample x) {
	return (t_sample)genlib_fasteratan2(y, x);
}

inline t_sample fastertanh(t_sample x) {
	return (t_sample)genlib_fastertanh((float)x);
}

/****************************************************************/



inline t_sample minimum(t_sample x, t_sample y) { return (y<x?y:x); }
inline t_sample maximum(t_sample x, t_sample y) { return (x<y?y:x); }

inline t_sample clamp(t_sample x, t_sample minVal, t_sample maxVal) {
	return minimum(maximum(x,minVal),maxVal);
}

template<typename T>
inline T smoothstep(t_sample e0, t_sample e1, T x) {
	T t = clamp( safediv(x-T(e0),T(e1-e0)), 0., 1. );
	return t*t*(T(3) - T(2)*t);
}

inline t_sample mix(t_sample x, t_sample y, t_sample a) {
	return x+a*(y-x);
}

inline t_sample scale(t_sample in, t_sample inlow, t_sample inhigh, t_sample outlow, t_sample outhigh, t_sample power)
{
	t_sample value;
	t_sample inscale = safediv(1., inhigh - inlow);
	t_sample outdiff = outhigh - outlow;

	value = (in - inlow) * inscale;
	if (value > 0.0)
		value = pow(value, power);
	else if (value < 0.0)
		value = -pow(-value, power);
	value = (value * outdiff) + outlow;

	return value;
}

inline t_sample linear_interp(t_sample a, t_sample x, t_sample y) {
	return x+a*(y-x);
}

inline t_sample cosine_interp(t_sample a, t_sample x, t_sample y) {
	const t_sample a2 = (t_sample(1.)-genlib_cosT8_safe(a*t_sample(GENLIB_PI)))/t_sample(2.);
	return(x*(t_sample(1.)-a2)+y*a2);
}

inline t_sample cubic_interp(t_sample a, t_sample w, t_sample x, t_sample y, t_sample z) {
	const t_sample a1 = t_sample(1.) + a;
	const t_sample aa = a * a1;
	const t_sample b = t_sample(1.) - a;
	const t_sample b1 = t_sample(2.) - a;
	const t_sample bb = b * b1;
	const t_sample fw = t_sample(-.1666667) * bb * a;
	const t_sample fx = t_sample(.5) * bb * a1;
	const t_sample fy = t_sample(.5) * aa * b1;
	const t_sample fz = t_sample(-.1666667) * aa * b;
	return w * fw + x * fx + y * fy + z * fz;
}

// deprecated, as it shows some instability with feedback
inline t_sample fastcubic_interp(t_sample a, t_sample w, t_sample x, t_sample y, t_sample z) {
	const t_sample a2 = a*a;
	const t_sample f0 = z - y - w + x;
	const t_sample f1 = w - x - f0;
	const t_sample f2 = y - w;
	const t_sample f3 = x;
	return(f0*a*a2 + f1*a2 + f2*a + f3);
}

// Breeuwsma catmull-rom spline interpolation
inline t_sample spline_interp(t_sample a, t_sample w, t_sample x, t_sample y, t_sample z) {
	const t_sample c0 = x;
	const t_sample c1 = t_sample(0.5) * (y - w);
	const t_sample c2 = w - t_sample(2.5) * x + y + y - t_sample(0.5) * z;
	const t_sample c3 = t_sample(0.5) * (z - w) + t_sample(1.5) * (x - y);
	return (((c3 * a + c2) * a + c1) * a + c0);
}

// 6-point, 5th-order B-spline
inline t_sample spline6_interp(t_sample a, t_sample y0, t_sample y1, t_sample y2, t_sample y3, t_sample y4, t_sample y5) {
	// http://yehar.com/blog/wp-content/uploads/2009/08/deip.pdf
	// 6-point, 5th-order B-spline (x-form)
	const t_sample ym2py2 = y0+y4;
	const t_sample ym1py1 = y1+y3;
	const t_sample y2mym2 = y4-y0;
	const t_sample y1mym1 = y3-y1;
	const t_sample sixthym1py1 = 1/6.0*ym1py1;
	const t_sample c0 = 1/120.0*ym2py2 + 13/60.0*ym1py1 + 11/20.0*y2;
	const t_sample c1 = 1/24.0*y2mym2 + 5/12.0*y1mym1;
	const t_sample c2 = 1/12.0*ym2py2 + sixthym1py1 - 1/2.0*y2;
	const t_sample c3 = 1/12.0*y2mym2 - 1/6.0*y1mym1;
	const t_sample c4 = 1/24.0*ym2py2 - sixthym1py1 + 1/4.0*y2;
	const t_sample c5 = 1/120.0*(y5-y0) + 1/24.0*(y1-y4) + 1/12.0*(y3-y2);
	return ((((c5*a+c4)*a+c3)*a+c2)*a+c1)*a+c0;
}

template<typename T1, typename T2>
inline T1 neqp(T1 x, T2 y) {
	return ((((x) != T1(y))) ? (x) : T1(0));
}

template<typename T1, typename T2>
inline T1 gtp(T1 x, T2 y) { return ((((x) > T1(y))) ? (x) : T1(0)); }
template<typename T1, typename T2>
inline T1 gtep(T1 x, T2 y) { return ((((x) >= T1(y))) ? (x) : T1(0)); }
template<typename T1, typename T2>
inline T1 ltp(T1 x, T2 y) { return ((((x) < T1(y))) ? (x) : T1(0)); }
template<typename T1, typename T2>
inline T1 ltep(T1 x, T2 y) { return ((((x) <= T1(y))) ? (x) : T1(0)); }

inline t_sample fract(t_sample x) { double unused; return (t_sample)modf((double)x, &unused); }

// log2(x) = log(x)/log(2)
template<typename T>
inline T log2(T x) {
	return log(x)*GENLIB_1_OVER_LOG_2;
}

inline t_sample atodb(t_sample in) {
	return t_sample((in <= 0.) ? -999. : (20. * log10(in)));
}

inline t_sample dbtoa(t_sample in) {
	return t_sample(pow(10., in * 0.05));
}

inline t_sample ftom(t_sample in, t_sample tuning=440.) {
	return t_sample(69. + 17.31234050465299 * log(safediv(in, tuning)));
}

inline t_sample mtof(t_sample in, t_sample tuning=440.) {
	return t_sample(tuning * exp(.057762265 * (in - 69.0)));
}

inline t_sample mstosamps(t_sample ms, t_sample samplerate=44100.) {
	return t_sample(samplerate * ms * t_sample(0.001));
}

inline t_sample sampstoms(t_sample s, t_sample samplerate=44100.) {
	return t_sample(t_sample(1000.) * s / samplerate);
}

inline t_sample triangle(t_sample phase, t_sample p1) {
	phase = wrap(phase, 0., 1.);
	p1 = clamp(p1, 0., 1.);
	if (phase < p1)
		return t_sample((p1) ? phase/p1 : 0.);
	else
		return t_sample((p1==1.) ? phase : 1. - ((phase - p1) / (1. - p1)));
}

struct Delta {
	t_sample history;
	Delta() { reset(); }
	inline void reset(t_sample init=0) { history=init; }

	inline t_sample operator()(t_sample in1) {
		t_sample ret = in1 - history;
		history = in1;
		return ret;
	}
};
struct Change {
	t_sample history;
	Change() { reset(); }
	inline void reset(t_sample init=0) { history=init; }

	inline t_sample operator()(t_sample in1) {
		t_sample ret = in1 - history;
		history = in1;
		return sign(ret);
	}
};

struct Rate {
	t_sample phase, diff, mult, invmult, prev;
	int wantlock, quant;

	Rate() { reset(); }

	inline void reset() {
		phase = diff = prev = 0;
		mult = invmult = 1;
		wantlock = 1;
		quant = 1;
	}

	inline t_sample perform_lock(t_sample in1, t_sample in2) {
		// did multiplier change?
		if (in2 != mult && !genlib_isnan(in2)) {
			mult = in2;
			invmult = safediv(1., mult);
			wantlock = 1;
		}
		t_sample diff = in1 - prev;

		if (diff < t_sample(-0.5)) {
			diff += t_sample(1);
		} else if (diff > t_sample(0.5)) {
			diff -= t_sample(1);
		}

		if (wantlock) {
			// recalculate phase
			phase = (in1 - GENLIB_QUANT(in1, quant)) * invmult
						+ GENLIB_QUANT(in1, quant * mult);
			diff = 0;
			wantlock = 0;
		} else {
			// diff is always between -0.5 and 0.5
			phase += diff * invmult;
		}

		if (phase > t_sample(1.) || phase < t_sample(-0.)) {
			phase = phase - (long)(phase);
		}

		prev = in1;

		return phase;
	}

	inline t_sample perform_cycle(t_sample in1, t_sample in2) {
		// did multiplier change?
		if (in2 != mult && !genlib_isnan(in2)) {
			mult = in2;
			invmult = safediv(1., mult);
			wantlock = 1;
		}
		t_sample diff = in1 - prev;

		if (diff < t_sample(-0.5)) {
			if (wantlock) {
				wantlock = 0;
				phase = in1 * invmult;
				diff = t_sample(0);
			} else {
				diff += t_sample(1);
			}
		} else if (diff > t_sample(0.5)) {
			if (wantlock) {
				wantlock = 0;
				phase = in1 * invmult;
				diff = t_sample(0);
			} else {
				diff -= t_sample(1);
			}
		}

		// diff is always between -0.5 and 0.5
		phase += diff * invmult;

		if (phase > t_sample(1.) || phase < t_sample(-0.)) {
			phase = phase - (long)(phase);
		}

		prev = in1;

		return phase;
	}

	inline t_sample perform_off(t_sample in1, t_sample in2) {
		// did multiplier change?
		if (in2 != mult && !genlib_isnan(in2)) {
			mult = in2;
			invmult = safediv(1., mult);
			wantlock = 1;
		}
		t_sample diff = in1 - prev;

		if (diff < t_sample(-0.5)) {
			diff += t_sample(1);
		} else if (diff > t_sample(0.5)) {
			diff -= t_sample(1);
		}

		phase += diff * invmult;

		if (phase > t_sample(1.) || phase < t_sample(-0.)) {
			phase = phase - (long)(phase);
		}

		prev = in1;

		return phase;
	}
};

struct DCBlock {
	t_sample x1, y1;
	DCBlock() { reset(); }
	inline void reset() { x1=0; y1=0; }

	inline t_sample operator()(t_sample in1) {
		t_sample y = in1 - x1 + y1*t_sample(0.9997);
		x1 = in1;
		y1 = y;
		return y;
	}
};


#ifdef GENLIB_USE_FLOAT32

// initializing at global scope to avoid issues on windows with static initializers
// (runtime crash due to missing __cxx_guard_acquire, #15365)
static const t_sample EXP2_NEG23 = exp2f(-23.f);

struct Noise {
    uint32_t state[4];

	// uses system clock to generate a random seed
	// ensures distinct seeds even if creating several Noise objects at the same clock value
	static uint64_t uniqueTickCount(void) {
		static uint64_t lasttime = 0;
		uint64_t time = genlib_ticks();
		return (time <= lasttime) ? (++lasttime) : (lasttime = time);
	}
    
    Noise() { reset(); }
	Noise(t_sample seed) { reset(seed); } 
    
	void reset(t_sample seed) { 
	   uint64_t x = (uint64_t)(seed*1E6);
		state[3] = splitmix32(state[2] = splitmix32(state[1] = splitmix32(state[0] = splitmix32(x))));
	}
	void reset() { reset( uniqueTickCount() ); }
	
	// adapted from the xoshiro128+ PRNG, see http://prng.di.unimi.it
    /*  xoshiro128+: Written in 2018 by David Blackman and Sebastiano Vigna (vigna@acm.org)
    To the extent possible under law, the author has dedicated all copyright
    and related and neighboring rights to this software to the public domain
    worldwide. This software is distributed without any warranty.
    See <http://creativecommons.org/publicdomain/zero/1.0/>. */
	inline t_sample operator()() {
		const uint32_t result = state[0] + state[3];
        const uint32_t t = state[1] << 9;
        state[2] ^= state[0];
        state[3] ^= state[1];
        state[1] ^= state[2];
        state[0] ^= state[3];
        state[2] ^= t;
        state[3] = (state[3] << 11) | (state[3] >> 21); // rotl(s[3], 11) => (x << k) | (x >> (32 - k))
        // discard lower 8 bits (exponent), convert to double in 0..2, map to -1..1:
        // exactly quivalent to ldexpf((t_sample)(result >> 8), -23) - 1.0;
		// but much cheaper on ARM CPU
		return ((result >> 8)*EXP2_NEG23) - 1.f; 
	}
	
    // splitmix32 suggested by David Blackman and Sebastiano Vigna as a good seed for xoshiro256+:
	/* This is a fixed-increment version of Java 8's SplittableRandom generator
    See http://dx.doi.org/10.1145/2714064.2660195 and 
    http://docs.oracle.com/javase/8/docs/api/java/util/SplittableRandom.html
    It is a very fast generator passing BigCrush, and it can be useful if
    for some reason you absolutely want 64 bits of state. */
    uint32_t splitmix32(uint64_t seed) {
	    uint64_t z = (seed += 0x9e3779b97f4a7c15);
	    z = (z ^ (z >> 33)) * 0x62a9d9ed799705f5;
	    z = (z ^ (z >> 28)) * 0xcb24d0a5c88c35b3;
	    return z >> 32;
    } 
};
#else

// initializing at global scope to avoid issues on windows with static initializers
// (runtime crash due to missing __cxx_guard_acquire, #15365)
static const t_sample EXP2_NEG52 = exp2(-52);

struct Noise {
    uint64_t state[4];

	// uses system clock to generate a random seed
	// ensures distinct seeds even if creating several Noise objects at the same clock value
	static uint64_t uniqueTickCount(void) {
		static uint64_t lasttime = 0;
		uint64_t time = genlib_ticks();
		return (time <= lasttime) ? (++lasttime) : (lasttime = time);
	}
    
    Noise() { reset(); }
	Noise(t_sample seed) { reset(seed); } 
    
	void reset(t_sample seed) { 
	   uint64_t x = (uint64_t)(seed*1E6);
	   state[3] = splitmix64(state[2] = splitmix64(state[1] = splitmix64(state[0] = splitmix64(x))));
	}
	void reset() { reset( uniqueTickCount() ); }
	
	// adapted from the xoshiro256+ PRNG, see http://prng.di.unimi.it
    /*  xoshiro256+: Written in 2018 by David Blackman and Sebastiano Vigna (vigna@acm.org)
    To the extent possible under law, the author has dedicated all copyright
    and related and neighboring rights to this software to the public domain
    worldwide. This software is distributed without any warranty.
    See <http://creativecommons.org/publicdomain/zero/1.0/>. */
	inline t_sample operator()() {
		const uint64_t result = state[0] + state[3];
        const uint64_t t = state[1] << 17;
        state[2] ^= state[0];
        state[3] ^= state[1];
        state[1] ^= state[2];
        state[0] ^= state[3];
        state[2] ^= t;
        state[3] = (state[3] << 45) | (state[3] >> 19); // rotl(s[3], 45) => (x << k) | (x >> (64 - k))
        // discard lower 11 bits, convert to double in 0..2, map to -1..1:
        // equivalent to ldexp((double)(result >> 11), -52) - 1.0;
		return ((result >> 11)*EXP2_NEG52) - 1.0; 
	}
	
    // splitmix64 suggested by David Blackman and Sebastiano Vigna as a good seed for xoshiro256+:
	/* This is a fixed-increment version of Java 8's SplittableRandom generator
    See http://dx.doi.org/10.1145/2714064.2660195 and 
    http://docs.oracle.com/javase/8/docs/api/java/util/SplittableRandom.html
    It is a very fast generator passing BigCrush, and it can be useful if
    for some reason you absolutely want 64 bits of state. */
    uint64_t splitmix64(uint64_t seed) {
	    uint64_t z = (seed += 0x9e3779b97f4a7c15);
	    z = (z ^ (z >> 30)) * 0xbf58476d1ce4e5b9;
	    z = (z ^ (z >> 27)) * 0x94d049bb133111eb;
	    return z ^ (z >> 31);
    }  
};
#endif

struct Phasor {
	t_sample phase;
	Phasor() { reset(); }
	void reset(t_sample v=0.) { phase=v; }
	inline t_sample operator()(t_sample freq, t_sample invsamplerate) {
		const t_sample pincr = freq * invsamplerate;
		//phase = genlib_wrapfew(phase + pincr, 0., 1.); // faster for low frequencies, but explodes with high frequencies
		phase = wrap(phase + pincr, 0., 1.);
		return phase;
	}
};

struct PlusEquals {
	t_sample count;
	PlusEquals() { reset(); }
	void reset(t_sample v=0.) { count=v; }

	// reset post-application mode:
	inline t_sample post(t_sample incr, t_sample reset, t_sample min, t_sample max) {
		count = reset ? min : wrap(count+incr, min, max);
		return count;
	}
	inline t_sample post(t_sample incr=1., t_sample reset=0., t_sample min=0.) {
		count = reset ? min : count+incr;
		return count;
	}

	// reset pre-application mode:
	inline t_sample pre(t_sample incr, t_sample reset, t_sample min, t_sample max) {
		count = reset ? min+incr : wrap(count+incr, min, max);
		return count;
	}
	inline t_sample pre(t_sample incr=1., t_sample reset=0., t_sample min=0.) {
		count = reset ? min+incr : count+incr;
		return count;
	}
};

struct MulEquals {
	t_sample count;
	MulEquals() { reset(); }
	void reset(t_sample v=0.) { count=v; }

	// reset post-application mode:
	inline t_sample post(t_sample incr, t_sample reset, t_sample min, t_sample max) {
		count = reset ? min : wrap(fixdenorm(count*incr), min, max);
		return count;
	}
	inline t_sample post(t_sample incr=1., t_sample reset=0., t_sample min=0.) {
		count = reset ? min : fixdenorm(count*incr);
		return count;
	}

	// reset pre-application mode:
	inline t_sample pre(t_sample incr, t_sample reset, t_sample min, t_sample max) {
		count = reset ? min*incr : wrap(fixdenorm(count*incr), min, max);
		return count;
	}
	inline t_sample pre(t_sample incr=1., t_sample reset=0., t_sample min=0.) {
		count = reset ? min*incr : fixdenorm(count*incr);
		return count;
	}
};

struct Sah {
	t_sample prev, output;
	Sah() { reset(); }
	void reset(t_sample o=0.) {
		output = prev = o;
	}

	inline t_sample operator()(t_sample in, t_sample trig, t_sample thresh) {
		if (prev <= thresh && trig > thresh) {
			output = in;
		}
		prev = trig;
		return output;
	}
};

struct Train {
	t_sample phase, state;
	Train() { reset(); }
	void reset(t_sample p=0) { phase = p; state = 0.; }

	inline t_sample operator()(t_sample pulseinterval, t_sample width, t_sample pulsephase) {
		if (width <= t_sample(0.)) {
			state = t_sample(0.);	// no pulse!
		} else if (width >= 1.) {
			state = t_sample(1.); // constant pulse!
		} else {
			const t_sample interval = maximum(pulseinterval, t_sample(1.));	// >= 1.
			const t_sample p1 = clamp(pulsephase, t_sample(0.), t_sample(1.));	// [0..1]
			const t_sample p2 = p1+width;						// (p1..p1+1)
			const t_sample pincr = t_sample(1.)/interval;			// (0..1]
			phase += pincr;								// +ve
			if (state) {	// on:
				if (phase > p2) {
					state = t_sample(0.);				// turn off
					phase -= (int)(1.+phase-p2);		// wrap phase back down
				}
			} else {		// off:
				if (phase > p1) {
					state = t_sample(1.);				// turn on.
				}
			}
		}
		return state;
	}
};

struct Delay {
	t_sample *memory;
	long size, wrap, maxdelay;
	long reader, writer;

	t_genlib_data *dataRef;

	Delay() : memory(0) {
		size = wrap = maxdelay = 0;
		reader = writer = 0;
		dataRef = 0;
	}
	~Delay() {
		if (dataRef != 0) {
			// store write position for persistence:
			genlib_data_setcursor(dataRef, writer);
			// decrement reference count:
			genlib_data_release(dataRef);
		}
	}

	inline void reset(const char *name, long d) {
		// if needed, acquire the Data's global reference:
		if (dataRef == 0) {

			void *ref = genlib_obtain_reference_from_string(name);
			dataRef = genlib_obtain_data_from_reference(ref);
			if (dataRef == 0) {
				genlib_report_error("failed to acquire data");
				return;
			}

			// scale maxdelay to next highest power of 2:
			maxdelay = d;
			size = maxdelay < 2 ? 2 : maxdelay;
			size = long(next_power_of_two(size));

			// first reset should resize the memory:
			genlib_data_resize(dataRef, size, 1);

			t_genlib_data_info info;
			if (genlib_data_getinfo(dataRef, &info) == GENLIB_ERR_NONE) {
				if (info.dim != size) {
					// at this point, could resolve by reducing to
					// maxdelay = size = next_power_of_two(info.dim+1)/2;
					// but really, if this happens, it means more than one
					// object is referring to the same t_gen_dsp_data.
					// which is probably bad news.
					genlib_report_error("delay memory size error");
					memory = 0;
					return;
				}
				memory = info.data;
				writer = genlib_data_getcursor(dataRef);
			} else {
				genlib_report_error("failed to acquire data info");
			}

		} else {
			// subsequent reset should zero the memory & heads:
			set_zero64(memory, size);
			writer = 0;
		}

		reader = writer;
		wrap = size-1;
	}

	// called at bufferloop end, updates read pointer time
	inline void step() {
		reader++;
		if (reader >= size) reader = 0;
	}

	inline void write(t_sample x) {
		writer = reader;	// update write ptr
		memory[writer] = x;
	}

	inline t_sample read_step(t_sample d) {
		// extra half for nice rounding:
		// min 1 sample delay for read before write (r != w)
		const t_sample r = t_sample(size + reader) - clamp(d-t_sample(0.5), t_sample(reader != writer), t_sample(maxdelay));
		long r1 = long(r);
		return memory[r1 & wrap];
	}

	inline t_sample read_linear(t_sample d) {
		// min 1 sample delay for read before write (r != w)
		t_sample c = t_sample(clamp(d, t_sample(reader != writer), t_sample(maxdelay)));
		const t_sample r = t_sample(size + reader) - c;
		long r1 = long(r);
		long r2 = r1+1;
		t_sample a = r - (t_sample)r1;
		t_sample x = memory[r1 & wrap];
		t_sample y = memory[r2 & wrap];
		return linear_interp(a, x, y);
	}

	inline t_sample read_cosine(t_sample d) {
		// min 1 sample delay for read before write (r != w)
		const t_sample r = t_sample(size + reader) - clamp(d, t_sample(reader != writer), t_sample(maxdelay));
		long r1 = long(r);
		long r2 = r1+1;
		t_sample a = r - (t_sample)r1;
		t_sample x = memory[r1 & wrap];
		t_sample y = memory[r2 & wrap];
		return cosine_interp(a, x, y);
	}

	// cubic requires extra sample of compensation:
	inline t_sample read_fastcubic(t_sample d) {
		// min 1 sample delay for read before write (r != w)
		// plus extra 1 sample compensation for 4-point interpolation
		const t_sample r = t_sample(size + reader) - clamp(d, t_sample(1.) + t_sample(reader != writer), t_sample(maxdelay));
		long r1 = long(r);
		long r2 = r1+1;
		long r3 = r1+2;
		long r4 = r1+3;
		t_sample a = r - (t_sample)r1;
		t_sample w = memory[r1 & wrap];
		t_sample x = memory[r2 & wrap];
		t_sample y = memory[r3 & wrap];
		t_sample z = memory[r4 & wrap];
		return fastcubic_interp(a, w, x, y, z);
	}
	
	// cubic requires extra sample of compensation:
	inline t_sample read_cubic(t_sample d) {
		// min 1 sample delay for read before write (r != w)
		// plus extra 1 sample compensation for 4-point interpolation
		const t_sample r = t_sample(size + reader) - clamp(d, t_sample(1.) + t_sample(reader != writer), t_sample(maxdelay));
		long r1 = long(r);
		long r2 = r1+1;
		long r3 = r1+2;
		long r4 = r1+3;
		t_sample a = r - (t_sample)r1;
		t_sample w = memory[r1 & wrap];
		t_sample x = memory[r2 & wrap];
		t_sample y = memory[r3 & wrap];
		t_sample z = memory[r4 & wrap];
		return cubic_interp(a, w, x, y, z);
	}

	// spline requires extra sample of compensation:
	inline t_sample read_spline(t_sample d) {
		// min 1 sample delay for read before write (r != w)
		// plus extra 1 sample compensation for 4-point interpolation
		const t_sample r = t_sample(size + reader) - clamp(d, t_sample(1.) + t_sample(reader != writer), t_sample(maxdelay));
		long r1 = long(r);
		long r2 = r1+1;
		long r3 = r1+2;
		long r4 = r1+3;
		t_sample a = r - (t_sample)r1;
		t_sample w = memory[r1 & wrap];
		t_sample x = memory[r2 & wrap];
		t_sample y = memory[r3 & wrap];
		t_sample z = memory[r4 & wrap];
		return spline_interp(a, w, x, y, z);
	}
	
	// spline requires extra sample of compensation:
	inline t_sample read_spline6(t_sample d) {
		// min 1 sample delay for read before write (r != w)
		// plus extra 1 sample compensation for 4-point interpolation
		const t_sample r = t_sample(size + reader) - clamp(d, t_sample(1.) + t_sample(reader != writer), t_sample(maxdelay));
		long r0 = long(r);
		long r1 = r1+1;
		long r2 = r1+2;
		long r3 = r1+3;
		long r4 = r1+4;
		long r5 = r1+5;
		t_sample a = r - (t_sample)r0;
		t_sample y0 = memory[r0 & wrap];
		t_sample y1 = memory[r1 & wrap];
		t_sample y2 = memory[r2 & wrap];
		t_sample y3 = memory[r3 & wrap];
		t_sample y4 = memory[r4 & wrap];
		t_sample y5 = memory[r5 & wrap];
		return spline6_interp(a, y0, y1, y2, y3, y4, y5);
	}
};

template<typename T=t_sample>
struct DataInterface {
	long dim, channels;
	T *mData;
	void *mDataReference;		// this was t_symbol *mName
	int modified;

	DataInterface() : dim(0), channels(1), mData(0), modified(0) { mDataReference = 0; }

	// raw reading/writing/overdubbing (internal use only, no bounds checking)
	inline t_sample read(long index, long channel=0) const {
		return mData[channel+index*channels];
	}
	inline void write(T value, long index, long channel=0) {
		mData[channel+index*channels] = value;
		modified = 1;
	}
	// NO LONGER USED:
	inline void overdub(T value, long index, long channel=0) {
		mData[channel+index*channels] += value;
		modified = 1;
	}

	// averaging overdub (used by splat)
	inline void blend(T value, long index, long channel, t_sample alpha) {
		long offset = channel+index*channels;
		const T old = mData[offset];
		mData[offset] = old + alpha * (value - old);
		modified = 1;
	}

	// NO LONGER USED:
	inline void read_ok(long index, long channel=0, bool ok=1) const {
		return ok ? mData[channel+index*channels] : T(0);
	}
	inline void write_ok(T value, long index, long channel=0, bool ok=1) {
		if (ok) mData[channel+index*channels] = value;
	}
	inline void overdub_ok(T value, long index, long channel=0, bool ok=1) {
		if (ok) mData[channel+index*channels] += value;
	}

	// Bounds strategies:
	inline long index_clamp(long index) const { return clamp(index, 0, dim-1); }
	inline long index_wrap(long index) const { return wrap(index, 0, dim); }
	inline long index_fold(long index) const { return fold(index, 0, dim); }
	inline bool index_oob(long index) const { return (index < 0 || index >= dim); }
	inline bool index_inbounds(long index) const { return (index >=0 && index < dim); }

	// channel bounds:
	inline long channel_clamp(long c) const { return clamp(c, 0, channels-1); }
	inline long channel_wrap(long c) const { return wrap(c, 0, channels); }
	inline long channel_fold(long c) const { return fold(c, 0, channels); }
	inline bool channel_oob(long c) const { return (c < 0 || c >= channels); }
	inline bool channel_inbounds(long c) const { return !channel_oob(c); }

	// Indexing strategies:
	// [0..1] -> [0..(dim-1)]
	inline t_sample phase2index(t_sample phase) const { return phase * t_sample(dim-1); }
	// [0..1] -> [min..max]
	inline t_sample subphase2index(t_sample phase, long min, long max) const {
		min = index_clamp(min);
		max = index_clamp(max);
		return t_sample(min) + phase * t_sample(max-min);
	}
	// [-1..1] -> [0..(dim-1)]
	inline t_sample signal2index(t_sample signal) const { return phase2index((signal+t_sample(1.)) * t_sample(0.5)); }

	inline T peek(t_sample index, long channel=0) const {
		const long i = (long)index;
		if (index_oob(i) || channel_oob(channel)) {
			return 0.;
		} else {
			return read(i, channel);
		}
	}

	inline T index(t_sample index, long channel=0) const {
		channel = channel_clamp(channel);
		// no-interp:
		long i = (long)index;
		// bound:
		i = index_clamp(i);
		return read(i, channel);
	}

	inline T cell(t_sample index, long channel=0) const {
		channel = channel_clamp(channel);
		// no-interp:
		long i = (long)index;
		// bound:
		i = index_wrap(i);
		return read(i, channel);
	}

	inline T cycle(t_sample phase, long channel=0) const {
		channel = channel_clamp(channel);
		t_sample index = phase2index(phase);
		// interp:
		long i1 = (long)index;
		long i2 = i1+1;
		const t_sample alpha = index - (t_sample)i1;
		// bound:
		i1 = index_wrap(i1);
		i2 = index_wrap(i2);
		// interp:
		T v1 = read(i1, channel);
		T v2 = read(i2, channel);
		return mix(v1, v2, alpha);
	}

	inline T lookup(t_sample signal, long channel=0) const {
		channel = channel_clamp(channel);
		t_sample index = signal2index(signal);
		// interp:
		long i1 = (long)index;
		long i2 = i1+1;
		t_sample alpha = index - (t_sample)i1;
		// bound:
		i1 = index_clamp(i1);
		i2 = index_clamp(i2);
		// interp:
		T v1 = read(i1, channel);
		T v2 = read(i2, channel);
		return mix(v1, v2, alpha);
	}
	// NO LONGER USED:
	inline void poke(t_sample value, t_sample index, long channel=0) {
		const long i = (long)index;
		if (!(index_oob(i) || channel_oob(channel))) {
			write(fixdenorm(value), i, channel);
		}
	}
	// NO LONGER USED:
	inline void splat_adding(t_sample value, t_sample phase, long channel=0) {
		const t_sample valuef = fixdenorm(value);
		channel = channel_clamp(channel);
		t_sample index = phase2index(phase);
		// interp:
		long i1 = (long)index;
		long i2 = i1+1;
		const t_sample alpha = index - (t_sample)i1;
		// bound:
		i1 = index_wrap(i1);
		i2 = index_wrap(i2);
		// interp:
		overdub(valuef*(1.-alpha), i1, channel);
		overdub(valuef*alpha,      i2, channel);
	}
	// NO LONGER USED:
	inline void splat(t_sample value, t_sample phase, long channel=0) {
		const t_sample valuef = fixdenorm(value);
		channel = channel_clamp(channel);
		t_sample index = phase2index(phase);
		// interp:
		long i1 = (long)index;
		long i2 = i1+1;
		const t_sample alpha = index - (t_sample)i1;
		// bound:
		i1 = index_wrap(i1);
		i2 = index_wrap(i2);
		// interp:
		const T v1 = read(i1, channel);
		const T v2 = read(i2, channel);
		write(v1 + (1.-alpha)*(valuef-v1), i1, channel);
		write(v2 + (alpha)*(valuef-v2), i2, channel);
	}
};

// DATA_MAXIMUM_ELEMENTS * 8 bytes = 256 mb limit
#define DATA_MAXIMUM_ELEMENTS	(33554432)

struct Data : public DataInterface<t_sample> {
	t_genlib_data * dataRef;	// a pointer to some external source of the data

	Data() : DataInterface<t_sample>() {
		dataRef = 0;
	}
	~Data() {
		//genlib_report_message("releasing data handle %d", dataRef);
		if (dataRef != 0) {
			genlib_data_release(dataRef);
		}
	}
	void reset(const char * name, long s, long c) {
		// if needed, acquire the Data's global reference:
		if (dataRef == 0) {
			void *ref = genlib_obtain_reference_from_string(name);
			dataRef = genlib_obtain_data_from_reference(ref);
			if (dataRef == 0) {
				genlib_report_error("failed to acquire data");
				return;
			}
		}
		genlib_data_resize(dataRef, s, c);
		getinfo();
	}
	bool setbuffer(void *bufferRef) {
		//genlib_report_message("set buffer %p", bufferRef);
		if (dataRef == 0) {
			// error: no data, or obtain?
			return false;
		}
		genlib_data_setbuffer(dataRef, bufferRef);
		getinfo();
		return true;
	}

	void getinfo() {
		t_genlib_data_info info;
		if (genlib_data_getinfo(dataRef, &info) == GENLIB_ERR_NONE) {
			mData = info.data;
			dim = info.dim;
			channels = info.channels;
		} else {
			genlib_report_error("failed to acquire data info");
		}
	}
};

// Used by SineData
struct DataLocal : public DataInterface<t_sample> {
	DataLocal() : DataInterface<t_sample>() {}
	~DataLocal() {
		if (mData) sysmem_freeptr(mData);
		mData = 0;
	}

	void reset(long s, long c) {
		mData=0;
		resize(s, c);
	}

	void resize(long s, long c) {
		if (s * c > DATA_MAXIMUM_ELEMENTS) {
			s = DATA_MAXIMUM_ELEMENTS/c;
			genlib_report_message("warning: resizing data to < 256MB");
		}
		if (mData) {
			sysmem_resizeptr(mData, sizeof(t_sample) * s * c);
		} else {
			mData = (t_sample *)sysmem_newptr(sizeof(t_sample) * s * c);
		}
		if (!mData) {
			genlib_report_error("out of memory");
			resize(512, 1);
			return;
		} else {
			dim = s;
			channels = c;
		}
		set_zero64(mData, dim * channels);
	}

	// copy from a buffer~
	// resizing is safe only during initialization!
	bool setbuffer(void *dataReference) {
		mDataReference = dataReference; // replaced mName
		bool result = false;
		t_genlib_buffer *b;
		t_genlib_buffer_info info;
		if (mDataReference != 0) {
			b = (t_genlib_buffer *)genlib_obtain_buffer_from_reference(mDataReference);
			if (b) {
				if (genlib_buffer_edit_begin(b)==GENLIB_ERR_NONE) {
					if (genlib_buffer_getinfo(b, &info)==GENLIB_ERR_NONE) {
						float *samples = info.b_samples;
						long frames = info.b_frames;
						long nchans = info.b_nchans;
						//long size = info.b_size;
						//long modtime = info.b_modtime;	// cache & compare?

						// resizing is safe only during initialization!
						if (mData == 0) resize(frames, nchans);

						long frames_safe = frames < dim ? frames : dim;
						long channels_safe = nchans < channels ? nchans : channels;
						// copy:
						for (int f=0; f<frames_safe; f++) {
							for (int c=0; c<channels_safe; c++) {
								t_sample value = samples[c+f*nchans];
								write(value, f, c);
							}
						}
						result = true;
					} else {
						genlib_report_message("couldn't get info for buffer\n");
					}
					genlib_buffer_edit_end(b, 1);
				} else {
					genlib_report_message("buffer locked\n");
				}
			}
		} else {
			genlib_report_message("buffer reference not valid");
		}
		return result;
	}
};

struct Buffer : public DataInterface<float> {
	t_genlib_buffer* mBuf;
	t_genlib_buffer_info mInfo;
	float mDummy;		// safe access in case buffer is not valid

	Buffer() : DataInterface<float>() {}

	void reset(const char *name) {
		dim = 1;
		channels = 1;
		mData = &mDummy;
		mDummy = 0.f;
		mBuf = 0;

		// call into genlib:
		mDataReference = genlib_obtain_reference_from_string(name);
	}

	void setbuffer(void *ref) {
		mDataReference = ref;
	}

	void begin() {
		t_genlib_buffer *b = genlib_obtain_buffer_from_reference(mDataReference);
		mBuf = 0;
		if (b) {
			if (genlib_buffer_perform_begin(b) == GENLIB_ERR_NONE) {
				mBuf = b;
			} else {
				//genlib_report_message ("not a buffer~ %s", mName->s_name);
			}
		} else {
			//genlib_report_message("no object %s\n", mName->s_name);
		}

		if (mBuf && genlib_buffer_getinfo(mBuf, &mInfo)==GENLIB_ERR_NONE) {
			// grab data:
			mBuf = b;
			mData = mInfo.b_samples;
			dim = mInfo.b_frames;
			channels = mInfo.b_nchans;
		} else {
			//genlib_report_message("couldn't get info");
			mBuf = 0;
			mData = &mDummy;
			dim = 1;
			channels = 1;
		}
	}

	void end() {
		if (mBuf) {
			genlib_buffer_perform_end(mBuf);
			if (modified) {
				genlib_buffer_dirty(mBuf);
			}
			modified = 0;
		}
		mBuf = 0;
	}
};

struct SineData : public DataLocal {
	SineData() : DataLocal() {
		const int costable_size = 1 << 14;	// 14 bit index (noise floor at around -156 dB)
		mData = 0;
		resize(costable_size, 1);
		for (int i=0; i<dim; i++) {
			mData[i] = t_sample(cos(i * GENLIB_PI * 2. / (t_sample)(dim)));
		}
	}

	~SineData() {
		if (mData) sysmem_freeptr(mData);
		mData = 0;
	}
};

template<typename T>
inline int dim(const T& data) { return data.dim; }

template<typename T>
inline int channels(const T& data) { return data.channels; }

// used by cycle when no buffer/data is specified:
struct SineCycle {

	uint32_t phasei, pincr;
	t_sample f2i;

	void reset(t_sample samplerate, t_sample init = 0) {
		phasei = FLOAT_TO_UINT32(init * t_sample(4294967296.0));
		pincr = 0;
		f2i = t_sample(4294967296.0) / samplerate;
	}

	inline void freq(t_sample f) {
		pincr = FLOAT_TO_UINT32(f * f2i);
	}

	inline void phase(t_sample f) {
		phasei = FLOAT_TO_UINT32(f * t_sample(4294967296.0));
	}

	inline t_sample phase() const {
		return t_sample(phasei * t_sample(0.232830643653869629e-9));
	}

	template<typename T>
	inline t_sample operator()(const DataInterface<T>& buf) {
		T *data = buf.mData;
		// divide uint32_t range down to buffer size (32-bit to 14-bit)
		uint32_t idx = phasei >> 18;
		// compute fractional portion and divide by 18-bit range
		const t_sample frac = t_sample(phasei & 262143) * t_sample(3.81471181759574e-6);
		// index safely in 14-bit range:
		const t_sample y0 = data[idx];
		const t_sample y1 = data[(idx+1) & 16383];
		const t_sample y = linear_interp(frac, y0, y1);
		phasei += pincr;
		return y;
	}
};

#endif

