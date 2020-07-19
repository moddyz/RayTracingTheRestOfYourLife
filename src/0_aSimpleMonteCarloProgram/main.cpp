#include <gm/types/intRange.h>

#include <gm/functions/lengthSquared.h>
#include <gm/functions/randomNumber.h>

#include <iomanip>
#include <iostream>
#include <math.h>
#include <stdlib.h>

int main( int i_argc, char** i_argv )
{
    // This program attempts to approximate PI by producing random samples in a square,
    // and computing the ratio of C/N, such that:
    //
    // C = Samples contained within the circle inscribed in the square.
    // N = Total number of samples.

    int            numSamples          = 1000;
    int            samplesInsideCircle = 0;
    float          radius              = 1;
    gm::FloatRange sampleRange( -radius, radius );
    for ( int sampleIndex = 0; sampleIndex < numSamples; ++sampleIndex )
    {
        gm::Vec2f coordinate( gm::RandomNumber( sampleRange ), gm::RandomNumber( sampleRange ) );
        if ( gm::LengthSquared( coordinate ) < radius )
        {
            samplesInsideCircle += 1;
        }
    }

    std::cout << std::fixed << std::setprecision( 12 );
    std::cout << "Estimate of Pi = " << 4.0 * double( samplesInsideCircle ) / numSamples << '\n';

    return 0;
}
