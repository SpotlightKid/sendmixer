
//------------------------------------------------------------------------------
// This file was generated using the Faust compiler (https://faust.grame.fr),
// and the Faust post-processor (https://github.com/jpcima/faustpp).
//
// Source: sendmixer.dsp
// Name: SendMixer
// Author: Christopher Arndt
// Copyright: 
// License: MIT license
// Version: 0.1.0
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

#define FAUSTPP_VIRTUAL // do not declare any methods virtual
#define FAUSTPP_PRIVATE public // do not hide any members
#define FAUSTPP_PROTECTED public // do not hide any members

// define the DSP in the anonymous namespace
#define FAUSTPP_BEGIN_NAMESPACE namespace {
#define FAUSTPP_END_NAMESPACE }


#if defined(__GNUC__)
#   pragma GCC diagnostic push
#   pragma GCC diagnostic ignored "-Wunused-parameter"
#endif

#ifndef FAUSTPP_PRIVATE
#   define FAUSTPP_PRIVATE private
#endif
#ifndef FAUSTPP_PROTECTED
#   define FAUSTPP_PROTECTED protected
#endif
#ifndef FAUSTPP_VIRTUAL
#   define FAUSTPP_VIRTUAL virtual
#endif

#ifndef FAUSTPP_BEGIN_NAMESPACE
#   define FAUSTPP_BEGIN_NAMESPACE
#endif
#ifndef FAUSTPP_END_NAMESPACE
#   define FAUSTPP_END_NAMESPACE
#endif

FAUSTPP_BEGIN_NAMESPACE

#ifndef FAUSTFLOAT
#define FAUSTFLOAT float
#endif 

FAUSTPP_END_NAMESPACE
#include <algorithm>
#include <cmath>
FAUSTPP_BEGIN_NAMESPACE


#ifndef FAUSTCLASS 
#define FAUSTCLASS mydsp
#endif

#ifdef __APPLE__ 
#define exp10f __exp10f
#define exp10 __exp10
#endif

class mydsp : public dsp {
	
 FAUSTPP_PRIVATE:
	
	FAUSTFLOAT fVslider0;
	float fRec0[2];
	FAUSTFLOAT fCheckbox0;
	FAUSTFLOAT fVslider1;
	float fRec1[2];
	FAUSTFLOAT fCheckbox1;
	FAUSTFLOAT fVslider2;
	float fRec2[2];
	int fSampleRate;
	
 public:
	
	void metadata(Meta* m) { 
		m->declare("author", "Christopher Arndt");
		m->declare("basics.lib/name", "Faust Basic Element Library");
		m->declare("basics.lib/version", "0.1");
		m->declare("compile_options", "-lang cpp -es 1 -scal -ftz 0");
		m->declare("description", "A stereo channel strip with one master gain and two pre/post-fader sends");
		m->declare("filename", "sendmixer.dsp");
		m->declare("license", "MIT license");
		m->declare("name", "SendMixer");
		m->declare("signals.lib/name", "Faust Signal Routing Library");
		m->declare("signals.lib/version", "0.0");
		m->declare("version", "0.1.0");
	}

	FAUSTPP_VIRTUAL int getNumInputs() {
		return 2;
	}
	FAUSTPP_VIRTUAL int getNumOutputs() {
		return 6;
	}
	FAUSTPP_VIRTUAL int getInputRate(int channel) {
		int rate;
		switch ((channel)) {
			case 0: {
				rate = 1;
				break;
			}
			case 1: {
				rate = 1;
				break;
			}
			default: {
				rate = -1;
				break;
			}
		}
		return rate;
	}
	FAUSTPP_VIRTUAL int getOutputRate(int channel) {
		int rate;
		switch ((channel)) {
			case 0: {
				rate = 1;
				break;
			}
			case 1: {
				rate = 1;
				break;
			}
			case 2: {
				rate = 1;
				break;
			}
			case 3: {
				rate = 1;
				break;
			}
			case 4: {
				rate = 1;
				break;
			}
			case 5: {
				rate = 1;
				break;
			}
			default: {
				rate = -1;
				break;
			}
		}
		return rate;
	}
	
	static void classInit(int sample_rate) {
	}
	
	FAUSTPP_VIRTUAL void instanceConstants(int sample_rate) {
		fSampleRate = sample_rate;
	}
	
	FAUSTPP_VIRTUAL void instanceResetUserInterface() {
		fVslider0 = FAUSTFLOAT(0.0f);
		fCheckbox0 = FAUSTFLOAT(0.0f);
		fVslider1 = FAUSTFLOAT(-60.0f);
		fCheckbox1 = FAUSTFLOAT(0.0f);
		fVslider2 = FAUSTFLOAT(-60.0f);
	}
	
	FAUSTPP_VIRTUAL void instanceClear() {
		for (int l0 = 0; (l0 < 2); l0 = (l0 + 1)) {
			fRec0[l0] = 0.0f;
		}
		for (int l1 = 0; (l1 < 2); l1 = (l1 + 1)) {
			fRec1[l1] = 0.0f;
		}
		for (int l2 = 0; (l2 < 2); l2 = (l2 + 1)) {
			fRec2[l2] = 0.0f;
		}
	}
	
	FAUSTPP_VIRTUAL void init(int sample_rate) {
		classInit(sample_rate);
		instanceInit(sample_rate);
	}
	FAUSTPP_VIRTUAL void instanceInit(int sample_rate) {
		instanceConstants(sample_rate);
		instanceResetUserInterface();
		instanceClear();
	}
	
	FAUSTPP_VIRTUAL mydsp* clone() {
		return new mydsp();
	}
	
	FAUSTPP_VIRTUAL int getSampleRate() {
		return fSampleRate;
	}
	
