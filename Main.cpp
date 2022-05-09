#include "Main.h"
#include "DialogHook.h"

AsiPlugin::AsiPlugin() {
	dialogHook_ = std::make_unique<DialogHook>();
}

AsiPlugin::~AsiPlugin() {

}