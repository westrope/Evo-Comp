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
#include "mapFunctions.h"

unsigned long long int mutate( int arg2, unsigned long long int curLocation );
double fitness( int arg1, unsigned long long int location );
void mainLoop( int arg1, int arg2 );

using namespace std;

int main( int argc, char* argv[] ) {

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
  if( arg1 != 0 && arg1 != 1 ) {
    cout << "First argument must be a 0 or 1" << endl;
    exit( -1 );
  }

  // get second argument
  if( arg2 != 0 && arg2 != 1 && arg2 != 2 ) {
    cout << "Second argument must be a 0, 1, or 2" << endl;
    exit( -1 );
  }

  // init random variable
  initRand();

  for( int i = 0; i < 1000; i++ ) {
    mainLoop( arg1, arg2 );
  }

}

void mainLoop( int arg1, int arg2 ){
  int evalNum, movNum;
  unsigned long long int curLocation, tmp, x, y, mask;
  curLocation = randULL();
  double curFit, tmpFit, xmap, ymap;
  curFit = fitness( arg1, curLocation );
  movNum = 0;
  mask = ( 1<<10 ) - 1;
  
  for( int i = 0; i < 10000; i++ ) {
    tmp = mutate( arg2, curLocation );
    if( (tmpFit = fitness( arg1, tmp )) > curFit ) {
      curLocation = tmp;
      curFit = tmpFit;
      evalNum = i;
      movNum++;
    }
  }

  x = ( curLocation & mask );
  y = ( ( curLocation>>10 ) & mask );
  if( arg1 == 0 ) {
    x = bitDeGray( x );
    y = bitDeGray( y );
  }
  xmap = map( x, 0, 1023, 0.0, 10.0 );
  ymap = map( y, 0, 1023, -10.0, 10.0 );  
  cout << evalNum << " " << movNum << " " << xmap << " " << ymap << " " << curFit << endl;

}

unsigned long long int mutate( int arg2, unsigned long long int curLocation ) {

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

double fitness( int arg1, unsigned long long int location ) {

  double xmap, ymap, fit;
  unsigned long long int x, y, tmp, mask;
  tmp = location;
  mask = (1<<10) - 1;

  switch( arg1 ) {
  case 0:
    x = ( tmp & mask );
    y = ( (tmp>>10 ) & mask );
    x = bitDeGray( x );
    y = bitDeGray( y );
    xmap = map( x, 0, 1023, 0.0, 10.0 );
    ymap = map( y, 0, 1023, -10.0, 10.0 );
    fit = ( 1.0 ) / ( ((xmap - 1.0) * (xmap - 1.0)) + ((ymap - 3.0) * (ymap - 3.0)) + 1.0);
    return fit;
  case 1:
    x = ( tmp & mask );
    y = ( (tmp>>10 ) & mask );
    xmap = map( x, 0, 1023, 0.0, 10.0 );
    ymap = map( y, 0, 1023, -10.0, 10.0 );
    fit = ( 1.0 ) / ( ((xmap - 1.0) * (xmap - 1.0)) + ((ymap - 3.0) * (ymap - 3.0)) + 1.0);
    return fit;
  default:
    cout << "Bad argument." << endl;
    exit( -1 );
  }
}

