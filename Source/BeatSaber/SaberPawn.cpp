#include "SaberPawn.h"
#include "HandController.h"
#include "Camera/CameraComponent.h"

ASaberPawn::ASaberPawn()
{
	PrimaryActorTick.bCanEverTick = true;

	VRRoot = CreateDefaultSubobject<USceneComponent>(FName("VRRoot"));
	VRRoot->SetupAttachment(GetRootComponent());

	Camera = CreateDefaultSubobject<UCameraComponent>(FName("Camera"));
	Camera->SetupAttachment(VRRoot);

	if (LeftSaberMaterial)
	{
		LeftSaberMaterial = CreateDefaultSubobject<UMaterial>(TEXT("LeftSaberMaterial"));
	}
	if (RightSaberMaterial)
	{
		RightSaberMaterial = CreateDefaultSubobject<UMaterial>(TEXT("RightSaberMaterial"));
	}
}

void ASaberPawn::BeginPlay()
{
	Super::BeginPlay();
	
	LeftController = GetWorld()->SpawnActor<AHandController>(HandControllerClass);

	if (LeftController)
	{
		if (LeftSaberMaterial)
		{
			LeftController->SetSabreMeshMaterial(LeftSaberMaterial);
		}
		LeftController->AttachToComponent(VRRoot, FAttachmentTransformRules::KeepRelativeTransform);
		LeftController->SetHand(EControllerHand::Left);
		LeftController->SetOwner(this);
	}

	RightController = GetWorld()->SpawnActor<AHandController>(HandControllerClass);

	if (RightController)
	{
		if (RightSaberMaterial)
		{
			RightController->SetSabreMeshMaterial(RightSaberMaterial);
		}
		RightController->AttachToComponent(VRRoot, FAttachmentTransformRules::KeepRelativeTransform);
		RightController->SetHand(EControllerHand::Right);
		RightController->SetOwner(this);
	}
}

void ASaberPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASaberPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

