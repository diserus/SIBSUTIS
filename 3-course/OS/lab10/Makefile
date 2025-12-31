all:
	gcc -lpthread -std=c11 peterson_basic.c -o peterson
	gcc -lpthread -std=c11 peterson_atomic_relaxed.c -o relaxd
	gcc -lpthread -std=c11 peterson_atomic_seq_cst.c -o seq_cst
	gcc -lpthread -std=c11 peterson_atomic_acq_rel.c -o acq_rel

