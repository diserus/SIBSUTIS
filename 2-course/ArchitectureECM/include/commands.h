// Ввод вывод
#define NOP 0x00
#define CPUINFO 0x01

// Ввод вывод
#define READ 0x0A
#define WRITE 0x0B

// Загрузка выгрузка
#define LOAD 0x14
#define STORE 0x15

// Арифметика
#define ADD 0x1E
#define SUB 0x1F
#define DIVIDE 0x20
#define MUL 0x21

// Передача управления
#define JUMP 0x28
#define JNEG 0x29
#define JZ 0x2A
#define HALT 0x2B

// Пользовательские комманды
#define NOT 0x33
#define AND 0x34
#define OR 0x35
#define XOR 0x36
#define LOGRC 0x44
#define RCCL 0x45
