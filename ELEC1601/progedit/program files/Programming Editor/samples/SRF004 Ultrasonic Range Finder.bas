' Sample program for SRF04 ultrasonic range finder
' Note the NC pin on the module must be connected to 0V
' or else the SRF04 will not work with PICAXE.

symbol trig = 3            ' Define output pin for Trigger pulse
symbol echo  = 6           ' Define input pin for Echo pulse
symbol range = w1          ' 16 bit variable for range (remember w1 = b2 + b3)

main:
    pulsout trig,2         ' produces about 20uS pulse (must be minimum of 10uS)
    pulsin echo,1,range    ' measures the range in 10uS steps
    pause 10               ' SRF04 mandatory 10mS recharge period after ranging completes

' now convert range to cm (divide by 6.2) or inches (divide by 14.9)
' as picaxe cannot use fractions, multiply by 10 then divide by full number
' e.g. range x 10 then / 62 is the same as range / 6.2

    let range = range * 10 / 62 ' multiply by 10 then divide by 62 
    debug range			' display range via debug command

    goto main           	' and around forever




