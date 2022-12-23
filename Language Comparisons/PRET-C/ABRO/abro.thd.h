/*Thread abro */
abro:
asm("nop");/*asm("#@PRET_Thread start abro");*/
{
	// line:32
	while (1)
	{
		// line:33
		O = 0;
		// line:34
		EOT_abro__14
		EOT__abro__14:;
		asm("nop");/*asm("#@PRET_EOT end");*/
		// line:35
		//strong abort
		PRET_S_ABORT__abro__15_START
		{
			// line:36
			//PAR ID: 16 Threads: [tA, tB] 
			PAR16
			abro_join16:;
			asm("nop");/*asm("#@PRET_PAR end");*/
			// line:37
			O = 1;
			// line:38
			while (1)
			{
				// line:38
				EOT_abro__19
				EOT__abro__19:;
				asm("nop");/*asm("#@PRET_EOT end");*/
				// line:38
				O = 0;
				PRET_END_OF_LOOP__abro__18:;/*asm("nop");*/ //force asm comment to stay put

			}
		}
		//when strong abort{...} when(R == 1);
		PRET_S_ABORT__abro__15_END
		PRET_END_OF_LOOP__abro__12:;/*asm("nop");*/ //force asm comment to stay put

	}
	abro_death:
	KILL_abro
}
/*Thread tA */
tA:
asm("nop");/*asm("#@PRET_Thread start tA");*/
{
	// line:44
	//strong abort
	PRET_S_ABORT__abro__22_START
	{
		// line:44
		while (1)
		{
			// line:44
			EOT_abro__24
			EOT__abro__24:;
			asm("nop");/*asm("#@PRET_EOT end");*/
			PRET_END_OF_LOOP__abro__23:;/*asm("nop");*/ //force asm comment to stay put

		}
	}
	//when strong abort{...} when(A == 1);
	PRET_S_ABORT__abro__22_END
	tA_death:
	KILL_tA
}
/*Thread tB */
tB:
asm("nop");/*asm("#@PRET_Thread start tB");*/
{
	// line:48
	//strong abort
	PRET_S_ABORT__abro__26_START
	{
		// line:48
		while (1)
		{
			// line:48
			EOT_abro__28
			EOT__abro__28:;
			asm("nop");/*asm("#@PRET_EOT end");*/
			PRET_END_OF_LOOP__abro__27:;/*asm("nop");*/ //force asm comment to stay put

		}
	}
	//when strong abort{...} when(B == 1);
	PRET_S_ABORT__abro__26_END
	tB_death:
	KILL_tB
}
/*Thread Inputs */
Inputs:
asm("nop");/*asm("#@PRET_Thread start Inputs");*/
{
	// line:52
	while (1)
	{
		// line:53
		A = I[tick][0];
		// line:54
		B = I[tick][1];
		// line:55
		R = I[tick][2];
		// line:56
		EOT_abro__34
		EOT__abro__34:;
		asm("nop");/*asm("#@PRET_EOT end");*/
		PRET_END_OF_LOOP__abro__30:;/*asm("nop");*/ //force asm comment to stay put

	}
	Inputs_death:
	KILL_Inputs
}
/*Thread Results */
Results:
asm("nop");/*asm("#@PRET_Thread start Results");*/
{
	// line:61
	while (1)
	{
		// line:62
		printf("Tick %d: %d %d %d  %d\n", tick, A, B, R, O);
		// line:63
		tick++;
		// line:64
		EOT_abro__39
		EOT__abro__39:;
		asm("nop");/*asm("#@PRET_EOT end");*/
		PRET_END_OF_LOOP__abro__36:;/*asm("nop");*/ //force asm comment to stay put

	}
	Results_death:
	KILL_Results
}

