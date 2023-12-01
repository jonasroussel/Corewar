.name "L'avancée"
.comment "On continue a mieux comprendre Corewar"

    st r1, 24
    st r2, -4
    ld %0, r6
    fork %:while
    zjmp %:attack

while: live %1
    zjmp %:while

attack: live %1