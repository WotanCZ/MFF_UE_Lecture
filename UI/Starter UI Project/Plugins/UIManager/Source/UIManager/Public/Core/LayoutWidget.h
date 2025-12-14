#pragma once

#include "CommonUserWidget.h"
#include "GameplayTagContainer.h"
#include "LayoutWidget.generated.h"

class UInputMappingContext;
class UMenuWidget;
class UCommonActivatableWidgetContainerBase;

UCLASS(Blueprintable, NotBlueprintType)
class UIMANAGER_API ULayoutWidget : public UCommonUserWidget
{
	GENERATED_BODY()

protected: // Custom UI Layers

	UPROPERTY(EditDefaultsOnly, Category = Input)
	TObjectPtr<UInputMappingContext> RootInputMapping;
	
	UPROPERTY(BlueprintReadOnly, Category = Layers)
	TMap<FGameplayTag, TObjectPtr<UCommonActivatableWidgetContainerBase>> LayerMap;

public:

	UMenuWidget* AddToLayer(TSubclassOf<UMenuWidget> WidgetClass, FGameplayTag LayerTag);
	void RemoveFromLayer(UMenuWidget* Menu, FGameplayTag LayerTag);
	void ClearLayer(FGameplayTag LayerTag);

	UFUNCTION(BlueprintCallable, Category = Layers)
	void RegisterLayer(FGameplayTag LayerTag, UCommonActivatableWidgetContainerBase* ContainerWidget);

protected:
	
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;
	
};