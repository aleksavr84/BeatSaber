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
	
	UPROPERTY(EditAnywhere)
	class UWidgetComponent* WidgetComp;

	UPROPERTY()
	class UPawnOverlay* PawnOverlay;

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	void SetPlayerScore();

private:
	UPROPERTY(VisibleAnywhere)
	class USceneComponent* VRRoot;
	
	UPROPERTY(VisibleAnywhere)
	class UCameraComponent* Camera;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class AHandController> HandControllerClass;

	UPROPERTY(EditAnywhere)
	float ControllerRotation = 0.f;

	UPROPERTY()
	AHandController* LeftController;

	UPROPERTY(EditDefaultsOnly)
	UMaterial* LeftSaberMaterial;

	UPROPERTY()
	AHandController* RightController;

	UPROPERTY(EditDefaultsOnly)
	UMaterial* RightSaberMaterial;

	class ASaberPlayerController* SaberController;
};
