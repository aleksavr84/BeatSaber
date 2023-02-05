#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MotionControllerComponent.h"
#include "Types.h"
#include "HandController.generated.h"

UCLASS()
class BEATSABER_API AHandController : public AActor
{
	GENERATED_BODY()
	
public:	
	AHandController();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;
	void SetSabreMeshMaterial(UMaterial* Material);

private:
	// Default sub object
	UPROPERTY(EditAnywhere)
	class UBoxComponent* CollisionBox;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* SaberMesh;

	UPROPERTY(VisibleAnywhere)
	UMotionControllerComponent* MotionController;

	// Callbacks
	UFUNCTION()
	void ActorBeginOverlap(AActor* OverlappedActor, AActor* OtherActor);

	UFUNCTION()
	void ActorEndOverlap(AActor* OverlappedActor, AActor* OtherActor);

	// Effects
	UPROPERTY(EditDefaultsOnly)
	class UHapticFeedbackEffect_Base* HapticEffect;

	// References
	class ABeat* Beat;
	class ASaberPawn* SaberPawn;
	class APlayerController* SaberController;

	// Helpers
	void CalculateMovementDirection();
	void SlicingTheBeat();
	void HapticFeedback();
	EHand GetHand();
	
	// Calculate Direction
	FVector StartLocation;
	bool bBeatOverlapped;
	bool bCalculated;
	float MinOffsetY = 0.5;
	float MinOffsetZ = 0.5;
	EMovementDirection MovementDirection;

	AHandController* OtherController;

public:
	void SetHand(EControllerHand Hand) { MotionController->SetTrackingSource(Hand); }
	void PairController(AHandController* Controller);
};
