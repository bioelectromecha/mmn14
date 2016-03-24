.entry LOOP
.entry LENGTH
.extern L3
.extern W
MAIN: mov K, BLA
add r2,STR
mov **,r4
LOOP: jmp BLA
prn #-5
sub **, r4
inc r0
BLA: mov **,r3
bne MAIN
END: stop
STR: .string "abcdef"
LENGTH: .data 6,-9,15
K: .data 2
