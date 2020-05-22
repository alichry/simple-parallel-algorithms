#ifndef SPA_REDTREE_UTILS_H_
#define SPA_REDTREE_UTILS_H_

#include <math.h>
#include "err.h"

int redtree_levels(int processors, int *levels);
int redtree_is_receiver(int level, int rank);
int redtree_get_neighbor(int level, int rank);
#endif

