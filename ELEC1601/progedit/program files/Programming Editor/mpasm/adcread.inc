; sub procedure to read a byte from the serial ADC module
; the data byte is returned in both register B4 and W

; first make sure the DDR (TRISB) is correct
adcread:
	bsf	STATUS,RP0	; move to memory page 1
	bcf	TRISB,0		; make sure ADC_CS is output
	bcf	TRISB,1		; make sure ADC_CLK is output
	bsf	TRISB,2		; make sure ADC_D_I is input
	bcf	STATUS,RP0	; back to page 0

; make sure clock is low and CS is selected
	bcf	PORTB,1		; make sure clock line is low
	nop 			; nop to separate two bcf's
	bcf	PORTB,0		; select ADC device

; send the initial wakeup pulse to the ADC
	bsf	PORTB,1		; send an ADC clock pulse
	movlw	d'1'		; of length 1ms
	call	pause
	bcf	PORTB,1

; clear the data byte and set counter to 8 bits
	clrf	B4		; clear data byte B4 to zero
	movlw	d'8'		; set counter to 8 bits
	movwf	COUNTER

; shift the 8 bits of data into B4
; this is done by setting/clearing the carry bit
; depending on whether the ADC signal is high/low
; the carry bit is then rotated left into B4
adclp:	bsf	PORTB,1		; send an ADC clock pulse
	movlw	d'1'		; of length 1ms
	call	pause
	bcf	PORTB,1

	bcf	STATUS,C	; clear carry bit
	btfsc	PORTB,2		; test ADC signal
	bsf	STATUS,C	; high so set carry high
	rlf	B4,F		; rotate new bit into data byte

	decfsz	COUNTER,F	; all bits done?
	goto	adclp		; no so loop

; disable CS and return
	bsf	PORTB,0		; disable ADC
	movfw	B4		; put data value into W
	return			; return from sub