	FAUSTPP_VIRTUAL void buildUserInterface(UI* ui_interface) {
		ui_interface->openVerticalBox("SendMixer");
		ui_interface->declare(&fVslider1, "1", "");
		ui_interface->declare(&fVslider1, "abbrev", "send_a_lvl");
		ui_interface->declare(&fVslider1, "style", "knob");
		ui_interface->declare(&fVslider1, "symbol", "send_a_lvl");
		ui_interface->declare(&fVslider1, "unit", "dB");
		ui_interface->addVerticalSlider("Send A", &fVslider1, -60.0f, -60.0f, 0.0f, 0.00999999978f);
		ui_interface->declare(&fCheckbox0, "2", "");
		ui_interface->declare(&fCheckbox0, "abbrev", "send_a_post");
		ui_interface->declare(&fCheckbox0, "symbol", "send_a_post");
		ui_interface->addCheckButton("Send A Post", &fCheckbox0);
		ui_interface->declare(&fVslider2, "3", "");
		ui_interface->declare(&fVslider2, "abbrev", "send_b_lvl");
		ui_interface->declare(&fVslider2, "style", "knob");
		ui_interface->declare(&fVslider2, "symbol", "send_b_lvl");
		ui_interface->declare(&fVslider2, "unit", "dB");
		ui_interface->addVerticalSlider("Send B", &fVslider2, -60.0f, -60.0f, 0.0f, 0.00999999978f);
		ui_interface->declare(&fCheckbox1, "4", "");
		ui_interface->declare(&fCheckbox1, "abbrev", "send_b_post");
		ui_interface->declare(&fCheckbox1, "symbol", "send_b_post");
		ui_interface->addCheckButton("Send B Post", &fCheckbox1);
		ui_interface->declare(&fVslider0, "5", "");
		ui_interface->declare(&fVslider0, "abbrev", "main_lvl");
		ui_interface->declare(&fVslider0, "symbol", "main_lvl");
		ui_interface->declare(&fVslider0, "unit", "dB");
		ui_interface->addVerticalSlider("Volume", &fVslider0, 0.0f, -90.0f, 20.0f, 0.00999999978f);
		ui_interface->closeBox();
	}
	
	FAUSTPP_VIRTUAL void compute(int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) {
		FAUSTFLOAT* input0 = inputs[0];
		FAUSTFLOAT* input1 = inputs[1];
		FAUSTFLOAT* output0 = outputs[0];
		FAUSTFLOAT* output1 = outputs[1];
		FAUSTFLOAT* output2 = outputs[2];
		FAUSTFLOAT* output3 = outputs[3];
		FAUSTFLOAT* output4 = outputs[4];
		FAUSTFLOAT* output5 = outputs[5];
		float fSlow0 = (0.00100000005f * float(fVslider0));
		int iSlow1 = int(float(fCheckbox0));
		float fSlow2 = (0.00100000005f * float(fVslider1));
		int iSlow3 = int(float(fCheckbox1));
		float fSlow4 = (0.00100000005f * float(fVslider2));
		for (int i = 0; (i < count); i = (i + 1)) {
			float fTemp0 = float(input0[i]);
			fRec0[0] = (fSlow0 + (0.999000013f * fRec0[1]));
			float fTemp1 = std::pow(10.0f, (0.0500000007f * fRec0[0]));
			float fTemp2 = (fTemp0 * fTemp1);
			output0[i] = FAUSTFLOAT(fTemp2);
			float fTemp3 = float(input1[i]);
			float fTemp4 = (fTemp3 * fTemp1);
			output1[i] = FAUSTFLOAT(fTemp4);
			fRec1[0] = (fSlow2 + (0.999000013f * fRec1[1]));
			float fTemp5 = std::pow(10.0f, (0.0500000007f * fRec1[0]));
			output2[i] = FAUSTFLOAT(((iSlow1 ? fTemp2 : fTemp0) * fTemp5));
			output3[i] = FAUSTFLOAT((fTemp5 * (iSlow1 ? fTemp4 : fTemp3)));
			fRec2[0] = (fSlow4 + (0.999000013f * fRec2[1]));
			float fTemp6 = std::pow(10.0f, (0.0500000007f * fRec2[0]));
			output4[i] = FAUSTFLOAT(((iSlow3 ? fTemp2 : fTemp0) * fTemp6));
			output5[i] = FAUSTFLOAT((fTemp6 * (iSlow3 ? fTemp4 : fTemp3)));
			fRec0[1] = fRec0[0];
			fRec1[1] = fRec1[0];
			fRec2[1] = fRec2[0];
		}
	}

};
FAUSTPP_END_NAMESPACE


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
    const float *in0,const float *in1,
    float *out0,float *out1,float *out2,float *out3,float *out4,float *out5,
    unsigned count) noexcept
{

    mydsp &dsp = static_cast<mydsp &>(*fDsp);
    float *inputs[] = {
        const_cast<float *>(in0),const_cast<float *>(in1),
    };
    float *outputs[] = {
        out0,out1,out2,out3,out4,out5,
    };
    dsp.compute(count, inputs, outputs);

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
        return "Volume";
    
    default:
        return 0;
    }
}

const char *SendMixer::parameter_short_label(unsigned index) noexcept
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
        static const ParameterRange range = { -60, -60, 0 };
        return &range;
    }
    
    case 1: {
        static const ParameterRange range = { 0, 0, 1 };
        return &range;
    }
    
    case 2: {
        static const ParameterRange range = { -60, -60, 0 };
        return &range;
    }
    
    case 3: {
        static const ParameterRange range = { 0, 0, 1 };
        return &range;
    }
    
    case 4: {
        static const ParameterRange range = { 0, -90, 20 };
        return &range;
    }
    
    default:
        return 0;
    }
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




