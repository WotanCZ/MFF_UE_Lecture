#pragma once

#include "UserInterfaceModule.h"
#include "Blueprint/UserWidget.h"
#include "ViewHolderWidget.generated.h"

class UOverlay;
class UViewWidget;

UCLASS(Blueprintable, NotBlueprintType)
class USERINTERFACE_API UViewHolderWidget : public UUserWidget
{
	GENERATED_BODY()

public: // Custom UI Layers

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UOverlay> HUDElements;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UOverlay> Screens;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UOverlay> Dialogs;

public:

	// Add to layer based on type
	UFUNCTION(BlueprintCallable)
	void AddToLayer(UViewWidget* Widget);
};