
case 0x0 :
	{
		uint64_t out ;
		out = ( (uint64_t) b + ( (uint64_t) a )  ) ;
		msr &= ~MicroBlaze::MSR_C ;
		if ( (( out & ( (uint64_t) 1 << (uint64_t) 32 )) != 0 )) {
			msr |= MicroBlaze::MSR_C ;
		}
		snprintf ( name , MicroBlaze::NS , "add: r%u = r%u + r%u = 0x%x (carry_out=%u)\n" , rD , rB , rA , (unsigned) out , !! ( msr & MicroBlaze::MSR_C )) ;

		if ( iword == 0 )
		{
			traceFn ( MicroBlaze::ILLEGAL_INST , MicroBlaze::ip ( pc )) ;
			valid = 0 ;
		}
		*MicroBlaze::getD ( ) = (unsigned) out ;
	}
	break ;

case 0x8 :
	{
		uint64_t out ;
		out = ( (uint64_t) b + ( (uint64_t) a )  ) ;
		msr &= ~MicroBlaze::MSR_C ;
		if ( (( out & ( (uint64_t) 1 << (uint64_t) 32 )) != 0 )) {
			msr |= MicroBlaze::MSR_C ;
		}
		snprintf ( name , MicroBlaze::NS , "add: r%u = 0x%x + r%u = 0x%x (carry_out=%u)\n" , rD , b , rA , (unsigned) out , !! ( msr & MicroBlaze::MSR_C )) ;
		*MicroBlaze::getD ( ) = (unsigned) out ;
	}
	break ;

case 0x2 :
	{
		uint64_t out ;
		carry_in = 0 ;
		if (( msr & MicroBlaze::MSR_C ) != 0 ) carry_in = 1 ;
		out = ( (uint64_t) b + ( (uint64_t) a )  + carry_in ) ;
		msr &= ~MicroBlaze::MSR_C ;
		if ( (( out & ( (uint64_t) 1 << (uint64_t) 32 )) != 0 )) {
			msr |= MicroBlaze::MSR_C ;
		}
		snprintf ( name , MicroBlaze::NS , "addc: r%u = r%u + r%u (carry_in) = 0x%x (carry_out=%u)\n" , rD , rB , rA , (unsigned) out , !! ( msr & MicroBlaze::MSR_C )) ;
		*MicroBlaze::getD ( ) = (unsigned) out ;
	}
	break ;

case 0xa :
	{
		uint64_t out ;
		carry_in = 0 ;
		if (( msr & MicroBlaze::MSR_C ) != 0 ) carry_in = 1 ;
		out = ( (uint64_t) b + ( (uint64_t) a )  + carry_in ) ;
		msr &= ~MicroBlaze::MSR_C ;
		if ( (( out & ( (uint64_t) 1 << (uint64_t) 32 )) != 0 )) {
			msr |= MicroBlaze::MSR_C ;
		}
		snprintf ( name , MicroBlaze::NS , "addc: r%u = 0x%x + r%u (carry_in) = 0x%x (carry_out=%u)\n" , rD , b , rA , (unsigned) out , !! ( msr & MicroBlaze::MSR_C )) ;
		*MicroBlaze::getD ( ) = (unsigned) out ;
	}
	break ;

case 0x4 :
	{
		unsigned out ;
		out = (  b + (  a )  ) ;
		snprintf ( name , MicroBlaze::NS , "addk: r%u = r%u + r%u = 0x%x\n" , rD , rB , rA , (unsigned) out ) ;
		*MicroBlaze::getD ( ) = (unsigned) out ;
	}
	break ;

case 0xc :
	{
		unsigned out ;
		out = (  b + (  a )  ) ;
		snprintf ( name , MicroBlaze::NS , "addk: r%u = 0x%x + r%u = 0x%x\n" , rD , b , rA , (unsigned) out ) ;
		*MicroBlaze::getD ( ) = (unsigned) out ;
	}
	break ;

case 0x6 :
	{
		unsigned out ;
		carry_in = 0 ;
		if (( msr & MicroBlaze::MSR_C ) != 0 ) carry_in = 1 ;
		out = (  b + (  a )  + carry_in ) ;
		snprintf ( name , MicroBlaze::NS , "addkc: r%u = r%u + r%u (carry_in) = 0x%x\n" , rD , rB , rA , (unsigned) out ) ;
		*MicroBlaze::getD ( ) = (unsigned) out ;
	}
	break ;

case 0xe :
	{
		unsigned out ;
		carry_in = 0 ;
		if (( msr & MicroBlaze::MSR_C ) != 0 ) carry_in = 1 ;
		out = (  b + (  a )  + carry_in ) ;
		snprintf ( name , MicroBlaze::NS , "addkc: r%u = 0x%x + r%u (carry_in) = 0x%x\n" , rD , b , rA , (unsigned) out ) ;
		*MicroBlaze::getD ( ) = (unsigned) out ;
	}
	break ;

case 0x21 :
	{
		unsigned out ;
		out = (  b & (  a )  ) ;
		snprintf ( name , MicroBlaze::NS , "and: r%u = r%u & r%u = 0x%x\n" , rD , rB , rA , (unsigned) out ) ;
		*MicroBlaze::getD ( ) = (unsigned) out ;
	}
	break ;

