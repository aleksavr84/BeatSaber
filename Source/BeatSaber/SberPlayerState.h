#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "SberPlayerState.generated.h"

/**
 * 
 */
UCLASS()
class BEATSABER_API ASberPlayerState : public APlayerState
{
	GENERATED_BODY()
	
public:
	void AddToScore(float ScoreAmount);

private:
	UPROPERTY()
	class ASaberPawn* SaberPawn;

	UPROPERTY()
	class ASaberPlayerController* SaberController;
};
