#include "Library.h"
#include <Windows.h>

unsigned long SAMP::GetSAMPHandle() {
	static unsigned long samp = 0;
	if ( !samp ) {
		samp = reinterpret_cast<unsigned long>( GetModuleHandleA( "samp.dll" ) );
		if ( samp == 0xFFFFFFFF ) {
			samp = 0;
		}
	}
	return samp;
}

SAMP::SAMPVersionCode SAMP::GetSAMPVersion() {
	static SAMPVersionCode sampVersion = SAMPVersionCode::unknown;
	if ( sampVersion != SAMPVersionCode::unknown ) {
		return sampVersion;
	}
	unsigned long samp = GetSAMPHandle();
	if ( !samp ) {
		sampVersion = SAMPVersionCode::notLoaded;
	} else {
		unsigned long EntryPoint = reinterpret_cast<IMAGE_NT_HEADERS*>( samp + reinterpret_cast<IMAGE_DOS_HEADER*>( samp )->e_lfanew )->OptionalHeader.AddressOfEntryPoint;
		switch ( EntryPoint ) {
			case ( 0x31DF13 ): {
				sampVersion = SAMPVersionCode::R1;
				break;
			}
			case ( 0x3195DD ): {
				sampVersion = SAMPVersionCode::R2;
				break;
			}
			case ( 0xCC4D0 ): {
				sampVersion = SAMPVersionCode::R3;
				break;
			}
			case ( 0xCBCB0 ): {
				sampVersion = SAMPVersionCode::R4;
				break;
			}
			case ( 0xFDB60 ): {
				sampVersion = SAMPVersionCode::DL;
				break;
			}
			default: {
				sampVersion = SAMPVersionCode::unknown;
				break;
			}
		}
	}
	return sampVersion;
}