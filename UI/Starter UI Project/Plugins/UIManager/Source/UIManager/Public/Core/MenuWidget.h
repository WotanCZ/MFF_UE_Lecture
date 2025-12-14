#pragma once

#include "CommonActivatableWidget.h"
#include "CommonButtonBase.h"
#include "MenuWidget.generated.h"

class UInputAction;
class AGameHUD;

struct FUIInputConfig;

UENUM(BlueprintType)
enum class EWidgetInputMode : uint8
{
	Default,
	GameAndMenu,
	Game,
	Menu
};

UCLASS(Abstract, Blueprintable)
class UIMANAGER_API UMenuWidget : public UCommonActivatableWidget
{
	GENERATED_BODY()

public:
	
	UFUNCTION(BlueprintCallable, Category = Navigation)
	bool HandleNestedBackNavigation();
	
protected:

	UFUNCTION(BlueprintCallable, Category = Input)
	virtual void BindActions() {};

	UFUNCTION(BlueprintCallable, Category = Input)
	virtual void UnbindActions() {};

	UFUNCTION(BlueprintImplementableEvent, Category = Input)
	void OnInputMethodChanged(ECommonInputType CommonInput);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = Input)
	bool IsGamepadMode();
	
protected:

	UPROPERTY(EditDefaultsOnly, Category = Input)
	EWidgetInputMode InputConfig = EWidgetInputMode::Menu;

	UPROPERTY(EditDefaultsOnly, Category = Input)
	EMouseCaptureMode GameMouseCaptureMode = EMouseCaptureMode::NoCapture;
	
	UPROPERTY(EditDefaultsOnly, Category = Input)
	bool bStopAllNavigation = true;

	UPROPERTY(BlueprintReadOnly, Category = Input)
	ECommonInputType InputType;

protected:
	
	FDelegateHandle InputChangedHandle;

protected:
	
	void HandleInputMethodChanged(const ECommonInputType CommonInputType);

protected:

	virtual void NativePreConstruct() override;
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;
	virtual void SynchronizeProperties() override;
	virtual void NativeOnActivated() override;
	virtual void NativeOnDeactivated() override;
	virtual TOptional<FUIInputConfig> GetDesiredInputConfig() const override;
};