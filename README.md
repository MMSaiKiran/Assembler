# Assembler for the HACK Assembly Language

Predefined Symbols and their Values:
Symbol          Value
R0        |        0
R1        |        1
R2        |        2
R3        |        3
:
R15       |        15
SCREEN    |        16748
KEYBOARD  |        0




HACK Assembly Language has two type of instructions:
A Instructions and C Instructions


It has three 16 bit registers D,M,A for Data, Memory and Address respectively.
'M' will access the Memory element at the address 'A' ie M[A].

Each instruction is of 16 bits length of which the MSB(Most Significant Bit) illustrates weather the instruction is an A type or the C type. If MSB is '0' then it is a A instruction else it is a C instruction.

A Instructions:
--- Written using: @variable_name,@value
--- This will set the value of address register (A) to the specified value or to the value given.
--- Example: @loop,@2678
--- A = value of loop, A = 2678 respectively

C Instructions:


