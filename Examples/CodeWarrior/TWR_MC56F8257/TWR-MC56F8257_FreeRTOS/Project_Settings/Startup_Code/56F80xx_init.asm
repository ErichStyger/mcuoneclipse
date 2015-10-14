
; -------------------------------------------------------
;
;       56F80xx_init.asm
;
;	Metrowerks, a Freescale Company
;	sample code
;
;	description:  main entry point to C code.
;                 setup runtime for C and call main
;
; -------------------------------------------------------

;===============================

; OMR mode bits

;===============================

NL_MODE                                                          EQU  $8000
CM_MODE                                                          EQU  $0100
XP_MODE                                                          EQU  $0080
R_MODE                                                           EQU  $0020
SA_MODE                                                          EQU  $0010

;===============================

; init

;===============================

        section startup

        XREF  F_stack_addr
        XREF  F_xROM_to_xRAM
        XREF  F_pROM_to_xRAM
        XREF  F_Ldata_size
        XREF  F_Ldata_ROM_addr
        XREF  F_Ldata_RAM_addr
        org   p:


        GLOBAL Finit_56800_

        SUBROUTINE "Finit_56800_",Finit_56800_,Finit_56800_END-Finit_56800_

Finit_56800_:

;
; setup the OMr with the values required by C
;
        bfset #NL_MODE,omr    ; ensure NL=1  (enables nsted DO loops)
        nop
        nop
        bfclr #(CM_MODE|XP_MODE|R_MODE|SA_MODE),omr               ; ensure CM=0  (optional for C)
                                                                  ; ensure XP=0 to enable harvard architecture
                                                                  ; ensure R=0  (required for C)
                                                                  ; ensure SA=0 (required for C)


; setup the m01 register for linear addressing

        move.w  #-1,x0
        moveu.w x0,m01                  ; set the m register to linear addressing

        moveu.w hws,la                  ; clear the hardware stack
        moveu.w hws,la
        nop
        nop


CALLMAIN:                               ; initialize compiler environment

                                        ; initialize the Stack
        move.l  #>>F_Lstack_addr,r0
        bftsth  #$0001,r0
        bcc     noinc
        adda    #1,r0
noinc:
        tfra    r0,sp                   ; set stack pointer too
        move.w  #0,r1
        nop
        move.w  r1,x:(sp)               ; put zero at top of stack
        adda    #1,sp                   ; increment stack
        move.w  r1,x:(sp)               ; put another zero


; Stationery default routine
; 56800E LC register doesn't have 8191 element limitation of 56800
; so we can use hardware loop here

; zeroBSS hardware loop utility
        move.l  #>>F_Xbss_length,r2     ; move count
        move.l  #>>F_Xbss_start_addr,r1 ; start address is BSS start
        move.w  #0,x0                   ; zero value
        nop
        do      r2,>>end_zeroBSS        ; copy for r2 times
        nop
        move.w  x0,x:(r1)+              ; stash value at x address r1
end_zeroBSS:



; pROM-to-xRAM utility
        nop
        move.w  #F_pROM_to_xRAM,r0      ; check for the option
        tst.w   r0
        beq     end_prom2xram           ; if no pROM-to-xRAM, then exit
        nop
        move.l  #>>F_Ldata_size,r2      ; set data size
        move.l  #>>F_Ldata_ROM_addr,r3  ; src address -- pROM data start
        move.l  #>>F_Ldata_RAM_addr,r1  ; dest address -- xRAM data start
        do      r2,>>end_prom2xram      ; copy for r2 times
        move.w  p:(r3)+,x0              ; fetch value at address r3
        nop
        nop
        nop
        move.w  x0,x:(r1)+              ; stash value at address r1
end_prom2xram:


; call main()

        move.w  #0,y0                   ; pass parameters to main()
        move.w  #0,R2
        move.w  #0,R3

        jsr     Fmain                   ; call the user program

loop_at_end_of_app:
        debughlt
        bra    loop_at_end_of_app

Finit_56800_END:

        endsec
