'================================================================================
' Copyright © Micromega Corporation 2004. All rights reserved
'
' File: uM-FPU.bas
'
' This file contains a program template that provides all of the definitions
' and support code for interfacing the uM-FPU floating point coprocessor with
' the PICAXE. It can be used as a template for new programs, or the
' necessary parts can be copied to an existing program. Unused routines can
' be deleted to save space, but it is recommended that the uM-FPU definitions
' be copied as a complete block. In order to reduce memory requirements, some
' routines fall through to the code that follows it.  All of these cases are
' clearly commented. When deleting unused routines, or copying routines to
' another program be sure to check if any following code is required.
'
' @author Cam Thompson, Micromega Corporation
' @version V0.1 - July 5, 2004
' changes:
'   V0.1 - July 5, 2004
'	- original version
'
'================================================================================

'================================================================================
'==================== uM-FPU PICAXE definitions (V0.1) ==========================
'================================================================================

'-------------------- uM-FPU pin definitions ------------------------------------

symbol	FPU_CLOCK 	= output7	'um-FPU clock pin		
symbol	FPU_DATAOUT = output6	'uM-FPU data output
symbol	FPU_DATAIN 	= input6	'uM-FPU data input

'-------------------- uM-FPU variables ------------------------------------------

symbol	opcode	= w6		'(b13,b12) opcode
symbol	dataWord	= w6		'(b13,b12) data word
symbol	highByte	= b13		'high byte of dataWord
symbol	dataByte	= b12		'low byte of dataWord
symbol	format	= b12		'format (same as dataByte)
symbol	status	= b12		'status (same as dataByte)
symbol	reg		= b11		'register
symbol	bitcnt	= b10		'bit counter

'-------------------- uM-FPU status bits ----------------------------------------

symbol	IS_ZERO	= 0x81	'positive zero
symbol	IS_NZERO	= 0x83	'negative zero
symbol	IS_NEGATIVE	= 0x82	'negative
symbol	IS_NAN	= 0x84	'NaN (Not-a-Number)
symbol	IS_PINF	= 0x88	'positive infinity
symbol	IS_NINF	= 0x8A	'negative infinity

'-------------------- uM-FPU opcodes --------------------------------------------

symbol	SELECTA	= 0x00	'select A register
symbol	SELECTB	= 0x10	'select B register
symbol	WRITEA	= 0x20	'write to register and select A
symbol	WRITEB	= 0x30	'write to register and select B
symbol	GET		= 0x40	'read from register
symbol	SET		= 0x50	'A = REG

symbol	FADD		= 0x60	'A = A + REG (float)
symbol	FSUB		= 0x70	'A = A - REG (float)
symbol	FMUL		= 0x80	'A = A * REG (float)
symbol	FDIV		= 0x90	'A = A / REG (float)

symbol	LADD		= 0xA0	'A = A + REG (long)
symbol	LSUB		= 0xB0	'A = A - REG (long)
symbol	LMUL		= 0xC0	'A = A * REG (long)
symbol	LDIV		= 0xD0	'A = A / REG (long)

