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

float fitness( int key[] );
void translate ( int key[], char tmpkey[] );

//char eng1[488], eng2[488], cipher1[488], cipher2[488];
//float engnum[488], sum = 0;

float sum = 0;
float engfreq[27][27];
float ciphertxt[27][27];
string cipher, tmp;
//float ciphernum[488];

class individual {
public:
  int key[26];
  float fit;
  
};

// user functions go here


int main() {


  // get cipher from cin

  while( getline( cin, tmp ) ) {
    cipher.append( tmp );
  }

  // remove spaces from cipher
  cipher.erase( remove( cipher.begin(), cipher.end(), ' ' ), cipher.end() );

  // read in freq.txt
  FILE *freq = fopen( "freq.txt", "r" );

  for( int i = 0; i < 27; i++ ) {
    for( int k = 0; k < 27; k++ ) {
      engfreq[i][k] = 0;
      ciphertxt[i][k] = 0;
    }
  }
 

  
  // init ciphertxt edges
  engfreq[0][1] = ciphertxt[0][1] = 'a';
  engfreq[0][2] = ciphertxt[0][2] = 'b';
  engfreq[0][3] = ciphertxt[0][3] = 'c';
  engfreq[0][4] = ciphertxt[0][4] = 'd';
  engfreq[0][5] = ciphertxt[0][5] = 'e';
  engfreq[0][6] = ciphertxt[0][6] = 'f';
  engfreq[0][7] = ciphertxt[0][7] = 'g';
  engfreq[0][8] = ciphertxt[0][8] = 'h';
  engfreq[0][9] = ciphertxt[0][9] = 'i';
  engfreq[0][10] = ciphertxt[0][10] = 'j';
  engfreq[0][11] = ciphertxt[0][11] = 'k';
  engfreq[0][12] = ciphertxt[0][12] = 'l';
  engfreq[0][13] = ciphertxt[0][13] = 'm';
  engfreq[0][14] = ciphertxt[0][14] = 'n';
  engfreq[0][15] = ciphertxt[0][15] = 'o';
  engfreq[0][16] = ciphertxt[0][16] = 'p';
  engfreq[0][17] = ciphertxt[0][17] = 'q';
  engfreq[0][18] = ciphertxt[0][18] = 'r';
  engfreq[0][19] = ciphertxt[0][19] = 's';
  engfreq[0][20] = ciphertxt[0][20] = 't';
  engfreq[0][21] = ciphertxt[0][21] = 'u';
  engfreq[0][22] = ciphertxt[0][22] = 'v';
  engfreq[0][23] = ciphertxt[0][23] = 'w';
  engfreq[0][24] = ciphertxt[0][24] = 'x';
  engfreq[0][25] = ciphertxt[0][25] = 'y';
  engfreq[0][26] = ciphertxt[0][26] = 'z';

  engfreq[1][0] = ciphertxt[1][0] = 'a';
  engfreq[2][0] = ciphertxt[2][0] = 'b';
  engfreq[3][0] = ciphertxt[3][0] = 'c';
  engfreq[4][0] = ciphertxt[4][0] = 'd';
  engfreq[5][0] = ciphertxt[5][0] = 'e';
  engfreq[6][0] = ciphertxt[6][0] = 'f';
  engfreq[7][0] = ciphertxt[7][0] = 'g';
  engfreq[8][0] = ciphertxt[8][0] = 'h';
  engfreq[9][0] = ciphertxt[9][0] = 'i';
  engfreq[10][0] = ciphertxt[10][0] = 'j';
  engfreq[11][0] = ciphertxt[11][0] = 'k';
  engfreq[12][0] = ciphertxt[12][0] = 'l';
  engfreq[13][0] = ciphertxt[13][0] = 'm';
  engfreq[14][0] = ciphertxt[14][0] = 'n';
  engfreq[15][0] = ciphertxt[15][0] = 'o';
  engfreq[16][0] = ciphertxt[16][0] = 'p';
  engfreq[17][0] = ciphertxt[17][0] = 'q';
  engfreq[18][0] = ciphertxt[18][0] = 'r';
  engfreq[19][0] = ciphertxt[19][0] = 's';
  engfreq[20][0] = ciphertxt[20][0] = 't';
  engfreq[21][0] = ciphertxt[21][0] = 'u';
  engfreq[22][0] = ciphertxt[22][0] = 'v';
  engfreq[23][0] = ciphertxt[23][0] = 'w';
  engfreq[24][0] = ciphertxt[24][0] = 'x';
  engfreq[25][0] = ciphertxt[25][0] = 'y';
  engfreq[26][0] = ciphertxt[26][0] = 'z';


  char eng1, eng2;
  float tmp2;
  int pos1 = 0, pos2 = 0;
  
    // check if file is open
  if( freq != NULL ) {
    for( int i = 0; i < 488; i++ ) {
      fscanf( freq, "%c%c %f ", &eng1, &eng2, &tmp2 );
      sum += tmp2;
      for( int j = 0; j < 27; j++ ) {
	if( eng1 == engfreq[j][0] ) {
	  pos1 = j;
	  break;
	}
      }

      for( int j = 0; j < 27; j++ ) {
	if( eng2 == engfreq[0][j] ) {
	  pos2 = j;
	  break;
	}
      }
      engfreq[pos1][pos2] = tmp2; 
    }
  }

  // normalize freq tables
  for( int i = 1; i < 27; i++ ) {
    for( int j = 1; j < 27; j++ ) {
      engfreq[i][j] /= sum;
     }
  }

  char cip1, cip2;
  sum = 0;
  pos1 = pos2 = 0;

  for( int i = 0; i < cipher.size() - 1; i++ ) {
    cip1 = cipher[i];
    cip2 = cipher[i + 1];

    // get first position
    for( int j = 1; j < 27; j++ ) {
      if( cip1 == ciphertxt[j][0] ) {
	pos1 = j;
	break;
      }
    }

    // get second position
    for( int j = 1; j < 27; j++ ) {
      if( cip2 == ciphertxt[0][j] ) {
	pos2 = j;
	break;
      }
    }

    // add a count for the letter pair
    ciphertxt[pos1][pos2] += 1;
    sum++;
  }

  // normalize cipher freq table
  for( int i = 1; i < 27; i++ ) {
    for( int k = 1; k < 27; k++ ) {
      ciphertxt[i][k] /= sum;
    }
  }

  //  osjpedqyvkrtznbhcgalmuifxw

  int key[26] = {14,18,9,15,4,3,16,24,21,10,17,19,25,13,1,7,2,6,0,11,12,20,8,5,23,22 };
  int fit = 0;
  
  fit = fitness( key );
  cout << fit << endl;
 

} // end main