case 0x29 :
	{
		unsigned out ;
		out = (  b & (  a )  ) ;
		snprintf ( name , MicroBlaze::NS , "and: r%u = 0x%x & r%u = 0x%x\n" , rD , b , rA , (unsigned) out ) ;
		*MicroBlaze::getD ( ) = (unsigned) out ;
	}
	break ;

case 0x23 :
	{
		unsigned out ;
		out = (  ( ~ b ) & (  a )  ) ;
		snprintf ( name , MicroBlaze::NS , "andn: r%u = r%u & r%u = 0x%x\n" , rD , rB , rA , (unsigned) out ) ;

		if ( iword & 0x400 )
		{
			out = ( a != b ) ;
			snprintf ( name , MicroBlaze::NS , "pcmpne: r%u != r%u = %u\n" , rA , rB , out ) ;
		}
		*MicroBlaze::getD ( ) = (unsigned) out ;
	}
	break ;

case 0x2b :
	{
		unsigned out ;
		out = (  ( ~ b ) & (  a )  ) ;
		snprintf ( name , MicroBlaze::NS , "andn: r%u = 0x%x & r%u = 0x%x\n" , rD , b , rA , (unsigned) out ) ;
		*MicroBlaze::getD ( ) = (unsigned) out ;
	}
	break ;

case 0x22 :
	{
		unsigned out ;
		out = (  b ^ (  a )  ) ;
		snprintf ( name , MicroBlaze::NS , "xor: r%u = r%u ^ r%u = 0x%x\n" , rD , rB , rA , (unsigned) out ) ;

		if ( iword & 0x400 )
		{
			out = ( a == b ) ;
			snprintf ( name , MicroBlaze::NS , "pcmpeq: r%u == r%u = %u\n" , rA , rB , out ) ;
		}
		*MicroBlaze::getD ( ) = (unsigned) out ;
	}
	break ;

case 0x2a :
	{
		unsigned out ;
		out = (  b ^ (  a )  ) ;
		snprintf ( name , MicroBlaze::NS , "xor: r%u = 0x%x ^ r%u = 0x%x\n" , rD , b , rA , (unsigned) out ) ;
		*MicroBlaze::getD ( ) = (unsigned) out ;
	}
	break ;

case 0x20 :
	{
		unsigned out ;
		out = (  b | (  a )  ) ;
		snprintf ( name , MicroBlaze::NS , "or: r%u = r%u | r%u = 0x%x\n" , rD , rB , rA , (unsigned) out ) ;

		if ( iword & 0x400 ) {
			temp = 0 ;
			if ((( a >> 0 ) & 0xff ) == (( b >> 0 ) & 0xff )) { temp = 4 ; }
			if ((( a >> 8 ) & 0xff ) == (( b >> 8 ) & 0xff )) { temp = 3 ; }
			if ((( a >> 16 ) & 0xff ) == (( b >> 16 ) & 0xff )) { temp = 2 ; }
			if ((( a >> 24 ) & 0xff ) == (( b >> 24 ) & 0xff )) { temp = 1 ; }

			snprintf ( name , MicroBlaze::NS , "pcmpbf: r%u versus r%u = %u\n" , rA , rB , temp ) ;
			out = temp ;
		}
		{
			unsigned cmd = iword & 0x7ff ;

			if (( iword & ~0x7ff ) == MicroBlaze::MB_NOP )
			{
				if ( cmd != 0 )
				{
					snprintf ( name , MicroBlaze::NS , "cmd: 0x%x\n" , iword & 0x7ff ) ;
					traceFn ( MicroBlaze::SIM_CMD , MicroBlaze::ip ( cmd )) ;
				} else {
					snprintf ( name , MicroBlaze::NS , "nop:\n" ) ;
				}
			}
		}
		*MicroBlaze::getD ( ) = (unsigned) out ;
	}
	break ;

case 0x28 :
	{
		unsigned out ;
		out = (  b | (  a )  ) ;
		snprintf ( name , MicroBlaze::NS , "or: r%u = 0x%x | r%u = 0x%x\n" , rD , b , rA , (unsigned) out ) ;
		{
			unsigned cmd = iword & 0x7ff ;

			if (( iword & ~0x7ff ) == MicroBlaze::MB_NOP )
			{
				if ( cmd != 0 )
				{
					snprintf ( name , MicroBlaze::NS , "cmd: 0x%x\n" , iword & 0x7ff ) ;
					traceFn ( MicroBlaze::SIM_CMD , MicroBlaze::ip ( cmd )) ;
				} else {
					snprintf ( name , MicroBlaze::NS , "nop:\n" ) ;
				}
			}
		}
		*MicroBlaze::getD ( ) = (unsigned) out ;
	}
	break ;

case 0x1 :
	{
		uint64_t out ;
		out = ( (uint64_t) b + ( ~ ( (uint64_t) a ))  + 1 ) ;
		msr &= ~MicroBlaze::MSR_C ;
		if ( ! (( out & ( (uint64_t) 1 << (uint64_t) 32 )) != 0 )) {
			msr |= MicroBlaze::MSR_C ;
		}
		snprintf ( name , MicroBlaze::NS , "rsub: r%u = r%u - r%u = 0x%x (carry_out=%u)\n" , rD , rB , rA , (unsigned) out , !! ( msr & MicroBlaze::MSR_C )) ;
		*MicroBlaze::getD ( ) = (unsigned) out ;
	}
	break ;

