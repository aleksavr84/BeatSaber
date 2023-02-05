#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "SaberPlayerController.generated.h"

UCLASS()
class BEATSABER_API ASaberPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	void SetHUDScore(float Score);

private:
	UPROPERTY()
	class ASaberPawn* SaberPawn;
};
