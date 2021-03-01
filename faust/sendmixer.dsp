declare name "SendMixer";
declare description "A stereo channel strip with one master gain and two pre/post-fader sends";
declare version "0.1.0";
declare author "Christopher Arndt";
declare license "MIT license";

import("stdfaust.lib");

// Controls
send_a_lvl = vslider("[1]Send A[style:knob][unit:dB][symbol: send_a_lvl][abbrev: send_a_lvl]", -60.0, -60.0, 0.0, 0.01) : si.smoo;
send_a_pos = checkbox("[2]Send A Post[symbol: send_a_post][abbrev: send_a_post]");
send_b_lvl = vslider("[3]Send B[style:knob][unit:dB][symbol: send_b_lvl][abbrev: send_b_lvl]", -60.0, -60.0, 0.0, 0.01) : si.smoo;
send_b_pos = checkbox("[4]Send B Post[symbol: send_b_post][abbrev: send_b_post]");
main_lvl = vslider("[5]Main Level[unit:dB][symbol: main_lvl][abbrev: main_lvl]", 0.0, -90.0, 20.0, 0.01) : si.smoo;

// A single mixer strip
channel = _ * ba.db2linear(main_lvl);
strip = _ <: channel, _, channel : _, send;
send = _,_ <: select2(send_a_pos) * ba.db2linear(send_a_lvl), select2(send_b_pos) * ba.db2linear(send_b_lvl);

// Combin two strips into a stero strip
stereostrip = strip, strip;

// And route the channels to be ordered in stereo pairs
router(a1, b1, c1, a2, b2, c2) = a1, a2, b1, b2, c1, c2;

// Process
process = stereostrip : router;
