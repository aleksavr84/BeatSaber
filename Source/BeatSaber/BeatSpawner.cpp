#include "BeatSpawner.h"
#include "TimerManager.h"
#include "Kismet/KismetMathLibrary.h"
#include "Beat.h"

ABeatSpawner::ABeatSpawner()
{
 	// PrimaryActorTick.bCanEverTick = true;

}

void ABeatSpawner::BeginPlay()
{
	Super::BeginPlay();
 
    GenerateBeat();
}

void ABeatSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABeatSpawner::GenerateBeat()
{
    if (TotalBeatsToSpawn > 0)
    {
        TotalBeatsToSpawn--;
        FTimerHandle Handle;
        bIsBeat = false;

        GetWorldTimerManager().SetTimer(
            Handle,
            this,
            &ABeatSpawner::GenerateRandomSide,
            BeatTime
        );
    }
}

void ABeatSpawner::GenerateRandomSide()
{
    bIsDoubleBeat = UKismetMathLibrary::RandomBool();
    bIsInvertedBeat = UKismetMathLibrary::RandomBool();

    if (bIsDoubleBeat)
    {
        // Spawning a double beat
        // Right
        SpawnBeat(FVector(GetActorLocation().X, GetActorLocation().Y + SpawnOffset, GetActorLocation().Z), bIsInvertedBeat);
        // Left
        SpawnBeat(FVector(GetActorLocation().X, GetActorLocation().Y - SpawnOffset, GetActorLocation().Z), bIsInvertedBeat);
    }
    else
    {
        // Spawning a single beat on Random Side
        if (UKismetMathLibrary::RandomBool())
        {
            // Right
            SpawnBeat(FVector(GetActorLocation().X, GetActorLocation().Y + SpawnOffset, GetActorLocation().Z), bIsInvertedBeat);
        }
        else
        {
            // Left
            SpawnBeat(FVector(GetActorLocation().X, GetActorLocation().Y - SpawnOffset, GetActorLocation().Z), bIsInvertedBeat);
        }
    }
  
    GenerateBeat();
}

void ABeatSpawner::SpawnBeat(FVector Location, bool bInvert)
{
    if (BeatClass && (!bIsBeat || bIsDoubleBeat))
    {
        bIsBeat = true;

        FActorSpawnParameters SpawnParams;
        SpawnParams.Owner = GetOwner();

        UWorld* World = GetWorld();

        if (World)
        {
            ABeat* Beat = World->SpawnActor<ABeat>(
                BeatClass,
                Location,
                GetActorRotation(),
                SpawnParams
                );
            Beat->SetInverted(bInvert);   
        }
    }
}

