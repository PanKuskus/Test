// Fill out your copyright notice in the Description page of Project Settings.


#include "procedural_terrain.h"

class Terrain
{
public:
	int section;
	TArray<FVector> vertices;
	TArray<int32> Triangles;
	TArray<FVector> normals;
	TArray<FVector2D> UV0;
	TArray<FProcMeshTangent> tangents;
	TArray<FLinearColor> vertexColors;


	Terrain(int _section, FVector point1, FVector point2, FVector point3)
	{
		section = _section;
		vertices.Add(point1);
		vertices.Add(point2);
		vertices.Add(point3);


		Triangles.Add(0);
		Triangles.Add(1);
		Triangles.Add(2);


		normals.Add(FVector(1, 0, 0));
		normals.Add(FVector(1, 0, 0));
		normals.Add(FVector(1, 0, 0));


		UV0.Add(FVector2D(0, 0));
		UV0.Add(FVector2D(10, 0));
		UV0.Add(FVector2D(0, 10));


		tangents.Add(FProcMeshTangent(0, 1, 0));
		tangents.Add(FProcMeshTangent(0, 1, 0));
		tangents.Add(FProcMeshTangent(0, 1, 0));


		vertexColors.Add(FLinearColor(0.75, 0.75, 0.75, 1.0));
		vertexColors.Add(FLinearColor(0.75, 0.75, 0.75, 1.0));
		vertexColors.Add(FLinearColor(0.75, 0.75, 0.75, 1.0));
	}

};

// Sets default values
Aprocedural_terrain::Aprocedural_terrain()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	mesh = CreateDefaultSubobject<UProceduralMeshComponent>(TEXT("GeneratedMesh"));
	RootComponent = mesh;
	mesh->bUseAsyncCooking = true;
}

// Called when the game starts or when spawned
void Aprocedural_terrain::BeginPlay()
{
	Super::BeginPlay();
	CreateTriangle();
	
}

// Called every frame
void Aprocedural_terrain::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void Aprocedural_terrain::CreateTriangle()
{
	Terrain triangle1(0, FVector(0, 0, 0), FVector(0, 100, 0), FVector(0, 0, 100));
	Terrain triangle2(1, FVector(0, 100, 0), FVector(0, 100, 200), FVector(0, 0, 100));

	int cubeSize = 100;
	int totalSize = 10;
	for (int x = 0; x <= totalSize; x++)
	{
		for (int y = 0; y <= totalSize; y++)
		{
			for (int z = 0; z <= totalSize; z++)
			{
				FVector x1 = FVector(x * cubeSize, y * cubeSize, z * cubeSize);
				FVector x2 = FVector(x * cubeSize + cubeSize, y * cubeSize, z * cubeSize); //x lines
				DrawDebugingLine(x1, x2);

				FVector y1 = FVector(x * cubeSize, y * cubeSize, z * cubeSize);
				FVector y2 = FVector(x * cubeSize, y * cubeSize + cubeSize, z * cubeSize); //y lines
				DrawDebugingLine(y1, y2);

				FVector z1 = FVector(x * cubeSize, y * cubeSize, z * cubeSize);
				FVector z2 = FVector(x * cubeSize, y * cubeSize, z * cubeSize + cubeSize); //z lines
				DrawDebugingLine(z1, z2);

			}
		}
	}

	

	mesh->CreateMeshSection_LinearColor(triangle1.section, triangle1.vertices, triangle1.Triangles, triangle1.normals, triangle1.UV0, triangle1.vertexColors, triangle1.tangents, true);
	mesh->CreateMeshSection_LinearColor(triangle2.section, triangle2.vertices, triangle2.Triangles, triangle2.normals, triangle2.UV0, triangle2.vertexColors, triangle2.tangents, true);
	mesh->ContainsPhysicsTriMeshData(true);
}

void Aprocedural_terrain::DrawDebugingLine(FVector start, FVector end)
{
	DrawDebugLine(
		GetWorld(),
		start,
		end,
		FColor(30, 30, 30),
		false, 1000, 0,
		0.5
	);

}
