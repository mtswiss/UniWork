{\rtf1\ansi\ansicpg1252\deff0\deflang1033{\fonttbl{\f0\fnil\fcharset0 Courier;}}
\viewkind4\uc1\pard\f0\fs17 init: 
\par \tab pause 100 ' motor controller start up pause
\par 
\par set_speed:
\par \tab let pins = %00110000 \tab ' set left speed
\par \tab pulsout 6,75 \tab\tab ' send a pulse of length in \lquote speed\rquote 
\par \tab pause 10 \tab\tab\tab ' short delay
\par \tab let pins = %11000000 \tab ' set right speed
\par \tab pulsout 4,75 \tab\tab ' send
\par \tab pause 10
\par \tab 
\par 
\par main:
\par \tab if input1 is on then go_f \tab ' forward
\par \tab if input2 is on then go_l \tab ' left
\par \tab if input6 is on then go_r \tab ' right
\par \tab goto go_s \tab\tab\tab\tab ' stop as no line nearby
\par 
\par go_f: 
\par \tab let pins = %10100000 \tab\tab ' go forward
\par \tab goto main
\par go_l: 
\par \tab let pins = %00100000 \tab\tab ' go left
\par \tab goto main
\par go_r:
\par \tab let pins = %10000000 \tab\tab ' go right
\par \tab goto main
\par go_s:
\par \tab let pins = %00000000 \tab\tab ' stop - not over line!
\par \tab goto main
\par }
 