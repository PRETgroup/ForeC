#include <stdio.h>

int abro_vector[20][3] = {
	{0,0,0},
	{0,1,0},
	{1,0,0},
	{0,0,0},
	{0,1,0}
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
      PAR(tA, tB);  // Await A and B
      O = 1;  // Emit O
      while (1) { O = 0; EOT; }      
    } when (R == 1);
  }
}

thread tA() {
  sabort (A == 1) {while (1) { EOT; }}
}

thread tB() {
  sabort (B == 1) {while (1) { EOT;} }
}
