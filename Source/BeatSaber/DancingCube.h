#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DancingCube.generated.h"

UCLASS()
class BEATSABER_API ADancingCube : public AActor
{
	GENERATED_BODY()
	
public:	
	ADancingCube();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

};
