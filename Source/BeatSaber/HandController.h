#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MotionControllerComponent.h"
#include "HandController.generated.h"

UENUM(BlueprintType)
enum class EMovementDirection : uint8
{
	EMD_Stopped UMETA(DisplayName = "Stopped"),
	EMD_Left UMETA(DisplayName = "Left"),
	EMD_Right UMETA(DisplayName = "Right"),
	EMD_Up UMETA(DisplayName = "Up"),
	EMD_Down UMETA(DisplayName = "Down"),

	EMD_MAX UMETA(DisplayName = "DefalutMAX")
};

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
	class APlayerPawn* SaberPawn;
	class APlayerController* SaberController;

	// Helpers
	void CalculateMovementDirection();
	void SlicingTheBeat();
	void HapticFeedback();
	
	// Calculate Direction
	FVector StartLocation;
	bool bBeatOverlapped;
	bool bCalculated;
	float MinOffsetY = 0.25;
	float MinOffsetZ = 0.25;
	EMovementDirection MovementDirection;

public:
	void SetHand(EControllerHand Hand) { MotionController->SetTrackingSource(Hand); }
};
