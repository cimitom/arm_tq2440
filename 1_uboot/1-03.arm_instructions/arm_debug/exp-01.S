.text
.global _start
_start:
	mov r1,#0xff
	mov r2,#1
	add r3,r2,r1
	sub r3,r1,#0xff

@存储器访问指令ldr,str
mov r1, #0xcf
str r1, [r2]
ldr r0, [r2]

@程序状态寄存器访问指令msr，mrs
mrs r3, cpsr
mov r1, #4
mov r2, #5
cmp r1, r2
mrs r4, cpsr
eor r0, r3, r4
msr cpsr, r3


@ror循环右移指令
mov r1, #0xf0
mov r1, r1, lsl#8
add r1, r1, #0xf0
mov r0, r1, ror#8

@lsl移位指令
mov r1, #0xff
mov r0, r1,lsl#4

@bl跳转指令
@	a = 1;
@	fun:c = 3;
@	b = 2;
mov r1, #1
bl fun
mov r2, #2
b fun_end

fun:
	mov r3, #3
	mov pc, lr

fun_end:
	nop

@b跳转指令
@if(a>0)
@	c= a - b
@else
@	c= a + b

mov r1, #5
mov r2, #6
cmp r1,r2
bgt blanch1
add r3, r1, r2
b end
blanch1:
sub r3, r1, r2

end:
nop
@tst测试位指令
mov r1, #5
tst r1, #2

mov r1, #5
tst r1, #7

mov r1, #5
tst r1, #1

mov r1, #5
tst r1, #0

@cmp比较指令
mov r1, #2
cmp r1, #1

mov r1, #1
cmp r1, #2

mov r1, #1
cmp r1, #1

@为清除指令
mov r1, #0xff
bic r0, r1, #0b101

mov r1, #0b101011
bic r0, r1, #0b101

@and逻辑与指令（按位与）
mov r1, #5
and r2, r1, #2

mov r1, #5
and r2, r1, #7

mov r1, #5
and r2, r1, #1

mov r1, #5
and r2, r1, #0

@add加法指令
mov r1, #0xff
mov r2, #0xff
add r0, r1,r2

mov r1, #0xff
add r0, r1, #0xff

@sub减法指令
mov r1, #3
mov r2, #4
sub r0,r1,r2

@mvn传送取反的值
mvn r0, #4
mvn r1, #0b10;
mvn r2, #5
mvn r3, r1

@mov数据传送指令
	mov r1, #3
	mov r2, #4
	mov r2, #0xff
	mov r3, #0b1010
	add r3, r1, r2
