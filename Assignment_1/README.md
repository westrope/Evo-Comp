# Assignment One

This assignment is to use basic local search techniques to find a global
maximum on a small plane. The maximum is known, meaning this assingment is just
to get our feet wet.

The x an y coordinates will each be stored in the lowest 20 bits of an
unsigned long long int. Each getting ten bits. They will either be stored as
binary or as Gray code. The bits will then be mapped from their 0 - 1023 range
to the appropriate ranges for both x and y.

The mutation that will occur is one of three options. The first being a new
random point will be chosen. The second is flipping a random bit in the 20 bits.
The last option is for incrementing or decrementing either the x or y value.

Both the mapping and mutation options are passed on the command line.

The basic algorithm is as follows:

```
initialize random number generator
initialize W
for( i = 1; i < 10000; i++ ) {
     W' = mutate(W)
     if( fitness(W') > fitness(W) )
     	 W = W'
}
```

Each of the six possible combinations will be run 1000 times with each random
starting point being given 10,000 cycles to find the maximum. With this data
we should be able to create some statistics and come to conclusions.