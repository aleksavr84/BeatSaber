#include "SaberPawn.h"
#include "HandController.h"
#include "PawnOverlay.h"
#include "SaberGameMode.h"
#include "Components/WidgetComponent.h"
#include "SaberPlayerController.h"
#include "Camera/CameraComponent.h"

ASaberPawn::ASaberPawn()
{
	PrimaryActorTick.bCanEverTick = true;

	VRRoot = CreateDefaultSubobject<USceneComponent>(FName("VRRoot"));
	VRRoot->SetupAttachment(GetRootComponent());

	Camera = CreateDefaultSubobject<UCameraComponent>(FName("Camera"));
	Camera->SetupAttachment(VRRoot);

	WidgetComp = CreateDefaultSubobject<UWidgetComponent>(FName("WidgetComponent"));
	WidgetComp->SetupAttachment(VRRoot);
	WidgetComp->SetWidgetSpace(EWidgetSpace::World);
	
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

	if (WidgetComp)
	{
		PawnOverlay = Cast<UPawnOverlay>(WidgetComp->GetWidget());
	}

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

	if (LeftController && RightController)
	{
		LeftController->PairController(RightController);
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

void ASaberPawn::SetPlayerScore()
{
	ASaberGameMode* BeatSaberGameMode = GetWorld()->GetAuthGameMode<ASaberGameMode>();
	
	SaberController = SaberController == nullptr ? Cast<ASaberPlayerController>(GetController()) : SaberController;
	
	if (BeatSaberGameMode)
	{
		BeatSaberGameMode->PlayerUpdateScore(this, SaberController);
	}
}

