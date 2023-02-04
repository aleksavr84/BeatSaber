#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BeatSpawner.generated.h"

UCLASS()
class BEATSABER_API ABeatSpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	ABeatSpawner();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(EditAnywhere)
	TSubclassOf<class ABeat> BeatClass;

	UPROPERTY(EditAnywhere)
	float BeatTime = 1.25f;

	UPROPERTY(EditAnywhere)
	int32 TotalBeatsToSpawn = 30;

	void GenerateBeat();
	void SpawnBeat();
	bool bIsBeat;
};