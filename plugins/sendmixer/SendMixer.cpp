//------------------------------------------------------------------------------
// This file was generated using the Faust compiler (https://faust.grame.fr),
// and the Faust post-processor (https://github.com/SpotlightKid/faustdoctor).
//
// Source: sendmixer.dsp
// Name: SendMixer
// Author: Christopher Arndt
// Copyright: 
// License: MIT
// Version: 0.1.0
// FAUST version: 2.76.0
// FAUST compilation options: -a /home/chris/tmp/tmpgdoulxdf.cpp -lang cpp -ct 1 -es 1 -mcd 16 -mdd 1024 -mdy 33 -single -ftz 0
//------------------------------------------------------------------------------




#include "SendMixer.hpp"

#include <utility>
#include <cmath>

class SendMixer::BasicDsp {
public:
    virtual ~BasicDsp() {}
};

//------------------------------------------------------------------------------
// Begin the Faust code section

namespace {

template <class T> inline T min(T a, T b) { return (a < b) ? a : b; }
template <class T> inline T max(T a, T b) { return (a > b) ? a : b; }

class Meta {
public:
    // dummy
    void declare(...) {}
};

class UI {
public:
    // dummy
    void openHorizontalBox(...) {}
    void openVerticalBox(...) {}
    void closeBox(...) {}
    void declare(...) {}
    void addButton(...) {}
    void addCheckButton(...) {}
    void addVerticalSlider(...) {}
    void addHorizontalSlider(...) {}
    void addVerticalBargraph(...) {}
    void addHorizontalBargraph(...) {}
};

typedef SendMixer::BasicDsp dsp;

} // namespace

#define FAUSTDR_VIRTUAL // do not declare any methods virtual
#define FAUSTDR_PRIVATE public // do not hide any members
#define FAUSTDR_PROTECTED public // do not hide any members

// define the DSP in the anonymous namespace
#define FAUSTDR_BEGIN_NAMESPACE namespace {
#define FAUSTDR_END_NAMESPACE }


#if defined(__GNUC__)
#   pragma GCC diagnostic push
#   pragma GCC diagnostic ignored "-Wunused-parameter"
#endif

#ifndef FAUSTDR_PRIVATE
#   define FAUSTDR_PRIVATE private
#endif
#ifndef FAUSTDR_PROTECTED
#   define FAUSTDR_PROTECTED protected
#endif
#ifndef FAUSTDR_VIRTUAL
#   define FAUSTDR_VIRTUAL virtual
#endif

#ifndef FAUSTDR_BEGIN_NAMESPACE
#   define FAUSTDR_BEGIN_NAMESPACE
#endif
#ifndef FAUSTDR_END_NAMESPACE
#   define FAUSTDR_END_NAMESPACE
#endif

FAUSTDR_BEGIN_NAMESPACE

// END PREAMBLE
// START INTRINSICS
// END INTRINSICS
// START CLASS CODE
#ifndef FAUSTFLOAT
#define FAUSTFLOAT float
#endif 

FAUSTDR_END_NAMESPACE
#include <algorithm>
#include <cmath>
#include <cstdint>
#include <math.h>
FAUSTDR_BEGIN_NAMESPACE

#ifndef FAUSTCLASS 
#define FAUSTCLASS mydsp
#endif

#ifdef __APPLE__ 
#define exp10f __exp10f
#define exp10 __exp10
#endif

#if defined(_WIN32)
#define RESTRICT __restrict
#else
#define RESTRICT __restrict__
#endif


class mydsp : public dsp {
	
 FAUSTDR_PRIVATE:
	
	int fSampleRate;
	float fConst0;
	float fConst1;
	FAUSTFLOAT fVslider0;
	float fRec0[2];
	FAUSTFLOAT fVslider1;
	float fRec1[2];
	FAUSTFLOAT fCheckbox0;
	FAUSTFLOAT fVslider2;
	float fRec2[2];
	FAUSTFLOAT fCheckbox1;
	
 public:
	mydsp() {
	}
	
