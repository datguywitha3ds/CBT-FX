# CBT-FX: It just works
This is my attempt at writing a sound effect driver that's natively compatible with [GBDK-2020](https://github.com/gbdk-2020/gbdk-2020/) (Instead of having to use register values or converting other assembly drivers to GBDK-2020), made to be used with the [FX Hammer editor](https://www.pouet.net/prod.php?which=17337). It's aimed at people who want good sounding sound effects but don't wanna have to do custom solutions, feel free to use the translated example SFX's too (see [here](https://github.com/datguywitha3ds/CBT-FX/blob/main/include/sfx)).

  * [Usage](#usage)
  * [For music driver users](#for-music-driver-users)
  * [Pros of this driver](#pros-of-this-driver)
  * [Cons](#cons)
  * [C array format](#c-array-format)
  * [Many many a thank](#many-many-a-thank)

## Usage
 1. Copy `cbtfx.h`, `cbtfx.c` from the `include` folder and `hammer2cbt.py` to your source.
 2. Create your sound effects first in the before mentioned [FX Hammer editor](https://www.pouet.net/prod.php?which=17337).
 3. Copy your .sav file generated by the editor (normally called `hammered.sav`) to your source directory
 4. Use the `hammer2cbt.py` script to convert your desired effects, it takes a few necessary arguments:
 ```
usage: hammer2cbt.py [-h] [--fxammo FXAMMO] [--fxinv] fxsav fxnum out

positional arguments:
  fxsav            FX Hammer .sav file (Normally called 'hammered.sav').
  fxnum            Index of the desired SFX to export.
  out              Folder where .c and .h files will be saved.

optional arguments:
  -h, --help       show this help message and exit
  --fxammo FXAMMO  Number of SFX to export (starts at fxnum, ends at fxnum +
                   fxammo)
  --fxinv          invert pan values for SFX (FX Hammer has them inverted by
                   default, without this flag, the panning will be corrected)
  example:
      python3 hammer2cbt.py --fxammo 10 hammered.sav 0 include/sfx/

      ^ Exports SFX's $00-$09 to the sfx folder.
```
 5. Include the generated .h files into your desired .c files.
 6. Add a call to `CBTFX_update` in your main loop so it gets called every frame, or add it as a VBL interrupt (Recommended to avoid stutter).
 7. When you need to play a sound effect, call `CBTFX_init(&your_SFX_name[0])` (There's also a macro generated called `CBTFX_PLAY_your_SFX_name` that should do the same thing.).

This repository comes with an example project and all the sound effects from FX Hammer converted and an example on hUGEDriver integration (See `src`).

## For music driver users
If you're already using a driver for music such as [hUGEdriver](https://github.com/SuperDisk/hUGEDriver), [GBT Player](https://github.com/AntonioND/gbt-player/tree/master/legacy_gbdk) or any other, you will need to add a few lines of code to the CBTFX functions to make it play ball with this.
There's 4 macros in `cbtfx.c` that should be set to your music driver's mute functions, the before mentioned drivers have a single function that toggles channels, in that case you should set them like: 
```c
// For hUGEdriver
#define MUSIC_DRIVER_CH2_ON hUGE_mute_channel(HT_CH2, 0);
#define MUSIC_DRIVER_CH2_OFF hUGE_mute_channel(HT_CH2, 1);
#define MUSIC_DRIVER_CH4_ON hUGE_mute_channel(HT_CH4, 0);
#define MUSIC_DRIVER_CH4_OFF hUGE_mute_channel(HT_CH4, 1);

// For GBT Player
#define MUSIC_DRIVER_CH2_ON gbt_enable_channels(GBT_CHAN_2);
#define MUSIC_DRIVER_CH2_OFF gbt_enable_channels(GBT_CHAN_2);
#define MUSIC_DRIVER_CH4_ON gbt_enable_channels(GBT_CHAN_4);
#define MUSIC_DRIVER_CH4_OFF gbt_enable_channels(GBT_CHAN_4);
```

ALSO remember to update CBTFX **after** your music driver, to avoid the music driver going over the sound effects.

## Pros of this driver
- Works with GBDK-2020 out of the box, easy to tweak.
- SFX's are 1:1 to FX Hammer's playback.
- SFX are fairly small in output size, every SFX step takes up 7 bytes at most, with one-channel SFX going from 2 to 5 bytes per step.

## Cons
- Driver/SFX data isn't designed for bank switching out of the box, my personal understanding of bank switching with GBDK is small so if anyone would like to add that feature, it'd be great.
- Only one sfx at a time.

## C array format
This is a chopped down version of my first attempt at this driver, with still a few bits to save, but mostly small:
```

Header:

  Offset Description
  ====== ==========================
    00   Channels used + SFX priority (bits 7-4 = CH_Used, bits 3-0 = Priority)
    01   SFX length in steps

Step(s):

  Offset Description
  ====== ==========================
    00   Step length in frames
    01   Frame pan (Directly written to NR51)

        -- Only written if SFX uses CH2 --
    02   CH2 Duty (Directly written to NR21)
        ----------------------------------

    03   Frame volume (bits 7-4 = CH2 volume, bits 3-0 = CH4 volume)

         -- Only written if SFX uses CH2 --   
    04   CH2 Frequency (Lower 8 bits from 11 bit frequency, Directly written to NR23)
    05   CH2 Frequency (Higher 3 bits from 11 bit frequency, Directly written to NR24)
        ----------------------------------

         -- Only written if SFX uses CH4 --   
    06   CH4 Frequency (Directly written to NR43)
         ----------------------------------

```

## Many many a thank
- ZestyDev for giving me some ideas on what to update on the driver + energy to do it
- bbbbbr for getting my code to work at first and helping me out with other code related shenanigans
- SuperDisk for helping me out with some hUGE related stuff

