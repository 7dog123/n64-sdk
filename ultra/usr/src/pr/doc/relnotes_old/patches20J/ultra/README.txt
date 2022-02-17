
This patch contains bug fixes and the addition of new functions for OS 2.0J to date.
Please refer to Changefiles.txt for a list of files which were changed as a result of the bug fixes. 

The following change will be made when the patch is applied. 

99/03/19
        * Since the R4300 WatchLo register was not initialized for N64OS, a bug would occur (however rarely) which caused a Watch exception. This patch fixes this bug.