case 0x9 :
	{
		uint64_t out ;
		out = ( (uint64_t) b + ( ~ ( (uint64_t) a ))  + 1 ) ;
		msr &= ~MicroBlaze::MSR_C ;
		if ( ! (( out & ( (uint64_t) 1 << (uint64_t) 32 )) != 0 )) {
			msr |= MicroBlaze::MSR_C ;
		}
		snprintf ( name , MicroBlaze::NS , "rsub: r%u = 0x%x - r%u = 0x%x (carry_out=%u)\n" , rD , b , rA , (unsigned) out , !! ( msr & MicroBlaze::MSR_C )) ;
		*MicroBlaze::getD ( ) = (unsigned) out ;
	}
	break ;

case 0x3 :
	{
		uint64_t out ;
		carry_in = 0 ;
		if (( msr & MicroBlaze::MSR_C ) != 0 ) carry_in = 1 ;
		out = ( (uint64_t) b + ( ~ ( (uint64_t) a ))  + carry_in ) ;
		msr &= ~MicroBlaze::MSR_C ;
		if ( ! (( out & ( (uint64_t) 1 << (uint64_t) 32 )) != 0 )) {
			msr |= MicroBlaze::MSR_C ;
		}
		snprintf ( name , MicroBlaze::NS , "rsubc: r%u = r%u - r%u (carry_in) = 0x%x (carry_out=%u)\n" , rD , rB , rA , (unsigned) out , !! ( msr & MicroBlaze::MSR_C )) ;
		*MicroBlaze::getD ( ) = (unsigned) out ;
	}
	break ;

case 0xb :
	{
		uint64_t out ;
		carry_in = 0 ;
		if (( msr & MicroBlaze::MSR_C ) != 0 ) carry_in = 1 ;
		out = ( (uint64_t) b + ( ~ ( (uint64_t) a ))  + carry_in ) ;
		msr &= ~MicroBlaze::MSR_C ;
		if ( ! (( out & ( (uint64_t) 1 << (uint64_t) 32 )) != 0 )) {
			msr |= MicroBlaze::MSR_C ;
		}
		snprintf ( name , MicroBlaze::NS , "rsubc: r%u = 0x%x - r%u (carry_in) = 0x%x (carry_out=%u)\n" , rD , b , rA , (unsigned) out , !! ( msr & MicroBlaze::MSR_C )) ;
		*MicroBlaze::getD ( ) = (unsigned) out ;
	}
	break ;

case 0x5 :
	{
		unsigned out ;
		out = (  b + ( ~ (  a ))  + 1 ) ;
		snprintf ( name , MicroBlaze::NS , "rsubk: r%u = r%u - r%u = 0x%x\n" , rD , rB , rA , (unsigned) out ) ;

		switch ( iword & 3 )
		{
			case 1 : /* cmp */
				out &= ~ ( 1 << 31 ) ;
				if ( (int) a > (int) b ) out |= 1 << 31 ;
				snprintf ( name , MicroBlaze::NS , "cmp: r%u = r%u > r%u = %u\n" , rD , rA , rB , ((unsigned) out ) >> 31 ) ;
				break ;
			case 3 : /* cmpu */
				memcpy ( name , "cmpu " , 5 ) ;
				out &= ~ ( 1 << 31 ) ;
				if ( a > b ) out |= 1 << 31 ;
				snprintf ( name , MicroBlaze::NS , "cmpu: r%u = r%u > r%u = %u\n" , rD , rA , rB , ((unsigned) out ) >> 31 ) ;
				break ;
			default :/* rsubk */
				break ;
		}
		*MicroBlaze::getD ( ) = (unsigned) out ;
	}
	break ;

case 0xd :
	{
		unsigned out ;
		out = (  b + ( ~ (  a ))  + 1 ) ;
		snprintf ( name , MicroBlaze::NS , "rsubk: r%u = 0x%x - r%u = 0x%x\n" , rD , b , rA , (unsigned) out ) ;
		*MicroBlaze::getD ( ) = (unsigned) out ;
	}
	break ;

case 0x7 :
	{
		unsigned out ;
		carry_in = 0 ;
		if (( msr & MicroBlaze::MSR_C ) != 0 ) carry_in = 1 ;
		out = (  b + ( ~ (  a ))  + carry_in ) ;
		snprintf ( name , MicroBlaze::NS , "rsubkc: r%u = r%u - r%u (carry_in) = 0x%x\n" , rD , rB , rA , (unsigned) out ) ;
		*MicroBlaze::getD ( ) = (unsigned) out ;
	}
	break ;

case 0xf :
	{
		unsigned out ;
		carry_in = 0 ;
		if (( msr & MicroBlaze::MSR_C ) != 0 ) carry_in = 1 ;
		out = (  b + ( ~ (  a ))  + carry_in ) ;
		snprintf ( name , MicroBlaze::NS , "rsubkc: r%u = 0x%x - r%u (carry_in) = 0x%x\n" , rD , b , rA , (unsigned) out ) ;
		*MicroBlaze::getD ( ) = (unsigned) out ;
	}
	break ;

