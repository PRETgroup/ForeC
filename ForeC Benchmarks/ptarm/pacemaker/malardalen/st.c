/* Statistics Program:
 * This program computes for two arrays of numbers the sum, the
 * mean, the variance, and standard deviation.  It then determines the
 * correlation coefficient between the two arrays.
 */


int main () {
	int MAX = 1000;
	int i;
	int Seed = 0;
	double ArrayA[1000], ArrayB[1000];
	double MeanA, MeanB, VarA, VarB, StddevA, StddevB;
	double SumA, SumB;
	double numerator;
	double diffsA, diffsB;
	double Aterm, Bterm, Aterm_sqrt, Bterm_sqrt;
	double Coef;

	// Initialise.
	for (i=0; i < MAX; i = i + 1) {
		ArrayA[i] = i + (((Seed * 133) + 81) % 8095)/8095.0;
		ArrayB[i] = i + (((Seed * 133) + 81) % 8095)/8095.0;
	}
	
	// Mean.
	SumA = 0;
	SumB = 0;
	for (i = 0; i < MAX; i = i + 1) {
		SumA = SumA + ArrayA[i];
		SumB = SumB + ArrayB[i];
	}
	MeanA = SumA / MAX;
	MeanB = SumB / MAX;
	
	// Standard deviation.
	diffsA = 0.0;
	diffsB = 0.0;
	for (i = 0; i < MAX; i = i + 1) {
		diffsA = diffsA + (ArrayA[i] - MeanA) * (ArrayA[i] - MeanA);
		diffsB = diffsB + (ArrayB[i] - MeanB) * (ArrayB[i] - MeanB);
	}
	VarA = diffsA/MAX;
	VarB = diffsB/MAX;
	
	StddevA = VarA;
	StddevB = VarB;
	for (i = 0; i < 10; i = i + 1) {
		StddevA = 0.5 * (StddevA + VarA/StddevA);
		StddevB = 0.5 * (StddevB + VarB/StddevB);
	}
		
	// Correlation.
	numerator = 0.0;
	Aterm = Bterm = 0.0;
	for (i = 0; i < MAX; i = i + 1) {
		numerator = numerator + (ArrayA[i] - MeanA) * (ArrayB[i] - MeanB);
		Aterm = Aterm + (ArrayA[i] - MeanA) * (ArrayA[i] - MeanA);
		Bterm = Bterm + (ArrayB[i] - MeanB) * (ArrayB[i] - MeanB);
	}
	
	for (i = 0; i < 10; i = i + 1) {
		Aterm_sqrt = 0.5 * (Aterm_sqrt + Aterm/Aterm_sqrt);
		Bterm_sqrt = 0.5 * (Bterm_sqrt + Bterm/Bterm_sqrt);
	}
	
	Coef = numerator / (Aterm_sqrt * Bterm_sqrt);
}
