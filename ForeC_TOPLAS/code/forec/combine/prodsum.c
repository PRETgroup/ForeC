typedef struct {int prod; int sum;} ProdSum;

ProdSum prodsum(ProdSum th1,ProdSum th2) {
	ProdSum res = {.prod=(th1.prod*th2.prod), .sum=(th1.sum+th2.sum)};
	return res;
}
// th1={.prod=2,.sum=2} and th2={.prod=5,.sum=5}
// prodsum(th1,th2)={.prod=10,.sum=7}