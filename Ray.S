#include <avr/io.h>

.global RayMainAsm
RayMainAsm:
    ret

;***** AddVector3 *****
;	input:
;	X, Vector3 A Address
;	Y, Vector3 B Address
;	Z, Vector3 Res Address
;   using:
;   X, Y, Z, r19, r18, r17, r16
AddVector3:
    ld r16, X+      ; A.xh
    ld r17, X+      ; A.xl
    ld r18, Y+      ; B.xh
    ld r19, Y+      ; B.xl
    add r17, r19
    adc r16, r18
    st Z+, r16      ; Res.xl
    st Z+, r17      ; Res.xh

    ld r16, X+      ; A.yh
    ld r17, X+      ; A.yl
    ld r18, Y+      ; B.yh
    ld r19, Y+      ; B.yl
    add r17, r19
    adc r16, r18
    st Z+, r16      ; Res.yl
    st Z+, r17      ; Res.yh
    
    ld r16, X+      ; A.zh
    ld r17, X+      ; A.zl
    ld r18, Y+      ; B.zh
    ld r19, Y+      ; B.zl
    add r17, r19
    adc r16, r18
    st Z+, r16      ; Res.zl
    st Z+, r17      ; Res.zh
    ret

;***** NegateVector3 *****
;	input:
;	X, Vector3 Address
;   using:
;   X, r19, r18, r17, r16
NegateVector3:
    ld r16, X+      ; A.xh
    ld r17, X+      ; A.xl
    neg r17
    com r16
    st -X, r16      ; Res.xl
    st -X, r17      ; Res.xh

    ld r16, X+      ; A.yh
    ld r17, X+      ; A.yl
    neg r17
    com r16
    st -X, r16      ; Res.yl
    st -X, r17      ; Res.yh
    
    ld r16, X+      ; A.zh
    ld r17, X+      ; A.zl
    neg r17
    com r16
    st -X, r16      ; Res.zl
    st -X, r17      ; Res.zh
    ret

;***** NormalizeVector3 *****
;	input:
;	X, Vector3 Address
;   using:
;   X, r19, r18, r17, r16
NormalizeVector3:
    ld r16, X+      ; A.xh
    ld r17, X+      ; A.xl
    mul r16, r16
    mov r18, r0
    mul r17, r17
    add r18, r0
    ldi r19, 0
    adc r19, r1
    ldi r16, 0
    ldi r17, 0
    ldi r18, 0
    ldi r19, 0
    ret


.section .bss
Vector3:
    .byte 6

