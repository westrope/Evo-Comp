/* localsearch.cpp

   Ian Westrope
   Evolutionary Computation
   Spring 2015

*/

#include <iostream>
#include <cstdlib>
#include <bitset>

#include "bitHelpers.h"
#include "rand.h"

unsigned long long int mutate( int arg1, int arg2, unsigned long long int curLocation );

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

  // convert arguments to integers
  // might not catch bad strings :(
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

  // call functions
  if( arg1 == 0 ) {
    // call gray code function
  } else if( arg1 == 1 ) {
    // call binary function
  } else {
    cout << "Bad arguments" << endl;
    exit(-1);
  }

  // init random variable
  initRand();
  unsigned long long int startLocation;
  startLocation = randULL();


  std::bitset<64> x(startLocation);

  cout << x << endl;

  startLocation = mutate( arg1, arg2, startLocation );
  
  cout << bitset<64>(startLocation) << endl;
}

/*
void grayLoop( int arg2 ) {
  // init Random number generator
  initRand();

  // init start location
  unsigned long long int curLocation;
  unsigned long long int newLocation;
  // start 1000 loop here
  curLocation = randULL();

  int bestFit = fitness( curLocation );
  for( int i = 0; i < 10000; i++ ) {
    newLocation = mutate( arg2, curLocation );
    if( fitness( newLocation ) > bestFit ) {
      curLocation = newLocation;
      bestFit = fitness(newLocation);
    }
  }
}

void binLoop( int arg2 ) {
  // init Random number generator
  initRand();

  // init start location
  unsigned long long int curLocation;
  unsigned long long int newLocation;
  // start 1000 loop here
  curLocation = randULL();

  int bestFit = fitness( curLocation );
  for( int i = 0; i < 10000; i++ ) {
    newLocation = mutate( arg2, curLocation );
    if( fitness( newLocation ) > bestFit ) {
      curLocation = newLocation;
      bestFit = fitness(newLocation);
    }
  }
}
*/

unsigned long long int mutate( int arg1, int arg2, unsigned long long int curLocation ) {

  unsigned long long int tmp;
  unsigned long long int x, y, mask;
  int flip, incDec;

  mask = ( 1<<10 ) - 1;
  
  // random mutation
  if( arg2 == 0 ) {
    tmp = randULL();
    return tmp;

    // bit flip mutation
  } else if( arg2 == 1 ) {
    flip = randMod( 20 );
    tmp = ( 1<<flip );
    tmp = ( curLocation ^ tmp );
    return tmp;

    // inc/dec gray code mutation
    // need to extract and then degray each number then gray them before putting them
    // back together
  } else if( arg2 == 2 ) {
    tmp = curLocation;
    x = ( tmp & mask );
    y = ( ( tmp>>10 ) & mask );
    incDec = randMod( 4 );
    switch( incDec ) {
    case 0:
      x += 1;
      x = ( x & 1023 );
      break;
    case 1:
      x -= 1;
      x = ( x & 1023 );
      break;
    case 2:
      y += 1;
      y = ( y & 1023 );
      break;
    case 3:
      y -= 1;
      y = ( y & 1023 );
      break;
    default:
      cout << "Bad random number" << endl;
      exit(-1);
    }
    tmp = ( ( tmp<<10 ) | y );
    tmp = ( ( tmp<<10 ) | x );
    return tmp;

    } else {
    cout << "Bad arugments" << endl;
    exit( -1 );
  }

 
}

/*
int fitness( unsigned long long int location ) {


}
*/
