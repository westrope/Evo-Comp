#include <iostream>
#include <cstdlib>
#include <vector>
#include <bitset>
#include <cstring>
#include <string>
#include <fstream>

#include "rand.h"

using namespace std;

int main() {
  string cipher, tmp;

  while( getline( cin, tmp ) )
    {
      cipher.append( tmp );
    }
  //  cout << cipher << endl;

  ifstream freq;
  freq.open( "freq.txt", ios::in );

  string freqletter[488];
  int freqnumber[488];

  if( freq.is_open() ) {
    for(int i = 0; i < 488; i++ ) {
      freq >> freqletter[i];
      freq >> freqnumber[i];
    }
  }

  freq.close();

  // for(int i = 0; i < 488; i++ ) {
  //   cout << freqletter[i] << " " << freqnumber[i] << endl;
  // }


  
}
