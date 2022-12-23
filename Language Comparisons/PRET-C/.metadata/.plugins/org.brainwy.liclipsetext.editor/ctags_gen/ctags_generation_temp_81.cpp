#include <stdio.h>

const int INPUT_SEQUENCE = 6;
static const int I[INPUT_SEQUENCE][3] = {
//	  A, B, R
	{0,0,0},
	{1,1,0},
	{0,0,0},
	{1,1,0},
	{1,1,1},
	{1,1,0}
};

static int tick = 0;

ReactiveInput int A;
ReactiveInput int B;
ReactiveInput int R;
ReactiveOutput int O;

int main() {
  printf("        A B R  O\n");
  abort {
    PAR(Inputs, abro, Results);
  } when (tick == INPUT_SEQUENCE);
}  

thread abro() {
  while (1) {  // Loop each R
    O = 0;
    EOT;  // Mimic the surface behavior of Esterel because all PRET-C aborts are immediate
    abort {
      PAR(tA, tB);  // Await A and B
      O = 1;  // Emit O
      while (1) { O = 0; EOT; }      
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
  A = abro_vector[tick][0];
  B = abro_vector[tick][0];
  R = abro_vector[tick][0];  
}

thread Results() {
  printf("Tick %d: %d %d %d  %d\n", tick, A, B, R, O);
  tick++;
}
