/*
 * Automatically generated C code by
 * KIELER SCCharts - The Key to Efficient Modeling
 *
 * http://rtsys.informatik.uni-kiel.de/kieler
 */

#include "ABRO.h"

#define _SC_NOTRACE
#define _SC_NO_SIGNALS2VARS
#define _SC_ID_MAX 5

#include "scl.h"
#include "sc.h"
#include "sc-generic.h"

int tick(TickData* d) {
  tickstart(5);
  d->term1 = 0;
  d->O = 0;
  fork1(_region_0,_region_1, 2) {
    _region_0:
    label_0:
    d->O = 0;
    if(!d->term1){
      pause;
      goto label_0;
    } else {
      
    }
  } par {
    _region_1:
    label_1:
    d->abort1 = 0;
    fork1(_region_2,_region_3, 1) {
      _region_2:
      d->abort2 = 0;
      label_2:
      prio(4);
      pause;
      if(d->A){
        d->abort2 = 1;
        
      } else {
        if(d->R){
          d->abort1 = 1;
          
        } else {
          prio(2);
          goto label_2;
        }
      }
    } par {
      _region_3:
      d->abort3 = 0;
      label_3:
      prio(3);
      pause;
      if(d->B){
        d->abort3 = 1;
        
      } else {
        if(d->R){
          d->abort1 = 1;
          
        } else {
          prio(1);
          goto label_3;
        }
      }

    } join2(2, 4);
    if(d->abort1){
      prio(2);
      goto label_1;
    } else {
      d->O = d->O || 1;
      label_4:
      pause;
      if(d->R){
        d->abort1 = 1;
        prio(2);
        goto label_1;
      } else {
        goto label_4;
      }
    }

  } join1(5);
  
  tickreturn();
}

void reset(TickData* d) {
}