	void metadata(Meta* m) { 
		m->declare("author", "Christopher Arndt");
		m->declare("basics.lib/name", "Faust Basic Element Library");
		m->declare("basics.lib/tabulateNd", "Copyright (C) 2023 Bart Brouns <bart@magnetophon.nl>");
		m->declare("basics.lib/version", "1.19.1");
		m->declare("compile_options", "-a /home/chris/tmp/tmpgdoulxdf.cpp -lang cpp -ct 1 -es 1 -mcd 16 -mdd 1024 -mdy 33 -single -ftz 0");
		m->declare("description", "A stereo channel strip with one master gain and two pre/post-fader sends");
		m->declare("filename", "sendmixer.dsp");
		m->declare("license", "MIT");
		m->declare("maths.lib/author", "GRAME");
		m->declare("maths.lib/copyright", "GRAME");
		m->declare("maths.lib/license", "LGPL with exception");
		m->declare("maths.lib/name", "Faust Math Library");
		m->declare("maths.lib/version", "2.8.0");
		m->declare("name", "SendMixer");
		m->declare("platform.lib/name", "Generic Platform Library");
		m->declare("platform.lib/version", "1.3.0");
		m->declare("signals.lib/name", "Faust Signal Routing Library");
		m->declare("signals.lib/version", "1.6.0");
		m->declare("version", "0.1.0");
	}

	FAUSTDR_VIRTUAL int getNumInputs() {
		return 2;
	}
	FAUSTDR_VIRTUAL int getNumOutputs() {
		return 6;
	}
	
	static void classInit(int sample_rate) {
	}
	
	FAUSTDR_VIRTUAL void instanceConstants(int sample_rate) {
		fSampleRate = sample_rate;
		fConst0 = 44.1f / std::min<float>(1.92e+05f, std::max<float>(1.0f, float(fSampleRate)));
		fConst1 = 1.0f - fConst0;
	}
	
	FAUSTDR_VIRTUAL void instanceResetUserInterface() {
		fVslider0 = FAUSTFLOAT(0.0f);
		fVslider1 = FAUSTFLOAT(-6e+01f);
		fCheckbox0 = FAUSTFLOAT(0.0f);
		fVslider2 = FAUSTFLOAT(-6e+01f);
		fCheckbox1 = FAUSTFLOAT(0.0f);
	}
	
	FAUSTDR_VIRTUAL void instanceClear() {
		for (int l0 = 0; l0 < 2; l0 = l0 + 1) {
			fRec0[l0] = 0.0f;
		}
		for (int l1 = 0; l1 < 2; l1 = l1 + 1) {
			fRec1[l1] = 0.0f;
		}
		for (int l2 = 0; l2 < 2; l2 = l2 + 1) {
			fRec2[l2] = 0.0f;
		}
	}
	
	FAUSTDR_VIRTUAL void init(int sample_rate) {
		classInit(sample_rate);
		instanceInit(sample_rate);
	}
	
	FAUSTDR_VIRTUAL void instanceInit(int sample_rate) {
		instanceConstants(sample_rate);
		instanceResetUserInterface();
		instanceClear();
	}
	
	FAUSTDR_VIRTUAL mydsp* clone() {
		return new mydsp();
	}
	
	FAUSTDR_VIRTUAL int getSampleRate() {
		return fSampleRate;
	}
	
