#include "Beat.h"
#include "TimerManager.h"
#include "ProceduralMeshComponent.h"

ABeat::ABeat()
{
	PrimaryActorTick.bCanEverTick = true;

	BeatMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("BeatMesh"));
	BeatMesh->SetupAttachment(GetRootComponent());
	BeatMesh->SetVisibility(false);

	ProcedualMesh = CreateDefaultSubobject<UProceduralMeshComponent>(FName("ProcedualMesh"));
	ProcedualMesh->SetupAttachment(BeatMesh);
	ProcedualMesh->bUseAsyncCooking = true;

	HitSideMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("HitSideMesh"));
	HitSideMesh->SetupAttachment(ProcedualMesh);

	if (LeftBeatMaterial)
	{
		LeftBeatMaterial = CreateDefaultSubobject<UMaterial>(TEXT("LeftBeatMaterial"));
	}
	if (RightBeatMaterial)
	{
		RightBeatMaterial = CreateDefaultSubobject<UMaterial>(TEXT("RightBeatMaterial"));
	}
}

void ABeat::BeginPlay()
{
	Super::BeginPlay();
	
	SetBeatMaterial();
	StartTimer();
}

void ABeat::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if (!bIsInitialized)
	{
		Init();
	}
	
	if (bIsInitialized && 
		!bIsRotated &&
		bStartRotation)
	{
		Rotate(DeltaTime);
	}

	if (!bStopMovement)
	{
		Move();
	}	
}

void ABeat::Init()
{
	SetBeatSide();
	SetBeatMaterial();
	GenerateRandomRotation();

	bIsInitialized = true;
}

void ABeat::StartTimer()
{
	FTimerHandle Handle;
	
	GetWorldTimerManager().SetTimer(
		Handle,
		this,
		&ABeat::StartRotation,
		FMath::RandRange(2, 5)
	);
}

void ABeat::SetBeatSide()
{
	FVector BeatLocation = GetActorLocation();

	if (BeatLocation.Y >= 0)
	{
		if (!bIsInverted)
		{
			BeatSide = EBeatSpawnSide::EBS_Right;
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("Inverted Right -> Left"))
			BeatSide = EBeatSpawnSide::EBS_Left;
		}	
	} 
	else if (BeatLocation.Y < 0)
	{
		if (!bIsInverted)
		{
			BeatSide = EBeatSpawnSide::EBS_Left;
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("Inverted Left -> Right"))
			BeatSide = EBeatSpawnSide::EBS_Right;
		}
	}
}

void ABeat::GenerateRandomRotation()
{
	switch (FMath::RandRange(0, 3))
	{
		// Right
	case 0:
		BeatRotation = FRotator(0, 0, 0);
		break;
		// Up
	case 1:
		BeatRotation = FRotator(0, 0, -90);
		break;
		// Left
	case 2:
		BeatRotation = FRotator(0, 0, -180);
		break;
		// Down
	case 3:
		BeatRotation = FRotator(0, 0, -270);
		break;
	}
}

void ABeat::StartRotation()
{
	bStartRotation = true;
}

void ABeat::Rotate(float DeltaTime)
{
	if (!FMath::IsNearlyEqual(GetActorRotation().Roll, BeatRotation.Roll, 0.5))
	{
		FRotator RotationValue = FMath::RInterpTo(GetActorRotation(), BeatRotation, DeltaTime, 5.f);

		SetActorRotation(FQuat(RotationValue));
	}
	else
	{
		bIsRotated = true;
	}
	}

void ABeat::SetBeatMaterial()
{
	switch (BeatSide)
	{
	case EBeatSpawnSide::EBS_Left:
		if (LeftBeatMaterial)
		{
			HitSideMesh->SetMaterial(0, LeftBeatMaterial);
		}
		break;
	case EBeatSpawnSide::EBS_Right:
		if (RightBeatMaterial)
		{
			HitSideMesh->SetMaterial(0, RightBeatMaterial);
		}
		break;
	}
}

void ABeat::Move()
{
	FTransform DeltaTransform;
	DeltaTransform.SetLocation(FVector(MovementSpeed * -1, 0, 0));
	DeltaTransform.SetScale3D(GetActorScale3D());

	AddActorWorldTransform(DeltaTransform);
}

void ABeat::OnBeatOverlap_Implementation(FVector HitDirection, FVector Impulse)
{
	//UE_LOG(LogTemp, Warning, TEXT("Doing some work here"));
}

void ABeat::CheckValidHit(EMovementDirection Direction, EHand Hand)
{
	if ((BeatDirection == EBeatDirection::EBD_Right &&
		Direction == EMovementDirection::EMD_Left
		|| BeatDirection == EBeatDirection::EBD_Left &&
		Direction == EMovementDirection::EMD_Right
		|| BeatDirection == EBeatDirection::EBD_Down &&
		Direction == EMovementDirection::EMD_Up
		|| BeatDirection == EBeatDirection::EBD_Top &&
		Direction == EMovementDirection::EMD_Down) &&
		(BeatSide == EBeatSpawnSide::EBS_Left &&
			Hand == EHand::ECH_Left)
		|| (BeatSide == EBeatSpawnSide::EBS_Right &&
			Hand == EHand::ECH_Right))
	{
		// Valid Hit
		switch (Direction)
		{
		case EMovementDirection::EMD_Left:
			OnBeatOverlap(FVector(0, 0, 1), FVector(500, -500, 0));
			break;
		case EMovementDirection::EMD_Right:
			OnBeatOverlap(FVector(0, 0, 1), FVector(500, 500, 0));
			break;
		case EMovementDirection::EMD_Up:
			OnBeatOverlap(FVector(0, 1, 0), FVector(500, 0, -500));
			break;
		case EMovementDirection::EMD_Down:
			OnBeatOverlap(FVector(0, 1, 0), FVector(500, 0, 500));
			break;
		}
		bStopMovement = true;
	}
	// Invalid Hit
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Invalid Hit"));
	}
}
