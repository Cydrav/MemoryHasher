#include <thread>
#include ".\Sha256\Sha256.h"
#include ".\Hasher\ProgramSH.h"
int main() {
	std::vector<segmentInfo*> segmentQueue(segments);
	segmentQueue[Segments::text] = getSegmentInfo(".text");
	segmentQueue[Segments::rdata] = getSegmentInfo(".rdata");
	segmentQueue[Segments::vmp0] = getSegmentInfo(".vmp0");
	segmentQueue[Segments::vmp1] = getSegmentInfo(".vmp1");

	printf("Pre-hashing...\n");

	chunkSegments(segmentQueue);

	printf("Starting hasher!\n");

	std::thread hasher([&]() { while (true) { compareMemory(segmentQueue); Sleep(100); } });
	hasher.detach();

	getchar();

	return 0;
}
