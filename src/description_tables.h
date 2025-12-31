// TODO: IMPLEMENT IDT AND GDT

//
#ifndef DESCRIPTOR_TABLES
#define DESCRIPTOR_TABLES
#include "types.h"
struct GDT_ENTRY {
    uint16_t limit_low;     // Segment limit (bits 0-15)
    uint16_t base_low;      // Base address (bits 0-15)
    uint8_t  base_mid;      // Base address (bits 16-23)
    uint8_t  access;        // Access byte
    uint8_t  flags_limit;   // Flags (top 4 bits) + Segment limit high (bits 16-19)
    uint8_t  base_high;     // Base address (bits 24-31)
} __attribute__((packed));
struct GDT_PTR {
    uint16_t limit;
    uint32_t base;
} __attribute__((packed));
struct gdt_entry_arg {
    uint32_t base;
    uint32_t limit;
    uint8_t access;
    uint8_t flags;
};

void gdt_init();
void encode_gdt(uint32_t num, struct gdt_entry_arg *arg);


#endif
