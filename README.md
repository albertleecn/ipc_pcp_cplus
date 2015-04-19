problem:
multi-producers, multi-consumers problem

main technologies:
posix thread
posix semaphore
c++

version:
0.1

result:
This program is running
Hello PCP:
PoolSize:2
GoodCnt:6
ProducersCnt:4
ConsumersCnt:3
hi, i am the 0x100481000th thread(P0)
hi, i am the 0x100504000th thread(P1)
hi, i am the 0x100587000th thread(P2)
hi, i am the 0x10060a000th thread(P3)
hi, i am the 0x10068d000th thread(C0)
hi, i am the 0x100710000th thread(C1)
hi, i am the 0x100793000th thread(C2)
P(0x100481000,0):put[1,G:id(1),p_id(0),time(2015-3-19 11:47:42)]
Pool:
1:G:id(1),p_id(0),time(2015-3-19 11:47:42)
2:G:id(-1),p_id(-1),time(1970-0-1 0:0:0)

P(0x100504000,1):put[2,G:id(2),p_id(1),time(2015-3-19 11:47:43)]
Pool:
1:G:id(1),p_id(0),time(2015-3-19 11:47:42)
2:G:id(2),p_id(1),time(2015-3-19 11:47:43)

C(0x10068d000,0):take[1,G:id(1),p_id(0),time(2015-3-19 11:47:42)]
C(0x100710000,1):take[2,G:id(2),p_id(1),time(2015-3-19 11:47:43)]
P(0x100587000,2):put[3,G:id(3),p_id(2),time(2015-3-19 11:47:45)]
Pool:
1:G:id(3),p_id(2),time(2015-3-19 11:47:45)
2:G:id(-1),p_id(-1),time(1970-0-1 0:0:0)

P(0x10060a000,3):put[4,G:id(4),p_id(3),time(2015-3-19 11:47:47)]
Pool:
1:G:id(3),p_id(2),time(2015-3-19 11:47:45)
2:G:id(4),p_id(3),time(2015-3-19 11:47:47)

P(0x100587000,2) exits!
C(0x100793000,2):take[3,G:id(3),p_id(2),time(2015-3-19 11:47:45)]
P(0x10060a000,3) exits!
C(0x10068d000,0):take[4,G:id(4),p_id(3),time(2015-3-19 11:47:47)]
P(0x100481000,0):put[5,G:id(5),p_id(0),time(2015-3-19 11:47:51)]
Pool:
1:G:id(5),p_id(0),time(2015-3-19 11:47:51)
2:G:id(-1),p_id(-1),time(1970-0-1 0:0:0)

C(0x10068d000,0) exits!
P(0x100504000,1):put[6,G:id(6),p_id(1),time(2015-3-19 11:47:52)]
Pool:
1:G:id(5),p_id(0),time(2015-3-19 11:47:51)
2:G:id(6),p_id(1),time(2015-3-19 11:47:52)

P(0x100481000,0) exits!
C(0x100710000,1):take[5,G:id(5),p_id(0),time(2015-3-19 11:47:51)]
P(0x100504000,1) exits!
C(0x100793000,2):take[6,G:id(6),p_id(1),time(2015-3-19 11:47:52)]
C(0x100710000,1) exits!
C(0x100793000,2) exits!
This program exits!
