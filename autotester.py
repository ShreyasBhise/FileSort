import os
import sys
import testmaker
#Program takes argument: mode(1 for integer, 0 for char) for input generation, file to generate input to(testcases), a.out execution output(outs), cmdline sort of output(toCompare)
#python autotester.py 1 testcases/test9.txt outs/out9.txt toCompare/out9_new.txt 
#python autotester.py 0 testcases/test9.txt outs/out9.txt toCompare/out9_new.txt 
testmaker.generateTestInput(sys.argv[1], sys.argv[2])
s = "";
if int(sys.argv[1]) == 1:
	s = "-n"

for sortType in ('-q','-i'):
	cmdStr = '/ilab/users/syb29/sysProg/projects/SystemsAsst0/a.out %s %s > %s' % (sortType, sys.argv[2], sys.argv[3])
	#print(cmdStr)
	os.system(cmdStr)
	cmdSort = 'sort %s < %s > %s' % (s, sys.argv[3], sys.argv[4])
	#print(cmdSort)
	os.system(cmdSort)
	cmdDiff = 'diff %s %s' % (sys.argv[3], sys.argv[4])
	ret = os.system(cmdDiff)
	assert (ret == 0)
	sizeOut = os.stat(sys.argv[3]).st_size;
	assert(sizeOut > 0)
	print(sortType + ' sort was successful')
