#include <elf.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <shared_object.so>\n", argv[0]);
        return 1;
    }

    const char *elfFile = argv[1];
    FILE *file = fopen(elfFile, "rb");
    if (!file) {
        perror("fopen");
        return 1;
    }

    Elf64_Ehdr ehdr;
    fread(&ehdr, sizeof(ehdr), 1, file);


    if (memcmp(ehdr.e_ident, ELFMAG, SELFMAG) != 0) {
        fprintf(stderr, "Not an ELF file\n");
        fclose(file);
        return 1;
    }

    if (ehdr.e_ident[EI_CLASS] != ELFCLASS64) {
        fprintf(stderr, "Only 64-bit ELF supported\n");
        fclose(file);
        return 1;
    }

    fseek(file, ehdr.e_shoff, SEEK_SET);
    Elf64_Shdr *shdrs = malloc(ehdr.e_shnum * sizeof(Elf64_Shdr));
    if (!shdrs) {
        perror("malloc");
        fclose(file);
        return 1;
    }

    for (int i = 0; i < ehdr.e_shnum; ++i) {
        fread(&shdrs[i], sizeof(Elf64_Shdr), 1, file);
    }

    if (ehdr.e_shstrndx >= ehdr.e_shnum) {
        fprintf(stderr, "Invalid e_shstrndx\n");
        free(shdrs);
        fclose(file);
        return 1;
    }

    Elf64_Shdr *shstrtab = &shdrs[ehdr.e_shstrndx];
    char *shstrtab_data = malloc(shstrtab->sh_size);
    fseek(file, shstrtab->sh_offset, SEEK_SET);
    fread(shstrtab_data, 1, shstrtab->sh_size, file);

    Elf64_Shdr *dynsym = NULL, *dynstr = NULL;
    for (int i = 0; i < ehdr.e_shnum; ++i) {
        const char *name = shstrtab_data + shdrs[i].sh_name;
        if (strcmp(name, ".dynsym") == 0) {
            dynsym = &shdrs[i];
        } else if (strcmp(name, ".dynstr") == 0) {
            dynstr = &shdrs[i];
        }
    }

    if (!dynsym || !dynstr) {
        fprintf(stderr, "Missing .dynsym or .dynstr section\n");
        free(shstrtab_data);
        free(shdrs);
        fclose(file);
        return 1;
    }

    char *dynstr_data = malloc(dynstr->sh_size);
    fseek(file, dynstr->sh_offset, SEEK_SET);
    fread(dynstr_data, 1, dynstr->sh_size, file);

    size_t sym_count = dynsym->sh_size / sizeof(Elf64_Sym);
    Elf64_Sym sym;
    printf("Exported functions:\n");
    for (size_t i = 0; i < sym_count; ++i) {
        fseek(file, dynsym->sh_offset + i * sizeof(Elf64_Sym), SEEK_SET);
        fread(&sym, sizeof(Elf64_Sym), 1, file);

        if (ELF64_ST_TYPE(sym.st_info) == STT_FUNC &&
            (ELF64_ST_BIND(sym.st_info) == STB_GLOBAL ||
             ELF64_ST_BIND(sym.st_info) == STB_WEAK) &&
            sym.st_shndx != SHN_UNDEF) {
            const char *name = dynstr_data + sym.st_name;
            if (name[0] != '\0') {
                printf("%s\n", name);
            }
        }
    }

    free(dynstr_data);
    free(shstrtab_data);
    free(shdrs);
    fclose(file);
    return 0;
}