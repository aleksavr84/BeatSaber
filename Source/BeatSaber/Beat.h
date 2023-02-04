#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Beat.generated.h"

UENUM(BlueprintType)
enum class EBeatSide : uint8
{
	EBS_Left UMETA(DisplayName = "Left"),
	EBS_Right UMETA(DisplayName = "Right"),

	EMD_MAX UMETA(DisplayName = "DefalutMAX")
};

UCLASS()
class BEATSABER_API ABeat : public AActor
{
	GENERATED_BODY()
	
public:	
	ABeat();

	UFUNCTION(BlueprintNativeEvent)
	void OnBeatOverlap(FVector HitDirection, FVector Impulse);

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
	EBeatSide BeatSide = EBeatSide::EBS_Right;

	void Init();
	bool bIsInitialized;
	bool bStopMovement = false;
	void SetBeatMaterial();
	void Move();

	UPROPERTY(EditDefaultsOnly)
	double MovementSpeed = 3;

public:	
	virtual void Tick(float DeltaTime) override;
	FORCEINLINE void SetBeatSide(EBeatSide Side) { BeatSide = Side; }
	FORCEINLINE void StopMovement(bool bStop) { bStopMovement = bStop; }

};
