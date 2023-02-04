#include "BeatSpawner.h"
#include "TimerManager.h"
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
            &ABeatSpawner::SpawnBeat,
            BeatTime
        );
    }
}

void ABeatSpawner::SpawnBeat()
{
    if (BeatClass && !bIsBeat)
    {
        bIsBeat = true;

        FActorSpawnParameters SpawnParams;
        SpawnParams.Owner = GetOwner();

        UWorld* World = GetWorld();

        if (World)
        {
            ABeat* Beat = World->SpawnActor<ABeat>(
                BeatClass,
                GetActorLocation(),
                GetActorRotation(),
                SpawnParams
                );
            Beat->SetBeatSpawnSide(EBeatSpawnSide::EBS_Left);
        }
        
        GenerateBeat();
    }
}

