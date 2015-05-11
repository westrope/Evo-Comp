#include <iostream>

#include "rand.h"
#include "tree.h"

using namespace std;

void xover( int mindepth, Tree *t );
double fitness();

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
  // init array of tree pointers here
  // run rest of program here
  
  Tree *test;

  test = Tree::getRandTree(5);
  test->check();
  test->print();
  xover(2, test);
  test->print();
  
  
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
void xover( int mindepth, Tree *t )
{
  Tree *parent, *s;
  Side side;
  int depth;

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
  
}
