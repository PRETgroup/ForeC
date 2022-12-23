int abro_vector[20][4] = {
	{0,0,0,0},
	{0,1,0,0},
	{1,0,0,1},
	{0,0,0,0},
	{0,1,0,0},
	{0,0,0,0},
	{0,0,0,0},
	{1,0,0,0},
	{0,1,0,0},
	{0,0,0,0},
	{1,0,0,0},
	{0,0,0,0},
	{0,0,1,0},
	{0,0,1,0},
	{0,0,1,0},
	{0,0,0,0},
	{0,0,0,0},
	{1,1,0,1},
	{0,0,0,0},
	{0,0,0,0}
};

ReactiveInput int a = 0;
ReactiveInput int b = 0;
ReactiveInput int r = 0;
ReactiveOutput int o = 0;

int main() {
	PAR(GT,t0);
}

thread t0  (void) {
	while(1) {
		strong abort {
			PAR(GT,t1,t2);
		} when (r == 1);
		o = 1;
		printf("O\n");
	}
}
thread t1(void) {
	/*while(a != 1) { //await
		EOT;
		printf("await a\n");
	}*/

}

thread t2(void) {
	/*while(b != 1) { //await
		EOT;
		printf("await b\n");
	}*/
}

thread GT (void) {
	static int i = 0;
	while(1) {
		a = abro_vector[i][0];
		b = abro_vector[i][1];
		r = abro_vector[i][2];
		o = abro_vector[i][3];
		i++;
		if (i >= 20) {
			i = 0;
		}
		EOT;
	}
}