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

thread main() {
  while (1) {  // Loop each R
    O = 0;
    EOT;  // Mimic the surface behavior of Esterel because all PRET-C aborts are immediate
    sabort (R == 1) {
      PAR(tA, tB);  // Await A and B
      O = 1;  // Emit O
      while (1) { O = 0; EOT; }      
    }
  }
}

thread tA() {
  sabort (A == 1) {while (1) { EOT; }}
}

thread tB() {
  sabort (B == 1) {while (1) { EOT;} }
}




// thread GT (void) {
// 	static int i = 0;
// 	while(1) {
// 		a = abro_vector[i][0];
// 		b = abro_vector[i][1];
// 		r = abro_vector[i][2];
// 		o = abro_vector[i][3];
// 		i++;
// 		if (i >= 20) {
// 			i = 0;
// 		}
// 		EOT;
// 	}
// }