	FAUSTDR_VIRTUAL void buildUserInterface(UI* ui_interface) {
		ui_interface->openVerticalBox("SendMixer");
		ui_interface->declare(&fVslider1, "1", "");
		ui_interface->declare(&fVslider1, "style", "knob");
		ui_interface->declare(&fVslider1, "symbol", "send_a_lvl");
		ui_interface->declare(&fVslider1, "unit", "dB");
		ui_interface->addVerticalSlider("Send A", &fVslider1, FAUSTFLOAT(-6e+01f), FAUSTFLOAT(-6e+01f), FAUSTFLOAT(0.0f), FAUSTFLOAT(0.01f));
		ui_interface->declare(&fCheckbox0, "2", "");
		ui_interface->declare(&fCheckbox0, "symbol", "send_a_post");
		ui_interface->addCheckButton("Send A Post", &fCheckbox0);
		ui_interface->declare(&fVslider2, "3", "");
		ui_interface->declare(&fVslider2, "style", "knob");
		ui_interface->declare(&fVslider2, "symbol", "send_b_lvl");
		ui_interface->declare(&fVslider2, "unit", "dB");
		ui_interface->addVerticalSlider("Send B", &fVslider2, FAUSTFLOAT(-6e+01f), FAUSTFLOAT(-6e+01f), FAUSTFLOAT(0.0f), FAUSTFLOAT(0.01f));
		ui_interface->declare(&fCheckbox1, "4", "");
		ui_interface->declare(&fCheckbox1, "symbol", "send_b_post");
		ui_interface->addCheckButton("Send B Post", &fCheckbox1);
		ui_interface->declare(&fVslider0, "5", "");
		ui_interface->declare(&fVslider0, "style", "slider");
		ui_interface->declare(&fVslider0, "symbol", "main_lvl");
		ui_interface->declare(&fVslider0, "unit", "dB");
		ui_interface->addVerticalSlider("Main Level", &fVslider0, FAUSTFLOAT(0.0f), FAUSTFLOAT(-9e+01f), FAUSTFLOAT(2e+01f), FAUSTFLOAT(0.01f));
		ui_interface->closeBox();
	}
	
	FAUSTDR_VIRTUAL void compute(int count, FAUSTFLOAT** RESTRICT inputs, FAUSTFLOAT** RESTRICT outputs) {
		FAUSTFLOAT* input0 = inputs[0];
		FAUSTFLOAT* input1 = inputs[1];
		FAUSTFLOAT* output0 = outputs[0];
		FAUSTFLOAT* output1 = outputs[1];
		FAUSTFLOAT* output2 = outputs[2];
		FAUSTFLOAT* output3 = outputs[3];
		FAUSTFLOAT* output4 = outputs[4];
		FAUSTFLOAT* output5 = outputs[5];
		float fSlow0 = fConst0 * float(fVslider0);
		float fSlow1 = fConst0 * float(fVslider1);
		int iSlow2 = int(float(fCheckbox0));
		float fSlow3 = fConst0 * float(fVslider2);
		int iSlow4 = int(float(fCheckbox1));
		for (int i0 = 0; i0 < count; i0 = i0 + 1) {
			fRec0[0] = fSlow0 + fConst1 * fRec0[1];
			float fTemp0 = std::pow(1e+01f, 0.05f * fRec0[0]);
			float fTemp1 = float(input0[i0]);
			float fTemp2 = fTemp1 * fTemp0;
			output0[i0] = FAUSTFLOAT(fTemp2);
			float fTemp3 = float(input1[i0]);
			float fTemp4 = fTemp3 * fTemp0;
			output1[i0] = FAUSTFLOAT(fTemp4);
			fRec1[0] = fSlow1 + fConst1 * fRec1[1];
			float fTemp5 = std::pow(1e+01f, 0.05f * fRec1[0]);
			output2[i0] = FAUSTFLOAT(((iSlow2) ? fTemp2 : fTemp1) * fTemp5);
			output3[i0] = FAUSTFLOAT(fTemp5 * ((iSlow2) ? fTemp4 : fTemp3));
			fRec2[0] = fSlow3 + fConst1 * fRec2[1];
			float fTemp6 = std::pow(1e+01f, 0.05f * fRec2[0]);
			output4[i0] = FAUSTFLOAT(((iSlow4) ? fTemp2 : fTemp1) * fTemp6);
			output5[i0] = FAUSTFLOAT(fTemp6 * ((iSlow4) ? fTemp4 : fTemp3));
			fRec0[1] = fRec0[0];
			fRec1[1] = fRec1[0];
			fRec2[1] = fRec2[0];
		}
	}

};
// END CLASS CODE
// START EPILOG
FAUSTDR_END_NAMESPACE



