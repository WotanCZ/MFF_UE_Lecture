#pragma once

#include "GameplayTagContainer.h"
#include "GameFramework/HUD.h"
#include "GameHUD.generated.h"

class UMenuWidget;
class ULayoutWidget;
class APlayerController;

UCLASS(Blueprintable, NotBlueprintType)
class UIMANAGER_API AGameHUD : public AHUD
{
	GENERATED_BODY()

public: // Blueprint Config

	// Our widget with layers for the rest of the UI
	UPROPERTY(EditDefaultsOnly, Category = Config)
	TSubclassOf<ULayoutWidget> LayoutClass;

	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnGameHUDReady);
	UPROPERTY(BlueprintAssignable)
	FOnGameHUDReady OnGameHUDReady;

public:
	
	UFUNCTION(BlueprintCallable, BlueprintCosmetic, Category = UI)
	static UMenuWidget* PushMenuToLayer(const APlayerController* PlayerController, UPARAM(meta = (Categories = "UI.Layer")) FGameplayTag LayerTag, UPARAM(meta = (AllowAbstract = false)) TSubclassOf<UMenuWidget> MenuClass);

	UFUNCTION(BlueprintCallable, BlueprintCosmetic, Category = UI)
	static void RemoveMenuFromLayer(const APlayerController* PlayerController, UPARAM(meta = (Categories = "UI.Layer")) FGameplayTag LayerTag, UPARAM(meta = (AllowAbstract = false)) UMenuWidget* Menu);

	UFUNCTION(BlueprintCallable, BlueprintCosmetic, Category = UI)
	static void ClearMenuLayer(const APlayerController* PlayerController, UPARAM(meta = (Categories = "UI.Layer")) FGameplayTag LayerTag);

protected: // Actor overrides

	// We create our UI here
	virtual void BeginPlay() override;

	// We destroy our UI here
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	
	virtual UMenuWidget* AddMenuToLayer(TSubclassOf<UMenuWidget> MenuClass, FGameplayTag LayerTag);
	virtual void RemoveMenu(UMenuWidget* Menu, FGameplayTag LayerTag);
	virtual void ClearLayer(FGameplayTag LayerTag);
	
protected:

	UPROPERTY(Transient)
	TObjectPtr<ULayoutWidget> LayoutWidget;

};