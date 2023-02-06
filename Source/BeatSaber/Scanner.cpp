#include "Scanner.h"
#include "DancingCube.h"
#include "TimerManager.h"

AScanner::AScanner()
{
	PrimaryActorTick.bCanEverTick = true;

}

void AScanner::BeginPlay()
{
	Super::BeginPlay();
	
	StartTimer();
}

void AScanner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bSouldRotate)
	{
		Rotate(DeltaTime);
	}
}

void AScanner::StartTimer()
{
	FTimerHandle Handle;

	GetWorldTimerManager().SetTimer(
		Handle,
		this,
		&AScanner::GetNextRotator,
		0.5
	);
}

void AScanner::GetNextRotator()
{
	if (!DancingCubes.IsEmpty())
	{
		if (CurrentElement == 0)
		{
			switch (FMath::RandRange(0, 4))
			{
			case 0:
				DesiredRotation = FRotator(0, 0, 20);
				break;
			case 1:
				DesiredRotation = FRotator(0, 0, -5);
				break;
			case 3:
				DesiredRotation = FRotator(0, 0, 5);
				break;
			case 4:
				DesiredRotation = FRotator(0, 0, -20);
				break;
			}
		}
		StartNextRotation();
	}
}

void AScanner::StartNextRotation()
{
	bSouldRotate = true;
}

void AScanner::Rotate(float DeltaTime)
{
	if (!DancingCubes.IsEmpty())
	{
		if (CurrentElement < DancingCubes.Num()) 
		{
			if (!FMath::IsNearlyEqual(DancingCubes[CurrentElement]->GetActorRotation().Roll, DesiredRotation.Roll, 1))
			{
				FRotator RotationValue = FMath::RInterpTo(DancingCubes[CurrentElement]->GetActorRotation(), DesiredRotation, DeltaTime, 2.f);
				DancingCubes[CurrentElement]->SetActorRotation(FQuat(RotationValue));
			}
			else
			{
				bSouldRotate = false;
				CurrentElement++;
				StartTimer();
			}
		} 
		else
		{
			CurrentElement = 0;
			StartTimer();
		}
	}
}

