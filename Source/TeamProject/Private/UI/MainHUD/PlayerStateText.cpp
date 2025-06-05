#include "UI/MainHUD/PlayerStateText.h"
#include "Components/TextBlock.h"

void UPlayerStateText::SetPlayerStateText(FText StateText)
{
	if(Tb_PlayerStateText)
		Tb_PlayerStateText->SetText(StateText);
}
