.text
.global set_tod_from_secs

## ENTRY POINT FOR REQUIRED FUNCTION
set_tod_from_secs:
        ## assembly instructions here
        ## a useful technique for this problem
        ##%edi = int time_of_day_sec
        ##%rsi = tod_t *tod
       
        #BlockA 
        coml	$86400,%edi    #describe the block
        jge		.OOB
        coml	$0,%edi
        jl	.OOB

        #BLockB
        movl	%edi,%eax	#eax now has time_of_day_sec
        	cqto			#prep for dicision
        movl	$3600,%r8d	#divider is 3600
        	idivl	%r8d	#divide edi/eax by 3600
        	movw	%aw,0(%rsi)		#tod->hours = time_of_day_sec / 3600
 		movl	%edx,%eax
        #For ispm

        #For min
       	cqto
        	movl 	$60,%r8d	#divider is 60 for min      		
        	idivl	%r8d		#divide eax(time_of_day_sec)/60
    		movw	%aw,2(%rsi)	#tod->minutes =tod->time_of_day_sec%3600 /60
    	#For sec
    		movw	%dw,4(%rsi) #tod->secs =tod->time_of_day_sec%3600 %60



        movX    SOME_GLOBAL_VAR(%rip), %reg  # load global variable into register
                                             # use movl / movq / movw / movb
                                             # and appropriately sized destination register

### Data area associated with the next function
.data
	
my_int:                         # declare location an single int
        .int 1234               # value 1234

other_int:                      # declare another accessible via name 'other_int'
        .int 0b0101             # binary value as per C

my_array:                       # declare multiple ints in a row 
        .int 10                 # for an array. Each are spaced
        .int 20                 # 4 bytes from each other
        .int 30


.text
.global  set_display_bits_from_tod

#################### ENTRY POINT FOR REQUIRED FUNCTION
set_display_bits_from_tod:
        ## assembly instructions here
        #%rdi = tod_t tod
        #%rsi = int *display
        #BlockA 
        coml	$12,%rdi    #describe the block
        jg		.OOB
        coml	$0,%edi
        jl	.OOB

	## two useful techniques for this problem
        movl    my_int(%rip),%eax    # load my_int into register eax
        leaq    my_array(%rip),%rdx  # load pointer to beginning of my_array into rdx


.text
.global clock_update
        
##################### ENTRY POINT FOR REQUIRED FUNCTION
clock_update:
	## assembly instructions here



