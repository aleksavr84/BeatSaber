#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Scanner.generated.h"

UCLASS()
class BEATSABER_API AScanner : public AActor
{
	GENERATED_BODY()
	
public:	
	AScanner();

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere)
	TArray<class ADancingCube*> DancingCubes;

	bool bGetNextElement;
	bool bSouldRotate;
	int32 CurrentElement = 0;
	FRotator DesiredRotation;

	void Rotate(float DeltaTime);
	void StartTimer();
	void StartNextRotation();
	void GetNextRotator();

public:	
	virtual void Tick(float DeltaTime) override;

};
