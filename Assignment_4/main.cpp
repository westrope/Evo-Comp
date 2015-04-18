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
  char eng1[488], eng2[488], cipher1[488], cipher2[488];
  float engnum[488], sum = 0;
  
  // check if file is open
  if( freq != NULL ) {
    for( int i = 0; i < 488; i++ ) {
      fscanf( freq, "%c%c %f ", &eng1[i], &eng2[i], &engnum[i] );
      sum += engnum[i];
      //      cout << eng1[i] << eng2[i] << " " << engnum[i] <<endl;
    }
  }

  // normalize freq tables
  for( int i = 0; i < 488; i++ ) {
    engnum[i] /= sum;
    // cout << eng1[i] << eng2[i] << " " << engnum[i] <<endl;    
  }
  

  // create cipher count tables
  float ciphertxt[27][27];
  float ciphernum[488];

  // init ciphertxt cells to all be 0
  
  // init ciphertxt edges
  ciphertxt[0][1] = 'a';
  ciphertxt[0][2] = 'b';
  ciphertxt[0][3] = 'c';
  ciphertxt[0][4] = 'd';
  ciphertxt[0][5] = 'e';
  ciphertxt[0][6] = 'f';
  ciphertxt[0][7] = 'g';
  ciphertxt[0][8] = 'h';
  ciphertxt[0][9] = 'i';
  ciphertxt[0][10] = 'j';
  ciphertxt[0][11] = 'k';
  ciphertxt[0][12] = 'l';
  ciphertxt[0][13] = 'm';
  ciphertxt[0][14] = 'n';
  ciphertxt[0][15] = 'o';
  ciphertxt[0][16] = 'p';
  ciphertxt[0][17] = 'q';
  ciphertxt[0][18] = 'r';
  ciphertxt[0][19] = 's';
  ciphertxt[0][20] = 't';
  ciphertxt[0][21] = 'u';
  ciphertxt[0][22] = 'v';
  ciphertxt[0][23] = 'w';
  ciphertxt[0][24] = 'x';
  ciphertxt[0][25] = 'y';
  ciphertxt[0][26] = 'z';

  ciphertxt[1][0] = 'a';
  ciphertxt[2][0] = 'b';
  ciphertxt[3][0] = 'c';
  ciphertxt[4][0] = 'd';
  ciphertxt[5][0] = 'e';
  ciphertxt[6][0] = 'f';
  ciphertxt[7][0] = 'g';
  ciphertxt[8][0] = 'h';
  ciphertxt[9][0] = 'i';
  ciphertxt[10][0] = 'j';
  ciphertxt[11][0] = 'k';
  ciphertxt[12][0] = 'l';
  ciphertxt[13][0] = 'm';
  ciphertxt[14][0] = 'n';
  ciphertxt[15][0] = 'o';
  ciphertxt[16][0] = 'p';
  ciphertxt[17][0] = 'q';
  ciphertxt[18][0] = 'r';
  ciphertxt[19][0] = 's';
  ciphertxt[20][0] = 't';
  ciphertxt[21][0] = 'u';
  ciphertxt[22][0] = 'v';
  ciphertxt[23][0] = 'w';
  ciphertxt[24][0] = 'x';
  ciphertxt[25][0] = 'y';
  ciphertxt[26][0] = 'z';
  

} // end main
