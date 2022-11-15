// Fill out your copyright notice in the Description page of Project Settings.


#include "MyActor.h"
#include "Components/StaticMeshComponent.h"
#include "Materials/MaterialInstanceConstant.h"

// Sets default values
AMyActor::AMyActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Mesh_1 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RootMeshComonent"));
	auto MeshAsset = ConstructorHelpers::FObjectFinder<UStaticMesh>(
		TEXT("StaticMesh'/Game/StarterContent/Shapes/Shape_Cube.Shape_Cube'"));
	if (MeshAsset.Object != nullptr) { Mesh_1->SetStaticMesh(MeshAsset.Object); }


	static ConstructorHelpers::FObjectFinder<UMaterialInterface> asset(TEXT("MaterialInstanceConstant'/Game/Material_Examples/M_MasterRockMaterial_Inst.M_MasterRockMaterial_Inst'"));
	Material = asset.Object;
	Mesh_1->SetMaterial(0,Material);
}

// Called when the game starts or when spawned
void AMyActor::BeginPlay()
{
	Super::BeginPlay();

	Material = Mesh_1->GetMaterial(1);
	Dissolve_Material=	UMaterialInstanceDynamic::Create(Material,this);
	if(Dissolve_Material != nullptr)
	{
		Mesh_1->SetMaterial(0,Dissolve_Material);
		
		Mesh_1->SetSimulatePhysics(true);
	}
}

// Called every frame
void AMyActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
