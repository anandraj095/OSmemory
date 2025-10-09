#include <stdlib.h>
#include <stdio.h>


typedef struct {
    int base;
    int limit;
    char perms;
} SegmentEntry;

typedef struct {
    char type;
    int va;
} Inputs;

int main() {

    SegmentEntry segment[4] = {
        {2048, 1024, 'R'},
        {4096, 2048, 'W'},             
        {8192, 1024, 'W'},             
        {0, 0, 0} 
    };

    Inputs input[] = {
        {'R', 500},     
        {'W', 600},     
        {'W', 17000},   
        {'R', 20000}
    };

    int size = sizeof(input) / sizeof(input[0]);

    for (int i = 0; i < size; i++) {

        int virtual_address = input[i].va;
        char permission = input[i].type;

        int offset = virtual_address & 0x3FFF;
        int seg = (virtual_address >> 14) & 0x0003;


        if (seg > 3 || seg < 0 || segment[seg].limit == 0){
            printf("Segmentation fault\n");
            continue;
        }

        if (offset >= segment[seg].limit) {
            printf("Segmentation Fault\n");
            continue;
        }

        int has_permission = 0;
        if (permission == 'R' && (segment[seg].perms == 'R'))
            has_permission = 1;
        else if (permission == 'W' && (segment[seg].perms == 'W'))
            has_permission = 1;

        if (!has_permission) {
            printf("Protection Fault: %s permission denied for Segment %d\n",
                   (permission == 'R' ? "READ" : "WRITE"), seg);
            continue;
        }

        int physical_address = segment[seg].base + offset;
        printf("Success! PA: %d\n", physical_address);
    }

    return 0;
}