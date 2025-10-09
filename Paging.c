#include <stdio.h>

// Constants
#define VPN_SHIFT 12         // Top 4 bits for VPN
#define PFN_SHIFT 12         // Shift PFN left 12 bits to make room for offset
#define OFFSET_MASK 0xFFF    // Bottom 12 bits

// Single-level page table: VPN -> PFN
int page_table[16] = {
    2, 4, 1, 7, 3, 5, 6, 8,   // VPN 0-7
    10, 11, 12, 13, 14, 9, 15, 0 // VPN 8-15
};

// Function to translate virtual address to physical address
unsigned int get_physical_addr(unsigned int virtual_addr) {
    // 1. Extract VPN (top 4 bits)
    unsigned int vpn = virtual_addr >> VPN_SHIFT;

    // 2. Extract offset (bottom 12 bits)
    unsigned int offset = virtual_addr & OFFSET_MASK;

    // 3. Look up PFN in the page table
    unsigned int pfn = page_table[vpn];

    // 4. Construct physical address
    unsigned int physical_addr = (pfn << PFN_SHIFT) | offset;

    // Debug print
    printf("VA: 0x%04X -> (VPN: %u, Offset: 0x%03X) -> PFN: %u -> PA: 0x%05X\n",
           virtual_addr, vpn, offset, pfn, physical_addr);

    return physical_addr;
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
