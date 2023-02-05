
#include "SberPlayerState.h"
#include "SaberPlayerController.h"
#include "SaberPawn.h"

void ASberPlayerState::AddToScore(float ScoreAmount)
{
    SetScore(GetScore() + ScoreAmount);

    SaberPawn = SaberPawn == nullptr ? Cast<ASaberPawn>(GetPawn()) : SaberPawn;

    if (SaberPawn)
    {
        SaberController = SaberController == nullptr ? Cast<ASaberPlayerController>(SaberPawn->Controller) : SaberController;

        if (SaberController)
        {
            SaberController->SetHUDScore(GetScore());
        }
    }
}