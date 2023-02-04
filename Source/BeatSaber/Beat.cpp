#include "Beat.h"
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
}

void ABeat::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if (!bIsInitialized)
	{
		Init();
	}
	
	if (!bStopMovement)
	{
		Move();
	}	
}

void ABeat::Init()
{
	bIsInitialized = true;
	SetBeatMaterial();
}

void ABeat::SetBeatMaterial()
{
	switch (BeatSide)
	{
	case EBeatSide::EBS_Left:
		if (LeftBeatMaterial)
		{
			HitSideMesh->SetMaterial(0, LeftBeatMaterial);
		}
		break;
	case EBeatSide::EBS_Right:
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