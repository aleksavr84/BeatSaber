#include "SaberPlayerController.h"
#include "PawnOverlay.h"
#include "Components/TextBlock.h"
#include "SaberHUD.h"
#include "SaberPawn.h"

void ASaberPlayerController::SetHUDScore(float Score)
{
    SaberPawn = SaberPawn == nullptr ? Cast<ASaberPawn>(GetPawn()) : SaberPawn;
   
    bool bHUDValid = SaberPawn &&
        SaberPawn->PawnOverlay &&
        SaberPawn->PawnOverlay->ScoreAmount;

    if (bHUDValid)
    {
        FString ScoreText = FString::Printf(TEXT("%d"), FMath::FloorToInt(Score));
        SaberPawn->PawnOverlay->ScoreAmount->SetText(FText::FromString(ScoreText));
    }
}

