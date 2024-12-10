#pragma once

#include "CommonUserWidget.h"
#include "ViewHolderWidget.generated.h"

class UViewWidget;
class UCommonActivatableWidget;
class UCommonActivatableWidgetStack;
class UCommonActivatableWidgetQueue;
enum class EViewLayer : uint8;

UCLASS(Blueprintable, NotBlueprintType)
class USERINTERFACE_API UViewHolderWidget : public UCommonUserWidget
{
	GENERATED_BODY()

protected: // Custom UI Layers

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UCommonActivatableWidgetStack> Screens;
	
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UCommonActivatableWidgetQueue> Dialogs;

	FDelegateHandle ScreenChangeHandle;
	FDelegateHandle DialogChangeHandle;

public:

	// Add to layer based on type
	UFUNCTION(BlueprintCallable)
	UViewWidget* AddToLayer(TSubclassOf<UViewWidget> WidgetClass, EViewLayer ViewType);

	UFUNCTION(BlueprintCallable)
	bool GetInputValidation();

	void ValidateInput(UCommonActivatableWidget* Widget);

protected:

	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;
};