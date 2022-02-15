#include "module_max.h"

namespace module_max {

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
  to licensing (at) cycling74.com.  The determination of whether a use is commercial use or non-commercial use is based
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

// global noise generator
Noise noise;
static const int GENLIB_LOOPCOUNT_BAIL = 100000;


// The State struct contains all the state and procedures for the gendsp kernel
typedef struct State {
	CommonState __commonstate;
	Data m_stereo_1;
	Phasor __m_phasor_2;
	int __exception;
	int vectorsize;
	t_sample samples_to_seconds;
	t_sample samplerate;
	// re-initialize all member variables;
	inline void reset(t_param __sr, int __vs) {
		__exception = 0;
		vectorsize = __vs;
		samplerate = __sr;
		m_stereo_1.reset("stereo", ((int)0), ((int)2));
		samples_to_seconds = (1 / samplerate);
		__m_phasor_2.reset(0);
		genlib_reset_complete(this);
		
	};
	// the signal processing routine;
	inline int perform(t_sample ** __ins, t_sample ** __outs, int __n) {
		vectorsize = __n;
		const t_sample * __in1 = __ins[0];
		t_sample * __out1 = __outs[0];
		t_sample * __out2 = __outs[1];
		if (__exception) {
			return __exception;
			
		} else if (( (__in1 == 0) || (__out1 == 0) || (__out2 == 0) )) {
			__exception = GENLIB_ERR_NULL_BUFFER;
			return __exception;
			
		};
		int stereo_dim = m_stereo_1.dim;
		int stereo_channels = m_stereo_1.channels;
		int stereo_dim_1309 = stereo_dim;
		t_sample div_1303 = safediv(samplerate, stereo_dim_1309);
		samples_to_seconds = (1 / samplerate);
		bool chan_ignore_28 = ((1 < 0) || (1 >= stereo_channels));
		// the main sample loop;
		while ((__n--)) {
			const t_sample in1 = (*(__in1++));
			t_sample phasor_1304 = __m_phasor_2(div_1303, samples_to_seconds);
			double sample_index_3 = (phasor_1304 * (stereo_dim - 1));
			int index_trunc_4 = fixnan(floor(sample_index_3));
			double index_fract_5 = (sample_index_3 - index_trunc_4);
			int index_trunc_6 = (index_trunc_4 - 1);
			int index_trunc_7 = (index_trunc_4 + 1);
			int index_trunc_8 = (index_trunc_4 + 2);
			bool index_ignore_9 = ((index_trunc_6 >= stereo_dim) || (index_trunc_6 < 0));
			bool index_ignore_10 = ((index_trunc_4 >= stereo_dim) || (index_trunc_4 < 0));
			bool index_ignore_11 = ((index_trunc_7 >= stereo_dim) || (index_trunc_7 < 0));
			bool index_ignore_12 = ((index_trunc_8 >= stereo_dim) || (index_trunc_8 < 0));
			// phase stereo channel 1;
			double read_stereo_13 = (index_ignore_9 ? 0 : m_stereo_1.read(index_trunc_6, 0));
			double read_stereo_14 = (index_ignore_10 ? 0 : m_stereo_1.read(index_trunc_4, 0));
			double read_stereo_15 = (index_ignore_11 ? 0 : m_stereo_1.read(index_trunc_7, 0));
			double read_stereo_16 = (index_ignore_12 ? 0 : m_stereo_1.read(index_trunc_8, 0));
			double readinterp_17 = spline_interp(index_fract_5, read_stereo_13, read_stereo_14, read_stereo_15, read_stereo_16);
			t_sample sample_stereo_1305 = readinterp_17;
			t_sample index_stereo_1306 = sample_index_3;
			t_sample out1 = sample_stereo_1305;
			double sample_index_18 = (phasor_1304 * (stereo_dim - 1));
			int index_trunc_19 = fixnan(floor(sample_index_18));
			double index_fract_20 = (sample_index_18 - index_trunc_19);
			int index_trunc_21 = (index_trunc_19 - 1);
			int index_trunc_22 = (index_trunc_19 + 1);
			int index_trunc_23 = (index_trunc_19 + 2);
			bool index_ignore_24 = ((index_trunc_21 >= stereo_dim) || (index_trunc_21 < 0));
			bool index_ignore_25 = ((index_trunc_19 >= stereo_dim) || (index_trunc_19 < 0));
			bool index_ignore_26 = ((index_trunc_22 >= stereo_dim) || (index_trunc_22 < 0));
			bool index_ignore_27 = ((index_trunc_23 >= stereo_dim) || (index_trunc_23 < 0));
			// phase stereo channel 1;
			double read_stereo_29 = ((chan_ignore_28 || index_ignore_24) ? 0 : m_stereo_1.read(index_trunc_21, 1));
			double read_stereo_30 = ((chan_ignore_28 || index_ignore_25) ? 0 : m_stereo_1.read(index_trunc_19, 1));
			double read_stereo_31 = ((chan_ignore_28 || index_ignore_26) ? 0 : m_stereo_1.read(index_trunc_22, 1));
			double read_stereo_32 = ((chan_ignore_28 || index_ignore_27) ? 0 : m_stereo_1.read(index_trunc_23, 1));
			double readinterp_33 = spline_interp(index_fract_20, read_stereo_29, read_stereo_30, read_stereo_31, read_stereo_32);
			t_sample sample_stereo_1300 = readinterp_33;
			t_sample index_stereo_1301 = sample_index_18;
			t_sample out2 = sample_stereo_1300;
			// assign results to output buffer;
			(*(__out1++)) = out1;
			(*(__out2++)) = out2;
			
		};
		return __exception;
		
	};
	inline void set_stereo(void * _value) {
		m_stereo_1.setbuffer(_value);
	};
	
} State;


///
///	Configuration for the genlib API
///

/// Number of signal inputs and outputs

int gen_kernel_numins = 1;
int gen_kernel_numouts = 2;

int num_inputs() { return gen_kernel_numins; }
int num_outputs() { return gen_kernel_numouts; }
int num_params() { return 1; }

/// Assistive lables for the signal inputs and outputs

const char *gen_kernel_innames[] = { "in1" };
const char *gen_kernel_outnames[] = { "out1", "out2" };

/// Invoke the signal process of a State object

int perform(CommonState *cself, t_sample **ins, long numins, t_sample **outs, long numouts, long n) {
	State* self = (State *)cself;
	return self->perform(ins, outs, n);
}

/// Reset all parameters and stateful operators of a State object

void reset(CommonState *cself) {
	State* self = (State *)cself;
	self->reset(cself->sr, cself->vs);
}

/// Set a parameter of a State object

void setparameter(CommonState *cself, long index, t_param value, void *ref) {
	State *self = (State *)cself;
	switch (index) {
		case 0: self->set_stereo(ref); break;
		
		default: break;
	}
}

/// Get the value of a parameter of a State object

void getparameter(CommonState *cself, long index, t_param *value) {
	State *self = (State *)cself;
	switch (index) {
		
		
		default: break;
	}
}

/// Get the name of a parameter of a State object

const char *getparametername(CommonState *cself, long index) {
	if (index >= 0 && index < cself->numparams) {
		return cself->params[index].name;
	}
	return 0;
}

/// Get the minimum value of a parameter of a State object

t_param getparametermin(CommonState *cself, long index) {
	if (index >= 0 && index < cself->numparams) {
		return cself->params[index].outputmin;
	}
	return 0;
}

/// Get the maximum value of a parameter of a State object

t_param getparametermax(CommonState *cself, long index) {
	if (index >= 0 && index < cself->numparams) {
		return cself->params[index].outputmax;
	}
	return 0;
}

/// Get parameter of a State object has a minimum and maximum value

char getparameterhasminmax(CommonState *cself, long index) {
	if (index >= 0 && index < cself->numparams) {
		return cself->params[index].hasminmax;
	}
	return 0;
}

/// Get the units of a parameter of a State object

const char *getparameterunits(CommonState *cself, long index) {
	if (index >= 0 && index < cself->numparams) {
		return cself->params[index].units;
	}
	return 0;
}

/// Get the size of the state of all parameters of a State object

size_t getstatesize(CommonState *cself) {
	return genlib_getstatesize(cself, &getparameter);
}

/// Get the state of all parameters of a State object

short getstate(CommonState *cself, char *state) {
	return genlib_getstate(cself, state, &getparameter);
}

/// set the state of all parameters of a State object

short setstate(CommonState *cself, const char *state) {
	return genlib_setstate(cself, state, &setparameter);
}

/// Allocate and configure a new State object and it's internal CommonState:

void *create(t_param sr, long vs) {
	State *self = new State;
	self->reset(sr, vs);
	ParamInfo *pi;
	self->__commonstate.inputnames = gen_kernel_innames;
	self->__commonstate.outputnames = gen_kernel_outnames;
	self->__commonstate.numins = gen_kernel_numins;
	self->__commonstate.numouts = gen_kernel_numouts;
	self->__commonstate.sr = sr;
	self->__commonstate.vs = vs;
	self->__commonstate.params = (ParamInfo *)genlib_sysmem_newptr(1 * sizeof(ParamInfo));
	self->__commonstate.numparams = 1;
	// initialize parameter 0 ("m_stereo_1")
	pi = self->__commonstate.params + 0;
	pi->name = "stereo";
	pi->paramtype = GENLIB_PARAMTYPE_SYM;
	pi->defaultvalue = 0.;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = false;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	
	return self;
}

/// Release all resources and memory used by a State object:

void destroy(CommonState *cself) {
	State *self = (State *)cself;
	genlib_sysmem_freeptr(cself->params);
		
	delete self;
}


} // module_max::
