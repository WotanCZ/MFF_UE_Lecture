#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "GameHUD.generated.h"

// We define different UI types
// We can use different management rules based on the type
UENUM(BlueprintType)
enum class EViewLayer : uint8
{
	Screen				UMETA(DisplayName = "Screen"),
	Dialog				UMETA(DisplayName = "Dialog")
};

UCLASS(Abstract)
class PROJECTSHOOTERBLANK_API AGameHUD : public AHUD
{
	GENERATED_BODY()
	
public:

	// Shows desired UI
	UFUNCTION(BlueprintCallable)
	virtual bool PushView(FName ViewName, EViewLayer Layer);
	
};
