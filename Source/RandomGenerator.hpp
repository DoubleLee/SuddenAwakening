#pragma once

#ifndef RANDOMGENERATOR_H
#define RANDOMGENERATOR_H

namespace Random
{
// call this in Game initialization

/**
 * @brief Seed is called to seed the random engines.
 *
 * Make sure to call this some time early durning engine construction.
 */
void Seed( );

// functions return random value between the parameters,
// inclusive example 0 - 10, will include 0 and 10

/**
 * @brief Between is for getting a random float between two floats.
 * @param low The low side for the range, inclusive.
 * @param high The high side for the range, inclusive.
 * @return The random float value.
 */
float Between( float low, float high );

/**
 * @brief Between is for getting a random double between two doubles.
 * @param low The low side for the range, inclusive.
 * @param high The high side for the range, inclusive.
 * @return The random double value.
 */
double Between( double low, double high );

/**
 * @brief Between is for getting a random in between two ints.
 * @param low The low side for the range, inclusive.
 * @param high The high side for the range, inclusive.
 * @return The random int value.
 */
int Between( int low, int high );

}

#endif // RANDOMGENERATOR_H