#if defined(__GNUC__)
#   pragma GCC diagnostic pop
#endif


//------------------------------------------------------------------------------
// End the Faust code section




SendMixer::SendMixer()
{
mydsp *dsp = new mydsp;
    fDsp.reset(dsp);
    dsp->instanceResetUserInterface();
}

SendMixer::~SendMixer()
{
}

void SendMixer::init(float sample_rate)
{
mydsp &dsp = static_cast<mydsp &>(*fDsp);
    dsp.classInit(sample_rate);
    dsp.instanceConstants(sample_rate);
    clear();
}

void SendMixer::clear() noexcept
{
mydsp &dsp = static_cast<mydsp &>(*fDsp);
    dsp.instanceClear();
}

void SendMixer::process(
    const float *in0, const float *in1, 
    float *out0, float *out1, float *out2, float *out3, float *out4, float *out5, 
    unsigned count) noexcept
{
mydsp &dsp = static_cast<mydsp &>(*fDsp);
    float *inputs[] = {
        const_cast<float *>(in0), const_cast<float *>(in1), 
    };
    float *outputs[] = {
        out0, out1, out2, out3, out4, out5, 
    };
    dsp.compute(count, inputs, outputs);
}

int SendMixer::parameter_group(unsigned index) noexcept
{
    switch (index) {
    
    default:
        return -1;
    }
}

const char *SendMixer::parameter_group_label(unsigned group_id) noexcept
{
    switch (group_id) {
    
    default:
        return 0;
    }
}

const char *SendMixer::parameter_group_symbol(unsigned group_id) noexcept
{
    switch (group_id) {
    
    default:
        return 0;
    }
}


int SendMixer::parameter_order(unsigned index) noexcept
{
    switch (index) {
    
    case 0:
        return 1;
    case 1:
        return 2;
    case 2:
        return 3;
    case 3:
        return 4;
    case 4:
        return 5;
    default:
        return -1;
    }
}

const char *SendMixer::parameter_label(unsigned index) noexcept
{
    switch (index) {
    
    case 0:
        return "Send A";
    case 1:
        return "Send A Post";
    case 2:
        return "Send B";
    case 3:
        return "Send B Post";
    case 4:
        return "Main Level";
    default:
        return 0;
    }
}

const char *SendMixer::parameter_short_label(unsigned index) noexcept
{
    switch (index) {
    
    case 0:
        return "Send A";
    case 1:
        return "Send A Post";
    case 2:
        return "Send B";
    case 3:
        return "Send B Post";
    case 4:
        return "Main Level";
    default:
        return 0;
    }
}

const char *SendMixer::parameter_style(unsigned index) noexcept
{
    switch (index) {
    
    case 4: {
        return "slider";
    }
    default:
        return "knob";
    }
}

const char *SendMixer::parameter_symbol(unsigned index) noexcept
{
    switch (index) {
    
    case 0:
        return "send_a_lvl";
    case 1:
        return "send_a_post";
    case 2:
        return "send_b_lvl";
    case 3:
        return "send_b_post";
    case 4:
        return "main_lvl";
    default:
        return 0;
    }
}

const char *SendMixer::parameter_unit(unsigned index) noexcept
{
    switch (index) {
    
    case 0:
        return "dB";
    case 1:
        return "";
    case 2:
        return "dB";
    case 3:
        return "";
    case 4:
        return "dB";
    default:
        return 0;
    }
}

const SendMixer::ParameterRange *SendMixer::parameter_range(unsigned index) noexcept
{
    switch (index) {
    
    case 0: {
        static const ParameterRange range = { -60.0, -60.0, 0.0 };
        return &range;
    }
    case 1: {
        static const ParameterRange range = { 0, 0, 1 };
        return &range;
    }
    case 2: {
        static const ParameterRange range = { -60.0, -60.0, 0.0 };
        return &range;
    }
    case 3: {
        static const ParameterRange range = { 0, 0, 1 };
        return &range;
    }
    case 4: {
        static const ParameterRange range = { 0.0, -90.0, 20.0 };
        return &range;
    }
    default:
        return 0;
    }
}

