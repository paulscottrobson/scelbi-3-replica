#
#		Convert test.bin to an include
#
test = open("test.bin","rb").read(-1)
test = [str(ord(x)) for x in test]
open("__binary.h","w").write(",".join(test))