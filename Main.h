#ifndef _MAIN_H_
#define _MAIN_H_

#include <memory>

class AsiPlugin
{
	std::unique_ptr<class DialogHook> dialogHook_;
public:
	AsiPlugin();
	~AsiPlugin();
} AsiPlugin; // class AsiPlugin

#endif // !_MAIN_H_