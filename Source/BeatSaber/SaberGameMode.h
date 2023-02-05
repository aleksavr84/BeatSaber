// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "SaberGameMode.generated.h"

/**
 * 
 */
UCLASS()
class BEATSABER_API ASaberGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	void PlayerUpdateScore(class ASaberPawn* PlayerPawn, class ASaberPlayerController* SaberPlayerController);
};