symbol	SQRT		= 0xE0	'A = sqrt(A)	
symbol	LOG		= 0xE1	'A = ln(A)
symbol	LOG10		= 0xE2	'A = log(A)
symbol	EXP		= 0xE3	'A = e ** A
symbol	EXP10		= 0xE4	'A = 10 ** A
symbol	SIN		= 0xE5	'A = sin(A) radians
symbol	COS		= 0xE6	'A = cos(A) radians
symbol	TAN		= 0xE7	'A = tan(A) radians
symbol	FLOOR		= 0xE8	'A = nearest integer <= A
symbol	CEIL		= 0xE9	'A = nearest integer >= A
symbol	ROUND		= 0xEA	'A = nearest integer to A
symbol	NEGATE	= 0xEB	'A = -A
symbol	ABS		= 0xEC	'A = |A|
symbol	INV		= 0xED	'A = 1 / A
symbol	DEGREES	= 0xEE	'A = A / (PI / 180) radians to degrees
symbol	RADIANS	= 0xEF	'A = A * (PI / 180) degreees to radians
symbol	SYNC		= 0xF0	'synchronization
symbol	FLOAT		= 0xF1	'float register 0 and store in register A
symbol	FIX		= 0xF2	'copy register A to register 0 and fix
symbol	FCOMPARE	= 0xF3	'compare A and B
symbol	LOADBYTE	= 0xF4	'write signed byte to register 0, convert to float
symbol	LOADUBYTE	= 0xF5	'write unsigned byte to register 0, convert to float
symbol	LOADWORD	= 0xF6	'write signed word to register 0, convert to float
symbol	LOADUWORD	= 0xF7	'write unsigned word to register 0, convert to float
symbol	READSTR	= 0xF8	'read zero terminated string
symbol	ATOF		= 0xF9	'convert ASCII to float, store in A register
symbol	FTOA		= 0xFA	'convert float to ASCII
symbol	ATOL		= 0xFB	'convert ASCII to long, store in A register
symbol	LTOA		= 0xFC	'convert long to ASCII
symbol	FSTATUS	= 0xFD	'get the status of A register
symbol	XOP		= 0xFE	'extended opcode
symbol	VERSION	= 0xFF	'return 8-bit version number
symbol	FUNC0		= 0xFE00	'user functions 0-15
symbol	LWRITEA	= 0xFEA0	'write long to register and select A
symbol	LWRITEB	= 0xFEB0	'write long to register and select B
symbol	LREAD		= 0xFEC0	'read long from register
symbol	LUDIV		= 0xFED0	'A = A / REG (unsigned long)
symbol	POWER		= 0xFEE0	'A = A ** B
symbol	ROOT		= 0xFEE1	'A = the Bth root of A
symbol	FMIN		= 0xFEE2	'A = minimum of A and B
symbol	FMAX		= 0xFEE3	'A = maximum of A and B
symbol	FRACTION	= 0xFEE4	'load register 0 with the fractional part of A
symbol	ASIN		= 0xFEE5	'A = asin(A) radians
symbol	ACOS		= 0xFEE6	'A = acos(A) radians
symbol	ATAN		= 0xFEE7	'A = atan(A) radians
symbol	ATAN2		= 0xFEE8	'A = atan(A/B)
symbol	LCOMPARE	= 0xFEE9	'long compare A and B
symbol	LUCOMPARE	= 0xFEEA	'unsigned long compare A and B
symbol	LSTATUS	= 0xFEEB	'long status
symbol	LNEGATE	= 0xFEEC	'A = -A (long)
symbol	LABS		= 0xFEED	'A = |A| (long)
symbol	LEFT		= 0xFEEE	'right parenthesis
symbol	RIGHT		= 0xFEEF	'left parenthesis
symbol	LOADZERO	= 0xFEF0	'load register 0 with zero
symbol	LOADONE	= 0xFEF1	'load register 0 with 1.0
symbol	LOADE		= 0xFEF2	'load register 0 with e
symbol	LOADPI	= 0xFEF3	'load register 0 with pi
symbol	LONGBYTE	= 0xFEF4	'write signed byte to register 0, convert to long
symbol	LONGUBYTE	= 0xFEF5	'write unsigned byte to register 0, convert to long
symbol	LONGWORD	= 0xFEF6	'write signed word to register 0, convert to long
symbol	LONGUWORD	= 0xFEF7	'write unsigned word to register 0, convert to long
symbol	IEEEMODE	= 0xFEF8	'set IEEE mode (default)
symbol	PICMODE	= 0xFEF9	'set PIC mode
symbol	BREAK		= 0xFEFB	'debug breakpoint
symbol	TRACEOFF	= 0xFEFC	'turn debug trace off
symbol	TRACEON	= 0xFEFD	'turn debug trace on
symbol	TRACESTR	= 0xFEFE	'send debug string to trace buffer
symbol	CHECKSUM	= 0xFEFF	'calculate code checksum

