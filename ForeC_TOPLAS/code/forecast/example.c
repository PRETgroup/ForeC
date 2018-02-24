/* thread:main:start */
main: {
	int x=0;
	@/* statement:abort:1:scope:start */ {@
		x=1;
		@@/* statement:pause:1:start */@@
		@@main.pc=&&pause1; goto *main.next->pc;@@
		@@pause1:;@@
		@@/* statement:pause:1:end */@@
		@/* statement:abort:1:start */@
		@if (x > 1) { goto abort1; }@
		@/* statement:abort:1:end */@
		@@@/* statement:par:1:tA:tB:start */@@@
		@@@mainState=1; main.pc=&&join1;@@@
		@@@goto *main.next->pc; join1:;@@@
		@@@/* statement:par:1:end */@@@
	@} abort1:;@
	@/* statement:abort:1:scope:end */@
	exit(0);
}
/* thread:main:end */
...