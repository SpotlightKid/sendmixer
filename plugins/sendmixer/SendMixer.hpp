
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






#pragma once
#ifndef SendMixer_Faust_pp_Gen_HPP_
#define SendMixer_Faust_pp_Gen_HPP_

#include <memory>

class SendMixer {
public:
    SendMixer();
    ~SendMixer();

    void init(float sample_rate);
    void clear() noexcept;

    void process(
        const float *in0,const float *in1,
        float *out0,float *out1,float *out2,float *out3,float *out4,float *out5,
        unsigned count) noexcept;

    enum { NumInputs = 2 };
    enum { NumOutputs = 6 };
    enum { NumActives = 5 };
    enum { NumPassives = 0 };
    enum { NumParameters = 5 };

    enum Parameter {
        p_send_a_lvl,
        p_send_a_post,
        p_send_b_lvl,
        p_send_b_post,
        p_main_lvl,
        
    };

    struct ParameterRange {
        float init;
        float min;
        float max;
    };

    static const char *parameter_label(unsigned index) noexcept;
    static const char *parameter_short_label(unsigned index) noexcept;
    static const char *parameter_symbol(unsigned index) noexcept;
    static const char *parameter_unit(unsigned index) noexcept;
    static const ParameterRange *parameter_range(unsigned index) noexcept;
    static bool parameter_is_trigger(unsigned index) noexcept;
    static bool parameter_is_boolean(unsigned index) noexcept;
    static bool parameter_is_integer(unsigned index) noexcept;
    static bool parameter_is_logarithmic(unsigned index) noexcept;

    float get_parameter(unsigned index) const noexcept;
    void set_parameter(unsigned index, float value) noexcept;

    
    float get_send_a_lvl() const noexcept;
    
    float get_send_a_post() const noexcept;
    
    float get_send_b_lvl() const noexcept;
    
    float get_send_b_post() const noexcept;
    
    float get_main_lvl() const noexcept;
    
    
    void set_send_a_lvl(float value) noexcept;
    
    void set_send_a_post(float value) noexcept;
    
    void set_send_b_lvl(float value) noexcept;
    
    void set_send_b_post(float value) noexcept;
    
    void set_main_lvl(float value) noexcept;
    

public:
    class BasicDsp;

private:
    std::unique_ptr<BasicDsp> fDsp;



};




#endif // SendMixer_Faust_pp_Gen_HPP_
