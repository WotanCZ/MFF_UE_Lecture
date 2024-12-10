#include "ViewWidget.h"
#include "ViewHUD.h"

AViewHUD* UViewWidget::GetViewHUD()
{
	APlayerController* player = GetOwningPlayer();

	if (IsValid(player))
	{
		return Cast<AViewHUD>(player->GetHUD());
	}
	
	return nullptr;
}

void UViewWidget::NativeOnActivated()
{
	Super::NativeOnActivated();
	BindActions();
}

void UViewWidget::NativeOnDeactivated()
{
	UnbindActions();
	Super::NativeOnDeactivated();
}
