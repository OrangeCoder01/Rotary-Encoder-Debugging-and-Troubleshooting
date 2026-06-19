# Rotary Encoder Debugging and Troubleshooting
This code is helpful for debugging the rotary encoder that has SW, CLK, and DT pins, 
it uses versatile coding strategies to detect changes in the rotary encoder's direction
of rotation and the press state.

There are multiple files uploaded, each is an improved version of the previous:
for example, the first .ino file which is "Rotary_encoder_debugging" is a basic code
that uses less accurate and prone-to-error code due to its simplicity,
for example, the code
forces the MCU to be delayed, unlike the "2nd_enchancement_rotary_encoder_debugging" is a more
efficient and practical code as it uses the "Attach Interrupt logic" which is helpful to 
trigger a function when there is a change in the state of the pin-- there are obstacles like
the illegal use of Serial printing (Serial.print or Serial.println) in an attach-interrupt
function-- so there is the flag technique to overcome this issue.
With attach-interrupt, every change whether clockwise, anticlockwise, or the
rotary encoder be pressed can be detected rightaway without missing out due delays
and the program halts all procedures and
executes specific functions and resumes back to where it was before the program got interrupted

There is the "3rd_enchancement_rotary_encoder_debugging", it is a a better version from the
previous code, as it adds the debouncing effect; when rotating or pressing the rotary encoder's
knob, there is jitter in the state, it bounces on and off states for either CLK or SW, 
this could be explained as clapping, using slow motion camera, the hands once clap, there
is multiple contact instead of one.
Same physics is applied to the rotary encoder.
The solution is simple, is to apply to the attach-interrupt function callback a time control, that catches the first
signal and ignores the consecutive ripples. SW pin takes more time that the CLK.
