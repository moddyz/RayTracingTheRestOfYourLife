#include <gm/types/intRange.h>

#include <gm/functions/lengthSquared.h>
#include <gm/functions/randomNumber.h>

#include <gm/types/vec2iRange.h>

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

    int            insideCircle           = 0;
    int            insideCircleStratified = 0;
    float          radius                 = 1;
    int            sqrtNumSamples         = 10000;
    gm::FloatRange normalisedRange( 0, radius );
    gm::FloatRange sampleRange( -radius, radius );
    for ( gm::Vec2i sampleIndex : gm::Vec2iRange( gm::Vec2i( 0, 0 ), gm::Vec2i( sqrtNumSamples, sqrtNumSamples ) ) )
    {
        // Standard sampling, random point in square extent.
        gm::Vec2f coordinate( gm::RandomNumber( sampleRange ), gm::RandomNumber( sampleRange ) );
        if ( gm::LengthSquared( coordinate ) < radius )
        {
            insideCircle += 1;
        }

        // Stratified sampling, by random sample in subdivided square regions.
        coordinate =
            gm::Vec2f( 2.0f * ( ( sampleIndex.X() + gm::RandomNumber( normalisedRange ) ) / sqrtNumSamples ) - 1.0f,
                       2.0f * ( ( sampleIndex.Y() + gm::RandomNumber( normalisedRange ) ) / sqrtNumSamples ) - 1.0f );
        if ( gm::LengthSquared( coordinate ) < radius )
        {
            insideCircleStratified++;
        }
    }

    std::cout << std::fixed << std::setprecision( 12 );
    std::cout << "Regular    Estimate of Pi = " << 4 * double( insideCircle ) / ( sqrtNumSamples * sqrtNumSamples )
              << '\n'
              << "Stratified Estimate of Pi = "
              << 4 * double( insideCircleStratified ) / ( sqrtNumSamples * sqrtNumSamples ) << '\n';

    return 0;
}
