#!/bin/sh

vectors=$(seq 0 255)

printf "/* generated automatically */\n"
printf "/* warning: changes will be lost */\n"

printf ".section .text\n"
for i in ${vectors}; do
    printf "x86_interrupt_${i}:\n"

    ## x86 exceptions 8, 10, 11, 12, 13, 14 and 21
    ## push an error code describing what caused them.
    ## In any other case, we have to push a dummy error
    ## code to maintain x86_interrupt_frame structure.
    if (( i != 8 && ( i < 10 || i > 14 ) && i != 21 )); then
        printf "pushq \$0\n"
    fi

    printf "pushq \$${i}\n"
    printf "jmp __x86_interrupt_handler_asm\n"
done

printf ".section .rodata\n"
printf ".global __x86_interrupts\n"
printf "__x86_interrupts:\n"
for i in ${vectors}; do
    printf ".quad x86_interrupt_${i}\n"
done
