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

/*
ohmtech-rdi: Silent warnings begin
*/

#if defined (__clang__)
   #pragma clang diagnostic push
   #pragma clang diagnostic ignored "-Wold-style-cast"
   #pragma clang diagnostic ignored "-Wreserved-id-macro"
   #pragma clang diagnostic ignored "-Wsign-conversion"
   #pragma clang diagnostic ignored "-Wcast-qual"
   #pragma clang diagnostic ignored "-Wunused-parameter"
   #pragma clang diagnostic ignored "-Wdeprecated-dynamic-exception-spec"
   #pragma clang diagnostic ignored "-Wzero-as-null-pointer-constant"
   #pragma clang diagnostic ignored "-Wcast-align"
   #pragma clang diagnostic ignored "-Wshorten-64-to-32"
   #pragma clang diagnostic ignored "-Wunreachable-code-return"

#elif defined (__GNUC__)
   #pragma GCC diagnostic push
   #pragma GCC diagnostic ignored "-Wpedantic"
   #pragma GCC diagnostic ignored "-Wunused-parameter"
   #pragma GCC diagnostic ignored "-Wsized-deallocation"

#endif

/*
ohmtech-rdi: Silent warnings end
*/



#include "genlib.h"
#include "genlib_exportfunctions.h"
#include <stdlib.h> // not cstdlib (causes problems with ARM embedded compiler)
#include <cstdio>
#include <cstring>

#ifndef MSP_ON_CLANG
#	include <cmath>
#endif

#ifdef __APPLE__
#	include <malloc/malloc.h>
#elif !defined(GEN_WINDOWS) // WIN32?
#	include <malloc.h>
#	define malloc_size malloc_usable_size
#endif

#ifndef GENLIB_NO_JSON
#ifdef MSP_ON_CLANG
#	include "json.c"
#	include "json_builder.c"
#endif
#include "json.h"
#include "json_builder.h"
#endif

// DATA_MAXIMUM_ELEMENTS * 8 bytes = 256 mb limit
#define DATA_MAXIMUM_ELEMENTS	(33554432)

#include "erb/detail/fnc.h"

//////////// export_genlib.cpp ////////////
// export version

void my_memset(void *p, int c, long size);
void my_memcpy(void *dst, const void *src, long size);

/*
ohmtech-rdi: Our allocation system is done in erb
*/

t_ptr sysmem_newptr(t_ptr_size size)
{
	//return (t_ptr)malloc(size);
	return (t_ptr)erb::allocate_bytes_auto(size);
}

t_ptr sysmem_newptrclear(t_ptr_size size)
{
	//t_ptr p = (t_ptr)malloc(size);
	t_ptr p = (t_ptr)erb::allocate_bytes_auto(size);

	if (p)
		my_memset(p, 0, size);

	return p;
}

/*
ohmtech-rdi: Not supported (but doesn't seem to be used)
*/

t_ptr sysmem_resizeptr(void *ptr, t_ptr_size newsize)
{
	//return (t_ptr)realloc(ptr, newsize);

#if defined (erb_TARGET_DAISY)
	asm ("bkpt 255");
#elif (erb_RAM_MEM_POOL_SIZE_SIMULATOR_CHECK)
	throw std::bad_alloc ();
#endif
	return nullptr;
}

/*
ohmtech-rdi: Not supported (but doesn't seem to be used)
*/

t_ptr sysmem_resizeptrclear(void *ptr, t_ptr_size newsize)
{
	/*size_t oldsize = malloc_size(ptr);
	t_ptr p = (t_ptr)realloc(ptr, newsize);

	if (p) {
		if (newsize > oldsize)
			my_memset((char *)p + oldsize, 0, newsize - oldsize);
	}
	return p;*/


#if defined (erb_TARGET_DAISY)
	asm ("bkpt 255");
#elif (erb_RAM_MEM_POOL_SIZE_SIMULATOR_CHECK)
	throw std::bad_alloc ();
#endif
	return nullptr;
}

/*
ohmtech-rdi: Not supported (but doesn't seem to be used)
*/

