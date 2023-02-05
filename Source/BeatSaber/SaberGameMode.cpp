#include "SaberGameMode.h"
#include "SberPlayerState.h"
#include "SaberPlayerController.h"

void ASaberGameMode::PlayerUpdateScore(class ASaberPawn* PlayerPawn, class ASaberPlayerController* SaberPlayerController)
{
	ASberPlayerState* PlayerState = SaberPlayerController ? Cast<ASberPlayerState>(SaberPlayerController->PlayerState) : nullptr;

	if (PlayerState)
	{
		PlayerState->AddToScore(1.f);
	}
}
