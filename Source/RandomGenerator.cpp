#include "RandomGenerator.h"

#include <chrono>
#include <random>
using namespace std;

std::mt19937 mRandomEngine32;
std::mt19937_64 mRandomEngine64;

namespace Random
{
void Seed()
	{
	auto time = chrono::high_resolution_clock::now().time_since_epoch().count();
	mRandomEngine32.seed(time);
	mRandomEngine64.seed(time);
	}

float Between( float low, float high )
	{
	uniform_real_distribution<float> dist(low,high);
	return dist(mRandomEngine32);
	}

double Between( double low, double high )
	{
	uniform_real_distribution<double> dist(low, high);
	return dist(mRandomEngine64);
	}

int Between( int low, int high )
	{
	uniform_int_distribution<int> dist( low, high );
	return dist(mRandomEngine32);
	}
}