t_ptr_size sysmem_ptrsize(void *ptr)
{
	//return malloc_size(ptr);

#if defined (erb_TARGET_DAISY)
	asm ("bkpt 255");
#elif (erb_RAM_MEM_POOL_SIZE_SIMULATOR_CHECK)
	throw std::bad_alloc ();
#endif
	return 0;
}

/*
ohmtech-rdi: Our allocation system is done in erb. Just "leak" memory, that
   will be reclaim differently for the simulator.
*/

void sysmem_freeptr(void *ptr)
{
	//free(ptr); <-- ohmtech-rdi
}

void sysmem_copyptr(const void *src, void *dst, t_ptr_size bytes)
{
	my_memcpy(dst, src, bytes);
}

void my_memset(void *p, int c, long size)
{
	char *p2 = (char *)p;
	int i;

	for (i = 0; i < size; i++, p2++)
		*p2 = char(c);
}

void my_memcpy(void *dst, const void *src, long size)
{
	char *s2 = (char *)src;
	char *d2 = (char *)dst;
	int i;

	for (i = 0; i < size; i++, s2++, d2++)
		*d2 = *s2;
}

void set_zero64(t_sample *memory, long size)
{
	long i;

	for (i = 0; i < size; i++, memory++) {
		*memory = 0.;
	}
}


/*
ohmtech-rdi:
*/

unsigned long genlib_ticks() {
	return 0; /* as in oopsy */
}

void genlib_report_error(const char *s)
{
#ifndef GEN_NO_STDLIB
	fprintf(stderr, "%s\n", s);
#endif
}

void genlib_report_message(const char *s)
{
#ifndef GEN_NO_STDLIB
	fprintf(stdout, "%s\n", s);
#endif
}

unsigned long systime_ticks(void)
{
	return 0;	// Gen code can deal with this
}

// NEED THIS FOR WINDOWS:

/*
ohmtech-rdi: We are using operator new in Sram
*/

/*void *operator new(size_t size) { return sysmem_newptr(size); }
void *operator new[](size_t size) { return sysmem_newptr(size); }
void operator delete(void *p) throw() { sysmem_freeptr(p); }
void operator delete[](void *p) throw() { sysmem_freeptr(p); }*/

void *genlib_obtain_reference_from_string(const char *name)
{
	return 0; // to be implemented
}

// the rest is stuff to isolate gensym, attrs, atoms, buffers etc.
t_genlib_buffer *genlib_obtain_buffer_from_reference(void *ref)
{
	return 0; // to be implemented
}

t_genlib_err genlib_buffer_edit_begin(t_genlib_buffer *b)
{
	return 0; // to be implemented
}

t_genlib_err genlib_buffer_edit_end(t_genlib_buffer *b, long valid)
{
	return 0; // to be implemented
}

t_genlib_err genlib_buffer_getinfo(t_genlib_buffer *b, t_genlib_buffer_info *info)
{
	return 0; // to be implemented
}

char *genlib_reference_getname(void *ref)
{
	return 0; // to be implemented
}

void genlib_buffer_dirty(t_genlib_buffer *b)
{
	 // to be implemented
}

t_genlib_err genlib_buffer_perform_begin(t_genlib_buffer *b)
{
	return 0; // to be implemented
}
void genlib_buffer_perform_end(t_genlib_buffer *b)
{
	// to be implemented
}

t_sample gen_msp_pow(t_sample value, t_sample power)
{
	return pow(value, power);
}

typedef struct {
	t_genlib_data_info	info;
	t_sample			cursor;	// used by Delay
	//t_symbol *		name;
} t_dsp_gen_data;

typedef struct {
   size_t frames;
   size_t channels;
   const void * data; // interleaved 32-bit floats
} t_erb_sample_data;

void genlib_data_setbuffer(t_genlib_data *b, void *ref)
{
	t_erb_sample_data *data = (t_erb_sample_data *)ref;
	genlib_data_resize(b, data->frames, data->channels);
	t_dsp_gen_data *self = (t_dsp_gen_data *)b;
	memcpy(self->info.data, data->data, sizeof(t_sample) * data->frames * data->channels);
}

/*
ohmtech-rdi: Using erb malloc
*/

