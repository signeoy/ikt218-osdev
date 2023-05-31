// https://github.com/uiaict/ikt218-osdev/
#include "screen.h"
#include <stdint.h>
#ifndef GDT
#define GDT
#define GDT_ENTRIES 5
#define IDT_ENTRIES 256

void start_gdt() asm ("start_gdt");

extern "C" {
  extern void loadGDT(uint32_t gdt_ptr);
}

// Define the GDT entry structure
struct gdt_entry_t {
    uint16_t limit_low;
    uint16_t base_low;
    uint8_t base_middle;
    uint8_t access;
    uint8_t granularity;
    uint8_t base_high;
} __attribute__((packed));

// Define the GDT pointers
struct gdt_ptr_t {
  uint16_t limit;
  uint32_t base;
} __attribute__((packed));

static gdt_entry_t gdt[GDT_ENTRIES];
static gdt_ptr_t gdt_ptr;

void set_gdt_gate(int32_t num, uint32_t base, uint32_t limit, uint8_t access, uint8_t gran) {

    gdt[num].base_low    = (base & 0xFFFF);
    gdt[num].base_middle = (base >> 16) & 0xFF;
    gdt[num].base_high   = (base >> 24) & 0xFF;

    gdt[num].limit_low   = (limit & 0xFFFF);
    gdt[num].granularity = (limit >> 16) & 0x0F;

    gdt[num].granularity |= gran & 0xF0;
    gdt[num].access      = access;

}


void start_gdt() {

    // Sets the GDT limit
    gdt_ptr.limit = sizeof(struct gdt_entry_t) * GDT_ENTRIES - 1;
    gdt_ptr.base = (uint32_t) &gdt;

    set_gdt_gate(0, 0, 0, 0, 0);                // Null
    set_gdt_gate(2, 0, 0xFFFFFFFF, 0x92, 0xCF); // Data
    set_gdt_gate(1, 0, 0xFFFFFFFF, 0x9A, 0xCF); // Text
   
    screenClear();

    // Adds feedback to the terminal
    screenPrint("Loading GDT...");

    // Load the GDT
    loadGDT((uint32_t)&gdt_ptr);

    screenPrint("Completed Loading the GDT.");
}

// Set the value of one GDT entry.

//Starts GDT
void start_gdt();

// Load the GDT
void gdt_load();

// Set the value of one GDT entry.
void set_gdt_gate(int32_t num, uint32_t base, uint32_t limit, uint8_t access, uint8_t gran);



