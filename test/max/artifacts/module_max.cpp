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
	Delay m_delay_9;
	Delay m_delay_10;
	int __exception;
	int vectorsize;
	t_sample m_led1_gate_8;
	t_sample m_led3_gate_11;
	t_sample m_led3_r_13;
	t_sample m_led3_g_12;
	t_sample m_led3_color_7;
	t_sample m_led1_intensity_trim_6;
	t_sample m_led1_intensity_cv_5;
	t_sample m_led1_intensity_pot_1;
	t_sample samplerate;
	t_sample m_led2_led_14;
	t_sample m_led2_gate_2;
	t_sample m_led1_button_4;
	t_sample m_led2_button_3;
	t_sample m_led1_led_15;
	// re-initialize all member variables;
	inline void reset(t_param __sr, int __vs) {
		__exception = 0;
		vectorsize = __vs;
		samplerate = __sr;
		m_led1_intensity_pot_1 = ((int)0);
		m_led2_gate_2 = ((int)0);
		m_led2_button_3 = ((int)0);
		m_led1_button_4 = ((int)0);
		m_led1_intensity_cv_5 = ((int)0);
		m_led1_intensity_trim_6 = ((int)0);
		m_led3_color_7 = ((int)0);
		m_led1_gate_8 = ((int)0);
		m_delay_9.reset("m_delay_9", ((int)48000));
		m_delay_10.reset("m_delay_10", ((int)48000));
		m_led3_gate_11 = ((int)0);
		m_led3_g_12 = ((int)0);
		m_led3_r_13 = ((int)0);
		m_led2_led_14 = ((int)0);
		m_led1_led_15 = ((int)0);
		genlib_reset_complete(this);
		
	};
	// the signal processing routine;
	inline int perform(t_sample ** __ins, t_sample ** __outs, int __n) {
		vectorsize = __n;
		const t_sample * __in1 = __ins[0];
		const t_sample * __in2 = __ins[1];
		t_sample * __out1 = __outs[0];
		t_sample * __out2 = __outs[1];
		if (__exception) {
			return __exception;
			
		} else if (( (__in1 == 0) || (__in2 == 0) || (__out1 == 0) || (__out2 == 0) )) {
			__exception = GENLIB_ERR_NULL_BUFFER;
			return __exception;
			
		};
		t_sample expr_21 = (((int)1) - m_led3_color_7);
		t_sample sin_1 = sin(m_led3_color_7);
		t_sample add_14 = (m_led2_button_3 + m_led2_gate_2);
		t_sample clamp_13 = ((add_14 <= ((int)0)) ? ((int)0) : ((add_14 >= ((int)1)) ? ((int)1) : add_14));
		t_sample add_9 = (m_led1_button_4 + m_led1_gate_8);
		t_sample clamp_8 = ((add_9 <= ((int)0)) ? ((int)0) : ((add_9 >= ((int)1)) ? ((int)1) : add_9));
		t_sample mul_12 = (m_led1_intensity_trim_6 * m_led1_intensity_cv_5);
		t_sample add_11 = (m_led1_intensity_pot_1 + mul_12);
		t_sample clamp_10 = ((add_11 <= ((int)0)) ? ((int)0) : ((add_11 >= ((int)1)) ? ((int)1) : add_11));
		t_sample mul_7 = (clamp_8 * clamp_10);
		t_sample led3_gate_next_24 = fixdenorm(m_led3_color_7);
		t_sample led3_g_next_25 = fixdenorm(expr_21);
		t_sample led3_r_next_26 = fixdenorm(sin_1);
		t_sample led2_led_next_27 = fixdenorm(clamp_13);
		t_sample led1_led_next_28 = fixdenorm(mul_7);
		// the main sample loop;
		while ((__n--)) {
			const t_sample in1 = (*(__in1++));
			const t_sample in2 = (*(__in2++));
			t_sample tap_5 = m_delay_9.read_step(((int)48000));
			t_sample out1 = tap_5;
			t_sample tap_3 = m_delay_10.read_step(((int)48000));
			t_sample out2 = tap_3;
			m_delay_9.write(in1);
			m_led1_led_15 = led1_led_next_28;
			m_led2_led_14 = led2_led_next_27;
			m_led3_r_13 = led3_r_next_26;
			m_led3_g_12 = led3_g_next_25;
			m_led3_gate_11 = led3_gate_next_24;
			m_delay_10.write(in2);
			m_delay_9.step();
			m_delay_10.step();
			// assign results to output buffer;
			(*(__out1++)) = out1;
			(*(__out2++)) = out2;
			
		};
		return __exception;
		
	};
	inline void set_led1_intensity_pot(t_param _value) {
		m_led1_intensity_pot_1 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_led2_gate(t_param _value) {
		m_led2_gate_2 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_led2_button(t_param _value) {
		m_led2_button_3 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_led1_button(t_param _value) {
		m_led1_button_4 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_led1_intensity_cv(t_param _value) {
		m_led1_intensity_cv_5 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_led1_intensity_trim(t_param _value) {
		m_led1_intensity_trim_6 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_led3_color(t_param _value) {
		m_led3_color_7 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_led1_gate(t_param _value) {
		m_led1_gate_8 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	
} State;


///
///	Configuration for the genlib API
///

/// Number of signal inputs and outputs

int gen_kernel_numins = 2;
int gen_kernel_numouts = 2;

int num_inputs() { return gen_kernel_numins; }
int num_outputs() { return gen_kernel_numouts; }
int num_params() { return 8; }

/// Assistive lables for the signal inputs and outputs

const char *gen_kernel_innames[] = { "in1", "in2" };
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
		case 0: self->set_led1_button(value); break;
		case 1: self->set_led1_gate(value); break;
		case 2: self->set_led1_intensity_cv(value); break;
		case 3: self->set_led1_intensity_pot(value); break;
		case 4: self->set_led1_intensity_trim(value); break;
		case 5: self->set_led2_button(value); break;
		case 6: self->set_led2_gate(value); break;
		case 7: self->set_led3_color(value); break;
		
		default: break;
	}
}

/// Get the value of a parameter of a State object

void getparameter(CommonState *cself, long index, t_param *value) {
	State *self = (State *)cself;
	switch (index) {
		case 0: *value = self->m_led1_button_4; break;
		case 1: *value = self->m_led1_gate_8; break;
		case 2: *value = self->m_led1_intensity_cv_5; break;
		case 3: *value = self->m_led1_intensity_pot_1; break;
		case 4: *value = self->m_led1_intensity_trim_6; break;
		case 5: *value = self->m_led2_button_3; break;
		case 6: *value = self->m_led2_gate_2; break;
		case 7: *value = self->m_led3_color_7; break;
		
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
	self->__commonstate.params = (ParamInfo *)genlib_sysmem_newptr(8 * sizeof(ParamInfo));
	self->__commonstate.numparams = 8;
	// initialize parameter 0 ("m_led1_button_4")
	pi = self->__commonstate.params + 0;
	pi->name = "led1_button";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_led1_button_4;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 1 ("m_led1_gate_8")
	pi = self->__commonstate.params + 1;
	pi->name = "led1_gate";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_led1_gate_8;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 2 ("m_led1_intensity_cv_5")
	pi = self->__commonstate.params + 2;
	pi->name = "led1_intensity_cv";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_led1_intensity_cv_5;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 3 ("m_led1_intensity_pot_1")
	pi = self->__commonstate.params + 3;
	pi->name = "led1_intensity_pot";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_led1_intensity_pot_1;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 4 ("m_led1_intensity_trim_6")
	pi = self->__commonstate.params + 4;
	pi->name = "led1_intensity_trim";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_led1_intensity_trim_6;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 5 ("m_led2_button_3")
	pi = self->__commonstate.params + 5;
	pi->name = "led2_button";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_led2_button_3;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 6 ("m_led2_gate_2")
	pi = self->__commonstate.params + 6;
	pi->name = "led2_gate";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_led2_gate_2;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 7 ("m_led3_color_7")
	pi = self->__commonstate.params + 7;
	pi->name = "led3_color";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_led3_color_7;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
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
