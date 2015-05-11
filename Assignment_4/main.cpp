#include <iostream>
#include <cstdlib>
#include <vector>
#include <bitset>
#include <cstring>
#include <string>
#include <fstream>
#include <cstdio>
#include <complex>

#include "rand.h"

using namespace std;

class individual {
public:
  int key[26];
  float fit;
};

float fitness( int key[] );
void translate ( int key[], char tmpkey[] );
void run();
void shuffle(int *a, int size);
void pmx(int *a, int *b, int *out, int k, int size);
void  mutate( int * a );

//globals
float sum = 0;
float engfreq[27][27];
float ciphertxt[27][27];
string cipher, tmp;
//vector<population>population, newpopulation;
int popSize = 100;
int generations = 200;
class individual population[100];
class individual newpopulation[100];

// user functions go here


int main() {

  initRand();

  // get cipher from cin

  while( getline( cin, tmp ) ) {
    cipher.append( tmp );
  }

  // remove spaces from cipher
  //cipher.erase( remove( cipher.begin(), cipher.end(), ' ' ), cipher.end() );

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
      //      engfreq[i][j] *= 100;      
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
      //      ciphertxt[i][k] *= 100;      
    }
  }

  run();
  float bestFit, nbest;
  int best;
  best = 0;
  bestFit = fitness(population[0].key);
  for( int i = 1; i < popSize; i++ ) {
    if( (nbest = fitness(population[i].key)) > bestFit ) {
      bestFit = nbest;
      best = i;
    }
  }

  char charkey[26];
  translate( population[best].key, charkey );
  cout << bestFit << endl;
  cout << "** westrope ";
  for( int i = 0; i < 26; i++ ) {
    cout << charkey[i];
  }
  cout << endl;


 
  //  osjpedqyvkrtznbhcgalmuifxw

  //int key[26] = {14,18,9,15,4,3,16,24,21,10,17,19,25,13,1,7,2,6,0,11,12,20,8,5,23,22 };
  //int fit = 0;

  // fit = fitness( key );

  //  cout << fit << endl;
 

} // end main

void run() {
  for( int i = 0; i < popSize; i++ ) {
    class individual ind;
    shuffle( ind.key, 26 );
    population[i] = ind;
    newpopulation[i] = ind;
  }

  for( int i = 0; i < generations; i++ ) {
     cout << i << endl;
    // get elite
    int e1 = 0, e2 = 0;
    float tmp1 = 0, tmp2 = 0, fit;
    
    for( int j = 0; j < popSize; j++ ) {
      population[j].fit = fitness(population[j].key);
      if( population[j].fit > tmp1 && population[j].fit > tmp2 && tmp1 >= tmp2) {
	tmp2 = population[j].fit;
	e2 = j;
      }
      else if( population[j].fit > tmp1 && population[j].fit > tmp2 && tmp1 <= tmp2) {
	tmp1 = population[j].fit;
	e1 = j;
      }
      else if( population[j].fit > tmp1 ) {
	tmp1 = population[j].fit;
	e1 = j;
      }
      else if( population[j].fit > tmp2 ) {
	tmp2 = population[j].fit;
	e2 = j;
      }
    }
    //   vector<population>newpopulation;
    
    newpopulation[0] = population[e1];
    newpopulation[1] = population[e2];

    // cout << "got elite" << endl;
    // tournament selection  
    int rand1, rand2, rand3; 
    for( int j = 2; j < popSize; j++ ){
      rand1 = randMod( popSize );
      rand2 = randMod( popSize );
      rand3 = randMod( popSize );
      float fit1, fit2, fit3;
      fit1 = population[rand1].fit;
      fit2 = population[rand2].fit;
      fit3 = population[rand3].fit;
      if( fit1 >= fit2 && fit1 >= fit3 )
	{
	  newpopulation[j] = population[rand1];
	  continue;
	}
      if( fit2 >= fit1 && fit2 >= fit3 )
	{
	  newpopulation[j] = population[rand2];
	  continue;
	}
      if( fit3 >= fit2 && fit3 >= fit1 )
	{
	  newpopulation[j] = population[rand3];
	  continue;
	}	
    }
    //cout << "did a tournament" << endl;

    // xover
    int a[26], b[26], c[26], d[26];      
    for( int k = 0; k < popSize - 1; k++ ) {
      if( choose(0.9) ) {
	pmx( newpopulation[k].key, newpopulation[k + 1].key, c, 8, 26 );
	pmx( newpopulation[k+1].key, newpopulation[k].key, d, 8, 26 );
	for( int h = 0; h < 26; h++ ) {
	  population[k].key[h] = c[h];
	  population[k+1].key[h] = d[h];
	}
      }else{
	population[k] = newpopulation[k];
	population[k+1] = newpopulation[k+1];
      }
    }
    /*
    int h = 2;
    while( h < popSize - 1 ) {

      if( choose(0.9) ) {
	pmx( newpopulation[h].key, newpopulation[h + 1].key, c, 8, 26 );
	pmx( newpopulation[h+1].key, newpopulation[h].key, d, 8, 26 );
	for( int k = 0; k < 26; k++ ) {
	  population[h].key[k] = c[k];
	}
	h++;
	if( h < popSize ) {
	  for( int k = 0; k < 26; k++ ) {
	    population[h].key[k] = d[k];
	  }	
	  h++;
	}
      }
      else{
	population[h] = newpopulation[rand1];
	h++;
	if( h < popSize ) {
	  population[h] = newpopulation[rand2];
	  h++;
	}
      }
    }
    */
    cout << "xover is done" << endl;
    
    // mutate
    for( int k = 2; k < popSize; k++ ){
      mutate( population[k].key );
    }

    // copy over elite
    population[0] = newpopulation[0];
    population[1] = newpopulation[1];

  }// main loop
  
}// end run