unsigned SendMixer::parameter_scale_point_count(unsigned index) noexcept
{
    switch (index) {
    
    default:
        return 0;
    }
}

const SendMixer::ParameterScalePoint *SendMixer::parameter_scale_point(unsigned index, unsigned point) noexcept
{
    switch (index) {
    
    default:
        return 0;
    }
    (void) point;
}

bool SendMixer::parameter_is_trigger(unsigned index) noexcept
{
    switch (index) {
    
    default:
        return false;
    }
}

bool SendMixer::parameter_is_boolean(unsigned index) noexcept
{
    switch (index) {
    
    case 1:
        return true;
    case 3:
        return true;
    default:
        return false;
    }
}

bool SendMixer::parameter_is_enum(unsigned index) noexcept
{
    switch (index) {
    
    default:
        return false;
    }
}

bool SendMixer::parameter_is_integer(unsigned index) noexcept
{
    switch (index) {
    
    case 1:
        return true;
    case 3:
        return true;
    default:
        return false;
    }
}

bool SendMixer::parameter_is_logarithmic(unsigned index) noexcept
{
    switch (index) {
    
    default:
        return false;
    }
}

float SendMixer::get_parameter(unsigned index) const noexcept
{
    mydsp &dsp = static_cast<mydsp &>(*fDsp);
    switch (index) {
    
    case 0:
        return dsp.fVslider1;
    case 1:
        return dsp.fCheckbox0;
    case 2:
        return dsp.fVslider2;
    case 3:
        return dsp.fCheckbox1;
    case 4:
        return dsp.fVslider0;
    default:
        (void)dsp;
        return 0;
    }
}

void SendMixer::set_parameter(unsigned index, float value) noexcept
{
    mydsp &dsp = static_cast<mydsp &>(*fDsp);
    switch (index) {
    
    case 0:
        dsp.fVslider1 = value;
        break;
    case 1:
        dsp.fCheckbox0 = value;
        break;
    case 2:
        dsp.fVslider2 = value;
        break;
    case 3:
        dsp.fCheckbox1 = value;
        break;
    case 4:
        dsp.fVslider0 = value;
        break;
    default:
        (void)dsp;
        (void)value;
        break;
    }
}


float SendMixer::get_send_a_lvl() const noexcept
{
    mydsp &dsp = static_cast<mydsp &>(*fDsp);
    return dsp.fVslider1;
}

float SendMixer::get_send_a_post() const noexcept
{
    mydsp &dsp = static_cast<mydsp &>(*fDsp);
    return dsp.fCheckbox0;
}

float SendMixer::get_send_b_lvl() const noexcept
{
    mydsp &dsp = static_cast<mydsp &>(*fDsp);
    return dsp.fVslider2;
}

float SendMixer::get_send_b_post() const noexcept
{
    mydsp &dsp = static_cast<mydsp &>(*fDsp);
    return dsp.fCheckbox1;
}

float SendMixer::get_main_lvl() const noexcept
{
    mydsp &dsp = static_cast<mydsp &>(*fDsp);
    return dsp.fVslider0;
}


void SendMixer::set_send_a_lvl(float value) noexcept
{
    mydsp &dsp = static_cast<mydsp &>(*fDsp);
    dsp.fVslider1 = value;
}

void SendMixer::set_send_a_post(float value) noexcept
{
    mydsp &dsp = static_cast<mydsp &>(*fDsp);
    dsp.fCheckbox0 = value;
}

void SendMixer::set_send_b_lvl(float value) noexcept
{
    mydsp &dsp = static_cast<mydsp &>(*fDsp);
    dsp.fVslider2 = value;
}

void SendMixer::set_send_b_post(float value) noexcept
{
    mydsp &dsp = static_cast<mydsp &>(*fDsp);
    dsp.fCheckbox1 = value;
}

void SendMixer::set_main_lvl(float value) noexcept
{
    mydsp &dsp = static_cast<mydsp &>(*fDsp);
    dsp.fVslider0 = value;
}


