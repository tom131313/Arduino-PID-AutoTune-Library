This is yet another derivative of the Arduino PID AutoTune Library.  (Original notice posted below.)

Caution - Not really Arduino any more but it's close and the name reflects the origin of the code.

This does run on a NI roboRIO.  I doubt it would be hard to put back on an Arduino.  It's actually a little more generic C++.

Another AutoTune (pull request waiting, probably forever, to be merged with the original) may be superior but I had this one done before that one was added to GitHub.  (It is missing DIRECT/REVERSE which I added to this version.)

The orignal AutoTune is an excellent start and has some issues that had to be fixed and enhanced before it was good enough for my purposes.  And in the spirit of one engineer's comment - if you don't like the tuning then run it again - I let the tuner run longer to have multiple tuning parameter choices and I plot the output so I understand and can readily verify what the tuner has done.

The DIRECT/REVERSE option has been added.

This version finds maxima without spurious junk that confounds accurate tuning.

The example program is tuning a pair of FIRST FRC robot motors to run at a setpoint speed during a tank turn.  Good for running at low speed during autonomous movement looking for taking aim at the target using camera vision.  The tuning parameters are used in the Talon SRX motor contoller which has the built-in PID controller.

Original Notice:

/**********************************************************************************************
 * Arduino PID AutoTune Library - Version 0.0.1
 * by Brett Beauregard <br3ttb@gmail.com> brettbeauregard.com
 *
 * This Library is ported from the AutotunerPID Toolkit by William Spinelli
 * (http://www.mathworks.com/matlabcentral/fileexchange/4652) 
 * Copyright (c) 2004
 *
 * This Library is licensed under the BSD License:
 * Redistribution and use in source and binary forms, with or without 
 * modification, are permitted provided that the following conditions are 
 * met:
 * 
 *     * Redistributions of source code must retain the above copyright 
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright 
 *       notice, this list of conditions and the following disclaimer in 
 *       the documentation and/or other materials provided with the distribution
 *       
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" 
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE 
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE 
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE 
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR 
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF 
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS 
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN 
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) 
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE 
 * POSSIBILITY OF SUCH DAMAGE.
 **********************************************************************************************/