t_genlib_data *genlib_obtain_data_from_reference(void *ref)
{
	//t_dsp_gen_data *self = (t_dsp_gen_data *)malloc(sizeof(t_dsp_gen_data));
	t_dsp_gen_data *self = (t_dsp_gen_data *)erb::allocate_bytes_auto(sizeof(t_dsp_gen_data));
	self->info.dim = 0;
	self->info.channels = 0;
	self->info.data = 0;
	self->cursor = 0;
	return (t_genlib_data *)self;
}

t_genlib_err genlib_data_getinfo(t_genlib_data *b, t_genlib_data_info *info)
{
	t_dsp_gen_data *self = (t_dsp_gen_data *)b;
	info->dim = self->info.dim;
	info->channels = self->info.channels;
	info->data = self->info.data;
	return GENLIB_ERR_NONE;
}

void genlib_data_release(t_genlib_data *b)
{
	t_dsp_gen_data *self = (t_dsp_gen_data *)b;

	if (self->info.data) {
		genlib_sysmem_freeptr(self->info.data);
		self->info.data = 0;
	}
}

long genlib_data_getcursor(t_genlib_data *b)
{
	t_dsp_gen_data *self = (t_dsp_gen_data *)b;
	return long(self->cursor);
}

void genlib_data_setcursor(t_genlib_data *b, long cursor)
{
	t_dsp_gen_data *self = (t_dsp_gen_data *)b;
	self->cursor = t_sample(cursor);
}

void genlib_data_resize(t_genlib_data *b, long s, long c)
{
	t_dsp_gen_data *self = (t_dsp_gen_data *)b;

	size_t sz, oldsz, copysz;
	t_sample *old = 0;
	t_sample *replaced = 0;
	int i, j, copydim, copychannels, olddim, oldchannels;

	//printf("data resize %d %d\n", s, c);

	// cache old for copying:
	old = self->info.data;
	olddim = self->info.dim;
	oldchannels = self->info.channels;

	// limit [data] size:
	if (s * c > DATA_MAXIMUM_ELEMENTS) {
		s = DATA_MAXIMUM_ELEMENTS/c;
		genlib_report_message("warning: constraining [data] to < 256MB");
	}
	// bytes required:
	sz = sizeof(t_sample) * s * c;
	oldsz = sizeof(t_sample) * olddim * oldchannels;

	if (old && sz == oldsz) {
		// no need to re-allocate, just resize
		// careful, audio thread may still be using it:
		if (s > olddim) {
			self->info.channels = c;
			self->info.dim = s;
		} else {
			self->info.dim = s;
			self->info.channels = c;
		}

		set_zero64(self->info.data, s * c);
		return;

	} else {

		// allocate new:
		replaced = (t_sample *)sysmem_newptr(sz);

		// check allocation:
		if (replaced == 0) {
			genlib_report_error("allocating [data]: out of memory");
			// try to reallocate with a default/minimal size instead:
			if (s > 512 || c > 1) {
				genlib_data_resize((t_genlib_data *)self, 512, 1);
			} else {
				// if this fails, then Max is kaput anyway...
				genlib_data_resize((t_genlib_data *)self, 4, 1);
			}
			return;
		}

		// fill with zeroes:
		set_zero64(replaced, s * c);

		// copy in old data:
		if (old) {
			// frames to copy:
			// clamped:
			copydim = olddim > s ? s : olddim;
			// use memcpy if channels haven't changed:
			if (c == oldchannels) {
				copysz = sizeof(t_sample) * copydim * c;
				//post("reset resize (same channels) %p %p, %d", self->info.data, old, copysz);
				memcpy(replaced, old, copysz);
			} else {
				// memcpy won't work if channels have changed,
				// because data is interleaved.
				// clamp channels copied:
				copychannels = oldchannels > c ? c : oldchannels;
				//post("reset resize (different channels) %p %p, %d %d", self->info.data, old, copydim, copychannels);
				for (i = 0; i < copydim; i++) {
					for (j = 0; j < copychannels; j++) {
						replaced[j + i * c] = old[j + i * oldchannels];
					}
				}
			}
		}

		// now update info:
		if (old == 0) {
			self->info.data = replaced;
			self->info.dim = s;
			self->info.channels = c;
		} else {
			// need to be careful; the audio thread may still be using it
			// since dsp_gen_data is preserved through edits
			// the order of resizing has to be carefully done
			// to prevent indexing out of bounds
			// (or maybe I'm being too paranoid here...)
			if (oldsz > sz) {
				// shrink size first
				if (s > olddim) {
					self->info.channels = c;
					self->info.dim = s;
				} else {
					self->info.dim = s;
					self->info.channels = c;
				}
				self->info.data = replaced;
			} else {
				// shrink size after
				self->info.data = replaced;
				if (s > olddim) {
					self->info.channels = c;
					self->info.dim = s;
				} else {
					self->info.dim = s;
					self->info.channels = c;
				}
			}

			// done with old:
			sysmem_freeptr(old);

		}

	}
}

