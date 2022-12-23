/*Thread t1 */
t1:
asm("nop");/*asm("#@PRET_Thread start t1");*/
{
	// line:15
	apple++;
	// line:16
	EOT_abort__10
	EOT__abort__10:;
	asm("nop");/*asm("#@PRET_EOT end");*/
	t1_death:
	KILL_t1
}
/*Thread t2 */
t2:
asm("nop");/*asm("#@PRET_Thread start t2");*/
{
	// line:20
	apple++;
	// line:21
	EOT_abort__13
	EOT__abort__13:;
	asm("nop");/*asm("#@PRET_EOT end");*/
	// line:22
	apple++;
	// line:23
	EOT_abort__15
	EOT__abort__15:;
	asm("nop");/*asm("#@PRET_EOT end");*/
	t2_death:
	KILL_t2
}