case 0x10 :
	if ( isMultiCycleInstruction == false ) {
		// Perform the stall but maintain the state of the core.
		isMultiCycleInstruction = true;
		remainingLatency = 2 ;
		snprintf ( name , MicroBlaze::NS , "mul (stall)\n" ) ;
	} else if ( remainingLatency > 1 ) {
		remainingLatency--;
		snprintf ( name , MicroBlaze::NS , "(stall)\n" ) ;
	} else {
		// Execute the instruction.
		isMultiCycleInstruction = false;
		unsigned out ;
		out = (  b * (  a )  ) ;
		snprintf ( name , MicroBlaze::NS , "mul: r%u = r%u * r%u = 0x%x\n" , rD , rB , rA , (unsigned) out ) ;
		*MicroBlaze::getD ( ) = (unsigned) out ;
	}
	break ;

case 0x18 :
	if ( isMultiCycleInstruction == false ) {
		// Perform the stall but maintain the state of the core.
		isMultiCycleInstruction = true;
		remainingLatency = 2 ;
		snprintf ( name , MicroBlaze::NS , "mul (stall)\n" ) ;
	} else if ( remainingLatency > 1 ) {
		remainingLatency--;
		snprintf ( name , MicroBlaze::NS , "(stall)\n" ) ;
	} else {
		// Execute the instruction.
		isMultiCycleInstruction = false;
		unsigned out ;
		out = (  b * (  a )  ) ;
		snprintf ( name , MicroBlaze::NS , "mul: r%u = 0x%x * r%u = 0x%x\n" , rD , b , rA , (unsigned) out ) ;
		*MicroBlaze::getD ( ) = (unsigned) out ;
	}
	break ;

case 0x36 :
case 0x3e : /* LSU: sw */
	if ( isMultiCycleInstruction == false ) {
		// Perform the stall but maintain the state of the core.
		isMultiCycleInstruction = true;
		remainingLatency = 1 ;
		ea = a + b ;
		snprintf ( name , MicroBlaze::NS , "sw (stall): [ 0x%x ] = r%u \n" , ea , rD ) ;
	} else if ( busIsBusyFn ( this , ea , 0) ) {
		snprintf ( name , MicroBlaze::NS , "sw (stall)\n" ) ;
	} else {
		// Execute the instruction.
		isMultiCycleInstruction = false;
		if ( ea & 3 ) traceFn ( MicroBlaze::ALIGN , MicroBlaze::ip ( ea )) ;
		traceFn ( MicroBlaze::STORE , MicroBlaze::ip ( ea )) ;
		storeFn ( this, ea , *MicroBlaze::getD () , 4 ) ;
		snprintf ( name , MicroBlaze::NS , "sw: [ 0x%x ] = r%u = 0x%x\n" , ea , rD , *MicroBlaze::getD () ) ;
	}
	break;

case 0x35 :
case 0x3d : /* LSU: sh */
	if ( isMultiCycleInstruction == false ) {
		// Perform the stall but maintain the state of the core.
		isMultiCycleInstruction = true;
		remainingLatency = 1 ;
		ea = a + b ;
		snprintf ( name , MicroBlaze::NS , "sh (stall): [ 0x%x ] = r%u \n" , ea , rD ) ;
	} else if ( busIsBusyFn ( this , ea , 0) ) {
		snprintf ( name , MicroBlaze::NS , "sh (stall)\n" ) ;
	} else {
		// Execute the instruction.
		isMultiCycleInstruction = false;
		if ( ea & 1 ) traceFn ( MicroBlaze::ALIGN , MicroBlaze::ip ( ea )) ;
		traceFn ( MicroBlaze::STORE , MicroBlaze::ip ( ea )) ;
		storeFn ( this, ea , *MicroBlaze::getD () , 2 ) ;
		snprintf ( name , MicroBlaze::NS , "sh: [ 0x%x ] = r%u = 0x%x\n" , ea , rD , *MicroBlaze::getD () ) ;
	}
	break;

case 0x34 :
case 0x3c : /* LSU: sb */
	if ( isMultiCycleInstruction == false ) {
		// Perform the stall but maintain the state of the core.
		isMultiCycleInstruction = true;
		remainingLatency = 1 ;
		ea = a + b ;
		snprintf ( name , MicroBlaze::NS , "sb (stall): [ 0x%x ] = r%u \n" , ea , rD ) ;
	} else if ( busIsBusyFn ( this , ea , 0) ) {
		snprintf ( name , MicroBlaze::NS , "sb (stall)\n" ) ;
	} else {
		// Execute the instruction.
		isMultiCycleInstruction = false;
		traceFn ( MicroBlaze::STORE , MicroBlaze::ip ( ea )) ;
		storeFn ( this, ea , *MicroBlaze::getD () , 1 ) ;
		snprintf ( name , MicroBlaze::NS , "sb: [ 0x%x ] = r%u = 0x%x\n" , ea , rD , *MicroBlaze::getD () ) ;
	}
	break;

