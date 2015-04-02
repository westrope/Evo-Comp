#include <iostream>
#include <cstdlib>
#include <vector>
#include <bitset>
#include <cstring>
#include <string>
#include <fstream>

#include "rand.h"



using namespace std;

class population {
public:
  int key[26];
  float fit;
};

float fitness(int key[], string cipher, string freqletter[], float freqnumber[] );
void shuffle(int *a, int size);
void pmx(int *a, int *b, int *out, int k, int size);
void  mutate( int * a );
char search( char a, string s );

int main() {
  int popSize = 128;
  string cipher, tmp;

  while( getline( cin, tmp ) )
    {
      cipher.append( tmp );
    }
  //  cout << cipher << endl;

  ifstream freq;
  freq.open( "freq.txt", ios::in );

  string freqletter[488];
  float freqnumber[488];

  if( freq.is_open() ) {
    for(int i = 0; i < 488; i++ ) {
      freq >> freqletter[i];
      freq >> freqnumber[i];
    }
  }

  freq.close();

  float sum;
  for( int i = 0; i < 488; i++ ) {
    sum += freqnumber[i];
  }

  for( int i = 0; i < 488; i++ ) {
    freqnumber[i] /= sum;
  }

  // for(int i = 0; i < 488; i++ ) {
  //   cout << freqletter[i] << " " << freqnumber[i] << endl;
  // }

  float fit;
  // int key[26] = {0, 1 , 2 , 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21,
  // 		 22, 23, 24, 25};
  // fit = fitness(key, cipher, freqletter, freqnumber);
  // cout << fit << endl;

  initRand();
  vector<population> population, newpopulation;
  class population ind;
  for( int i = 0; i < 128; i++ ) {
    shuffle( ind.key, 26 );
    population.push_back(ind);
  }

  int generations = 200;
  for( int i = 0; i < generations; i++ ) {
    printf("genderation %d\n", i);

    int e1 = 0, e2 = 0;
    float tmp1 = 100, tmp2 = 100, fit;

    for( int j = 0; j < popSize; j++ ) {
      population[i].fit = fitness(population[i].key, cipher, freqletter, freqnumber);
      if( population[i].fit < tmp1 && population[i].fit < tmp2 && tmp1 <= tmp2) {
	tmp2 = population[i].fit;
	e2 = j;
      }
      else if( population[i].fit < tmp1 && population[i].fit < tmp2 && tmp1 >= tmp2) {
	tmp1 = population[i].fit;
	e1 = j;
      }
      else if( population[i].fit < tmp1 ) {
	tmp1 = population[i].fit;
	e1 = j;
      }
      else if( population[i].fit < tmp2 ) {
	tmp2 = population[i].fit;
	e2 = j;
      }
    }

    //  vector<population> newpopulation;
  newpopulation.push_back( population[e1] );
  newpopulation.push_back( population[e2] );

  int rand1, rand2, rand3; 
  for( int j = 2; j < popSize; j++ ){
      rand1 = randMod( popSize );
      rand2 = randMod( popSize );
      rand3 = randMod( popSize );
      float fit1, fit2, fit3;
      fit1 = population[rand1].fit;
      fit2 = population[rand2].fit;
      fit3 = population[rand3].fit;
      if( fit1 <= fit2 && fit1 <= fit3 )
	{ newpopulation.push_back(population[rand1]); }
      if( fit2 <= fit1 && fit2 <= fit3 )
	{ newpopulation.push_back(population[rand2]); }
      if( fit3 <= fit2 && fit3 <= fit1 )
	{ newpopulation.push_back(population[rand3]); }      
    }
  
  int h = 2;
  int a[26], b[26], c[26], d[26];
  while( h < popSize ) {
    rand1 = randMod( popSize );
    rand2 = randMod( popSize );
    if( choose(0.9) ) {
      pmx( newpopulation[rand1].key, newpopulation[rand2].key, c, 3, 26 );
      pmx( newpopulation[rand1].key, newpopulation[rand2].key, d, 3, 26 );
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
      else{
      for( int k = 0; k < 26; k++ ) {
	population[h].key[k] = newpopulation[rand1].key[k];
      }		
	h++;
	if( h < popSize ) {
      for( int k = 0; k < 26; k++ ) {
	population[h].key[k] = newpopulation[rand2].key[k];
      }			  
	}
	h++;
      }
      
    }
    
  }

  for( int k = 2; k < popSize; k++ ){
    mutate( population[k].key );
  }

  population[0] = newpopulation[0];
  population[1] = newpopulation[1];
  
  }

  float bestFit, best, tmp5;
  best = 0;
  bestFit = fitness(population[0].key, cipher, freqletter, freqnumber);  
  for( int i = 1; i < popSize; i++ ) {
    if( (tmp5 =  fitness(population[i].key, cipher, freqletter, freqnumber)  ) < bestFit ) {
      bestFit = tmp5;
      best = i;
    }
  }  

   cout << "** westrope ";
  char result[26];
  for( int i = 0; i < 26; i++ ) {
    switch( population[best].key[i] ) {
    case 0:
      result[i] = 'a';
      break;
    case 1:
      result[i] = 'b';
      break;      
    case 2:
      result[i] = 'c';
      break;
    case 3:
      result[i] = 'd';
      break;
    case 4:
      result[i] = 'e';
      break;
    case 5:
      result[i] = 'f';
      break;
    case 6:
      result[i] = 'g';
      break;
    case 7:
      result[i] = 'h';
      break;
    case 8:
      result[i] = 'i';
      break;
    case 9:
      result[i] = 'j';
      break;
    case 10:
      result[i] = 'k';
      break;
    case 11:
      result[i] = 'l';
      break;
    case 12:
      result[i] = 'm';
      break;
    case 13:
      result[i] = 'n';
      break;
    case 14:
      result[i] = 'o';
      break;
    case 15:
      result[i] = 'p';
      break;
    case 16:
      result[i] = 'q';
      break;
    case 17:
      result[i] = 'r';
      break;
    case 18:
      result[i] = 's';
      break;
    case 19:
      result[i] = 't';
      break;
    case 20:
      result[i] = 'u';
      break;
    case 21:
      result[i] = 'v';
      break;
    case 22:
      result[i] = 'w';
      break;
    case 23:
      result[i] = 'x';
      break;
    case 24:
      result[i] = 'y';
      break;
    case 25:
      result[i] = 'z';
      break;
    default:
      break;
    }
  }
  for( int i = 0; i < 26; i++ ){
    cout << result[i];
  }
  cout << endl;
  }
  

