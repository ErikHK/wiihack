#0x80fyyzz0	r7, nuvarande tid i sekunder*60, alltså orörd
#0x80fyyzz4	rekordtid, också orörd
#0x80429fa0	points_addr, 0x80fyyzz0/60, helst också med tiondelar
#0x80d25bf8	regular_timeslot, (0x80fyyzz0/60)<<12

#TODO: 
#-skriva ut xxx0y-tid istället för xxx, där y är tiondelar
#-skriva ut tiden så att den INTE addas på med poäng!

#800e3ad4	48212c3c ;b 0x802f6710	;kan vara bättre att köra här

#i 802f6710:

#lwz r0,20(r1)		#orig för 3b38
lbz r0,10(r31)		#orig för 3ad4

#save registers
stwu r5, -0x4(sp)
stwu r6, -0x4(sp)
stwu r4, -0x4(sp)
stwu r3, -0x4(sp)
stwu r7, -0x4(sp)

#set r7=0x80fyyzz0
lis r5, 0x80d2
addi r5,r5,0x5408	#r5 = 0x80d25408 = world_addr
lwz r6, 0(r5) 		#r6 = world
lis r5, 0x80d2
addi r5,r5,0x50a8	#r5 = 0x80d250a8 = stage_addr
lwz r4, 0(r5)		#r4 = stage
li r3, 12		#shifta såhär mycket
slw r6,r6,r3		#shifta r6 12 steg
li r3, 4		#shifta 4
slw r4,r4,r3		#shifta r4 4
lis r7, 0x80f0
or r7,r7,r6
or r7,r7,r4			#r7 = 0x80fyyzz0

#check if finished playing, 1 at address 803551e4 if yes, 0 if no
lis r5, 0x8035
ori r5,r5,0x51e4	#r5 = 0x803551e4
lwz r6, 0(r5)		#r6 = värde i r5
cmpwi r6,1			#r6 == 1?
beq .stage_complete	#yepp, jump to stage_complete
					#here r6 == 0

#store timer++ in 0x80fyyzz0
lwz r6, 0(r7)		#r6 = värde ur 0x80fyyzz0
addi r6,r6,1		#timer++
stw r6, 0(r7)		#store it back

#make sure the record isn't zero
lwz r3, 4(r7)		#r3 = värde i r7+4 = record
cmpwi r3,0			#compare r3 to zero
bne .print_record	#if not, jump
li r3,0x7512		#else, set record to 0x7512=999*60/2
addi r3,r3,0x7512	#r3 = 999*60
stw r3,4(r7)		#record = 999*60

#print record at regular timeslot, 80d25bf8
.print_record:
lwz r3, 4(r7)		#r3 = record
li r5, 60			#div 60
divwu r3,r3,r5		#divide record by 60
li r4, 0xc			#shift 12 steps
slw r3,r3,r4		#shift r3 12 steps to the left

lis r5,0x80d2
ori r5,r5,0x5bf8	#r5 = time_addr
stw r3, 0(r5)		#store (record/60)<<12 in time_addr

#print timer into points_addr
lis r5, 0x8042		#r5 = 0x80420000
addi r5,r5,0x4fd0
addi r5,r5,0x4fd0	#r5 = 0x80429fa0
li r3,60			#load 60 into r3
divwu r6,r6,r3		#timer = timer/60
li r3,100			#100 into r3
mullw r6,r6,r3		#timer *= 100
stw r6, 0(r5)		#store back, r6 holds timer value
b .end				#jump past stage_complete

.stage_complete:
#here the stage is complete
#check if it's a new record!
lwz r4, 0(r7)		#r4 = värde i 0x80fyyz0
lwz r5, 4(r7)		#r5 = värde i 0x80fyyz4 = record

cmp 0,1,r5,r4		
bt lt, .recordend	#r4 > r5 => no record, go to recordend
stw r4, 4(r7)		#record the record

			
lis r5,0x80d2
ori r5,r5,0x5bf8	#r5 = time_addr
li r3,0				#r3 = 0
stw r3, 0(r5)		#store 0 to regular timeslot so it won't get
					#added to the points etc!


#lis r5, 0x8042		#r5 = 0x80420000
#addi r5,r5,0x4fd0
#addi r5,r5,0x4fd0	#r5 = 0x80429fa0
#li r3,60			#r3 = 60
#divw r6,r6,r3		#timer = timer/60
#stw r6, 0(r5)		#also print out timer to points_addr!

.recordend:
li r3,0				#store 0 to r3
stw r3, 0(r7)		#reset timer for next run etc

.end:

lwzu r7, 0(sp)
lwzu r3, 4(sp)
lwzu r4, 4(sp)
lwzu r6, 4(sp)
lwzu r5, 4(sp)
addi r1,r1,4
#b back

881F000A 94A1FFFC
94C1FFFC 9481FFFC
9461FFFC 94E1FFFC
3CA080D2 38A55408
80C50000 3CA080D2
38A550A8 80850000
3860000C 7CC61830
38600004 7C841830
3CE080F0 7CE73378
7CE72378 3CA08035
60A551E4 80C50000
2C060001 4182006C
80C70000 38C60001
90C70000 80670004
2C030000 40820010
38607512 38637512
90670004 80670004
38A0003C 7C632B96
3880000C 7C632030
3CA080D2 60A55BF8
90650000 3CA08042
38A54FD0 38A54FD0
3860003C 7CC61B96
38600064 7CC619D6
90C50000 48000030
80870000 80A70004
7C252000 41800018
90870004 3CA080D2
60A55BF8 38600000
90650000 38600000
90670000 84E10000
84610004 84810004
84C10004 84A10004
38210004

4BDED2C4

<memory offset="0x800e3ad4" value="48212c3c" />
<memory offset="0x802f6710" value="881F000A94A1FFFC94C1FFFC9481FFFC9461FFFC94E1FFFC3CA080D238A5540880C500003CA080D238A550A8808500003860000C7CC61830386000047C8418303CE080F07CE733787CE723783CA0803560A551E480C500002C0600014182006C80C7000038C6000190C70000806700042C030000408200103860751238637512906700048067000438A0003C7C632B963880000C7C6320303CA080D260A55BF8906500003CA0804238A54FD038A54FD03860003C7CC61B96386000647CC619D690C50000480000308087000080A700047C25200041800018908700043CA080D260A55BF83860000090650000386000009067000084E10000846100048481000484C1000484A10004382100044BDED2C4" />
