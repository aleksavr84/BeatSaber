#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Beat.generated.h"

UCLASS()
class BEATSABER_API ABeat : public AActor
{
	GENERATED_BODY()
	
public:	
	ABeat();

protected:
	virtual void BeginPlay() override;
	void PostActorCreated();
	void PostLoad();

private:
	//UPROPERTY(BlueprintReadOnly)
	//class UProceduralMeshComponent* ProcedualMesh;

	//UPROPERTY(BlueprintReadOnly)
	//UStaticMeshComponent* BeatMesh;

	void CreateCube();

public:	
	virtual void Tick(float DeltaTime) override;

};
