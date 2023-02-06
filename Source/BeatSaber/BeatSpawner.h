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
	class USoundCue* Music;

	UPROPERTY(EditAnywhere)
	float BeatTime = 2.f;

	UPROPERTY(EditAnywhere)
	int32 TotalBeatsToSpawn = 30;

	UPROPERTY(EditAnywhere)
	double SpawnOffset = 50;

	void PlayMusic();
	void GenerateBeat();
	void GenerateRandomSide();
	void SpawnBeat(FVector Location, bool bInvert);
	FVector BeatSpawnLocation;
	bool bIsFirstBeat = true;
	bool bIsBeat;
	bool bIsDoubleBeat;
	bool bIsInvertedBeat;
};
