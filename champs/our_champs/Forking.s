 .name "Forking"
.comment "What a forking duck"

jmp: 
    st r1, 6
    live %1
    st r16, -10
    ld %0, r16
    zjmp %:deb
    live %1
    live %1
    live %1
    live %1
    live %1
    live %1
    live %1
    live %1
    live %1
    live %1
    live %1
    live %1
    live %1
    live %1
    live %1
    live %1
    live %1
    live %1
    live %1
    live %1
    live %1
    live %1
    live %1
    live %1
    live %1
    live %1
    live %1
    live %1
    live %1
    live %1
    live %1
    live %1
    live %1
    live %1
    live %1
    live %1
    live %1
    live %1
    live %1
    live %1
    live %1
    live %1
    live %1
    live %1
    live %1
    live %1
    live %1
    live %1
    live %1
    live %1
    live %1
    live %1
    live %1
    live %1
    live %1
    live %1
    live %1
    live %1
    live %1
    live %1
    live %1
    live %1
    live %1
    live %1
    live %1
    live %1
    live %1
    live %1
    live %1
    live %1
    live %1
    live %1
    live %1
    live %1
    live %1

deb: st r1, 72
    st r16, -4
    ld %0, r16
    live %1
    fork %:setup_2

setup:  #850 cycles
    ld %0x0b640600, r6
    ld %0, r16
    fork %:boucle
    ld %0, r16 
    ld %0, r16
    ld %0, r16
    live %1
    zjmp %:attack

boucle: live %42
    zjmp %:boucle

setup_3: #atteint apres 805 cycles dans setup_2, 45 cycles
    ld -7, r6
    ld %8, r3
    live %1 
    ld %0, r16
    live %1
    zjmp %:attack

setup_2:                    #850 cycles
    ld %0x0c030001, r6
    ld %0, r16
    fork %:setup_3
    ld %4, r3
    ld %0, r16
    ld %0, r16
    ld %0, r16
    ld %0, r16 
    ld %0, r16
    live %1
    ld %0, r16

attack:
    sti r6, %6, r3