all:
	gcc writer.c -o writer
	gcc reader.c -o reader

	gcc shm_writer.c -lrt -o shm_writer
	gcc shm_reader.c -lrt -o shm_reader

	gcc sem_reader.c -lpthread -lrt -o sem_reader
	gcc sem_writer.c -lpthread -lrt -o sem_writer
