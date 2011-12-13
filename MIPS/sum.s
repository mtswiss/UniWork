# A program to sum a set of values in memory
# Author: Quoc Cam Huynh	
# SID: 309002893
# Input data: table of values
# Return data: sum of values
# Action: Sum values in table


# Data declaration section

.data

print_int: .word 1
read_int: .word 5
print_str: .word 4
out_string: .asciiz "\n Please enter a number between 1 to 10: "
exit_code: .word 10 # code in $v0 to exit a program
table: .word 10, 15, 20, 25, 30, 40, 50, 60, 70, 80 # table of integers
length: .word 10 # size of table
sum: .word 0 # memory location for sum of table

# $a0 is used to address the table
# $a1 holds the counter
# $a2 is used as a temporary to hold a value from the table
# $v0 holds the sum
# Program instruction section

.text

# Start of program instructions

main:

lw $v0, print_str
la $a0, out_string
syscall

lw $v0, read_int
syscall
move $a2, $v0
sw $a2, length

la $a0, table # load address of first item in table into $a0
sub $v0, $v0, $v0 # clear $v0 to be used for sum

lw $a1, length # initialise counter in $a1 to length of table


beg_while:

blez $a1, end_while # exit loop if counter <= 0
lw $a2, 0($a0) # load next value from table
add $v0, $v0, $a2 # add value to sum
add $a0, $a0, 4 # increment address to next value in table (4 bytes)
sub $a1, $a1, 1 # decrement count by 1

b beg_while # return to start of loop

end_while:

sw $v0, sum # save result of calculation in sum
move $a0, $v0
lw $v0, print_int
syscall

exit_main:

lw $v0, exit_code # load code to exit into $v0
syscall # call system to exit program
