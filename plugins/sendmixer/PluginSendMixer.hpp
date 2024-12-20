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

#ifndef PLUGIN_SENDMIXER_H
#define PLUGIN_SENDMIXER_H

#include "DistrhoPlugin.hpp"
#include "SendMixer.hpp"

START_NAMESPACE_DISTRHO

#ifndef MIN
#define MIN(a,b) ( (a) < (b) ? (a) : (b) )
#endif

#ifndef MAX
#define MAX(a,b) ( (a) > (b) ? (a) : (b) )
#endif

#ifndef CLAMP
#define CLAMP(v, min, max) (MIN((max), MAX((min), (v))))
#endif

// -----------------------------------------------------------------------

class PluginSendMixer : public Plugin {
public:
    PluginSendMixer();

    ~PluginSendMixer();

protected:
    // -------------------------------------------------------------------
    // Information

    const char* getLabel() const noexcept override {
        return "SendMixer";
    }

    const char* getDescription() const override {
        return "A stereo channel strip with one master gain and two pre/post-fader sends";
    }

    const char* getMaker() const noexcept override {
        return "chrisarndt.de";
    }

    const char* getHomePage() const override {
        return DISTRHO_PLUGIN_URI;
    }

    const char* getLicense() const noexcept override {
        return "https://spdx.org/licenses/MIT";
    }

    uint32_t getVersion() const noexcept override {
        return d_version(0, 2, 0);
    }

    // Go to:
    //
    // http://service.steinberg.de/databases/plugin.nsf/plugIn
    //
    // Get a proper plugin UID and fill it in here!
    int64_t getUniqueId() const noexcept override {
        return d_cconst('a', 'b', 'c', 'd');
    }

    // -------------------------------------------------------------------
    // Init

    void initAudioPort(bool input, uint32_t index, AudioPort& port) override;
    void initParameter(uint32_t index, Parameter& parameter) override;
    void initProgramName(uint32_t index, String& programName) override;
    void initPortGroup(uint32_t groupId, PortGroup& portGroup) override;

    // -------------------------------------------------------------------
    // Internal data

    float getParameterValue(uint32_t index) const override;
    void setParameterValue(uint32_t index, float value) override;
    void loadProgram(uint32_t index) override;

    // -------------------------------------------------------------------
    // Optional

    // Optional callback to inform the plugin about a sample rate change.
    void sampleRateChanged(double newSampleRate) override;

    // -------------------------------------------------------------------
    // Process

    void activate() override;
    void run(const float**, float** outputs, uint32_t frames) override;

    // -------------------------------------------------------------------

private:
    double          fSampleRate;
    SendMixer*     dsp;

    DISTRHO_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PluginSendMixer)
};

struct Preset {
    const char* name;
    float params[SendMixer::NumParameters];
};

const Preset factoryPresets[] = {
    {
        "Default",
        {
            -60.0f,  // Send A Level
            1.0f,  // Send A Post
            -60.0f,  // Send A Level
            1.0f,  // Send B Post
            0.0f   // Main Level
        }
    },
    {
        "Muted",
        {
            -60.0f,  // Send A Level
            1.0f,  // Send A Post
            -60.0f,  // Send A Level
            1.0f,  // Send B Post
            -90.0f   // Main Level
        }
    },
    {
        "Send A -15dB",
        {
            -15.0f,  // Send A Level
            1.0f,  // Send A Post
            -60.0f,  // Send A Level
            1.0f,  // Send B Post
            0.0f   // Main Level
        }
    },
    {
        "Send A -15dB (Pre)",
        {
            -15.0f,  // Send A Level
            0.0f,  // Send A Post
            -60.0f,  // Send A Level
            1.0f,  // Send B Post
            0.0f   // Main Level
        }
    },
    {
        "Send A+B -15dB",
        {
            -15.0f,  // Send A Level
            1.0f,  // Send A Post
            -15.0f,  // Send A Level
            1.0f,  // Send B Post
            0.0f   // Main Level
        }
    },
    {
        "Send A+B -15dB (Pre)",
        {
            -15.0f,  // Send A Level
            0.0f,  // Send A Post
            -15.0f,  // Send A Level
            0.0f,  // Send B Post
            0.0f   // Main Level
        }
    }
    //,{
    //    "Another preset",  // preset name
    //    {-14.0f, ...}      // array of SendMixer::NumParameters float param values
    //}
};

const uint presetCount = sizeof(factoryPresets) / sizeof(Preset);

// -----------------------------------------------------------------------

END_NAMESPACE_DISTRHO

#endif  // #ifndef PLUGIN_SENDMIXER_H
