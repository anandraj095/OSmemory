#include <stdio.h>
#include <stdlib.h>

int translate_address(int virtual_address, int base, int bound, int* physical_address) {
    if (virtual_address < bound && virtual_address >= 0){
        *physical_address = virtual_address + base;
    return 0;
    }
    return -1;
}

int main() {
    int base = 3000; 
    int bounds = 1000; 
    int virtual_address[4] = {100, 999, 1000, -5};
    int pa;

    int size_of_va = sizeof(virtual_address) / sizeof(virtual_address[0]);

    for (int i = 0; i < size_of_va; i++) {
        if (translate_address(virtual_address[i], base, bounds, &pa) == -1 ) {
            printf("Virtual address out of bound.\n");
        }
        else {
            printf("Physical address is %d of virtual address %d.\n", pa, virtual_address[i]);
        }
    }
    return 0;
}