#pragma once

#include "CoreMinimal.h"
#include "ViewWidget.h"
#include "PauseMenuView.generated.h"

class UInputAction;

UCLASS()
class USERINTERFACE_API UPauseMenuView : public UViewWidget
{
	GENERATED_BODY()
	
protected:

	UPROPERTY(EditDefaultsOnly, Category="Input Bindings")
	TObjectPtr<UInputAction> RestartInputAction;

private:

	FUIActionBindingHandle RestartActionHandle;

protected:

	UFUNCTION(BlueprintImplementableEvent)
	void OnRestartAction();
	
	virtual void BindActions() override;
	virtual void UnbindActions() override;
};
