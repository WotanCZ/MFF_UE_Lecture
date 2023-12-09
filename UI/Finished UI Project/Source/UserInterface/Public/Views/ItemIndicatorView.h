#pragma once

#include "ViewWidget.h"
#include "ItemIndicatorView.generated.h"

class AProjectShooterBlankCharacter;

UCLASS(Blueprintable)
class USERINTERFACE_API UItemIndicatorView : public UViewWidget
{
	GENERATED_BODY()

public: // Blueprint implementable events
	
	UFUNCTION(BlueprintImplementableEvent)
	void OnItemChanged(const bool bHasItem);
	
	UFUNCTION(BlueprintImplementableEvent)
	void OnRifleFired();
	
protected: // Delegate actions

	void ItemPickedUp();

	void RifleFired();

protected:

	UFUNCTION(BlueprintCallable)
	AProjectShooterBlankCharacter* GetPlayerCharacter();
	
protected: // Default overrides

	virtual void InitializeView() override;

	virtual void DeinitializeView() override;
	
	virtual void Created() override;
	
private: // Delegate Handles

	FDelegateHandle ItemPickHandle;
	FDelegateHandle RifleFiredHandle;
	
};