'==================== end of uM-FPU definitions =================================

'================================================================================
'==================== main routine ==============================================
'================================================================================

main:
	low FPU_CLOCK		'reset the uM-FPU coprocessor
	low FPU_DATAOUT
	pulsout FPU_CLOCK, 30	'send 300 usec reset pulse
	pause 2			'wait for reset

'  (application code would be inserted here)

  end          'end of program

'================================================================================
'==================== uM-FPU PICAXE support routines (V0.1) =====================
'================================================================================

print_long:
	dataByte = 0			'print free format long value

print_longFormat:
	highByte = LTOA			'print formatted long value
	gosub fpu_command
	goto fpu_getStr

print_float:
	dataByte = 0			'print free format float value

print_floatFormat:
	highByte = FTOA			'print formatted float value
	gosub fpu_command			'send conversion command
	'(falls through to fpu_getStr)

fpu_getStr:
	opcode = READSTR			'send read string command
	gosub fpu_command

fpu_getStr2:
	gosub fpu_getByte			'read next character
	if dataByte <> 0 then fpu_getStr3
	return				'if zero, then exit

fpu_getStr3:
	sertxd(dataByte)			'display character to terminal
	goto fpu_getStr2			'get next character

fpu_command:
	'check for opcodes then need register value
	if opcode <= LDIV then fpu_command2
	if opcode >= LWRITEA and opcode <= LUDIV then fpu_command2

	' check for opcodes that set B register to zero
	if opcode >= LOADBYTE and opcode <= LOADUWORD then fpu_command3
	if opcode >= RIGHT and opcode <= LONGUWORD then fpu_command3
	if opcode = FLOAT or opcode = FIX then fpu_command3
	if opcode = ATOF or opcode = ATOL then fpu_command3
	if opcode = FRACTION then fpu_command3
	goto fpu_command4			'send command

fpu_command2:
	dataByte = dataByte + reg	'add register value to opcode
	goto fpu_command4			'send command

fpu_command3:
	reg = 0				'set register variable to register 0

fpu_command4:
	if FPU_DATAIN = 1 then fpu_command4	'wait until uM-FPU is ready

	if highByte = 0 then fpu_sendByte	'send 8 or 16 bit opcode
	'(falls though to fpu_sendWord)

fpu_sendWord:
	for bitcnt = 1 to 8		'write high byte of word to FPU_DATA (MSB first)
	  low FPU_DATAOUT
	  if highByte < 128 then fpu_sendWord2
	  high FPU_DATAOUT

fpu_sendWord2:
	  pulsout FPU_CLOCK, 1		'pulse clock for 10us
	  highByte = highByte * 2	'shift variable left
	next bitcnt
	'(falls through to send low byte)

fpu_sendByte:
	for bitcnt = 1 to 8		'write byte to FPU_DATA (MSB first)
	  low FPU_DATAOUT
	  if dataByte < 128 then fpu_sendByte2
	  high FPU_DATAOUT

fpu_sendByte2:
	  pulsout FPU_CLOCK, 1		'pulse clock for 10us
	  dataByte = dataByte * 2
	next bitcnt
	return

fpu_getWord:		
	for bitcnt = 1 to 8		'read high byte of word from FPU_DATA (MSB first)
	  highByte = highByte * 2
	  if FPU_DATAIN = 0 then fpu_getWord2
	  highByte = highByte + 1

fpu_getWord2:
	  pulsout FPU_CLOCK, 1		'pulse clock for 10us
	next bitcnt
	'(falls through to read low byte)

fpu_getByte:		
	for bitcnt = 1 to 8		'read byte from FPU_DATA (MSB first)
	  dataByte = dataByte * 2
	  if FPU_DATAIN = 0 then fpu_getByte2
	  dataByte = dataByte + 1

fpu_getByte2:
	  pulsout FPU_CLOCK, 1		'pulse clock for 10us
	next bitcnt
	return

'==================== end of uM-FPU PICAXE support routines =====================