case 0x32 :
case 0x3a : /* LSU: lwu */
	if ( isMultiCycleInstruction == false ) {
		// Perform the stall but maintain the state of the core.
		isMultiCycleInstruction = true;
		remainingLatency = 1 ;
		ea = a + b ;
		snprintf ( name , MicroBlaze::NS , "lwu (stall): r%u = [ 0x%x ] \n" , rD , ea ) ;
	} else if ( busIsBusyFn ( this , ea , 1) ) {
		snprintf ( name , MicroBlaze::NS , "lwu (stall)\n" ) ;
	} else {
		// Execute the instruction.
		isMultiCycleInstruction = false;
		if ( ea & 3 ) traceFn ( MicroBlaze::ALIGN , MicroBlaze::ip ( ea )) ;
		traceFn ( MicroBlaze::LOAD , MicroBlaze::ip ( ea )) ;
		*MicroBlaze::getD ( ) = loadFn ( this, ea , 4 ) ;
		snprintf ( name , MicroBlaze::NS , "lwu: r%u = [ 0x%x ] = 0x%x\n" , rD , ea , *MicroBlaze::getD () ) ;
	}
	break;

case 0x31 :
case 0x39 : /* LSU: lhu */
	if ( isMultiCycleInstruction == false ) {
		// Perform the stall but maintain the state of the core.
		isMultiCycleInstruction = true;
		remainingLatency = 1 ;
		ea = a + b ;
		snprintf ( name , MicroBlaze::NS , "lhu (stall): r%u = [ 0x%x ] \n" , rD , ea ) ;
	} else if ( busIsBusyFn ( this , ea , 1) ) {
		snprintf ( name , MicroBlaze::NS , "lhu (stall)\n" ) ;
	} else {
		// Execute the instruction.
		isMultiCycleInstruction = false;
		if ( ea & 1 ) traceFn ( MicroBlaze::ALIGN , MicroBlaze::ip ( ea )) ;
		traceFn ( MicroBlaze::LOAD , MicroBlaze::ip ( ea )) ;
		*MicroBlaze::getD ( ) = loadFn ( this, ea , 2 ) ;
		snprintf ( name , MicroBlaze::NS , "lhu: r%u = [ 0x%x ] = 0x%x\n" , rD , ea , *MicroBlaze::getD () ) ;
	}
	break;

case 0x30 :
case 0x38 : /* LSU: lbu */
	if ( isMultiCycleInstruction == false ) {
		// Perform the stall but maintain the state of the core.
		isMultiCycleInstruction = true;
		remainingLatency = 1 ;
		ea = a + b ;
		snprintf ( name , MicroBlaze::NS , "lbu (stall): r%u = [ 0x%x ] \n" , rD , ea ) ;
	} else if ( busIsBusyFn ( this , ea , 1) ) {
		snprintf ( name , MicroBlaze::NS , "lbu (stall)\n" ) ;
	} else {
		// Execute the instruction.
		isMultiCycleInstruction = false;
		traceFn ( MicroBlaze::LOAD , MicroBlaze::ip ( ea )) ;
		*MicroBlaze::getD ( ) = loadFn ( this, ea , 1 ) ;
		snprintf ( name , MicroBlaze::NS , "lbu: r%u = [ 0x%x ] = 0x%x\n" , rD , ea , *MicroBlaze::getD () ) ;
	}
	break;

case 0x11 :
	switch ( iword & ( 3 << 9 )) {
		case 0x0 : /* Barrel: bsrl */
			if ( isMultiCycleInstruction == false ) {
				// Perform the stall but maintain the state of the core.
				isMultiCycleInstruction = true;
				remainingLatency = 1 ;
				snprintf ( name , MicroBlaze::NS , "bsrl (stall)\n" ) ;
			} else if ( remainingLatency > 1 ) {
				remainingLatency--;
				snprintf ( name , MicroBlaze::NS , "(stall)\n" ) ;
			} else {
				// Execute the instruction.
				isMultiCycleInstruction = false;
				b = b & 0x1f ;
				*MicroBlaze::getD ( ) = a >> b;
				snprintf ( name , MicroBlaze::NS , "bsrl: r%u = r%u >> r%u = 0x%x\n" , rD , rA , rB , *MicroBlaze::getD () ) ;
			}
			break ;
		case 0x200 : /* Barrel: bsra */
			if ( isMultiCycleInstruction == false ) {
				// Perform the stall but maintain the state of the core.
				isMultiCycleInstruction = true;
				remainingLatency = 1 ;
				snprintf ( name , MicroBlaze::NS , "bsra (stall)\n" ) ;
			} else if ( remainingLatency > 1 ) {
				remainingLatency--;
				snprintf ( name , MicroBlaze::NS , "(stall)\n" ) ;
			} else {
				// Execute the instruction.
				isMultiCycleInstruction = false;
				b = b & 0x1f ;
				*MicroBlaze::getD ( ) = ((int) a) >> b;
				snprintf ( name , MicroBlaze::NS , "bsra: r%u = r%u >> r%u = 0x%x\n" , rD , rA , rB , *MicroBlaze::getD () ) ;
			}
			break ;
		case 0x400 : /* Barrel: bsll */
			if ( isMultiCycleInstruction == false ) {
				// Perform the stall but maintain the state of the core.
				isMultiCycleInstruction = true;
				remainingLatency = 1 ;
				snprintf ( name , MicroBlaze::NS , "bsll (stall)\n" ) ;
			} else if ( remainingLatency > 1 ) {
				remainingLatency--;
				snprintf ( name , MicroBlaze::NS , "(stall)\n" ) ;
			} else {
				// Execute the instruction.
				isMultiCycleInstruction = false;
				b = b & 0x1f ;
				*MicroBlaze::getD ( ) = a << b;
				snprintf ( name , MicroBlaze::NS , "bsll: r%u = r%u << r%u = 0x%x\n" , rD , rA , rB , *MicroBlaze::getD () ) ;
			}
			break ;
		default : *MicroBlaze::getD ( ) = 0 ; break ;
	}
	break;

