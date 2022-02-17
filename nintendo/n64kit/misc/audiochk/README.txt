                        Readme.txt


Audio Parameter Checker Ver. 1.0


[Background]

When programming audio, the biggest concern is the size of the buffers.  In order 
to make the most efficient use of memory one wants to set the value as small as 
possible.  However, if the buffers are set too small, this will lead to the 
generation of noise.  The only way to determine how much of the buffer is actually 
being used is to modify the audio library.

[Description]

By using this tool, the programmer can ascertain the necessary values and effects 
of the various parameters relating to the given data.  What's more, since this 
ordinarily does not involve performing the audio, the measurements are done 
quickly.  The tool is divided into components for the MUS library and for the SGI 
audio library.  It is also divided into components for sequences and for sound 
effects.  Finally, each component is comprised of both Type 1 and Type 2 units.
The tool presumes use of the n_audio microcode.  Also, it makes use of the 
NuSystem audio library for the audio manager and for DMA routines.  (The values 
would not change very much if some other program (library) were used.)


Below is a list of the parameters that can be measured:


(Type 1)

* Minimum necessary size of DMA buffer
     -- In the MUS library, this is the parameter set with the musConfig member 
        syn_dma_buf_size.
     -- In the nualsgi library, this is the parameter set with the global variable 
        nuAuDmaBufSize.

* The maximum number of events ordinarily consumed during a performance (only for 
  the SGI audio library)
     -- The parameter set with the ALSeqpConfig or ALSndpConfig member maxEvents.

* The needed number of channels (only for the MUS library)
     -- The parameter set with the musConfig member "channels."

* The maximum number of updates ordinarily consumed during a performance
     -- In the MUS library, this parameter is set with the musConfig member 
        syn_updates.
     -- In the SGI audio library, this parameter is set with the ALSynConfig 
        member maxUpdates.

* The maximum length of the ACMD (command list) during an ordinary performance
     -- In the MUS library, this parameter is set with the musConfig member 
        syn_rsp_cmds.
     -- In the nualsgi library, this parameter is set with the global variable 
        nuAuAcmdLen.

(Type 2)

* The minimal necessary number of buffers, given the specified DMA buffer size
     -- In the MUS library, this parameter is set with the musConfig member 
        syn_num_dma_bufs.
     -- In the nualsgi library, this parameter is set with the global variable 
        nuAuDmaBufNum.

* The maximum number of DMAs in one frame, given the specified DMA buffer size

* The average number of DMAs in one frame, given the specified DMA buffer size




[Considerations]

Here we provide a simple explanation about the various parameters checked with 
this tool.

When the size of the DMA buffer is below the minimal required size, noise will be 
generated.  It is thus necessary to specify a value larger than this minimal size 
in the game.

   (Only for the SGI audio library)  If there are not enough events, then the 
   necessary parameter changes will not be effected and the audio will not play 
   normally.  Thus, please be certain to reserve the maximum necessary number of 
   events.  If you are going to perform numerous sequences or sound effects at the 
   same time, you simply need to sum these values.  Note that pan settings also 
   consume events, so you need to reserve an adequate surplus.

   (Only for the MUS library)  The necessary number of channels is displayed in a 
   way that brings attention to Full Release Mode on/off errors, etc.  A fixed 
   number of channels are consumed from the time the performance of data starts to 
   the time it ends, so be careful not to exceed the maximum number of channels.  
   Naturally, when more than one set of data is performed at the same time, you 
   need the summed number of channels.

Updates are consumed by every operation related to audio, so if there is an 
insufficient number of updates, the audio will not play normally.  Please be sure 
to reserve an ample surplus.

The ACMD (display list) is akin to the graphics display list.  When the ACMD is 
not long enough, structured memory will be over-written. Please be sure to reserve 
sufficient memory.

The values for the number of DMA buffers and the number of DMAs will vary, 
depending on the DMA buffer size.  If memory efficiency were given the highest 
priority, the DMA buffer size would be set as small as possible, but this would 
also greatly increase the number of DMAs.  When the number of DMAs is large, a DMA 
may not be completed in time for reasons related to overhead.  In addition, it 
will also have a large effect on other DMA applications such as for graphics.  As 
a rule, it is best to adjust the DMA buffer size so that the number of DMA buffers 
is slightly larger than the maximum number of consumed channels.

