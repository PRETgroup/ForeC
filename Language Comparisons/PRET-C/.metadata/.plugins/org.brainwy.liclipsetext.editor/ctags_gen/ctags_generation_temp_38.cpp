#include <stdio.h>

static const int I[INPUT_SEQUENCE][3] = {
//	  A, B, R
	{ 0, 0, 0 },
	{ 1, 1, 0 },
	{ 0, 0, 0 },
	{ 1, 1, 0 },
	{ 1, 1, 1 },
	{ 1, 1, 0 }
};

ReactiveInput int A;
ReactiveInput int B;
ReactiveInput int R;
ReactiveOutput int O;

int main() {
  while (1) {  // Loop each R
    O = 0;
    EOT;  // Mimic the surface behavior of Esterel because all PRET-C aborts are immediate
    abort {
      PAR(Inputs, tA, tB, Results);  // Await A and B
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
  A = abro_vector[i][0];
  B = abro_vector[i][0];
  R = abro_vector[i][0];  
}

thread Results() {
	
}
