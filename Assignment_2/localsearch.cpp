/* localsearch.cpp

   Ian Westrope
   Evolutionary Computation
   Spring 2015

*/

#include <iostream>
#include <cstdlib>
#include <random>

#include "bitHelpers.h"
#include "rand.h"
#include "mapFunctions.h"
#include "func.h"

// max and min values for x and y
#define MAX 100
#define MIN -100

double mutate( int arg, double val );
void mainLoop( int arg1, double arg2, double arg3 );

using namespace std;

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
   double lower_bound = 0;
   double upper_bound = 10000;
  
   double a_random_double = dis( gen );
   cout << a_random_double << endl;
}

void mainLoop( int arg1, double arg2, double arg3 ){
  double x, y, nx, ny, bestFit;
  int epoch, epochImproves;

  // init random number generator
  uniform_real_distribution<double> dis( MIN, MAX);
  random_device rd;
  mt19937 gen( rd() );

  // set x and y to random values
  x = dis( gen );
  y = dis( gen );

  // 200 runs before adjusting temp
  epoch = 200;

  // calculate fitness here
  for( int i = 0; i < 100000; i++ ) {
    // Number of improving moves in current epoch
    epochImproves = 0;

    for( int j = 0; j < epoch; j++ ) {
      // get new values
      nx = mutate( arg1, x );
      ny = mutate( arg1, y );

      
    }
  }
}
 
double mutate( int arg, double val ) {
  double nval;

  switch( arg ) {
  case 0: {
    random_device rd;
    mt19937 gen( rd() );
    uniform_real_distribution<double> dis( -0.1, 0.1 );
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
