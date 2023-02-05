#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Types.h"
#include "Beat.generated.h"

UCLASS()
class BEATSABER_API ABeat : public AActor
{
	GENERATED_BODY()
	
public:	
	ABeat();
	void CheckValidHit(EMovementDirection Direction, EControllerHand Hand, class ASaberPawn* PlayerPawn);

protected:
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintNativeEvent)
	void OnBeatOverlap(FVector HitDirection, FVector Impulse);

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class UProceduralMeshComponent* ProcedualMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* BeatMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* HitSideMesh;

	UPROPERTY(EditDefaultsOnly)
	UMaterial* LeftBeatMaterial;

	UPROPERTY(EditDefaultsOnly)
	UMaterial* RightBeatMaterial;

	UPROPERTY(EditAnywhere);
	EBeatSpawnSide BeatSide = EBeatSpawnSide::EBS_Right;

	UPROPERTY()
	class ASaberPlayerController* SaberPlayerController;

	void Init();
	bool bIsInitialized;
	bool bIsInverted;
	bool bStartRotation;
	bool bIsRotated;
	bool bStopMovement = false;
	FRotator BeatRotation = FRotator(0, 0, 0);
	EBeatDirection BeatDirection = EBeatDirection::EBD_Right;
	void SetBeatMaterial();
	void Move();
	void SetBeatSide();
	void GenerateRandomRotation();
	void StartTimer();
	void StartRotation();
	void Rotate(float DeltaTime);

	UPROPERTY(EditDefaultsOnly)
	double MovementSpeed = 3;

public:	
	virtual void Tick(float DeltaTime) override;
	FORCEINLINE void SetInverted(bool bInvert) { bIsInverted = bInvert; }
};
