import("stdfaust.lib");
/*process =
    dm.phaser2_demo; // stereo phaser*/

//process = 0,_~+(1):soundfile("sound[url:{'tango.wav'}]",2):!,!,_,_;
//process = 0,_~+(1):soundfile("sound[url:{ 'foo.wav' ;   'bara.wav'}]",2):!,!,_,_;
//process = 0,_~+(1):soundfile("foo[url:{'foo.wav'}]",2):!,!,_,_;


s = soundfile("foo[url:{'foo.wav'}]",2);

//speed = hslider("speed",1,-100,100,0.01);
speed = 1;
wrap(l,x) = select2((x>=0),l-abs(x),x);
loop(s, idx) = (idx, reader(s)) : outs(s)
with {
length(s) = idx,0 : s : _,si.block(outputs(s)-1);
srate(s)  = idx,0 : s : !,_,si.block(outputs(s)-2);
reader(s) = (speed * float(srate(s)))/ma.SR : (+,length(s):fmod)~  _ : wrap(length(s)) : int;
outs(s)   = s : si.block(2), si.bus(outputs(s)-2);
};

process = loop(s,0) <: _,_ ;

/*process = (waveform {10,20,30,40,50,60,70}, %(7)~+(3) : rdtable),
          (waveform {1.1,2.2,3.3,4.4,5.5,6.6,7.7}, %(7)~+(3) : rdtable);*/
