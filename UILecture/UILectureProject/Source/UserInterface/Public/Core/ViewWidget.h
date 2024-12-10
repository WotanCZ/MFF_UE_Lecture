#pragma once

#include "CommonActivatableWidget.h"
#include "ViewWidget.generated.h"

class AViewHUD;

UCLASS(Abstract, Blueprintable)
class USERINTERFACE_API UViewWidget : public UCommonActivatableWidget
{
	GENERATED_BODY()

protected:

	UFUNCTION(BlueprintCallable)
	virtual void BindActions() {};

	UFUNCTION(BlueprintCallable)
	virtual void UnbindActions() {};

	UFUNCTION(BlueprintCallable)
	AViewHUD* GetViewHUD();
	
protected:
	
	virtual void NativeOnActivated() override;
	virtual void NativeOnDeactivated() override;
};