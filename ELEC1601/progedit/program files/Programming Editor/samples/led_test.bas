'led_test.bas
'Generate pretty LED patterns.
'Author unknown, modified by CPS May '98.

'This is the test program downloaded to
'Revolution's Stamp Controller to test the
'pcb for correct operation before despatch.

'Load some pretty patterns into EEPROM memory.
eeprom ($0,$0F,$F0,$3C, $C3,$18,$3C,$7E, $FF,$E7,$C3,$81)
eeprom ($0,$03,$06,$0C, $30,$60,$C0,$60, $30,$0C,$06,$03, 0)

'Define symbols
symbol i = b0
symbol j = b1
symbol k = b2

'Define time delays
symbol const1 = 50
symbol const2 = 150

'Main program

'The let dirs= line is only required with the Stamp
'For PICAXE systems comment out the line using a '

let dirs = %11111111            'all pins output!


Loop:   For i = 0 To 7          'bar climbing
           pause const1
           high i
        Next i

        For i = 0 To 7          'and disappearing...
           pause const1
           low i
        Next i

        Let j = 1               'single light moving up
        For i = 0 To 7
           Let pins = j
           pause const1
           Let j = j + j
        Next i

        Let j = 64              'and rolling back
        GoSub roll_back
        
        Let j = 3               'bar climbing up
        For i = 0 To 6
           Let pins = j
           pause const1
           j=j+j|1
        Next i

        j = 127                 'and rolling back
        GoSub roll_back

        For i = 0 To 24         'some more effects
           read i, j
           Let pins = j
           pause const2
        Next i

        goto loop               'loop forever!

'sub-procedures
roll_back:
        For i = 0 To 6
           Let pins = j
           pause const1
           j = j / 2
        Next i
        Return












