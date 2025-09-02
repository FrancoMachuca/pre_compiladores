section .data
za resdw 10
zb resdw 10
zc resdw 10
x resdw 10
y resdw 10
section .text
global _main
   _main:
MOV zb, 0
MUL 2 2
MOV y, eax
ADD 2 2
MOV x, eax
MOV x, y
TEST 1, 1
SETNE al
TEST zb, zb
SETNE bl
AND al, bl
MOVZX eax, al
MOV za, eax
TEST za, za
SETZ al
MOVZX eax, al
MOV zc, eax
