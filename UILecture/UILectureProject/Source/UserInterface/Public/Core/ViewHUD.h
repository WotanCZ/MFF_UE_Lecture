#pragma once

#include <GameHUD.h>
#include "ViewHUD.generated.h"

class UViewWidget;
class UViewHolderWidget;
class AProjectShooterBlankPlayerController;
class UInputMappingContext;

UCLASS(Blueprintable, NotBlueprintType)
class USERINTERFACE_API AViewHUD : public AGameHUD
{
	GENERATED_BODY()

public: // Blueprint Config

	// Our widget with layers for the rest of the UI
	UPROPERTY(EditDefaultsOnly, Category = "Config")
	TSubclassOf<UViewHolderWidget> ViewHolderWidgetClass;
	
	UPROPERTY(EditDefaultsOnly, Category = "Config")
	TMap<FName, TSubclassOf<UViewWidget>> ViewClassMap;

public:

	// Shows desired UI
	virtual bool PushView(FName ViewName, EViewLayer Layer) override;

public:

	// Returns custom player controller class object
	UFUNCTION(BlueprintCallable)
	AProjectShooterBlankPlayerController* GetShooterPlayerController();

protected: // Actor overrides

	// We create our UI here
	virtual void BeginPlay() override;

	// We destroy our UI here
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

protected:

	UPROPERTY(Transient)
	TObjectPtr<UViewHolderWidget> ViewHolderWidget;

};