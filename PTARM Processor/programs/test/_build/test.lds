
SECTIONS {
	/* Code. */
	. = 0x0;
	.text : { * (.text); }

	/* Data directly after code. */
	.data : { * (.data); }

	bss_start = .;
	.bss : { * (.bss); }
	bss_end = .;
	bss_size = bss_end - bss_start;

	/* Stack limit */
	addr_stack_limit = .;

	/* Start of the stacks */
	addr_stack_start = 0x1ffdc;
	
	/* End of the stacks */
	addr_stack_end = addr_stack_start - 4*0x400;
	
	/* Exception on Expire table */
	eoe_table = 0x1ffe0;
}
