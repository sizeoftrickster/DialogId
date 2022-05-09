#include "DialogHook.h"
#include "Library.h"
#include "MinHook.h"
#include <string>

typedef void( __thiscall* DialogPrototypes )( void* _this, int dialogId, int dialogStyle, const char* dialogTitle,
	const char* dialogText, const char* dialogLeftButton, const char* dialogRightButton, bool dialogServerside );
DialogPrototypes fpHkDialog{ nullptr };

void __fastcall ShowDialog( void* _this, void* EDX, int dialogId, int dialogStyle, const char* dialogTitle,
	const char* dialogText, const char* dialogLeftButton, const char* dialogRightButton, bool dialogServerside ) {

	std::string hkDialogTitle = dialogTitle;
	hkDialogTitle += " [" + std::to_string( dialogId ) + "|" + std::to_string( dialogStyle ) + "]";

	return fpHkDialog( _this, dialogId, dialogStyle, hkDialogTitle.c_str(), dialogText, dialogLeftButton, dialogRightButton, dialogServerside );
}

DialogHook::DialogHook() {
	switch ( SAMP::GetSAMPVersion() ) {
		case ( SAMP::SAMPVersionCode::R1 ): {
			pShowDialog = reinterpret_cast<void*>( SAMP::GetSAMPHandle() + 0x6B9C0 );
			break;
		}
		case ( SAMP::SAMPVersionCode::R2 ): {
			pShowDialog = reinterpret_cast<void*>( SAMP::GetSAMPHandle() + 0x6BA70 );
			break;
		}
		case ( SAMP::SAMPVersionCode::R3 ): {
			pShowDialog = reinterpret_cast<void*>( SAMP::GetSAMPHandle() + 0x6F8C0 );
			break;
		}
		case ( SAMP::SAMPVersionCode::R4 ): {
			pShowDialog = reinterpret_cast<void*>( SAMP::GetSAMPHandle() + 0x6FFE0 );
			break;
		}
		case ( SAMP::SAMPVersionCode::DL ): {
			pShowDialog = reinterpret_cast<void*>( SAMP::GetSAMPHandle() + 0x6FA50 );
			break;
		}
		default: {
			break;
		}
	}
	if ( !pShowDialog )
		return;
// Тип перечисления "MH_STATUS" не входит в область.Старайтесь использовать "enum class" вместо "enum"
#pragma warning(push)
#pragma warning(disable: 26812)
	MH_Initialize();
	MH_CreateHook( pShowDialog, reinterpret_cast<LPVOID>( &ShowDialog ), reinterpret_cast<LPVOID*>( &fpHkDialog ) );
	MH_EnableHook( pShowDialog );
#pragma warning(pop)
}

DialogHook::~DialogHook() {
	MH_DisableHook( pShowDialog );
	MH_Uninitialize();
}