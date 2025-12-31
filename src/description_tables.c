// TODO: IMPLEMENT GDT AND IDT
#include "description_tables.h"
// NULL, CODE, DATA, TSS (Let not care about TSS for now)
struct GDT_ENTRY gdt_entries[3];
struct GDT_PTR gdt_ptr;
void gdt_init()
{
    struct gdt_entry_arg NULL_ARGS;
    struct gdt_entry_arg CODE_SEGMENT;
    struct gdt_entry_arg DATA_SEGMENT;
    NULL_ARGS.access = NULL_ARGS.base = NULL_ARGS.flags = NULL_ARGS.limit = 0;
    CODE_SEGMENT.access = 0x9A;
    CODE_SEGMENT.base = 0x00400000;
    CODE_SEGMENT.limit = 0x003FFFFF;
    CODE_SEGMENT.flags = 0xC;
    DATA_SEGMENT.base = 0x00800000;
    DATA_SEGMENT.limit = 0x003FFFFF;
    DATA_SEGMENT.flags = 0xC;
    DATA_SEGMENT.access = 0x92;
    encode_gdt(0, &NULL_ARGS);
    encode_gdt(1, &CODE_SEGMENT);
    encode_gdt(2, &DATA_SEGMENT);
    gdt_ptr.limit = sizeof(gdt_entries) - 1;
    gdt_ptr.base = (uint32_t) gdt_entries;
}
void encode_gdt(uint32_t num, struct gdt_entry_arg *arg)
{
    gdt_entries[num].limit_low   = arg->limit & 0xFFFF;
    gdt_entries[num].base_low    = arg->base & 0xFFFF;
    gdt_entries[num].access      = arg->access;
    gdt_entries[num].base_mid    = (arg->base >> 16) & 0xFF;
    gdt_entries[num].flags_limit = ((arg->limit >> 16) & 0x0F) | ((arg->flags & 0x0F) << 4);
    gdt_entries[num].base_high   = (arg->base >> 24) & 0xFF;
}
