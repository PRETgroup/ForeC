/*Thread t0 */
t0:
asm("nop");/*asm("#@PRET_Thread start t0");*/
{
	// line:20
	if (X == 1)
	{
		goto PRET_IF_AFTER__noncausal__16;
	}
	// line:20
	else
	{
		// line:20
		Y = 1;
	}
	PRET_IF_AFTER__noncausal__16:;asm("nop");

	t0_death:
	KILL_t0
}
/*Thread t1 */
t1:
asm("nop");/*asm("#@PRET_Thread start t1");*/
{
	// line:23
	if (Y == 1)
	{
		// line:23
		X = 1;
		goto PRET_IF_AFTER__noncausal__20;
	}
	else{
	}
	PRET_IF_AFTER__noncausal__20:;
	asm("nop");
	t1_death:
	KILL_t1
}

