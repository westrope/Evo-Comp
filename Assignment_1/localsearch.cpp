/* localsearch.cpp

   Ian Westrope
   Evolutionary Computation
   Spring 2015

*/

#include <iostream>
#include <cstdlib>

#include "bitHelpers.h"
#include "rand.h"

using namespace std;

int main( int argc, char* argv[] ) {

  // variables for command line arguments
  int grayFlag = 0;     // Gray code
  int binaryFlag = 0;
  int randomFlag = 0;
  int bitFlag = 0;
  int incFlag = 0;      // increment decrement mutation
  
  // check if there are the correct number of arguments
  if( argc > 3 || argc < 3 ) {
    cout << "Two arguments required" << endl;
    exit( -1 );
  }

  int arg1 = atoi( argv[1] );
  int arg2 = atoi( argv[2] );

  // get first argument
  if( arg1 == 0 ) {
    grayFlag = 1;
  } else if( arg1 == 1 ) {
    binaryFlag = 1;
  } else {
    cout << "First argument must be a 0 or 1" << endl;
    exit( -1 );
  }

  // get second argument
  if( arg2 == 0 ) {
    randomFlag = 1;
  } else if( arg2 == 1 ) {
    bitFlag = 1;
  } else if( arg2 == 2 ) {
    incFlag = 1;
  } else {
    cout << "Second argument must be a 0, 1, or 2" << endl;
    exit( -1 );
  }


  
  cout << "Test makefile" << endl;

}
