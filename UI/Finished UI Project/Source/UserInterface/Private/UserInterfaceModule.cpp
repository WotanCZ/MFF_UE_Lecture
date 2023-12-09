#include "UserInterfaceModule.h"
#include "Modules/ModuleManager.h"
#include <Logging/LogMacros.h>

DEFINE_LOG_CATEGORY(LogUserInterface);

class UserInterfaceModule : public FDefaultGameModuleImpl { };

IMPLEMENT_GAME_MODULE(UserInterfaceModule, UserInterface);