#include <iostream>
#include <cstdlib>
#include <vector>
#include <bitset>
#include <cstring>
#include <string>
#include <fstream>
#include <cstdio>

#include "rand.h"

using namespace std;

class individual {
public:
  int key[26];
  float fit;
  
};

// user functions go here


int main() {


  // get cipher from cin
  string cipher, tmp;
  while( getline( cin, tmp ) ) {
    cipher.append( tmp );
  }

  // read in freq.txt
  FILE *freq = fopen( "freq.txt", "r" );
  char eng1[488], eng2[488];
  float engnum[488];

  // check if file is open
  if( freq != NULL ) {
    for( int i = 0; i < 488; i++ ) {
      fscanf( freq, "%c%c %f ", &eng1[i], &eng2[i], &engnum[i] );
      //      eng1[i] = fgetc( freq );
      //eng2[i] = fgetc( freq );
   
      cout << eng1[i] << eng2[i] << " " << engnum[i] <<endl;
    }
  }
  

  // create cipher count tables
  char cipher1[488], cipher2[488];
  float ciphernum[488];

  for( int i = 0; i < cipher.size(); i++ ){
    
  }

} // end main
