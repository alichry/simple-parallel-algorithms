/**
 * Copyright 2020 Ali Cherry <cmcrc@alicherry.net>
 * This file is part of Simple Parallel Algorithms (SPA).
 * 
 * SPA is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 *
 * SPA is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with SPA.  If not, see <https://www.gnu.org/licenses/>.
 */

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