float fitness( int key[] ) {
  // translate key
  char tmpkey[26];
  translate( key, tmpkey );
  float fit = 0;

  // translate the sides of ciphertxt
  for( int i = 1; i < 27; i++ ) {
    ciphertxt[0][i] = tmpkey[i - 1];
    ciphertxt[i][0] = tmpkey[i - 1];
  }

  int cip1 = 0, cip2 = 0, eng1 = 0, eng2 = 0;
  float tmp1, tmp2;
  for( int i = 0; i < cipher.size() - 1; i++ ) {
    tmp1 = cipher[i];
    tmp2 = cipher[i+1];
    for( int j = 1; j < 27; j++ ) {
       if( tmp1 == engfreq[j][0] ) {
	eng1 = j;
      }
    }
    for( int j = 1; j < 27; j++ ) {
      if( tmp2 == engfreq[0][j] ) {
	eng2 = j;
      }
    }
    for( int j = 1; j < 27; j++ ) {
      if( tmp1 == ciphertxt[j][0] ) {
	cip1 = j;
      }
    }
    for( int j = 1; j < 27; j++ ) {
      if( tmp2 == ciphertxt[0][j] ) {
	cip2 = j;
      }
    }
    fit += ( engfreq[eng1][eng2] * ciphertxt[cip1][cip2] );
    
  }

  fit *= fit;
  fit = ( 1.0 / fit );

  return fit;

}

void translate ( int key[], char tmpkey[] ) {

  for( int i = 0; i < 26; i++ ) {
    switch( key[i] ) {
    case 0:
      tmpkey[i] = 'a';
      break;
    case 1:
      tmpkey[i] = 'b';
      break;      
    case 2:
      tmpkey[i] = 'c';
      break;
    case 3:
      tmpkey[i] = 'd';
      break;
    case 4:
      tmpkey[i] = 'e';
      break;
    case 5:
      tmpkey[i] = 'f';
      break;
    case 6:
      tmpkey[i] = 'g';
      break;
    case 7:
      tmpkey[i] = 'h';
      break;
    case 8:
      tmpkey[i] = 'i';
      break;
    case 9:
      tmpkey[i] = 'j';
      break;
    case 10:
      tmpkey[i] = 'k';
      break;
    case 11:
      tmpkey[i] = 'l';
      break;
    case 12:
      tmpkey[i] = 'm';
      break;
    case 13:
      tmpkey[i] = 'n';
      break;
    case 14:
      tmpkey[i] = 'o';
      break;
    case 15:
      tmpkey[i] = 'p';
      break;
    case 16:
      tmpkey[i] = 'q';
      break;
    case 17:
      tmpkey[i] = 'r';
      break;
    case 18:
      tmpkey[i] = 's';
      break;
    case 19:
      tmpkey[i] = 't';
      break;
    case 20:
      tmpkey[i] = 'u';
      break;
    case 21:
      tmpkey[i] = 'v';
      break;
    case 22:
      tmpkey[i] = 'w';
      break;
    case 23:
      tmpkey[i] = 'x';
      break;
    case 24:
      tmpkey[i] = 'y';
      break;
    case 25:
      tmpkey[i] = 'z';
      break;
    default:
      break;
    }
  }

}
