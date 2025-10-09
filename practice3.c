#include <stdio.h>
#include <stdlib.h>

int page_table[16] = {
    2, 4, 1, 7, 3, 5, 6, 8,   // VPN 0-7
    10, 11, 12, 13, 14, 9, 15, 0 // VPN 8-15
};

unsigned int get_physical_addr (unsigned int virtual_address) {
    
    unsigned int vpn = (virtual_address >> 12) & 0x000F;
    unsigned int offset = virtual_address & 0x0FFF;
    unsigned int pfn = page_table[vpn]; 
    unsigned int pa = (pfn << 12) | offset;

    printf("%#x\n", virtual_address);
    printf("%d\n", vpn);
    printf("%#x\n", offset);
    printf("%d\n", pfn);
    printf("%#x\n", pa);

    return pa;
}

int main() {
    // Example 1: VA = 0x4ABC
    // VPN = 0x4, offset = 0xABC, PFN = page_table[4] = 3
    unsigned int va1 = 0x4ABC;
    get_physical_addr(va1);

    // Example 2: VA = 0x0123
    // VPN = 0x0, offset = 0x123, PFN = page_table[0] = 2
    unsigned int va2 = 0x0123;
    get_physical_addr(va2);

    return 0;
}