#---end scope---
#---end scope---
#---end scope---
#---end scope---
#val BOOL -1
#---end scope---
.data
divByZero: .asciiz "Error division by zero\n"
outOfBounds: .asciiz "Error index out of bounds\n"
lbl1: .asciiz "val is true\n"
lbl2: .asciiz "val is false\n"
.text
print:
lw $a0,0($sp)
li $v0,4
syscall
jr $ra
printi:
lw $a0,0($sp)
li $v0,1
syscall
jr $ra
divException:
la $a0,divByZero
li $v0,4
syscall

li $v0,10
syscall

indexException:
la $a0,outOfBounds
li $v0,4
syscall

li $v0,10
syscall

printByValue:
move $fp,$sp
subu $fp,$fp,4
lw $25,4($fp)
label_14:
la $24,lbl1
#**********SAVING REGS IN ******
subu $sp,$sp,4
sw $24,0($sp)
subu $sp,$sp,4
sw $25,0($sp)
subu $sp,$sp,4
sw $fp,0($sp)
subu $sp,$sp,4
sw $ra,0($sp)
#**********SAVING REGS OUT ******
subu $sp,$sp,4
sw $24,0($sp)
jal print
addu $sp,$sp,4
#**********RESTORING REGS IN ******
lw $ra,0($sp)
addu $sp,$sp,4
lw $fp,0($sp)
addu $sp,$sp,4
lw $25,0($sp)
addu $sp,$sp,4
lw $24,0($sp)
addu $sp,$sp,4
#**********RESTORING REGS OUT ******
label_40:
j label_69
label_42:
la $24,lbl2
#**********SAVING REGS IN ******
subu $sp,$sp,4
sw $24,0($sp)
subu $sp,$sp,4
sw $25,0($sp)
subu $sp,$sp,4
sw $fp,0($sp)
subu $sp,$sp,4
sw $ra,0($sp)
#**********SAVING REGS OUT ******
subu $sp,$sp,4
sw $24,0($sp)
jal print
addu $sp,$sp,4
#**********RESTORING REGS IN ******
lw $ra,0($sp)
addu $sp,$sp,4
lw $fp,0($sp)
addu $sp,$sp,4
lw $25,0($sp)
addu $sp,$sp,4
lw $24,0($sp)
addu $sp,$sp,4
#**********RESTORING REGS OUT ******
label_68:
label_69:
jr $ra
main:
move $fp,$sp
subu $fp,$fp,4
j label_78
label_75:
li $24,1
j label_81
label_78:
li $24,0
j label_81
label_81:
#**********SAVING REGS IN ******
subu $sp,$sp,4
sw $24,0($sp)
subu $sp,$sp,4
sw $25,0($sp)
subu $sp,$sp,4
sw $fp,0($sp)
subu $sp,$sp,4
sw $ra,0($sp)
#**********SAVING REGS OUT ******
subu $sp,$sp,4
sw $24,0($sp)
jal printByValue
addu $sp,$sp,4
#**********RESTORING REGS IN ******
lw $ra,0($sp)
addu $sp,$sp,4
lw $fp,0($sp)
addu $sp,$sp,4
lw $25,0($sp)
addu $sp,$sp,4
lw $24,0($sp)
addu $sp,$sp,4
#**********RESTORING REGS OUT ******
label_106:
jr $ra
#---end scope---
#print (STRING)->VOID 0
#printi (INT)->VOID 0
#printByValue (BOOL)->VOID 0
#main ()->VOID 0
