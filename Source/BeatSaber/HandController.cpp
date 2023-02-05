#include "HandController.h"
#include "Beat.h"
#include "SaberPlayerController.h"
#include "SaberPawn.h"
#include "Haptics/HapticFeedbackEffect_Base.h"
#include "Components/BoxComponent.h"
#include "Kismet/KismetMathLibrary.h"

AHandController::AHandController()
{
	PrimaryActorTick.bCanEverTick = true;

	MotionController = CreateDefaultSubobject<UMotionControllerComponent>(FName("MotionController"));
	SetRootComponent(MotionController);
	MotionController->bDisplayDeviceModel = false;

	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
	CollisionBox->SetCollisionObjectType(ECollisionChannel::ECC_WorldDynamic);
	CollisionBox->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	CollisionBox->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
	CollisionBox->SetupAttachment(MotionController);

	SaberMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SaberMesh"));
	SaberMesh->SetupAttachment(CollisionBox);
}

void AHandController::BeginPlay()
{
	Super::BeginPlay();
	
	OnActorBeginOverlap.AddDynamic(this, &AHandController::ActorBeginOverlap);
	OnActorEndOverlap.AddDynamic(this, &AHandController::ActorEndOverlap);
}

void AHandController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bBeatOverlapped &&!bCalculated)
	{
		CalculateMovementDirection();
		// Activate Physics and slicing the Procedual Beat Mesh
		SlicingTheBeat();
	}
}

void AHandController::SetSabreMeshMaterial(UMaterial* Material)
{
	SaberMesh->SetMaterial(0, Material);
}

void AHandController::PairController(AHandController* Controller)
{
	OtherController = Controller;
	OtherController->OtherController = this;
}

void AHandController::CalculateMovementDirection()
{
	FVector MovementDelta = UKismetMathLibrary::GetDirectionUnitVector(StartLocation, GetActorLocation());

	MovementDelta.Normalize();
	
	// Right to Left
	if ((MovementDelta.Y < 0 && UKismetMathLibrary::Abs(MovementDelta.Y) >= MinOffsetY) 
		&& (UKismetMathLibrary::Abs(MovementDelta.Z) < MinOffsetZ))
	{
		MovementDirection = EMovementDirection::EMD_Left;
		bCalculated = true;
	}
	// Left to Right
	else if ((MovementDelta.Y > 0 && UKismetMathLibrary::Abs(MovementDelta.Y) >= MinOffsetY)
		&& (UKismetMathLibrary::Abs(MovementDelta.Z) < MinOffsetZ))
	{
		MovementDirection = EMovementDirection::EMD_Right;
		bCalculated = true;
	}
	// Up to Down
	else if ((MovementDelta.Z < 0 && UKismetMathLibrary::Abs(MovementDelta.Z) >= MinOffsetZ)
		&& (UKismetMathLibrary::Abs(MovementDelta.Y) < MinOffsetY))
	{
		MovementDirection = EMovementDirection::EMD_Down;
		bCalculated = true;
	}
	// Down to Top
	else if ((MovementDelta.Z > 0 && UKismetMathLibrary::Abs(MovementDelta.Z) >= MinOffsetZ)
		&& (UKismetMathLibrary::Abs(MovementDelta.Y) < MinOffsetY))
	{
		MovementDirection = EMovementDirection::EMD_Up;
		bCalculated = true;
	}
	// Not Moving
	else
	{
		MovementDirection = EMovementDirection::EMD_Stopped;
	}
}

void AHandController::SlicingTheBeat()
{
	SaberPawn = SaberPawn == nullptr ? Cast<ASaberPawn>(GetOwner()) : SaberPawn;

	switch (MovementDirection)
	{
	case EMovementDirection::EMD_Left:
		HapticFeedback();
		Beat->CheckValidHit(EMovementDirection::EMD_Left, MotionController->GetTrackingSource(), SaberPawn);
		break;
	case EMovementDirection::EMD_Right:
		HapticFeedback();
		Beat->CheckValidHit(EMovementDirection::EMD_Right, MotionController->GetTrackingSource(), SaberPawn);
		break;
	case EMovementDirection::EMD_Up:
		HapticFeedback();
		Beat->CheckValidHit(EMovementDirection::EMD_Up, MotionController->GetTrackingSource(), SaberPawn);
		break;
	case EMovementDirection::EMD_Down:
		HapticFeedback();
		Beat->CheckValidHit(EMovementDirection::EMD_Down, MotionController->GetTrackingSource(), SaberPawn);
		break;
	default:
		break;
	}
}

void AHandController::HapticFeedback()
{
	SaberController = SaberController == nullptr ? Cast<ASaberPlayerController>(Cast<ASaberPawn>(GetOwner())->Controller) : SaberController;

	if (SaberController && HapticEffect)
	{
		SaberController->PlayHapticEffect(
			HapticEffect,
			MotionController->GetTrackingSource(),
			1,
			false
		);
	}
}

EHand AHandController::GetHand()
{
	switch (MotionController->GetTrackingSource())
	{
	case EControllerHand::Left:
		return EHand::ECH_Left;
		break;
	case EControllerHand::Right:
		return EHand::ECH_Right;
		break;
	default:
		return EHand::ECH_MAX;
		break;
	}
}

void AHandController::ActorBeginOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	StartLocation = GetActorLocation();

	if (OtherActor->ActorHasTag(TEXT("Beat")))
	{
		Beat = Beat == nullptr ? Cast<ABeat>(OtherActor) : Beat;

		if (Beat)
		{
			bBeatOverlapped = true;
		}
	}	
}

void AHandController::ActorEndOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	Beat = nullptr;
	bBeatOverlapped = false;
	bCalculated = false;
	MovementDirection = EMovementDirection::EMD_Stopped;
}
