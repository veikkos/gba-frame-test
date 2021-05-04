# GBA Frame Test ROM

The program is a modified version of Joe Savage's awesome [Writing a
Game Boy Advance
Game](https://www.reinterpretcast.com/writing-a-game-boy-advance-game)
example of how to write a GBA game.

## Introduction

![Animation
GIF](https://github.com/veikkos/gba-frame-test/blob/master/animation.gif)

Frame Test ROM can be used to test that your GBA's display driving is
working as it should. It's mostly useful for people changing their
console displays to 3rd party models e.g. "IPS V2". These displays are
coming from several vendors and with varying quality. Some models can
have display tearing or are missing frames. With the test ROM you can
see how well your display works.

## Usage

Install test ROM to your GBA. You need a flash cart or similar
solution. Start the ROM and you should see vertical block going from
left to right over and over again.

### Examples

Example video of Gameboy Advance SP with original AGS-001 display
recorded with 480 FPS [from
YouTube](https://www.youtube.com/watch?v=Zwg9IndS9is). Like all the
original displays it shows the scanline pattern.

[Here is a slow motion
example](https://www.youtube.com/watch?v=GdLMmTVMPP0) of 3rd party IPS
V2 display showing frame drops. IPS displays do not use scanline
pattern but draw the entire screen at once.

### Frame drop

Take your phone and record the screen with the quickest slow motion
video recording mode you can find. For example 240 or 480 FPS will do
nicely.

Then inspect the video to see that there are no missing frames. Since
the block moves one step every frame you should be easily notice that
if it sometimes jumps more which means you had a frame drop.

### Tearing

You can also test if the [screen is
tearing](https://en.wikipedia.org/wiki/Screen_tearing). It happens
when the display was still drawing the vertical block but the driver
doesn't synchronize the process correctly and jumps to next
frame. Visually it causes a vertical discontinuity in the image.

Tearing is not to be confused with normal banding with original
scanline displays (AGB-001, AGS-001, AGS-101) when watching slow
motion footage since these displays draw line by line from top to
bottom.

## Download

You can find ROM binary from [release
page](https://github.com/veikkos/gba-frame-test/releases).

## Compiling

You need [devkitPro](https://devkitpro.org/) for GBA.

See `build.sh`. 

## Troubleshooting

* *"Logo is corrupted and boot fails"*
    * See issue and a solution at [Boot fail using Everdrive GBA](https://github.com/veikkos/gba-frame-test/issues/1)
