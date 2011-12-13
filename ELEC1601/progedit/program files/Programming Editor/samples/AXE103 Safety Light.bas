
; Test Program for AXE103 Safety Light
; Just Flashes LEDs on and off in different patterns!
; CPS 2002

init:
' make pins 0-2 outputs
	low 0
	low 1
	low 2

main:	
' all on - all off
	for b1 = 1 to 20
	   let pins = %00000111
	   pause 100
	   let pins = %00000000
	   pause 100
	next b1

' in circles
	for b1 = 1 to 20
	   let pins = %00000001
	   pause 100
	   let pins = %00000010
	   pause 100
	   let pins = %00000100
  	   pause 100
	next b1

' flashing in circles
	for b1 = 1 to 20
	   let pins = %00000001
	   pause 100
	   let pins = %00000000
	   pause 100
	   let pins = %00000010
	   pause 100
	   let pins = %00000000
	   pause 100
	   let pins = %00000100
	   pause 100
	   let pins = %00000000
	   pause 100
	   let pins = %00000010
	   pause 100
	   let pins = %00000000
	   pause 100
	next b1

'loop back to start
	goto main

