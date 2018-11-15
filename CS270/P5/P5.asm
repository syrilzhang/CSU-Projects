; P5 Assignment
; Author: <Luke Burford>
; Date:   <2/24/16>
; Email:  <lburford@rams.colostate.edu>
; Class:  CS270
;
; Description: Implements the arithmetic, bitwise, and shift operations

;------------------------------------------------------------------------------
; Begin reserved section: do not change ANYTHING in reserved section!

                .ORIG x3000
                BR Main

Functions       .FILL IntAdd         ; Address of IntAdd routine     (option 0)
                .FILL IntSub         ; Address of IntSub routine     (option 1)
                .FILL IntMul         ; Address of IntMul routine     (option 2)
                .FILL BinaryOr       ; Address of BinaryOr routine   (option 3)
                .FILL LeftShift      ; Address of LeftShift routine  (option 4)
                .FILL RightShift     ; Address of RightShift routine (option 5)

Main            LEA R0,Functions     ; The main routine calls one of the 
                LD  R1,Option        ; subroutines below based on the value of
                ADD R0,R0,R1         ; the Option parameter.
                LDR R0,R0,0          ;
                JSRR R0              ;
EndProg         HALT                 ;

; Parameters and return values for all functions
Option          .FILL #5             ; Which function to call
Param1          .FILL x000A          ; Space to specify first parameter .BLKW 1
Param2          .FILL x0002          ; Space to specify second parameter .BLKW 1
Result          .BLKW 1              ; Space to store result

; End reserved section: do not change ANYTHING in reserved section!
;------------------------------------------------------------------------------

; You may add variables and functions after here as you see fit.

;------------------------------------------------------------------------------
IntAdd
                LD R0, Param1
                LD R1, Param2
                ADD R2,R0,R1
                ST R2, Result        ; Result is Param1 + Param2
                                     ; Your code goes here (~4 lines)
                RET
;------------------------------------------------------------------------------
IntSub
                LD R0, Param1
                LD R1, Param2
                NOT R1,R1
                ADD R1,R1,#1
                ADD R2,R0,R1
                ST R1, Result        ; Result is Param1 - Param2
                                     ; Your code goes here (~6 lines)
                RET
;------------------------------------------------------------------------------
IntMul
                AND R2,R2,#0
                LD R0, Param1
                BRz EXIT
                LD R1, Param2
                BRz EXIT
LOOP
                ADD R2,R2,R0
                ADD R1,R1,#-1
                BRp LOOP
EXIT
                ST R2, Result        ; Result is Param1 * Param2
                                     ; Your code goes here (~9 lines)
                RET
;------------------------------------------------------------------------------
BinaryOr
                LD R0, Param1
                LD R1, Param2
                NOT R0,R0
                NOT R1,R1
                AND R2,R1,R0
                NOT R2,R2
                ST R2, Result        ; Result is Param1 | Param2
                                     ; Your code goes here (~7 lines)
                RET
;------------------------------------------------------------------------------
LeftShift       
                LD R0, Param1
                LD R1, Param2
LOOP1
                ADD R0,R0,R0
                ADD R1,R1,#-1
                BRp LOOP1            ; Result is Param1 << Param2
                ST R0, Result        ; (Fill vacant positions with 0's)
                                     ; Your code goes here (~7 lines)
                RET
;------------------------------------------------------------------------------
RightShift      
                AND R0, R0, #0  ; result
                LD R1, Param1   ; multiplicand
                LD R2, Param2   ; multiplier
                ADD R3, R0, #1  ; mask for testing bit
                ADD R4, R0, #1  ; mask for end condition (all 1 bits)
LOOP3
                ADD R3,R3,R3
                ADD R2,R2,#-1
                BRp LOOP3
                LD R2, Param2
                NOT R2,R2
                ADD R2,R2,#1
                ST R2, Param2
LOOP4           
                AND R2,R3,#15
                BRz EXIT1
                AND R2,R0,#0
                AND R2,R3,R1
                BRz LOOP5
                ADD R0,R0,R4
LOOP5           
                ADD R3,R3,R3
                ADD R4,R4,R4
                BRnzp LOOP4
EXIT1           
                ST R0, Result
                
                RET
;------------------------------------------------------------------------------
                .END