void genlib_reset_complete(void *data)
{
}

#ifndef GENLIB_NO_JSON
void genlib_build_json(CommonState *cself, json_value **jsonvalue, getparameter_method getmethod)
{
	int i;

	*jsonvalue = json_object_new(0);

	for (i = 0; i < cself->numparams; i++) {
		t_param val;

		(getmethod)(cself, i, &val);
		json_object_push(*jsonvalue, cself->params[i].name, json_double_new(val));
	}
}

size_t genlib_getstatesize(CommonState *cself, getparameter_method getmethod)
{
	size_t size;
	json_value *jsonvalue;

	genlib_build_json(cself, &jsonvalue, getmethod);
	size = json_measure(jsonvalue);
	json_builder_free(jsonvalue);

	return size;
}

short genlib_getstate(CommonState *cself, char *state, getparameter_method getmethod)
{
	json_value *jsonvalue;

	genlib_build_json(cself, &jsonvalue, getmethod);
	json_serialize(state, jsonvalue);
	json_builder_free(jsonvalue);

	return 0;
}

static void *json_custom_alloc(size_t size, int zero, void *user_data)
{
	return zero ? genlib_sysmem_newptrclear(size) : genlib_sysmem_newptr(size);
}

static void json_custom_free(void *ptr, void *user_data)
{
	genlib_sysmem_freeptr(ptr);
}

short genlib_setstate(CommonState *cself, const char *state, setparameter_method setmethod)
{
	json_settings settings;
	char error[256];

	memset(&settings, 0, sizeof(json_settings));
	settings.mem_alloc = &json_custom_alloc;
	settings.mem_free = &json_custom_free;

	json_value *value = json_parse_ex(&settings, state, strlen(state), error);
	if (value == NULL)
		return 1;

	if (value->type == json_object) {
		unsigned int i;
		for (i = 0; i < value->u.object.length; i++) {
			char *name = NULL;
			t_param val = 0;
			int j;

			if (value->u.object.values[i].value->type == json_double) {
				name = value->u.object.values[i].name;
				val = t_param(value->u.object.values[i].value->u.dbl);
			} else if (value->u.object.values[i].value->type == json_integer) {
				name = value->u.object.values[i].name;
				val = t_param(value->u.object.values[i].value->u.integer);
			}

			if (name) {
				for (j = 0; j < cself->numparams; j++) {
					if (!strcmp(cself->params[j].name, name)) {
						(setmethod)(cself, j, val, NULL);
					}
				}
			}
		}
	}

	json_value_free_ex(&settings, value);

	return 0;
}
#else
size_t genlib_getstatesize(CommonState *cself, getparameter_method getmethod)
{
	return 0;
}

short genlib_getstate(CommonState *cself, char *state, getparameter_method getmethod)
{
	return 0;
}

short genlib_setstate(CommonState *cself, const char *state, setparameter_method setmethod)
{
	return 0;
}
#endif



/*
ohmtech-rdi: Silent warnings begin
*/

#if defined (__clang__)
   #pragma clang diagnostic pop
#elif defined (__GNUC__)
   #pragma GCC diagnostic pop
#endif

/*
ohmtech-rdi: Silent warnings end
*/
