#include ".\ProgramSH.h"

std::string godHash;

segmentInfo* getSegmentInfo(PCHAR segmentName) { // Nawaz <3
	IMAGE_NT_HEADERS *pNtHdr = ImageNtHeader(GetModuleHandleA(0));
	IMAGE_SECTION_HEADER *pSectionHdr = (IMAGE_SECTION_HEADER*)(pNtHdr + 1);
	segmentInfo* pSectionInfo;
	for (int i = 0; i < pNtHdr->FileHeader.NumberOfSections; i++)
	{
		char *name = (char*)pSectionHdr->Name;
		if (!strcmp(name, segmentName))
		{
			pSectionInfo = new segmentInfo(segmentName);
			pSectionInfo->segmentStart = (DWORD)GetModuleHandleA(0) + pSectionHdr->VirtualAddress;
			pSectionInfo->segmentSz = pSectionHdr->Misc.VirtualSize;
			pSectionInfo->segmentEnd = pSectionInfo->segmentStart + pSectionInfo->segmentSz;
			return pSectionInfo;
		}
		pSectionHdr++;
	}
	printf("Segment \"%s\" was not found\n", segmentName);
	pSectionInfo = new segmentInfo("");
	pSectionInfo->segmentStart = 0;
	pSectionInfo->segmentSz = 0;
	pSectionInfo->segmentEnd = 0;
	return pSectionInfo;
}

void chunkSegments(std::vector<segmentInfo*> segmentVector) {
	for (int sz = 0; sz < Segments::segments-1; sz++) {
		for (int i = segmentVector[sz]->segmentStart; i < segmentVector[sz]->segmentEnd; i++) {
			if ((int)(*(char*)i) != -52 && (int)(*(char*)i)) {
				segmentVector[sz]->goodHash += std::to_string((int)(*(char*)i)) + " ";
			}
		}
		godHash += segmentVector[sz]->goodHash;
	}
	godHash = sha256(godHash);
}

void compareMemory(std::vector<segmentInfo*> segmentVector) {
	std::string temp;
	for (int sz = 0; sz < Segments::segments-1; sz++) {
		segmentVector[sz]->lastHash = "";
		for (int i = segmentVector[sz]->segmentStart; i < segmentVector[sz]->segmentEnd; i++) {
			if ((int)(*(char*)i) != -52 && (int)(*(char*)i)) {
				segmentVector[sz]->lastHash += std::to_string((int)(*(char*)i)) + " ";
			}
		}
		temp += segmentVector[sz]->lastHash;
	}
	temp = sha256(temp);

	if (temp != godHash)
		printf("Memory Modification Detected: Valid Hash (%s) - Last Hash (%s)\n", godHash.c_str(), temp.c_str());
}
