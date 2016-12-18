stack   segment para stack 'stack'
db      1024 dup (?)
stack   ends
data    segment para 'data'
      data1     db 100 dup(?)
    data2     db 50 dup(?)
data           ends
      code    segment para 'code'
assume cs:code, ds:data, es:data, ss:stack
     call FAR PTR main
dis proc near
        push cx
        mov  bl, data2[0]
        mov  dl, bl
        mov  cl, 4
        rol  dl, cl
        and  dl, 0fh
        call disp4
        mov  dl, bl
        and  dl, 0fh
        call disp4
        pop  cx
        ret
dis endp
disp4   proc near
        add  dl, 30h
        cmp  dl, 3ah
        jb   ddd
        add  dl, 27h
ddd:    mov  ah, 02h
        int  21h
        ret
    disp4   endp
mulx proc near
    MOV AL,[1 + data2]
    MOV BL,[2 + data2]
    MUL BL
    MOV BX,0 + offset data1
    MOV [BX],AL
    MOV AH,[0 + data1]
    ret
    ret
mulx endp
divx proc near
    MOV AL,[3 + data2]
    MOV BL,[4 + data2]
    MOV AH,0
    DIV BL
    MOV BX,1 + offset data1
    MOV [BX],AL
    MOV AH,[1 + data1]
    ret
    ret
divx endp
addx proc near
    MOV AL,[5 + data2]
    ADD AL,[6 + data2]
    MOV BX,2 + offset data1
    MOV [BX],AL
    MOV AH,[2 + data1]
    ret
    ret
addx endp
subx proc near
    MOV AL,[7 + data2]
    SUB Al,[8 + data2]
    MOV BX,3 + offset data1
    MOV [BX],AL
    MOV AH,[3 + data1]
    ret
    ret
subx endp
jiecheng proc near
    MOV AL,1
    MOV BX,4 + offset data1
    MOV [BX],AL
    MOV AL,[9 + data2]
    CMP AL,[4 + data1]
    JG t1
t0:
    MOV AL,1
    JMP t2
t1:
    MOV AL,0
t2:
    MOV [5 + data1],AL
    MOV BX,5 + offset data1
    MOV [BX],AL
    MOV AL,[5 + data1]
    CMP AL,0
  JA label0
    JMP label1
label0:
    MOV AL,1
    MOV BX,6 + offset data1
    MOV [BX],AL
    MOV AH,[6 + data1]
    ret
label1:
    MOV AL,1
    MOV BX,7 + offset data1
    MOV [BX],AL
    MOV AL,[9 + data2]
    SUB AL,[7 + data1]
    MOV BX,8 + offset data1
    MOV [BX],AL
    MOV BX,9 +offset data2
    MOV AX,[BX]
    PUSH AX
    MOV BX,8 +offset data1
    MOV AL,[BX]
    MOV BX,9 +offset data2
    MOV [BX],AL
    CALL jiecheng
    POP CX
    MOV data2[9],CL
    MOV BX,9 +offset data1
    MOV [BX],AH
    MOV AL,[9 + data2]
    MOV BL,[9 + data1]
    MUL BL
    MOV BX,10 + offset data1
    MOV [BX],AL
    MOV AH,[10 + data1]
    ret
    ret
jiecheng endp
main proc far
        push ds
        xor  ax, ax
        push ax
    mov ax, data
    mov ds, ax
    MOV AL,1
    MOV BX,11 + offset data1
    MOV [BX],AL
    MOV Al,[11 + data1]
    MOV BX,13 + offset data2
    MOV [BX],AL
    MOV AL,5
    MOV BX,12 + offset data1
    MOV [BX],AL
    MOV Al,[12 + data1]
    MOV BX,12 + offset data2
    MOV [BX],AL
    MOV AL,2
    MOV BX,13 + offset data1
    MOV [BX],AL
    MOV Al,[13 + data1]
    MOV BX,11 + offset data2
    MOV [BX],AL
    MOV AL,1
    MOV BX,14 + offset data1
    MOV [BX],AL
    MOV AL,[13 + data2]
    CMP AL,[14 + data1]
    JNE t4
t3:
    MOV AL,1
    JMP t5
t4:
    MOV AL,0
t5:
    MOV [15 + data1],AL
    MOV BX,15 + offset data1
    MOV [BX],AL
    MOV AL,[15 + data1]
    CMP AL,0
    JA label2
    JMP label3
label2:
    MOV BX,1 +offset data2
    MOV AX,[BX]
    PUSH AX
    MOV BX,12 +offset data2
    MOV AL,[BX]
    MOV BX,1 +offset data2
    MOV [BX],AL
    MOV BX,2 +offset data2
    MOV AX,[BX]
    PUSH AX
    MOV BX,11 +offset data2
    MOV AL,[BX]
    MOV BX,2 +offset data2
    MOV [BX],AL
    CALL mulx
    POP CX
    MOV data2[1],CL
    POP CX
    MOV data2[2],CL
    MOV BX,16 +offset data1
    MOV [BX],AH
    MOV AL,[16 + data1]
    MOV BX,10 + offset data2
    MOV [BX],AL
    JMP label4