case 0x19 :
	switch ( iword & ( 3 << 9 )) {
		case 0x0 : /* Barrel: bsrl */
			if ( isMultiCycleInstruction == false ) {
				// Perform the stall but maintain the state of the core.
				isMultiCycleInstruction = true;
				remainingLatency = 1 ;
				snprintf ( name , MicroBlaze::NS , "bsrl (stall)\n" ) ;
			} else if ( remainingLatency > 1 ) {
				remainingLatency--;
				snprintf ( name , MicroBlaze::NS , "(stall)\n" ) ;
			} else {
				// Execute the instruction.
				isMultiCycleInstruction = false;
				b = b & 0x1f ;
				*MicroBlaze::getD ( ) = a >> b;
				snprintf ( name , MicroBlaze::NS , "bsrl: r%u = r%u >> 0x%x = 0x%x\n" , rD , rA , b , *MicroBlaze::getD () ) ;
			}
			break ;
		case 0x200 : /* Barrel: bsra */
			if ( isMultiCycleInstruction == false ) {
				// Perform the stall but maintain the state of the core.
				isMultiCycleInstruction = true;
				remainingLatency = 1 ;
				snprintf ( name , MicroBlaze::NS , "bsra (stall)\n" ) ;
			} else if ( remainingLatency > 1 ) {
				remainingLatency--;
				snprintf ( name , MicroBlaze::NS , "(stall)\n" ) ;
			} else {
				// Execute the instruction.
				isMultiCycleInstruction = false;
				b = b & 0x1f ;
				*MicroBlaze::getD ( ) = ((int) a) >> b;
				snprintf ( name , MicroBlaze::NS , "bsra: r%u = r%u >> 0x%x = 0x%x\n" , rD , rA , b , *MicroBlaze::getD () ) ;
			}
			break ;
		case 0x400 : /* Barrel: bsll */
			if ( isMultiCycleInstruction == false ) {
				// Perform the stall but maintain the state of the core.
				isMultiCycleInstruction = true;
				remainingLatency = 1 ;
				snprintf ( name , MicroBlaze::NS , "bsll (stall)\n" ) ;
			} else if ( remainingLatency > 1 ) {
				remainingLatency--;
				snprintf ( name , MicroBlaze::NS , "(stall)\n" ) ;
			} else {
				// Execute the instruction.
				isMultiCycleInstruction = false;
				b = b & 0x1f ;
				*MicroBlaze::getD ( ) = a << b;
				snprintf ( name , MicroBlaze::NS , "bsll: r%u = r%u << 0x%x = 0x%x\n" , rD , rA , b , *MicroBlaze::getD () ) ;
			}
			break ;
		default : *MicroBlaze::getD ( ) = 0 ; break ;
	}
	break;

