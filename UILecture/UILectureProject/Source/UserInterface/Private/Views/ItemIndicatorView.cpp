#include "ItemIndicatorView.h"
#include "ViewHUD.h"
#include "GameFramework/PlayerController.h"
#include "ProjectShooterBlankCharacter.h"
#include "ProjectShooterBlankPlayerController.h"

void UItemIndicatorView::ItemPickedUp()
{
	AProjectShooterBlankCharacter* character = GetPlayerCharacter();
	if (IsValid(character))
	{
		OnItemChanged(character->bHasRifle);
	}
}

void UItemIndicatorView::RifleFired()
{
	OnRifleFired();
}

AProjectShooterBlankCharacter* UItemIndicatorView::GetPlayerCharacter()
{
	AViewHUD* viewHUD = Cast<AViewHUD>(GetOwningPlayer()->GetHUD());
	if (!IsValid(viewHUD)) return nullptr;

	AProjectShooterBlankPlayerController* player = viewHUD->GetShooterPlayerController();
	if (!IsValid(player)) return nullptr;
	
	return Cast<AProjectShooterBlankCharacter>(player->GetCharacter());
}

void UItemIndicatorView::NativeOnActivated()
{
	Super::NativeOnActivated();

	AProjectShooterBlankCharacter* playerCharacter = GetPlayerCharacter();

	if (IsValid(playerCharacter))
	{
		ItemPickHandle = playerCharacter->OnItemPickedUp.AddUObject(this, &UItemIndicatorView::ItemPickedUp);
		RifleFiredHandle = playerCharacter->OnRifleFired.AddUObject(this, &UItemIndicatorView::RifleFired);
	}
}

void UItemIndicatorView::NativeOnDeactivated()
{
	Super::NativeOnDeactivated();

	AProjectShooterBlankCharacter* playerCharacter = GetPlayerCharacter();

	if (IsValid(playerCharacter))
	{
		playerCharacter->OnItemPickedUp.Remove(ItemPickHandle);
		playerCharacter->OnRifleFired.Remove(RifleFiredHandle);
	}
}
