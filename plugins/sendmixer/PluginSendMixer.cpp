/*
 * SendMixer audio effect based on DISTRHO Plugin Framework (DPF)
 *
 * SPDX-License-Identifier: MIT
 *
 * Copyright (C) 2021 Christopher Arndt <chris@chrisarndt.de>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to
 * deal in the Software without restriction, including without limitation the
 * rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 */

#include "PluginSendMixer.hpp"

START_NAMESPACE_DISTRHO

// -----------------------------------------------------------------------

PluginSendMixer::PluginSendMixer()
    : Plugin(SendMixer::NumParameters, presetCount, 0)  // # of params, # of programs, 0 states
{
    dsp = new SendMixer;
    fSampleRate = getSampleRate();

    for (unsigned p = 0; p < SendMixer::NumParameters; ++p) {
        Parameter param;
        initParameter(p, param);
        setParameterValue(p, param.ranges.def);
    }
}

PluginSendMixer::~PluginSendMixer() {
    delete dsp;
}

// -----------------------------------------------------------------------
// Init

void PluginSendMixer::initAudioPort(bool input, uint32_t index, AudioPort& port) {
    if (input) {
        switch (index) {
            case 0:
                port.name = "Input L";
                port.symbol = "input_l";
                break;
            case 1:
                port.name = "Input R";
                port.symbol = "input_r";
                break;
            default:
                port.name = "Input";
                port.symbol = "input";
        }
    }
    else {
        switch (index) {
            case 0:
                port.name = "Main L";
                port.symbol = "main_l";
                break;
            case 1:
                port.name = "Main R";
                port.symbol = "main_r";
                break;
            case 2:
                port.name = "Send A L";
                port.symbol = "send_a_l";
                break;
            case 3:
                port.name = "Send A R";
                port.symbol = "send_a_r";
                break;
            case 4:
                port.name = "Send B L";
                port.symbol = "send_b_l";
                break;
            case 5:
                port.name = "Send B R";
                port.symbol = "send_b_r";
                break;
            default:
                port.name = "Output";
                port.symbol = "output";
        }
    }
}

void PluginSendMixer::initParameter(uint32_t index, Parameter& parameter) {
    if (index >= SendMixer::NumParameters)
        return;

    const SendMixer::ParameterRange* range = dsp->parameter_range(index);
    parameter.name = dsp->parameter_label(index);
    parameter.shortName = dsp->parameter_short_label(index);
    parameter.symbol = dsp->parameter_symbol(index);
    parameter.unit = dsp->parameter_unit(index);
    parameter.ranges.min = range->min;
    parameter.ranges.max = range->max;
    parameter.ranges.def = range->init;
    parameter.hints = kParameterIsAutomatable;

    if (dsp->parameter_is_boolean(index))
        parameter.hints |= kParameterIsBoolean;
    if (dsp->parameter_is_integer(index))
        parameter.hints |= kParameterIsInteger;
    if (dsp->parameter_is_logarithmic(index))
        parameter.hints |= kParameterIsLogarithmic;
    if (dsp->parameter_is_trigger(index))
        parameter.hints |= kParameterIsTrigger;

    int group_id = dsp->parameter_group(index);
    if (group_id != -1) {
        parameter.groupId = group_id;
    }

    unsigned sp_count = dsp->parameter_scale_point_count(index);

    if (sp_count > 0) {
        parameter.enumValues.count = sp_count;

        const char *style = dsp->parameter_style(index);
        if (strcmp(style, "menu") || strcmp(style, "radio")) {
            parameter.enumValues.restrictedMode = true;
        }

        {
            ParameterEnumerationValue* const values = new ParameterEnumerationValue[sp_count];
            parameter.enumValues.values = values;
            for (unsigned point=0; point<sp_count; point++) {
                const SendMixer::ParameterScalePoint* sp = dsp->parameter_scale_point(index, point);
                values[point].label = sp->label.c_str();
                values[point].value = sp->value;
            }
        }
    }
}

/**
   Initialize the port group @a groupId.@n
   This function will be called once,
   shortly after the plugin is created and all audio ports and parameters have been enumerated.
 */
void PluginSendMixer::initPortGroup(uint32_t groupId, PortGroup& portGroup) {
    portGroup.name = dsp->parameter_group_label(groupId);
    portGroup.symbol = dsp->parameter_group_symbol(groupId);
}

/**
  Set the name of the program @a index.
  This function will be called once, shortly after the plugin is created.
*/
void PluginSendMixer::initProgramName(uint32_t index, String& programName) {
    if (index < presetCount) {
        programName = factoryPresets[index].name;
    }
}

// -----------------------------------------------------------------------
// Internal data

/**
  Optional callback to inform the plugin about a sample rate change.
*/
void PluginSendMixer::sampleRateChanged(double newSampleRate) {
    fSampleRate = newSampleRate;
    dsp->init(newSampleRate);
}

/**
  Get the current value of a parameter.
*/
float PluginSendMixer::getParameterValue(uint32_t index) const {
    return dsp->get_parameter(index);
}

/**
  Change a parameter value.
*/
void PluginSendMixer::setParameterValue(uint32_t index, float value) {
    if (index >= SendMixer::NumParameters)
        return;

    const SendMixer::ParameterRange* range = dsp->parameter_range(index);
    dsp->set_parameter(index, CLAMP(value, range->min, range->max));
}

/**
  Load a program.
  The host may call this function from any context,
  including realtime processing.
*/
void PluginSendMixer::loadProgram(uint32_t index) {
    if (index < presetCount) {
        for (int i=0; i < SendMixer::NumParameters; i++) {
            setParameterValue(i, factoryPresets[index].params[i]);
        }
    }
}

// -----------------------------------------------------------------------
// Process

/**
  Plugin is activated.
*/
void PluginSendMixer::activate() {
    fSampleRate = getSampleRate();
    dsp->init(fSampleRate);
}


void PluginSendMixer::run(const float** inputs, float** outputs,
                          uint32_t frames) {
    dsp->process(inputs[0], inputs[1], outputs[0], outputs[1], outputs[2], outputs[3], outputs[4], outputs[5], (unsigned)frames);
}

// -----------------------------------------------------------------------

Plugin* createPlugin() {
    return new PluginSendMixer();
}

// -----------------------------------------------------------------------

END_NAMESPACE_DISTRHO
