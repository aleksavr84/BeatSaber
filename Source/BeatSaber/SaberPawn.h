#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "SaberPawn.generated.h"

UCLASS()
class BEATSABER_API ASaberPawn : public APawn
{
	GENERATED_BODY()

public:
	ASaberPawn();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	UPROPERTY(VisibleAnywhere)
	class UCameraComponent* Camera;

	UPROPERTY()
	class AHandController* LeftController;

	UPROPERTY()
	AHandController* RightController;

	UPROPERTY(VisibleAnywhere)
	class USceneComponent* VRRoot;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AHandController> HandControllerClass;

	UPROPERTY(EditAnywhere)
	float ControllerRotation = 0.f;
};
