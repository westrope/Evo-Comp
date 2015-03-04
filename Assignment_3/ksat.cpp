#include <iostream>
#include <cstdlib>
#include <vector>
#include <bitset>

#include "rand.h"

using namespace std;

vector<unsigned long long int> clause;
vector<unsigned long long int> nMask;
int n , k , c;

unsigned long long int tourn( unsigned long long int a, unsigned long long int b,
			      unsigned long long int d );

int fitness( unsigned long long int d );
unsigned long long int xover( unsigned long long int a, unsigned long long int b );
unsigned long long int mutate( unsigned long long int a );
int convert( char *binary );



int main( int argc, char* argv[] ) {
  initRand();
  
  if( argc != 4 ) {
    cout << "Three arguments required" << endl;
    exit ( -1 );
  }

  int numGenerations = atoi( argv[1] );
  int popSize = atoi( argv[2] );
  double xoverProb = atof( argv[3] );


  vector<unsigned long long int> population;

  cin >> n >> k >> c;

  unsigned long long int tmp1, tmp2, mask;
  char one[64];
  char two[64];
  for( int i = 0; i < c; i++ ) {
    cin >> one >> two;
    tmp1 = convert( one );
    tmp2 = convert( two );
    clause.push_back(tmp1);
    nMask.push_back(tmp2);
  }

   mask = (1<<(n)) -1;
  
  for( int i = 0; i < popSize; i++ ) {
    tmp1 = randULL();
    tmp1 = tmp1 & mask;
    population.push_back(tmp1);
  }

  for( int i = 0; i < numGenerations; i++ ) {

    // get 2 elite and stick them in newpopulation
    int e1 = 0, e2 = 1, tmp1 = 0 , tmp2 = 0, fit;
    for( int j = 0; j < popSize; j++ ) {
      fit = fitness( population[j] );
      if( fit > tmp1 && fit > tmp2 && tmp1 >= tmp2) {
	tmp2 = fit;
	e2 = j;
      }
      else if( fit > tmp1 && fit > tmp2 && tmp1 <= tmp2) {
	tmp1 = fit;
	e1 = j;
      }
      else if( fit > tmp1 ) {
	tmp1 = fit;
	e1 = j;
      }
      else if( fit > tmp2 ) {
	tmp2 = fit;
	e2 = j;
      }
    }
    vector<unsigned long long int> newpopulation;
    newpopulation.push_back( population[e1] );
    newpopulation.push_back( population[e2] );

    
    // randomly select 3 and put them in a tourny and put winner in new population until it is full
    int rand1, rand2, rand3;
    for( int j = 2; j < popSize; j++ ){
      rand1 = randMod( popSize );
      rand2 = randMod( popSize );
      rand3 = randMod( popSize );
      newpopulation.push_back(tourn( population[rand1], population[rand2], population[rand3] ));
    }

    // pick 2 from new population and xover into population until pop is full with new
    int h = 2;
    while( h < popSize ) {
      rand1 = randMod( popSize );
      rand2 = randMod( popSize );
      if( choose(xoverProb) ) {
	population[h] = xover( newpopulation[rand1], newpopulation[rand2] );
	h++;
      }
      /*
      else {
	population[h] = newpopulation[rand1];
	h++;
	if( h < popSize ) {
	  population[h] = newpopulation[rand2];
	}
	h++;
      }
      */
    }
    
    // mutate pop

    for( int j = 2; j < popSize; j++ ) {
      population[j] = mutate( population[j] );
    }

    population[0] = newpopulation[0];
    population[1] = newpopulation[1];
    
  }

  int bestFit, best;
  best = 0;
  bestFit = fitness( population[0] );
  for( int i = 1; i < popSize; i++ ) {
    if( fitness( population[i] ) > bestFit ) {
      bestFit = fitness(population[i]);
      best = i;
    }
  }

  cout << bestFit << " " << (bitset<64>) population[best] << endl;
  if( bestFit == c ) {
    cout << "Satisfiable" << endl;
  }
  else {
    cout << "Could not find a solution" << endl;
  }
  
}

int convert( char *binary ) {
  int p = 1, num = 0, tmp;
  for (int i = strlen(binary)-1; i >= 0; i-- ) {
    tmp = binary[i] - '0';
    if( tmp == 1 ){
      num = num + p;
    }
    p = p * 2;
  
  }
  return num;
}

unsigned long long int mutate( unsigned long long int a ){
  unsigned long long int mask;
  mask = a ^ ( ((randULL() & randULL()) & randULL()) & randULL() );
  return mask;
}

unsigned long long int xover( unsigned long long int a, unsigned long long int b ) {
  unsigned long long int mask, child, mask2;
  int count = 1;

  for( int i = 0; i < n; i++ ) {
    if( choose( 0.5 ) ) {
      mask += count;
    }
    else{
      mask2 += count;
    }
    count *= 2;
  }
  child = (a & mask) | (b & mask2);

  return child;

}

unsigned long long int tourn( unsigned long long int a, unsigned long long int b,
			      unsigned long long int d ) {
  int fit1, fit2, fit3;

  fit1 = fitness( a );
  fit2 = fitness( b );
  fit3 = fitness( d );

  if( fit1 >= fit2 && fit1 >= fit3 ) { return a; }
  if( fit2 >= fit1 && fit2 >= fit3 ) { return b; }
  if( fit3 >= fit2 && fit3 >= fit1 ) { return d; }
 
}

int fitness( unsigned long long int d ){
  int fit = 0;

  for( int i = 0; i < clause.size(); i++ ) {
    if( ((d & clause[i]) ^ nMask[i]) > 0 ) {
      fit++;
    }
  }

  return fit;
}
