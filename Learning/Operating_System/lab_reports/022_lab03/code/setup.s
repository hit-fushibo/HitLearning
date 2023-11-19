    .code16
    .global _setup_start
    .equ INITSEG, 0x9000
    jmp _setup_start
_setup_start:
    mov $0x03,%ah
    xor %bh,%bh
    int $0x10
    mov $25,%cx
    mov $0x0007,%bx
    mov $msg_setup,%bp
    mov %cs, %ax
    mov %ax, %es
    mov $0x1301,%ax
    int $0x10
    mov $INITSEG, %ax
    mov %ax, %ds
    mov $0x03, %ah
    xor %bh, %bh
    int $0x10
    mov $0, %dx
    mov $0x88, %ah
    int $0x15
    mov %ax, (2)
    mov $0x0000, %ax
    mov %ax, %ds
    lds 0x0104, %si
    mov $INITSEG, %ax
    mov %ax, %es
    mov $0x0004, %di
    mov $0x10, %cx
    rep
    movsb
    mov %cs, %ax
    mov %ax, %es
    mov $INITSEG, %ax
    mov %ax, %ds
    mov $0x03, %ah
    xor %bh, %bh
    int $0x10
    mov $18, %cx
    mov $0x0007, %bx
    mov $msg_cursor, %bp
    mov $0x1301, %ax
    int $0x10
    mov %dx, (0)
    call print_hex
    mov $0x03, %ah
    xor %bh, %bh
    int $0x10
    mov $14, %cx
    mov $0x0007, %bx
    mov $msg_memory, %bp
    mov $0x1301, %ax
    int $0x10
    mov %dx, (2)
    call print_hex
    mov $0x03, %ah
    xor %bh, %bh
    int $0x10
    mov $2, %cx
    mov $0x0007, %bx
    mov $msg_kb, %bp
    mov $0x1301, %ax
    int $0x10
    mov $0x03, %ah
    xor %bh, %bh
    int $0x10
    mov $12, %cx
    mov $0x0007, %bx
    mov $msg_cylinders, %bp
    mov $0x1301, %ax
    int $0x10
    mov %dx, (4)
    call print_hex
    mov $0x03, %ah
    xor %bh, %bh
    int $0x10
    mov $8, %cx
    mov $0x0007, %bx
    mov $msg_heads, %bp
    mov $0x1301, %ax
    int $0x10
    mov %dx, (6)
    call print_hex
    mov $0x03, %ah
    xor %bh, %bh
    int $0x10
    mov $10, %cx
    mov $0x0007, %bx
    mov $msg_sectors, %bp
    mov $0x1301, %ax
    int $0x10
    mov  %dx, (18)
    call print_hex
inf_loop:
    jmp inf_loop
print_hex:
    mov $4, %cx
print_digit:
    rol $4, %dx
    mov $0xe0f, %ax
    and %dl, %al
    add $0x30, %al
    cmp $0x3a, %al
    jl outp
    add $0x07, %al
outp:
    int $0x10
    loop print_digit
    ret
print_nl:
    mov $0xe0d, %ax
    int $0x10
    mov $0xa, %al
    int $0x10
    ret
msg_setup:
    .byte    13,10
    .ascii    "Now we are in SETUP"
    .byte    13,10,13,10
msg_cursor:
    .byte    13, 10
    .ascii    "Cursor Position:"
msg_memory:
    .byte    13, 10
    .ascii    "Memory Size:"
msg_cylinders:
    .byte    13, 10
    .ascii    "Cylinders:"
msg_heads:
    .byte    13, 10
    .ascii    "Heads:"
msg_sectors:
    .byte    13, 10
    .ascii    "Sectors:"
msg_kb:
    .ascii    "KB"
.org 510
boot_flag:
    .word    0xAA55