The greatest number of DMAs tends to be consumed at the start of the performance 
of the data.  For this reason, the average value is set high for short data like 
sound effects.  Of course, the maximum number of DMAs is also an important 
parameter, but the average value takes on importance when you consider the effect 
performances might have on graphics.  Naturally, it is best not to overlap the 
start of a performance with giant DMA transfers for graphics.  As mentioned above, 
when the buffer size changes, these values also change.


[How to Use]

The following subdirectories are found under chk_st1 (for use with the MUS 
library) and under chk_sgi  (for use with the SGI audio library).

      checkseq          For sequences.
      checkfsx          For sound effects.
      data              Sample data
      include           The dedicated library's include file.
      lib               The dedicated library itself.

By default, the data is held in the "data" directory, but it does not matter which 
directory is used.  The dedicated library is the publicly available library with 
a few additions to the source.


The following relates to each subdirectory:

       Makefile        Used to perform make
       params.h        Sets the parameters.  Be sure to set the playback
                       frequency
                       Also specifies the data
       params.c        The C source for assigning parameters  
                       Ordinarily this does not need to be edited                                                
       spec            The spec file.  Ordinarily this does not need to
                       be edited.
       check????.bin   The program itself.  Please use it as-is.
                 


Basically, check????.n64 will be created if make is executed after editing 
params.h, so please execute make.  check???1.n64 is Tool 1 and check???2.n64 is 
Tool 2.

Tool 1 immediately begins taking measurements.  Tool 2 starts after the DMA buffer 
size has been specified.  The DMA buffer size must be specified as a multiple of 
16bytes.  During measurement, the amount of time remaining is displayed in the 
upper-right corner of the screen.  The remaining time does not refer to the amount 
of time needed for measuring, but to the amount of time ordinarily needed to 
perform the data.  The amount of time needed to conduct measurements will vary, 
depending on the type of data.

In general, the number of data sets is automatically obtained from the given data.  
But in the case of the sequence tool for the MUS library, the number is limited to 
10 sets.  A larger number of data sets can be supported by editing params.c, 
params.h and spec.


Below we explain the various parameters in params.h

ONCE_CHECK_SEC           
The time for checking one set of data.  If the performance stops before the end 
of this time, the performance starts again from that point.  Specifies at least 2 
or 3 performances, or for the data to loop.  The time specified here is the actual 
performance time, which is longer than the time needed for measuring.

OUTPUT_RATE
Specifies the playback frequency.

MAX_DATA_SIZE 
(Only for SGI audio library sequences.)  Specifies the maximum size of 1 sequence 
of data that can be measured.  This probably does not need to be changed.

MAX_CHANNELS 
(Excluding SGI audio library sound effects.)  Specifies the maximum number of 
channels that can be measured. This probably does not need to be changed.

MAX_SOUNDS
(Only for SGI audio library sound effects.)  Specifies the maximum number of 
sounds that can be measured.

MAX_UPDATES
Specifies the maximum number of updates that can be measured. This probably does 
not need to be changed.

MAX_EVENTS
(Only for SGI audio library.) Specifies the maximum number of events that can be 
measured. This probably does not need to be changed.

MAX_ACMD_LENGTH
Specifies the maximum value for the ACMD (command list) that can be measured. This 
probably does not need to be changed.

AUDIO_HEAP_SIZE
Specifies the size of the audio heap. This probably does not need to be changed.

MAX_BUFFER_SIZE
Specifies the maximum value for the DMA buffer size than can be measured 
(specified). This probably does not need to be changed.

MAX_BUFFER_NUM
Specifies the maximum value for the number of DMA buffers. This probably does not 
need to be changed.


SBK_DATA
CTL_DATA
TBL_DATA
BIN_DATA
BFX_DATA
PTR_DATA
WBK_DATA
Specify the various data.  The first three characters indicate the extension.  
Enclose in parentheses ( " ) if this includes a path and spaces.



[Note]

This tool is meant to help the programmer get an idea of how the various 
parameters are being used.  When actually deciding on the parameters to set in a 
game, you need to incorporate sufficient margin for the situation at hand.  

In order to speed up the measurement, only the minimal processing is conducted to 
obtain the parameters.  Therefore, the measuring process is silent.

