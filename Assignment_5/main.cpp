#include <iostream>


#include "rand.h"
#include "tree.h"

using namespace std;

Tree * xover( int mindepth, Tree *t );
double fitness();

//globals
double input[51];
double output[51];
int numPoints;

int popsize = 1000;
int generations = 50;
int treeDepth = 7;

double probXover = 0.5;

int main()
{
  initRand();
  initOps(10);
  
  addOpOrTerm((char *)"+", 2, addOp);
  addOpOrTerm((char *)"-", 2, subOp);
  addOpOrTerm((char *)"*", 2, mulOp);
  addOpOrTerm((char *)"/", 2, divOp);
  addOpOrTerm((char *)"sin", 1, sinOp);
  addOpOrTerm((char *)"x", 0, xOp);
  addOpOrTerm((char *)NULL, 0, constOp);  // WARNING: null name means it is a constant!!!!


  // read in from cin here into global varabiables
  float in, out;
  cin >> numPoints;
  for( int i = 0; i < numPoints; i++ )
    {
      scanf( "%f %f", &in, &out );
      input[i] = in;
      output[i] = out;
      //      cout << input[i] << " " << output[i] << endl;
    }
  
  // init array of tree pointers here
  Tree *population[popsize];

  // init array with half randTrees half FullTrees
  int s = 1;
  for(int i = 0; i < popsize; i++)
    {
      if( s == 1 )
	{
	  population[i] = Tree::getRandTree(treeDepth);
	  s = 0;
	}
      else
	{
	  population[i] = Tree::getRandFullTree(treeDepth);
	  s = 1;
	}
      // set fitness of each tree here
    }

  // run rest of program here
  for( int i = 0; i < generations; i++ )
    {
      for( int k = 0; k < popsize; k++ )
	{
	  if( choose(probXover) )	  // xover if true
	    {
	      // xover
	      // run tournament to see if it goes into pop
	    }
	  else                            // else mutate
	    {
	      // mutate
	      // run tournament to see if it goes into pop
	    }
	}
    }
  
  Tree *test, *c, *n;

  test = Tree::getRandTree(5);
  test->check();
  test->print();
  test->eval();
  c = test->copy();
  n = xover(4, test);
  n->print();
  
  
  /*
    Mutation

    select random node

    if operator
    remove them from the tree if an operator 
    place in random node if an operator
    free removed node if needed

    else
    if constant then change randomly or change to x
    if x then change to constant by small percent
    

    Xover

    1) remove random subtree and replace with same depth random subtree
    2) swap two subtrees from two parents
    
   */
}

double fitness()
{
  double result;

  
}

// doubles as mutation by changing size of depth!
// mindepth is the maxsize of subtree to be placed in
// could add another parameter to make a min size of tree to be placed in as well...
Tree * xover( int mindepth, Tree *f )
{
  Tree *parent, *s, *t;
  Side side;
  int depth;
  
  t = f->copy();
  s = t->pickNode();
  while( mindepth < s->depth() )
    {
      s = t->pickNode();
    }
  depth = s->depth();
  parent = s->up();
  side = s->remove();

  Tree::free(s);
  s = Tree::getRandTree(depth);
  parent->join(side, s);
  t->check();

  return t;
  
}
