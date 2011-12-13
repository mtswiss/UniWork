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

	list      p=12F629             ; define PICmicro type
        #include <p12F629.inc>         ; variable definitions
	errorlevel -302		       ; suppress warning 302

; **************************************
; ***** (2) Setup PICmicro config. *****
; **************************************

;This default line uses internal resonator
	__CONFIG	_CP_OFF & _WDT_ON & _INTRC_OSC_NOCLKOUT & _PWRTE_ON & _BODEN_OFF & _MCLRE_OFF


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
	call	set_clock	; sets internal calibration
	clrf	GPIO		; initialise GPIO
	goto	init		; jump to init

; ***** Interrupt vector *****
	org	d'04'
	return			; return

; *************************************
; ***** (5) Common sub-procedures *****
; *************************************

	#include <wait.inc>     ; wait sub-procedure

				; (any other sub-procedures go here)

set_clock:
	call	H'3FF'		; retrieve calibration byte
	bsf     STATUS,RP0      ; move to page 1
	movwf	OSCCAL		; into register
	bcf     STATUS,RP0      ; move to page 0
	return

; ***************************************
; ***** (6) Start of assembler code *****
; ***************************************

; ***** Initialisation *****
init:					; (initialisation goes here)

	movlw	b'00000111'     ; set all GPIO port
	movwf	CMCON           ; to digital inputs


; ***** Main program *****
main:					; (main program goes here)





; ******************************
; ***** (7) End of Program *****
; ******************************

	end



