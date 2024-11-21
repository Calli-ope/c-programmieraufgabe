#include <stdio.h>
#include <stdlib.h>
#include <time.h>

unsigned int RandZ (unsigned char places) // from 1 to 9 places = max 999 999 999
/*
    Parameter:
        places=0 for init,
        places=1..9 for generating a random number with given places.
        A false number of places will be corrected.
    Return value:
        An unsigned integer with given positions (0 - 999 999 999).
        The number of positions can be less if the number starts with 0.
    Calling RandZ(1+RandZ(2)%9) generates a random number
        with random number of positions.
    Calling RandZ(RandZ(9)) includes the random initialising.
*/
{
    unsigned char j=1;
    double d=0.;
    if (places)
    {
        if (places>9) places = 1 + places%9; // unsigned places cannot be <0
        d = ((double) time(NULL)) / rand();
        //  extract all positions to right of comma
        d = d - (unsigned int) d;
        // shift the positions to left
        while (d*=10, j<places) j++;
    }
    else
        srand(time(NULL));  //  if places == 0 then init
    return (unsigned int) d;  // unsigned int = xxx xxx xxx
}