case 0x16 :
	switch ( iword & 0x780 ) {
		case 0x0 : /* Float: fadd */
			if ( isMultiCycleInstruction == false ) {
				// Perform the stall but maintain the state of the core.
				isMultiCycleInstruction = true;
				remainingLatency = 5 ;
				fa.i = a;
				fb.i = b;
				snprintf ( name , MicroBlaze::NS , "fadd (stall)\n" ) ;
			} else if ( remainingLatency > 1 ) {
				remainingLatency--;
				snprintf ( name , MicroBlaze::NS , "(stall)\n" ) ;
			} else {
				// Execute the instruction.
				isMultiCycleInstruction = false;
				fd.f = fb.f + fa.f ;
				*MicroBlaze::getD ( ) = fd.i;
				snprintf ( name , MicroBlaze::NS , "fadd: fd.f = %f + %f = %f\n", fb.f, fa.f, fd.f ) ;
			}
			break ;
		case 0x80 : /* Float: frsub */
			if ( isMultiCycleInstruction == false ) {
				// Perform the stall but maintain the state of the core.
				isMultiCycleInstruction = true;
				remainingLatency = 5 ;
				fa.i = a;
				fb.i = b;
				snprintf ( name , MicroBlaze::NS , "frsub (stall)\n" ) ;
			} else if ( remainingLatency > 1 ) {
				remainingLatency--;
				snprintf ( name , MicroBlaze::NS , "(stall)\n" ) ;
			} else {
				// Execute the instruction.
				isMultiCycleInstruction = false;
				fd.f = fb.f - fa.f ;
				*MicroBlaze::getD ( ) = fd.i;
				snprintf ( name , MicroBlaze::NS , "frsub: fd.f = %f - %f = %f\n", fb.f, fa.f, fd.f ) ;
			}
			break ;
		case 0x100 : /* Float: fmul */
			if ( isMultiCycleInstruction == false ) {
				// Perform the stall but maintain the state of the core.
				isMultiCycleInstruction = true;
				remainingLatency = 5 ;
				fa.i = a;
				fb.i = b;
				snprintf ( name , MicroBlaze::NS , "fmul (stall)\n" ) ;
			} else if ( remainingLatency > 1 ) {
				remainingLatency--;
				snprintf ( name , MicroBlaze::NS , "(stall)\n" ) ;
			} else {
				// Execute the instruction.
				isMultiCycleInstruction = false;
				fd.f = fb.f * fa.f ;
				*MicroBlaze::getD ( ) = fd.i;
				snprintf ( name , MicroBlaze::NS , "fmul: fd.f = %f * %f = %f\n", fb.f, fa.f, fd.f ) ;
			}
			break ;
		case 0x180 : /* Float: fdiv */
			if ( isMultiCycleInstruction == false ) {
				// Perform the stall but maintain the state of the core.
				isMultiCycleInstruction = true;
				remainingLatency = 29 ;
				fa.i = a;
				fb.i = b;
				snprintf ( name , MicroBlaze::NS , "fdiv (stall)\n" ) ;
			} else if ( remainingLatency > 1 ) {
				remainingLatency--;
				snprintf ( name , MicroBlaze::NS , "(stall)\n" ) ;
			} else {
				// Execute the instruction.
				isMultiCycleInstruction = false;
				fd.f = fb.f / fa.f ;
				*MicroBlaze::getD ( ) = fd.i;
				snprintf ( name , MicroBlaze::NS , "fdiv: fd.f = %f / %f = %f\n", fb.f, fa.f, fd.f ) ;
			}
			break ;
		case 0x200 : /* Float: cmp */
			switch ( (iword >> 4) & 0x7 ) {
				case 0x0 : /* Float: fcmp.un */
					if ( isMultiCycleInstruction == false ) {
						// Perform the stall but maintain the state of the core.
						isMultiCycleInstruction = true;
						remainingLatency = 2 ;
						fa.i = a;
						fb.i = b;
						snprintf ( name , MicroBlaze::NS , "fcmp.un (stall)\n" ) ;
					} else if ( remainingLatency > 1 ) {
						remainingLatency--;
						snprintf ( name , MicroBlaze::NS , "(stall)\n" ) ;
					} else {
						// Execute the instruction.
						isMultiCycleInstruction = false;
						temp = 0;
						*MicroBlaze::getD ( ) = temp ;
						snprintf ( name , MicroBlaze::NS , "fcmp.un: fd.f = %f  %f = %u\n", fb.f, fa.f, temp ) ;
					}
					break ;
				case 0x1 : /* Float: fcmp.lt */
					if ( isMultiCycleInstruction == false ) {
						// Perform the stall but maintain the state of the core.
						isMultiCycleInstruction = true;
						remainingLatency = 2 ;
						fa.i = a;
						fb.i = b;
						snprintf ( name , MicroBlaze::NS , "fcmp.lt (stall)\n" ) ;
					} else if ( remainingLatency > 1 ) {
						remainingLatency--;
						snprintf ( name , MicroBlaze::NS , "(stall)\n" ) ;
					} else {
						// Execute the instruction.
						isMultiCycleInstruction = false;
						temp = fb.f < fa.f;
						*MicroBlaze::getD ( ) = temp ;
						snprintf ( name , MicroBlaze::NS , "fcmp.lt: fd.f = %f < %f = %u\n", fb.f, fa.f, temp ) ;
					}
					break ;
				case 0x2 : /* Float: fcmp.eq */
					if ( isMultiCycleInstruction == false ) {
						// Perform the stall but maintain the state of the core.
						isMultiCycleInstruction = true;
						remainingLatency = 2 ;
						fa.i = a;
						fb.i = b;
						snprintf ( name , MicroBlaze::NS , "fcmp.eq (stall)\n" ) ;
					} else if ( remainingLatency > 1 ) {
						remainingLatency--;
						snprintf ( name , MicroBlaze::NS , "(stall)\n" ) ;
					} else {
						// Execute the instruction.
						isMultiCycleInstruction = false;
						temp = fb.f == fa.f;
						*MicroBlaze::getD ( ) = temp ;
						snprintf ( name , MicroBlaze::NS , "fcmp.eq: fd.f = %f == %f = %u\n", fb.f, fa.f, temp ) ;
					}
					break ;
				case 0x3 : /* Float: fcmp.le */
					if ( isMultiCycleInstruction == false ) {
						// Perform the stall but maintain the state of the core.
						isMultiCycleInstruction = true;
						remainingLatency = 2 ;
						fa.i = a;
						fb.i = b;
						snprintf ( name , MicroBlaze::NS , "fcmp.le (stall)\n" ) ;
					} else if ( remainingLatency > 1 ) {
						remainingLatency--;
						snprintf ( name , MicroBlaze::NS , "(stall)\n" ) ;
					} else {
						// Execute the instruction.
						isMultiCycleInstruction = false;
						temp = fb.f <= fa.f;
						*MicroBlaze::getD ( ) = temp ;
						snprintf ( name , MicroBlaze::NS , "fcmp.le: fd.f = %f <= %f = %u\n", fb.f, fa.f, temp ) ;
					}
					break ;
				case 0x4 : /* Float: fcmp.gt */
					if ( isMultiCycleInstruction == false ) {
						// Perform the stall but maintain the state of the core.
						isMultiCycleInstruction = true;
						remainingLatency = 2 ;
						fa.i = a;
						fb.i = b;
						snprintf ( name , MicroBlaze::NS , "fcmp.gt (stall)\n" ) ;
					} else if ( remainingLatency > 1 ) {
						remainingLatency--;
						snprintf ( name , MicroBlaze::NS , "(stall)\n" ) ;
					} else {
						// Execute the instruction.
						isMultiCycleInstruction = false;
						temp = fb.f > fa.f;
						*MicroBlaze::getD ( ) = temp ;
						snprintf ( name , MicroBlaze::NS , "fcmp.gt: fd.f = %f > %f = %u\n", fb.f, fa.f, temp ) ;
					}
					break ;
				case 0x5 : /* Float: fcmp.nq */
					if ( isMultiCycleInstruction == false ) {
						// Perform the stall but maintain the state of the core.
						isMultiCycleInstruction = true;
						remainingLatency = 2 ;
						fa.i = a;
						fb.i = b;
						snprintf ( name , MicroBlaze::NS , "fcmp.nq (stall)\n" ) ;
					} else if ( remainingLatency > 1 ) {
						remainingLatency--;
						snprintf ( name , MicroBlaze::NS , "(stall)\n" ) ;
					} else {
						// Execute the instruction.
						isMultiCycleInstruction = false;
						temp = fb.f != fa.f;
						*MicroBlaze::getD ( ) = temp ;
						snprintf ( name , MicroBlaze::NS , "fcmp.nq: fd.f = %f != %f = %u\n", fb.f, fa.f, temp ) ;
					}
					break ;
				case 0x6 : /* Float: fcmp.ge */
					if ( isMultiCycleInstruction == false ) {
						// Perform the stall but maintain the state of the core.
						isMultiCycleInstruction = true;
						remainingLatency = 2 ;
						fa.i = a;
						fb.i = b;
						snprintf ( name , MicroBlaze::NS , "fcmp.ge (stall)\n" ) ;
					} else if ( remainingLatency > 1 ) {
						remainingLatency--;
						snprintf ( name , MicroBlaze::NS , "(stall)\n" ) ;
					} else {
						// Execute the instruction.
						isMultiCycleInstruction = false;
						temp = fb.f >= fa.f;
						*MicroBlaze::getD ( ) = temp ;
						snprintf ( name , MicroBlaze::NS , "fcmp.ge: fd.f = %f >= %f = %u\n", fb.f, fa.f, temp ) ;
					}
					break ;
				default : *MicroBlaze::getD ( ) = 0 ; break ;
			}
			break;
		case 0x280 : /* Float: flt */
			if ( isMultiCycleInstruction == false ) {
				// Perform the stall but maintain the state of the core.
				isMultiCycleInstruction = true;
				remainingLatency = 5 ;
				fa.i = a;
				fb.i = b;
				snprintf ( name , MicroBlaze::NS , "flt (stall)\n" ) ;
			} else if ( remainingLatency > 1 ) {
				remainingLatency--;
				snprintf ( name , MicroBlaze::NS , "(stall)\n" ) ;
			} else {
				// Execute the instruction.
				isMultiCycleInstruction = false;
				fd.f = fa.i;
				*MicroBlaze::getD ( ) = fd.i;
			}
			break ;
		case 0x300 : /* Float: fint */
			if ( isMultiCycleInstruction == false ) {
				// Perform the stall but maintain the state of the core.
				isMultiCycleInstruction = true;
				remainingLatency = 6 ;
				fa.i = a;
				fb.i = b;
				snprintf ( name , MicroBlaze::NS , "fint (stall)\n" ) ;
			} else if ( remainingLatency > 1 ) {
				remainingLatency--;
				snprintf ( name , MicroBlaze::NS , "(stall)\n" ) ;
			} else {
				// Execute the instruction.
				isMultiCycleInstruction = false;
				fd.i = fa.f;
				*MicroBlaze::getD ( ) = fd.i;
			}
			break ;
		case 0x380 : /* Float: fsqrt */
			if ( isMultiCycleInstruction == false ) {
				// Perform the stall but maintain the state of the core.
				isMultiCycleInstruction = true;
				remainingLatency = 28 ;
				fa.i = a;
				fb.i = b;
				snprintf ( name , MicroBlaze::NS , "fsqrt (stall)\n" ) ;
			} else if ( remainingLatency > 1 ) {
				remainingLatency--;
				snprintf ( name , MicroBlaze::NS , "(stall)\n" ) ;
			} else {
				// Execute the instruction.
				isMultiCycleInstruction = false;
				fd.f = sqrt(fa.f);
				*MicroBlaze::getD ( ) = fd.i;
			}
			break ;
		default : *MicroBlaze::getD ( ) = 0; break ;
	}
	break;
