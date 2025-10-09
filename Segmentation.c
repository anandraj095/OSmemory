#include <stdio.h>

// Bitmasks for permissions
#define READ_PERMISSION  (1 << 0)   // bit 0 -> value = 1
#define WRITE_PERMISSION (1 << 1)   // bit 1 -> value = 2

// Structure for segment table entry
typedef struct {
    int base;
    int limit;
    char perms; // Bitmask for permissions (R/W)
} SegmentEntry;

// Structure for a memory access request
typedef struct {
    char type; // 'R' for Read, 'W' for Write
    int virtual_address;
} AccessRequest;

int main() {
    // Initialize the segment table
    SegmentEntry segment_table[4] = {
        {2048, 1024, READ_PERMISSION},                                // Segment 0: Code
        {4096, 2048, READ_PERMISSION | WRITE_PERMISSION},             // Segment 1: Heap
        {8192, 1024, READ_PERMISSION | WRITE_PERMISSION},             // Segment 2: Stack
        {0, 0, 0}                                                     // Segment 3: Unused
    };

    // Memory access requests
    AccessRequest requests[] = {
        {'R', 500},     // Read from Code Segment
        {'W', 600},     // Write to Code Segment
        {'W', 17000},   // Write to Heap Segment (offset 616)
        {'R', 20000}    // Read from Heap Segment (offset 3616)
    };

    int num_requests = sizeof(requests) / sizeof(requests[0]);

    // Process each request
    for (int i = 0; i < num_requests; i++) {
        char access_type = requests[i].type;
        int va = requests[i].virtual_address;

        // 1️⃣ Parse the 16-bit virtual address
        int segment_num = (va >> 14) & 0x03; // top 2 bits → segment number (0–3)
        int offset = va & 0x3FFF;            // lower 14 bits → offset

        if (access_type == 'R')
            printf("Access: READ, VA: %d -> ", va);
        else
            printf("Access: WRITE, VA: %d -> ", va);


        // 2️⃣ Check if the segment is valid
        if (segment_num > 3 || segment_table[segment_num].limit == 0) {
            printf("Segmentation Fault: Invalid segment number %d\n", segment_num);
            continue;
        }

        SegmentEntry segment = segment_table[segment_num];

        // 3️⃣ Bounds Check
        if (offset >= segment.limit) {
            printf("Segmentation Fault: Offset %d is out of bounds for Segment %d\n",
                   offset, segment_num);
            continue;
        }

        // 4️⃣ Permission Check
        int has_permission = 0;
        if (access_type == 'R' && (segment.perms & READ_PERMISSION))
            has_permission = 1;
        else if (access_type == 'W' && (segment.perms & WRITE_PERMISSION))
            has_permission = 1;

        if (!has_permission) {
            printf("Protection Fault: %s permission denied for Segment %d\n",
                   (access_type == 'R' ? "READ" : "WRITE"), segment_num);
            continue;
        }

        // 5️⃣ Translation
        int physical_address = segment.base + offset;
        printf("Success! PA: %d\n", physical_address);
    }

    return 0;
}
