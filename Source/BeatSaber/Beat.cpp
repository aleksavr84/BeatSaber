#include "Beat.h"
#include "ProceduralMeshComponent.h"

ABeat::ABeat()
{
 //	PrimaryActorTick.bCanEverTick = true;

	//ProcedualMesh = CreateDefaultSubobject<UProceduralMeshComponent>(FName("ProcedualMesh"));
	//SetRootComponent(ProcedualMesh);

	//ProcedualMesh->bUseAsyncCooking = true;
	////ProcedualMesh->bUseComplexAsSimpleCollision(false);

	//BeatMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("BeatMesh"));
	//BeatMesh->SetupAttachment(ProcedualMesh);
	//BeatMesh->SetVisibility(false);
}

// This is called when actor is spawned (at runtime or when you drop it into the world in editor)
void ABeat::PostActorCreated()
{
	Super::PostActorCreated();
	/*CreateCube();*/
}

void ABeat::BeginPlay()
{
	Super::BeginPlay();
	
}

// This is called when actor is already in level and map is opened
void ABeat::PostLoad()
{
	Super::PostLoad();
	/*CreateCube();*/
}

void ABeat::CreateCube()
{
	//TArray<FVector> vertices;
	//vertices.Add(FVector(0, 0, 0));
	//vertices.Add(FVector(0, 100, 0));
	//vertices.Add(FVector(0, 100, 100));
	//vertices.Add(FVector(0, 0, 100));

	//TArray<int32> Triangles;
	//Triangles.Add(0);
	//Triangles.Add(1);
	//Triangles.Add(2);
	//Triangles.Add(3);

	//TArray<FVector> normals;
	//normals.Add(FVector(1, 0, 0));
	//normals.Add(FVector(1, 0, 0));
	//normals.Add(FVector(1, 0, 0));
	//normals.Add(FVector(1, 0, 0));

	//TArray<FVector2D> UV0;
	//UV0.Add(FVector2D(0, 0));
	//UV0.Add(FVector2D(10, 0));
	//UV0.Add(FVector2D(10, 10));
	//UV0.Add(FVector2D(0, 10));


	//TArray<FProcMeshTangent> tangents;
	//tangents.Add(FProcMeshTangent(0, 1, 0));
	//tangents.Add(FProcMeshTangent(0, 1, 0));
	//tangents.Add(FProcMeshTangent(0, 1, 0));
	//tangents.Add(FProcMeshTangent(0, 1, 0));

	//TArray<FLinearColor> vertexColors;
	//vertexColors.Add(FLinearColor(0.75, 0.75, 0.75, 1.0));
	//vertexColors.Add(FLinearColor(0.75, 0.75, 0.75, 1.0));
	//vertexColors.Add(FLinearColor(0.75, 0.75, 0.75, 1.0));
	//vertexColors.Add(FLinearColor(0.75, 0.75, 0.75, 1.0));

	//ProcedualMesh->CreateMeshSection_LinearColor(0, vertices, Triangles, normals, UV0, vertexColors, tangents, true);

	//// Enable collision data
	//ProcedualMesh->ContainsPhysicsTriMeshData(true);
}

void ABeat::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

