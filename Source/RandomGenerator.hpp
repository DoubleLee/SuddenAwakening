#pragma once

#ifndef RANDOMGENERATOR_H
#define RANDOMGENERATOR_H

namespace Random
{
// call this in Game initialization
void Seed( );

// functions return random value between the parameters,
// inclusive example 0 - 10, will include 0 and 10
float Between( float low, float high );
double Between( double low, double high );
int Between( int low, int high );

}

#endif // RANDOMGENERATOR_H
