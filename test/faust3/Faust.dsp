// Faust.dsp

import("stdfaust.lib");

s = soundfile("foo",2);
process = so.loop(s,0) <: _,_ ;
