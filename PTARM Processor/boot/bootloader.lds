

SECTIONS {
	 . = 0x00000000;
	 .text : {
		   /* Makes sure that the exception vectors 
			  are placed just before the text section. */
		   * (vectors); 
		   /* Text segement containing bootloader code */
		   * (.text); 
	  }
}