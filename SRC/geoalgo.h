#ifndef __GEOALGO_H__
#define __GEOALGO_H__

#include "linked_list.h"
#include "math_fn.h"

/*----------------------------------------------------------------------------------*/
//                                  Ordering functions
/*----------------------------------------------------------------------------------*/

int isSuperior(Vertex const *p, Vertex const *q, Dllist const *dll, int const LNK);

/*----------------------------------------------------------------------------------*/
//                                  Algos
/*----------------------------------------------------------------------------------*/

void graham(Dllist *dll);

void jarvis(Dllist *dll);

/*----------------------------------------------------------------------------------*/
//                                  Merge sort
/*----------------------------------------------------------------------------------*/

Vertex* merge(Vertex *p, int P, Vertex* q, int Q, Dllist *dll, int LNK);

Vertex* sort(Vertex *p, int n, Dllist *dll, int LNK);

#endif