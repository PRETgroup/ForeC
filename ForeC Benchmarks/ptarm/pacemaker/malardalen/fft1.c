/*************************************************************************/
/*                                                                       */
/*   SNU-RT Benchmark Suite for Worst Case Timing Analysis               */
/*   =====================================================               */
/*                              Collected and Modified by S.-S. Lim      */
/*                                            sslim@archi.snu.ac.kr      */
/*                                         Real-Time Research Group      */
/*                                        Seoul National University      */
/*                                                                       */
/*                                                                       */
/*        < Features > - restrictions for our experimental environment   */
/*                                                                       */
/*          1. Completely structured.                                    */
/*               - There are no unconditional jumps.                     */
/*               - There are no exit from loop bodies.                   */
/*                 (There are no 'break' or 'return' in loop bodies)     */
/*          2. No 'switch' statements.                                   */
/*          3. No 'do..while' statements.                                */
/*          4. Expressions are restricted.                               */
/*               - There are no multiple expressions joined by 'or',     */
/*                'and' operations.                                      */
/*          5. No library calls.                                         */
/*               - All the functions needed are implemented in the       */
/*                 source file.                                          */
/*                                                                       */
/*************************************************************************/
/*                                                                       */
/*  FILE: fft1.c                                                         */
/*  SOURCE : Turbo C Programming for Engineering by Hyun Soon Ahn        */
/*                                                                       */
/*  DESCRIPTION :                                                        */
/*                                                                       */
/*     FFT using Cooly-Turkey algorithm.                                 */
/*     There are two inputs, ar[] and ai[]. ar[] is real number parts    */
/*     of input array and the ai[] is imaginary number parts of input.   */
/*                                                                       */
/*************************************************************************/


const double PI = 3.14159;
const double PI_half = 1.570795;
const double PI_twice = 6.28318;

double ar[8] = {1.0, 0.70711, 0.0, -0.70711, -1.0, -0.70711, 0.0, 0.70711};
double ai[8] = {0.0,  };

double sin(double rad);
int fft1(int n);

int main() {
	/* forward fft */
	fft1(8);
	
	return 0;
}

int fft1(int n) {
	int i, j, k, it, xp, xp2, j1, j2;
	double w, wr, wi, dr1, dr2, di1, di2, tr, ti, arg;
	
	if (n < 2) {
		return 999;
	}
	
	j = 2;
	
	/*  Main FFT Loops  */
	xp2 = n;
	for (it = 0; it < 1; it = it + 1) #1#1 {
		xp = xp2;
		xp2 = xp2/2;
		w = PI / xp2;

		for (k = 0; k < xp2; k = k + 1) #4#4 {
			arg = k * w;	// 0 to PI
			wr = sin(PI_half - arg);
			wi = -sin(arg);
			i = k - xp;
			
			for (j = xp; j <= n; j = j + xp) #1#1 {
				j1 = j + i;
				j2 = j1 + xp2;
				dr1 = ar[j1];
				dr2 = ar[j2];
				di1 = ai[j1];
				di2 = ai[j2];
				tr = dr1 - dr2;
				ti = di1 - di2;
				ar[j1] = dr1 + dr2;
				ai[j1] = di1 + di2;
				ar[j2] = tr * wr - ti * wi;
				ai[j2] = ti * wr + tr * wi;
			}
		}
	}
	
	/*  Digit Reverse Counter  */
	j1 = n / 2;		// 4
	j2 = n - 1;		// 7
	j = 1;

	for (i = 1; i <= j2; i = i + 1) #7#7 {
		if (i < j) {
			tr = ar[j-1];
			ti = ai[j-1];
			ar[j-1] = ar[i-1];
			ai[j-1] = ai[i-1];
			ar[i-1] = tr;
			ai[i-1] = ti;
		}
		
		k = j1;
		while (k < j && k > 0) #0#2 {
			j = j - k;
			k = k / 2;	// If k = 1/2 = 0 and j > 0, then the while condition cannot terminate.
		}
		j = j + k;
	}
	
	return 0;
}

double sin(double rad) {
	double app;
	double diff;
	int inc;
	
	while (rad > PI_twice) #0#0 {
		rad = rad - PI_twice;
	}
	
	while (rad < -PI_twice) #0#0 {
		rad = rad + PI_twice;
	}
	
										// rad  = -PI_twice                  to  PI_twice
	diff = (rad * (-(rad*rad))) / 6.0;	// diff =  PI_twice^3/6              to -PI_twice^3/6
    app = rad + diff;					// app  = (-PI_twice + PI_twice^3/6) to (PI_twice - PI_twice^3/6)
    inc = 2;
	
	while ((diff >= 0.00001 && diff >= 0) || (-diff >= 0.00001 && diff < 0)) #0#11 {
		diff = (diff * (-(rad*rad))) / ((2.0 * inc) * (2.0 * inc + 1.0));
		app = app + diff;
		inc = inc + 1;
	}
	
	return(app);
}

