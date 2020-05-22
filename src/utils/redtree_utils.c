#include "redtree_utils.h"

int redtree_levels(int processors, int *levels)
{
    if (processors <= 0) {
        return SPA_UTILS_EBADINPUT;
    }
    *levels = (int) log2(processors);
    return 0;
}

int redtree_is_receiver(int level, int rank)
{
    int multp = (int) 2 * pow(2, level);
    return rank % multp == 0;
}

int redtree_get_neighbor(int level, int rank)
{
    int dist = (int) pow(2, level);
    if (redtree_is_receiver(level, rank)) {
        return rank + dist;
    }
    return rank - dist;
}
