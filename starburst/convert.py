#
# Compile starburst, check for uniqueness.
#
fontData = [ None ] * 64
fontHash = {}

for line in open("font.txt").readlines():
	line = line.strip()
	if line != "":
		ch = int(line[:3])
		assert fontData[ch] is None
		fontData[ch] = 0x8000
		for s in  line.split(":=")[1].split(" "):
			s = s.strip()
			if s != "":
				base = 0x0001 if s[0] == "A" else 0x0100
				base = base << int(s[1])
				fontData[ch] |= base

		assert fontData[ch] not in fontHash
		fontHash[fontData[ch]] = ch

fontData = [str(x) for x in fontData]
open("__starburst.h","w").write(",".join(fontData))

fontData = ["        dw {0}".format(x) for x in fontData]
open("__starburst.inc","w").write("\n".join(fontData))
