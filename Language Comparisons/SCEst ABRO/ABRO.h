#ifndef ABRO_H
#define ABRO_H
/*
 * Automatically generated C code by
 * KIELER SCCharts - The Key to Efficient Modeling
 *
 * http://rtsys.informatik.uni-kiel.de/kieler
 */

#define false 0
#define true 1
typedef int bool;


typedef struct {
  char A;
  char B;
  char R;
  char O;
  char term1;
  char abort1;
  char abort2;
  char abort3;
} TickData;

void reset(TickData* d);
int tick(TickData* d);

#endif /* !ABRO_H */
