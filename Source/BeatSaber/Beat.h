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

	UFUNCTION(BlueprintNativeEvent)
	void OnBeatOverlap(FVector HitDirection, FVector Impulse);
	void CheckValidHit(EMovementDirection Direction, EHand Hand);

protected:
	virtual void BeginPlay() override;

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

	UPROPERTY(EditAnywhere);
	EBeatDirection BeatDirection = EBeatDirection::EBD_Right;

	void Init();
	bool bIsInitialized;
	bool bStopMovement = false;
	void SetBeatMaterial();
	void Move();
	void Rotate();

	UPROPERTY(EditDefaultsOnly)
	double MovementSpeed = 3;

public:	
	virtual void Tick(float DeltaTime) override;
	FORCEINLINE void SetBeatSpawnSide(EBeatSpawnSide Side) { BeatSide = Side; }
	FORCEINLINE EBeatSpawnSide GetBeatSpawnSide() { return BeatSide; }
	FORCEINLINE void SetBeatDirection(EBeatDirection Direction) { BeatDirection = Direction; }
	FORCEINLINE EBeatDirection GetBeatDirection() { return BeatDirection; }
	FORCEINLINE void StopMovement(bool bStop) { bStopMovement = bStop; }
};