void  mutate( int * a ) {
  int rand1, rand2, tmp1, tmp2;
  rand1 = randMod(26);
  rand2 = randMod(26);

  tmp1 = a[rand1];
  tmp2 = a[rand2];

  a[rand1] = tmp2;
  a[rand2] = tmp1;
}


// uniform pmx xover
void pmx(int *a, int *b, int *out, int k, int size) 
{
    bool pick[size];   // which elements to copy from B
    int locA[size];    // locA[x] is where is x in A
    int locB[size];    // locB[x] is where is x in B
    const double prob = (double)k/size;

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

void shuffle(int *a, int size)
{
    for (int i=0; i<size; i++) {
        a[i] = i;
    }

    for (int i=size-1; i>0; i--) {
        int tmp, j;

        j = randMod(i+1);
        tmp = a[i];
        a[i] = a[j];
        a[j] = tmp;
    }
}


float fitness(int key[], string cipher, string freqletter[], float freqnumber[] ) {
  //translate the key and make cipher into clear
  char tmpkey[26];

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

  // for( int i = 0; i < 26; i++ ) {
  //   cout << tmpkey[i];
  // }
  // cout << endl;

  string tmpcipher;
  char t;

  for( int i = 0; i < cipher.size(); i++ ) { 
  }
  
  for( int i = 0; i < cipher.size(); i++ ) {
    switch( cipher[i] ) {
    case 'a':
      t = search( 'a', tmpkey );
      tmpcipher.push_back(i);
      break;
    case 'b':
      t = search( 'b', tmpkey );      
      tmpcipher.push_back(i);
      break;      
    case 'c':
      t = search( 'c', tmpkey );      
      tmpcipher.push_back(t);
      break;
    case 'd':
      t = search( 'd', tmpkey ) ;     
      tmpcipher.push_back(t);
      break;
    case 'e':
      t = search( 'e', tmpkey );      
      tmpcipher.push_back(t);
      break;
    case 'f':
      t = search( 'f', tmpkey );
      tmpcipher.push_back(t);      
      break;
    case 'g':
      t = search( 'g', tmpkey );
      tmpcipher.push_back(t);      
      break;
    case 'h':
      t = search( 'h', tmpkey );
      tmpcipher.push_back(t);      
      break;
    case 'i':
      t = search( 'i', tmpkey );
      tmpcipher.push_back(t);      
      break;
    case 'j':
      t = search( 'j', tmpkey );
      tmpcipher.push_back(t);      
      break;
    case 'k':
      t = search( 'k', tmpkey );
      tmpcipher.push_back(t);      
      break;
    case 'l':
      t = search( 'l', tmpkey );
      tmpcipher.push_back(t);      
      break;
    case 'm':
      t = search( 'm', tmpkey );
      tmpcipher.push_back(t);      
      break;
    case 'n':
      t = search( 'n', tmpkey );
      tmpcipher.push_back(t);      
      break;
    case 'o':
      t = search( 'o', tmpkey );
      tmpcipher.push_back(t);      
      break;
    case 'p':
      t = search( 'p', tmpkey );
      tmpcipher.push_back(t);      
      break;
    case 'q':
      t = search( 'q', tmpkey );
      tmpcipher.push_back(t);      
      break;
    case 'r':
      t = search( 'r', tmpkey );
      tmpcipher.push_back(t);      
      break;
    case 's':
      t = search( 's', tmpkey );
      tmpcipher.push_back(t);      
      break;
    case 't':
      t = search( 't', tmpkey );
      tmpcipher.push_back(t);      
      break;
    case 'u':
      t = search( 'u', tmpkey );
      tmpcipher.push_back(t);      
      break;
    case 'v':
      t = search( 'v', tmpkey );
      tmpcipher.push_back(t);      
      break;
    case 'w':
      t = search( 'w', tmpkey );
      tmpcipher.push_back(t);
      break;
    case 'x':
      t = search( 'x', tmpkey );
      tmpcipher.push_back(t);      
      break;
    case 'y':
      t = search( 'y', tmpkey );
      tmpcipher.push_back(t);      
      break;
    case 'z':
      t = search( 'z', tmpkey );
      tmpcipher.push_back(t);      
      break;
    default:
      break;
    }    
  }

    cout << tmpcipher << endl;


  //populate keyletter[] and keynumber[]
  float keynumber[488];
  for( int i = 0; i < 488; i++ ) keynumber[i] = 0;
  string tmp2;
  for( int i = 0; i < (tmpcipher.size() - 1); i++ ) {
    tmp2.push_back(tmpcipher[i]);
    tmp2.push_back(tmpcipher[i+1]);
    for( int j = 0; j < 488; j++ ) {
      if( freqletter[j].compare(tmp2) == 0 ) {
	keynumber[j] += 1;
      }
    }    
    tmp2.clear();
  }



  float sum;
  for( int i = 0; i < 488; i++ ) {
    sum += keynumber[i];
  }

  for( int i = 0; i < 488; i++ ) {
    keynumber[i] /= sum;
  }
  
 // for( int i = 0; i < 488; i++ ) {
 //   cout << freqletter[i] << " " << keynumber[i] << endl;
 // }

  
  
  //fitness equation
  float fit = 0;

  for( int i = 0; i < 488; i++ ) {
    fit += ( (freqnumber[i] - keynumber[i]) * (freqnumber[i] - keynumber[i]) );
  }
  
  return fit;
}

char search( char a, string s ) {
  char ret;
  int tmp;
  for( int i = 0; i < 26; i++ ) {
    if( s[i] == a ) tmp = i;
  }
 switch( tmp ) {
    case 0:
      return 'a';
      break;
    case 1:
      return 'b';
      break;      
    case 2:
      return 'c';
      break;
    case 3:
      return 'd';
      break;
    case 4:
      return 'e';
      break;
    case 5:
      return 'f';
      break;
    case 6:
      return 'g';
      break;
    case 7:
      return 'h';
      break;
    case 8:
      return 'i';
      break;
    case 9:
      return 'j';
      break;
    case 10:
      return 'k';
      break;
    case 11:
      return 'l';
      break;
    case 12:
      return 'm';
      break;
    case 13:
      return 'n';
      break;
    case 14:
      return 'o';
      break;
    case 15:
      return 'p';
      break;
    case 16:
      return 'q';
      break;
    case 17:
      return 'r';
      break;
    case 18:
      return 's';
      break;
    case 19:
      return 't';
      break;
    case 20:
      return 'u';
      break;
    case 21:
      return 'v';
      break;
    case 22:
      return 'w';
      break;
    case 23:
      return 'x';
      break;
    case 24:
      return 'y';
      break;
    case 25:
      return 'z';
      break;
    default:
      break;
    }
  
}


