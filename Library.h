#ifndef _LIBRARY_H_
#define _LIBRARY_H_

namespace SAMP
{
	enum class SAMPVersionCode : int
	{
		notLoaded = -1,
		unknown = 0,
		R1 = 1,
		R2 = 2,
		R3 = 3,
		R4 = 4,
		DL = 5
	};
	unsigned long   GetSAMPHandle();
	SAMPVersionCode GetSAMPVersion();
}; // namespace SAMP

#endif // !_LIBRARY_H_