.code16
.equ SETUPLEN, 2
.equ SETUPSEG,0x07e0
#entry _start
_start:
    mov $0x03,%ah
    xor %bh,%bh
    int $0x10
    mov $28,%cx
    mov $0x0007,%bx
    mov $msg1,%bp
    mov $0x07c0,%ax
    mov %ax,%es
    mov $0x1301,%ax
    int $0x10
load_setup:
    mov $0x0000,%dx
    mov $0x0002,%cx
    mov $0x0200,%bx
    mov $0x0200+SETUPLEN,%ax
    int $0x13
    jnc ok_load_setup
    mov $0x0000,%dx
    mov $0x0000,%ax
    int $0x13
    jmp load_setup
ok_load_setup:
    ljmp    $SETUPSEG,$0
msg1:
    .byte   13,10
    .ascii  "FUOS is booting :) ***"
    .byte   13,10,13,10
.org 510
boot_flag:
    .word   0xAA55
