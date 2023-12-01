.name "N 2"
.comment "Un deuxieme champion a peine meilleur que le precedent"

debut:
	st r1, 31
	ld	%0, r6 
	st r2, -12
	ld	%0, r6
	fork %:bouclelive
	zjmp %:writer

bouclelive: live %1
	zjmp %:bouclelive   

writer:
	ld %1, r5
	st r5, 436
	ld -19, r2
	ld 10 ,  r3
	ld 5, r4
	st r3, 385 
	st r4, 390
	st r2, 410
	st r5, 1251
	st r2, 1250
	ld %0, r6
	zjmp %100
	live %42
