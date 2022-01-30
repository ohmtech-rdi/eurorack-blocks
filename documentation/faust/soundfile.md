# Soundfile Mapping

In the previous chapter, we've seen how to map `erbui` controls to FAUST UI primitives.
We need know to talk about the  `soundfile` primitive,
which allows you to use audio samples in FAUST.


## Audio sample resources

To add audio sample to your project, you need to add a resource to it.
A resource is just like a source file, except it tends to be binary data.
In Eurorack-blocks, we have resources and types, which allows to state that
a particular file is an audio sample, and should be used as such by the program.

Resources are added in your `erbb` file, and we can add a kick sample, provided
we have a `kick.wav` at the root of our project:

```{code-block} erbb
---
lineno-start: 1
emphasize-lines: 9-11
---
module Kick {
   section qspi

   sources {
      file "Kick.dsp"
      file "Kick.erbui"
   }

   resources {
      data kick AudioSample { file "kick.wav" }
   }
}
```

If you don't want to put your audio samples in the root of your project, you can also
create, let's say, a `media` folder and put the audio file in it. In this case we would
have wrote `file "media/kick.wav"` above.

The line `section qspi` is a whole topic in itself.
You can read more about it in the {doc}`../guides/kick` chapter of this manual.
In a nutshell, if you have very small samples around a few Kilobytes, you won't need this line.
But if you are using bigger samples, you will need it, knowing that the sum of all
samples should be a bit below 8MB at most.

So now let's consider the following program, which plays our sample in a loop.

```{code-block} faust
---
lineno-start: 1
emphasize-lines: 3-5
---
// Kick.dsp

import("stdfaust.lib");
s = soundfile("kick",2);
process = so.loop() <: _,_ ;
```

Same as for UI controls, the binding will be automatic, because we can synthetise it.
If now we want to bind an audio sample to a FAUST `soundfile` from somewhere in
an imported module, we can use bindings for that, like we did for `erbui`:

```{code-block} erbb
---
lineno-start: 9
emphasize-lines: 4
---
   resources {
      data kick AudioSample {
         file "kick.wav"
         faust { bind { address "/DRUM/0x00/Kick Sample" }}
      }
   }
```

And that's it! Eurorack-blocks will take care of all the rest for you.


## Soundfile parts support (coming soon)

FAUST has a convenience system which allows to assemble multiple audio files, and
consolidate them like if it was a single file, each original audio files being as many
"parts" of the consolidated file:

```{code-block} faust
process = 0,_~+(1):soundfile("sound[url:{'foo.wav';'bar.wav'}]",2):!,!,_,_;
```

In this example, `foo.wav` and `bar.wav` are virtually consolidated to a single audio file
with 2 parts.
Though, you might have seen that we never specified the `url` attributes in the section above.
That's because we ignore it 😬

Rather, the support of parts is done using `wav` with what is known as "Cue" or "Splice"
markers, which are supported by every common sample editors,
and even some DAWs have native support for it.

This also allows you to be able to load directly all samples to this format that is used
also in the Eurorack industry,
and in particular in the excellent [Morphagene module](https://www.makenoisemusic.com/modules/morphagene) from Make Noise.
A lot of samples already in that format can be found for example on [Freesound](https://freesound.org/people/makenoisemusic/).
