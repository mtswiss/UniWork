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

	list      p=16F819             ; define PICmicro type
        #include <p16F819.inc>         ; variable definitions
	errorlevel -302		       ; suppress warning 302

; **************************************
; ***** (2) Setup PICmicro config. *****
; **************************************

;This default line uses external ceramic resonator
	__CONFIG	_CP_ALL & _WDT_ON & _XT_OSC & _PWRTE_ON & _BODEN_OFF & _LVP_OFF& _MCLR_ON & _WRT_ENABLE_OFF &_CPD_OFF &_DEBUG_OFF

;uncomment this line instead for internal resonator (provides two extra input pins on PORTA)
;	__CONFIG	_CP_ALL & _WDT_ON & _INTRC_IO & _PWRTE_ON & _BODEN_OFF & _LVP_OFF& _MCLR_ON & _WRT_ENABLE_OFF &_CPD_OFF &_DEBUG_OFF

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
	call	set_clock	; sets internal clock to 4MHz
	clrf	PORTA		; initialise PORTA
	clrf	PORTB		; initialise PORTB
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
	movlw	B'01100000'	; set 4MHz
	bsf	STATUS,RP0	; page 1
	movwf	OSCCON		; into OSCON
	clrf	OSCTUNE		; factory tuned
	bcf	STATUS,RP0	; page 0
	return

; ***************************************
; ***** (6) Start of assembler code *****
; ***************************************

; ***** Initialisation *****
init:					; (initialisation goes here)

				; these four lines need for old PIC16F84A programs as
				; they set PORTA to digital rather than default analogue
	bsf	STATUS,RP0	; page 1
	movlw	B'10000110'	; all digital
	movwf	ADCON1		; do it
	bcf	STATUS,RP0	; page 0


; ***** Main program *****
main:					; (main program goes here)




; ******************************
; ***** (7) End of Program *****
; ******************************

	end


