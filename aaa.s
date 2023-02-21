.text
.global set_tod_from_secs

#Entry point for set_tod_from_secs func
set_tod_from_secs:
        ##assembly instructions here,  
        ##time_of_day_sec in %edi, *tod in %rsi
        movl $86400, %eax        #assgin MAX_DAY_SECS
        cmpl $0, %edi #time_of_day_sec < 0
        jl .EXIT
        cmpl %eax, %edi #time_of_day_sec >= MAX_DAY_SECS
        jge  .EXIT
        jmp .NEXT11

.EXIT:
movl $1, %eax #return 1;
ret

.NEXT11: #line 23-24
movl %edi, %eax #prepare for division
movl $3600, %r8d
cqto # tod_hours in %eax
idivl %r8d #time_of_day_sec / 3600,
cmpl $12, %eax #tod_hours >= 12 ? 1 : 0;
jge .IF11
movw $0,6(%rsi) #ispm = 0, tod->ispm = ispm;
jmp  .NEXT12
.IF11:
movw $1,6(%rsi) #ispm = 1, tod->ispm = ispm;
        jmp  .NEXT12

.NEXT12: #line 25-26
movl $12, %r8d #tod_hours % 12;
cqto
idivl %r8d
movl %edx, %eax #tod_hours = tod_hours % 12;
cmpl $0, %edx
je .IF12
jmp  .NEXT13 #tod_hours = tod_hours
.IF12:
movl $12, %edx #tod_hours = 12

.NEXT13:
movl %edx,0(%rsi) #tod->hours = tod_hours;
movl $60, %r8d
movl %edi, %eax
cqto
idivl %r8d #tod_seconds = time_of_day_sec % 60;
movw %dx,4(%rsi)
cqto
idivl %r8d #tod_minutes=(time_of_day_sec/60)%60;
movw %dx,2(%rsi)
movl $0, %eax
ret 