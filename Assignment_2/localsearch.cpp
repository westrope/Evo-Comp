/* localsearch.cpp

   Ian Westrope
   Evolutionary Computation
   Spring 2015

*/

#include <iostream>
#include <cstdlib>
#include <random>
#include <complex>

#include "bitHelpers.h"
#include "rand.h"
#include "mapFunctions.h"
#include "func.h"

// max and min values for x and y
#define MAX 100
#define MIN -100




double mutate( int arg, double val );
void mainLoop( int arg1, double arg2, double arg3 );
bool accept( double newf, double f, double temp );

using namespace std;

random_device rd;
mt19937 gen( rd() );
uniform_real_distribution<double> dis( -0.1, 0.1 );

int main( int argc, char* argv[] ) {

  // check if there are the correct number of arguments
  // number of arguments should be 4
  // 0 == self
  // 1 == mutation type integer, 0 == uniform, 1 == normal, 2 == Cauchy
  // 2 == starting temp float greater than 0
  // 3 == cooling constant float between 0 and 1
  if( argc != 4 ) {
    cout << "Three arguments required" << endl;
    exit( -1 );
  }

  // convert arguments to integers
  // might not catch bad strings :(
  int arg1 = atoi( argv[1] );
  double arg2 = atof( argv[2] );
  double arg3 = atof( argv[3] );

  // check if first argument is correct
  if( arg1 != 0 && arg1 != 1  && arg1 != 2 ) {
    cout << "First argument must be a 0, 1, or 2" << endl;
    exit( -1 );
  }

  // check if second argument is correct
  if( arg2 <= 0 ) {
    cout << "Second argument must be greater than 0" << endl;
    exit( -1 );
  }

  // check if third argument is correct
  if( arg3 <= 0 || arg3 > 1 ) {
    cout << "Third argument must be greather than 0, but less than or equal to 1" << endl;
    exit( -1 );
  }

  // testing
  initRand();
  for( int i = 0; i < 100; i++ ) {
    mainLoop( arg1, arg2, arg3 );
  }

}

// arg1 = mutation
// arg2 = temp
// arg3 = cooling constant
void mainLoop( int arg1, double arg2, double arg3 ){
  double x, y, nx, ny, bestFit, newFit, curFit, bestx, besty, rate;
  int epoch, epochImproves;

  // init random number generator
  uniform_real_distribution<double> dis( MIN, MAX);
  random_device rd;
  mt19937 gen( rd() );

  // set x and y to random values
  bestx = x = dis( gen );
  besty = y = dis( gen );

  // 200 runs before adjusting temp
  epoch = 200;

  // calculate fitness here
  curFit = bestFit = fr( x, y );
  
  for( int i = 0; i < 100000; ) {
    // Number of improving moves in current epoch
    epochImproves = 0;

    for( int j = 0; j < epoch; j++ ) {
      // get new values
      nx = mutate( arg1, x );
      ny = mutate( arg1, y );

      // new fitness
      newFit = fr( nx, ny );

      // new eval
      i++;

      // check if we accept new values
      if( accept( newFit, curFit, arg2 ) ) {
	epochImproves++;
	x = nx;
	y = ny;
	curFit = newFit;
	
	if( curFit > bestFit ) {
	  bestx = x;
	  besty = y;
	  bestFit = curFit;
	}
      }
    }
    rate = epochImproves / epoch;
    if( arg3 < 1 ) {
      if( rate > 0.9 ) arg2 *= arg3; // make it cooler
      if( rate < 0.1 ) arg2 /= arg3; // make it hotter
    }
  }
  // print results
  cout << "Best Fitness: " << bestFit << endl;
}

bool accept( double newf, double f, double temp ) {
  return ( newf >= f ) || ( randUnit() < exp( (newf - f) / temp ) ); 
}
 
double mutate( int arg, double val ) {
  double nval;

  switch( arg ) {
  case 0: {
    nval = dis( gen );
    nval += val;
    return nval;
  }
  case 1: {
    nval = randNorm( 0.1 );
    nval += val;
    return nval;
  }
  case 2: {
    nval = randCauchy( 0, 0.1 );
    nval += val;
    return nval;
  }
  default: {
    cout << "Unexpected error in mutate function." << endl;
    exit( -1 );
  }
  }
}
