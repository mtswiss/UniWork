; Robot Arm Test Program
; Program for internal PICAXE-28 

; Output 7 = motor back
; Output 6 = motor forward
; Output 5 = not used
; Output 4 = waist
; Output 3 = shoulder
; Output 2 = elbow
; Output 1 = wrist
; Output 0 = gripper

; Input 0 = push switch 0
; Input 1 = push switch 1

; wait for switch push

main:	if pin0 = 1 then loop
	if pin1 = 1 then loop
	goto main

; switch each motor forward and back
loop: 	let pins = %01000001
	pause 2000
	let pins = %10000001
	pause 2000
	let pins = %01000010
	pause 2000
	let pins = %10000010
	pause 2000
	let pins = %01000100
	pause 2000
	let pins = %10000100
	pause 2000
	let pins = %01001000
	pause 2000
	let pins = %10001000
	pause 2000
	let pins = %01010000
	pause 2000
	let pins = %10010000
	pause 2000
	let pins = %00000000
	goto loop