label3:
    MOV AL,2
    MOV BX,17 + offset data1
    MOV [BX],AL
    MOV AL,[13 + data2]
    CMP AL,[17 + data1]
    JNE t7
t6:
    MOV AL,1
    JMP t8
t7:
    MOV AL,0
t8:
    MOV [18 + data1],AL
    MOV BX,18 + offset data1
    MOV [BX],AL
    MOV AL,[18 + data1]
    CMP AL,0
    JA label5
    JMP label6
label5:
    MOV BX,3 +offset data2
    MOV AX,[BX]
    PUSH AX
    MOV BX,12 +offset data2
    MOV AL,[BX]
    MOV BX,3 +offset data2
    MOV [BX],AL
    MOV BX,4 +offset data2
    MOV AX,[BX]
    PUSH AX
    MOV BX,11 +offset data2
    MOV AL,[BX]
    MOV BX,4 +offset data2
    MOV [BX],AL
    CALL divx
    POP CX
    MOV data2[3],CL
    POP CX
    MOV data2[4],CL
    MOV BX,19 +offset data1
    MOV [BX],AH
    MOV AL,[19 + data1]
    MOV BX,10 + offset data2
    MOV [BX],AL
    JMP label7
label6:
    MOV AL,3
    MOV BX,20 + offset data1
    MOV [BX],AL
    MOV AL,[13 + data2]
    CMP AL,[20 + data1]
    JNE t10
t9:
    MOV AL,1
    JMP t11
t10:
    MOV AL,0
t11:
    MOV [21 + data1],AL
    MOV BX,21 + offset data1
    MOV [BX],AL
    MOV AL,[21 + data1]
    CMP AL,0
    JA label8
    JMP label9
label8:
    MOV BX,5 +offset data2
    MOV AX,[BX]
    PUSH AX
    MOV BX,12 +offset data2
    MOV AL,[BX]
    MOV BX,5 +offset data2
    MOV [BX],AL
    MOV BX,6 +offset data2
    MOV AX,[BX]
    PUSH AX
    MOV BX,11 +offset data2
    MOV AL,[BX]
    MOV BX,6 +offset data2
    MOV [BX],AL
    CALL addx
    POP CX
    MOV data2[5],CL
    POP CX
    MOV data2[6],CL
    MOV BX,22 +offset data1
    MOV [BX],AH
    MOV AL,[22 + data1]
    MOV BX,10 + offset data2
    MOV [BX],AL
    JMP label10
label9:
    MOV AL,4
    MOV BX,23 + offset data1
    MOV [BX],AL
    MOV AL,[13 + data2]
    CMP AL,[23 + data1]
    JNE t13
t12:
    MOV AL,1
    JMP t14
t13:
    MOV AL,0
t14:
    MOV [24 + data1],AL
    MOV BX,24 + offset data1
    MOV [BX],AL
    MOV AL,[24 + data1]
    CMP AL,0
    JA label11
    JMP label12
label11:
    MOV BX,7 +offset data2
    MOV AX,[BX]
    PUSH AX
    MOV BX,12 +offset data2
    MOV AL,[BX]
    MOV BX,7 +offset data2
    MOV [BX],AL
    MOV BX,8 +offset data2
    MOV AX,[BX]
    PUSH AX
    MOV BX,11 +offset data2
    MOV AL,[BX]
    MOV BX,8 +offset data2
    MOV [BX],AL
    CALL subx
    POP CX
    MOV data2[7],CL
    POP CX
    MOV data2[8],CL
    MOV BX,25 +offset data1
    MOV [BX],AH
    MOV AL,[25 + data1]
    MOV BX,10 + offset data2
    MOV [BX],AL
    JMP label13
label12:
    MOV AL,5
    MOV BX,26 + offset data1
    MOV [BX],AL
    MOV AL,[13 + data2]
    CMP AL,[26 + data1]
    JNE t16
t15:
    MOV AL,1
    JMP t17
t16:
    MOV AL,0
t17:
    MOV [27 + data1],AL
    MOV BX,27 + offset data1
    MOV [BX],AL
    MOV AL,[27 + data1]
    CMP AL,0
  JA label14
    JMP label15
label14:
    MOV BX,9 +offset data2
    MOV AX,[BX]
    PUSH AX
    MOV BX,12 +offset data2
    MOV AL,[BX]
    MOV BX,9 +offset data2
    MOV [BX],AL
    CALL jiecheng
    POP CX
    MOV data2[9],CL
    MOV BX,28 +offset data1
    MOV [BX],AH
    MOV AL,[28 + data1]
    MOV BX,10 + offset data2
    MOV [BX],AL
label15:
label13:
label10:
label7:
label4:
    MOV BX,0 +offset data2
    MOV AX,[BX]
    PUSH AX
    MOV BX,10 +offset data2
    MOV AL,[BX]
    MOV BX,0 +offset data2
    MOV [BX],AL
    CALL dis
    POP CX
    MOV data2[0],CL
    MOV BX,29 +offset data1
    MOV [BX],AH
    MOV AL,0
    MOV BX,30 + offset data1
    MOV [BX],AL
    MOV AH,[30 + data1]
    ret
    ret
main endp
code    ends
end main
