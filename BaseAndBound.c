#include <stdio.h>

int translate_address(int virtual_address, int base, int bounds, int *physical_address) {
    // 1. Bounds check: the virtual address must be within [0, bounds - 1]
    if (virtual_address >= 0 && virtual_address < bounds) {
        // 2. Translation: If valid, compute physical address
        *physical_address = base + virtual_address;
        return 0;  // success
    }

    // 3. Fault: if outside bounds, segmentation fault
    return -1;  // failure
}

int main() {
    int base_reg = 3000;
    int bounds_reg = 1000;
    int virtual_addresses[] = {100, 999, 1000, -5};
    int num_addresses = sizeof(virtual_addresses) / sizeof(virtual_addresses[0]);

    printf("Base Register  : %d\n", base_reg);
    printf("Bounds Register: %d\n\n", bounds_reg);  

    for (int i = 0; i < num_addresses; i++) {
        int current_va = virtual_addresses[i];
        int pa_result;  // store translated physical address

        if (translate_address(current_va, base_reg, bounds_reg, &pa_result) == 0) {
            printf("Virtual Address %d : Physical Address %d\n", current_va, pa_result);
        } else {
            printf("Virtual Address %d : Segmentation Fault: Address out of bounds\n", current_va);
        }
    }

    return 0;
}
