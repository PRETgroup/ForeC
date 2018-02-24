typedef struct {int value; int min;} Min; (*\label{code:mins:struct}*)

Min min(Min th1,Min th2) { (*\label{code:mins:combine}*)
	Min res;
	if (th1.value<th2.value) res.min=th1.value; else res.min=th2.value;
	res.value = res.min;
	return res;
}
// th1={.value=2,.min=0} and th2={.value=5,.min=0}
// min(th1,th2)={.value=2,.min=2}