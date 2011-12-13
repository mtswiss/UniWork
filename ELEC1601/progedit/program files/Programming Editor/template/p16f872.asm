; ***************************************
; ***** Assembler Code File Details *****
; ***************************************
;    Filename: 
;    Date: 
;    File Version: 
;    Written by: 
;    Function: 


; ************************************
; ***** (1) Setup PICmicro type. *****
; ************************************

	list      p=16F872             ; define PICmicro type
        #include <p16F872.inc>         ; variable definitions
	errorlevel -302		       ; suppress warning 302

; **************************************
; ***** (2) Setup PICmicro config. *****
; **************************************

;This default line uses external ceramic resonator
	__CONFIG	_CP_OFF & _WDT_ON & _XT_OSC & _PWRTE_ON & _BODEN_OFF & _LVP_OFF


; **********************************
; ***** (3) RAM File Registers *****
; **********************************

	cblock 	h'20'
TEMP		; Temporary Scratchpad
COUNTER		; Counter for loops
WC1		; Counter for wait loop
WC2		; Counter for wait loop
WC3		; Counter for wait loop
B0		; General purpose
B1		; General purpose
B2		; General purpose
B3		; General purpose
B4		; General purpose
		; (any other registers go here)
	endc

; ********************************************
; ***** (4) Assembler code reset vectors *****
; ********************************************

; ***** Reset vector *****
	org	d'00'
	clrf	PORTA		; initialise PORTA
	clrf	PORTB		; initialise PORTB
	clrf	PORTC		; initialise PORTC
	goto	init		; jump to init

; ***** Interrupt vector *****
	org	d'04'
	return			; return

; *************************************
; ***** (5) Common sub-procedures *****
; *************************************

	#include <wait.inc>     ; wait sub-procedure

				; (any other sub-procedures go here)

; ***************************************
; ***** (6) Start of assembler code *****
; ***************************************

; ***** Initialisation *****
init:					; (initialisation goes here)

	bsf     STATUS,RP0      ; move to page 1
	movlw   b'11111111'     ; set all high
	movwf   OPTION_REG      ; set option register
	movwf   TRISA           ; set porta as analogue inputs
	movwf   TRISC           ; set portc as inputs
	clrf    TRISB           ; set portb as outputs
	bcf     STATUS,RP0      ; move to page 0


; ***** Main program *****
main:					; (main program goes here)




; ******************************
; ***** (7) End of Program *****
; ******************************

	end