float fitness( int key[] ) {
  // translate key
  char tmpkey[26];
  translate( key, tmpkey );
  float fit = 0, tm3 = 0, tm4;
  string tmpcip = cipher;
  int place = 0;
  char lookup[26] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};
  // translate cipher
  for( int i = 0; i < cipher.size() -1; i++ ) {
    for( int j = 0; j < 26; j++ ) {
      if( cipher[i] == tmpkey[j] ) {
	tmpcip[i] = lookup[j];
	break;
      }
    }
  }

  //  for( int i = 0; i < tmpcip.size(); i++ ) {
  //  cout << tmpcip[i];
  //}
  //cout << endl;
  
  // translate the sides of ciphertxt
  for( int i = 1; i < 27; i++ ) {
    ciphertxt[0][i] = tmpkey[i - 1];
    ciphertxt[i][0] = tmpkey[i - 1];
  }

  int cip1 = 0, cip2 = 0, eng1 = 0, eng2 = 0;
  float tmp1, tmp2;
  for( int i = 0; i < tmpcip.size() - 1; i++ ) {
    tmp1 = tmpcip[i];
    tmp2 = tmpcip[i+1];
    for( int j = 1; j < 27; j++ ) {
       if( tmp1 == engfreq[j][0] ) {
	eng1 = j;
      }
       if( tmp1 == ciphertxt[j][0] ) {
	 cip1 = j;
       }
       if( tmp2 == engfreq[0][j] ) {
	 eng2 = j;
       }
       if( tmp2 == ciphertxt[0][j] ) {
	 cip2 = j;
       }
    }
    if( engfreq[eng1][eng2] == 0 ) {
      tm4 = -0.0009;
    }
    else {
      tm3 = ( engfreq[eng1][eng2] * ciphertxt[cip1][cip2] );
      tm4 = sqrt(tm3);      
    }
    fit += tm4;

  }

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
      cout << "why are you here?" << endl;
      break;
    }
  }

}

// uniform pmx xover
void pmx(int a[], int b[], int out[], int k, int size) 
{
    bool pick[size];   // which elements to copy from B
    int locA[size];    // locA[x] is where is x in A
    int locB[size];    // locB[x] is where is x in B
    const double prob = (double)k/size;

    for(int i = 0; i < size; i++ ){
      out[i] = 0;
    }

    // copy random subset of B
    for (int i=0; i<size; i++) {
        // choose 
        if (choose(prob)) {
            pick[i] = true;        // select what to copy from B
            out[i] = b[i];         // copy from B
        }
        else {
            pick[i] = false;       
            out[i] = -1;           // if not copied from B then mark -1
        }

        // make table as a side effect
        locA[a[i]] = locB[b[i]] = i;   // set up location lookup for A and B
    }
    // ASSERT: out[i] is either from B or -1.  pick[i]=T if B

    // print for to use as example
    //  printf("%4s", "PICK");
    //    for (int i=0; i<size; i++) //printf("%2s ", (pick[i] ? "*" : " "));
    //printf("\n");

    // copy the lost elements into the duplicate elements
    for (int i=0; i<size; i++) {
        // for each location in the child where an element from B was put 
        // was the element from A that could have been put there also
        if (pick[i] && !pick[locB[a[i]]]) {
            // a[i] was an element that was not picked so we need to put it
            // somewhere
            int loc;

            // find duplicate
            loc = i;
            do {
                loc = locA[b[loc]];
            }
            while (out[loc] != -1);

            out[loc] = a[i];  // copy lost element over duplicate
        }
    }

    // copy from A anything not already copied
    for (int i=0; i<size; i++) {
        if (out[i] == -1) out[i] = a[i];
    }
}  

void shuffle(int a[], int size)
{
    for (int i=0; i<size; i++) {
        a[i] = i;
    }

    for (int i=size-1; i>0; i--) {
        int tmp1, j;

        j = randMod(i+1);
        tmp1 = a[i];
        a[i] = a[j];
        a[j] = tmp1;
    }
}

void  mutate( int  a[] ) {
  int rand1, rand2, rand3, tmp1, tmp2, tmp3;
  rand1 = randMod(26);
  rand2 = randMod(26);
  rand3 = randMod(26);

  tmp1 = a[rand1];
  tmp2 = a[rand2];
  tmp3 = a[rand3];

  a[rand1] = tmp3;
  a[rand2] = tmp1;
  a[rand3] = tmp2;
}
