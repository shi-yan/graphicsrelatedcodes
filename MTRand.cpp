#include "MTRand.h"

MTRand* g_RNG = 0; 
inline MTRand* getRNG() {if(!g_RNG) g_RNG = new MTRand(); return g_RNG;}
void MTRand::deleteRNG() {if(g_RNG) delete g_RNG;}
