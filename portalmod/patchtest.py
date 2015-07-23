fo = open("portalmod_riiv.txt", "r+")
str = fo.readlines();
# Close opened file


fo.close()
newstring = ''
for s in str:
	s_split = s.split('"');
	#print s_split
	if len(s_split) > 2:
	#print s_split[1], s_split[3]
		if len(s_split[3]) <= 8:
			newstring = newstring + s_split[1] + ":dword:0x" + s_split[3] + "\n"
		else:
			line = s_split[3]
			split8 = [line[i:i+8] for i in range(0, len(line), 8)]
			i = 0
			for splittad in split8:
				newstring = newstring + "0x" + "%x" % (int(s_split[1],16)+4*i) + ":dword:0x" + splittad + "\n"
				i = i+1;

print newstring
f = open("patchres.txt", 'w')
f.write(newstring)
f.close()
raw_input()