#include <string>
#include <windows.h>
#include <DbgHelp.h>
#include <vector>
#include "..\Sha256\Sha256.h"

enum Segments {
	text,
	rdata,
	vmp0,
	vmp1,
	segments
};

struct segmentInfo {
	char segmentName[8];
	unsigned long segmentStart;
	unsigned long segmentSz;
	unsigned long segmentEnd = segmentStart + segmentSz;
	std::string goodHash;
	std::string lastHash;

	segmentInfo(const char* name) {
		strcpy(segmentName, name);
	}
};

extern std::string godHash;

segmentInfo* getSegmentInfo(PCHAR SegmentName);
void chunkSegments(std::vector<segmentInfo*> segmentVector);
void compareMemory(std::vector<segmentInfo*> segmentVector);