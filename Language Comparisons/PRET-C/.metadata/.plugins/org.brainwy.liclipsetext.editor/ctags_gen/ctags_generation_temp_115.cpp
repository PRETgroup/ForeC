#include <stdio.h>

#define INPUT_SEQUENCE 6
int I[INPUT_SEQUENCE][3] = {
//	  A, B, R
	{ 1, 1, 0},
	{ 1, 1, 0},
	{ 0, 0, 0},
	{ 1, 1, 0},
	{ 1, 1, 1},
	{ 1, 1, 0}
};

int tick = 0;

ReactiveInput int A;
ReactiveInput int B;
ReactiveInput int R;
ReactiveOutput int O = 0;

int main() {
  printf("        A B R  O\n");
  abort {
    PAR(Inputs, abro, Results);
  } when (tick == INPUT_SEQUENCE);
  
  return 0;
}  

thread abro() {
  while (1) {  // Loop each R
    EOT;  // Mimic the surface behavior of Esterel because all PRET-C aborts are immediate
    O = 0;
    abort {
      PAR(tA, tB);  // Await A and B
      O = 1;  // Emit O
      while (1) { EOT; O = 0; }      
    } when (R == 1);
  }
}

thread tA() {
  abort {while (1) { EOT; }} when (A == 1);
}

thread tB() {
  abort {while (1) { EOT;} } when (B == 1);
}

thread Inputs() {
  while (1) {
    A = I[tick][0];
    B = I[tick][1];
    R = I[tick][2];  
    EOT;
  }
}

thread Results() {
  while (1) {
    printf("Tick %d: %d %d %d  %d\n", tick, A, B, R, O);
    tick++;
    EOT;
  }
}
