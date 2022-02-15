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


#include "genlib.h"
#include "genlib_exportfunctions.h"
#include "genlib_ops.h"

namespace module_max {

int num_inputs();
int num_outputs();
int num_params();
int perform(CommonState *cself, t_sample **ins, long numins, t_sample **outs, long numouts, long n);
void reset(CommonState *cself);
void setparameter(CommonState *cself, long index, t_param value, void *ref);
void getparameter(CommonState *cself, long index, t_param *value);
const char *getparametername(CommonState *cself, long index);
t_param getparametermin(CommonState *cself, long index);
t_param getparametermax(CommonState *cself, long index);
char getparameterhasminmax(CommonState *cself, long index);
const char *getparameterunits(CommonState *cself, long index);
size_t getstatesize(CommonState *cself);
short getstate(CommonState *cself, char *state);
short setstate(CommonState *cself, const char *state);
void *create(t_param sr, long vs);
void destroy(CommonState *cself);

} // module_max::
