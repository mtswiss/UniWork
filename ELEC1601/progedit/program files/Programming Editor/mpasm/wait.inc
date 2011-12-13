; WAIT procedure: Delay for 0.1s (100ms)

wait:	movwf   WC3             ; move W to counter 3

wait3:	movlw	d'100'		; 100 x 1ms = 100ms loop
	movwf   WC2             ; move W to counter 2

wait2:  movlw   d'100'          ; 100 x 10us = 1ms loop
        movwf   WC1             ; move W to counter 2

wait1:  clrwdt                  ; 10us delay loop
        goto    $+1             ; 2us delay
        goto    $+1             ; 2us delay
        goto    $+1             ; 2us delay
        decfsz  WC1,F           ; skip if zero
        goto    wait1           ; loop 1

        decfsz  WC2,F           ; skip if zero
        goto    wait2           ; loop 2

        decfsz  WC3,F           ; skip if zero
        goto    wait3           ; loop 2

        return		        ; return

; PAUSE procedure: Delay for 1ms

pause:	movwf   WC2             ; move W to counter 2

pse2:   movlw   d'100'          ; 100 x 10us = 1ms loop
        movwf   WC1             ; move W to counter 2

pse1:   clrwdt                  ; 10us delay loop
        goto    $+1             ; 2us delay
        goto    $+1             ; 2us delay
        goto    $+1             ; 2us delay
        decfsz  WC1,F           ; skip if zero
        goto    pse1            ; loop 1
 
        decfsz  WC2,F           ; skip if zero
        goto    pse2            ; loop 2

        return		        ; return

