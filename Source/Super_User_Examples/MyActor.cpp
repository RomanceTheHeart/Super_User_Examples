// Fill out your copyright notice in the Description page of Project Settings.


#include "MyActor.h"

#include "Components/StaticMeshComponent.h"
#include "Materials/MaterialInstanceConstant.h"

// Sets default values
AMyActor::AMyActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	Overlap_Area = CreateDefaultSubobject<USphereComponent>(TEXT("OverlapComponent"));
	Overlap_Area->SetSphereRadius(60);


	SetRootComponent(Overlap_Area);


	Mesh_1 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RootMeshComonent"));
	auto MeshAsset = ConstructorHelpers::FObjectFinder<UStaticMesh>(
		TEXT("StaticMesh'/Game/StarterContent/Shapes/Shape_Sphere.Shape_Sphere'"));
	if (MeshAsset.Object != nullptr) { Mesh_1->SetStaticMesh(MeshAsset.Object); }

	Mesh_1->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform, EName::None);
	Mesh_1->SetRelativeLocation(FVector::ZeroVector);
	Mesh_1->SetRelativeRotation(FRotator::ZeroRotator);

	static ConstructorHelpers::FObjectFinder<UMaterialInterface> asset(TEXT(
		"MaterialInstanceConstant'/Game/Material_Examples/M_MasterRockMaterial_Inst.M_MasterRockMaterial_Inst'"));
	Material = asset.Object;
	Mesh_1->SetMaterial(0, Material);
}

// Called when the game starts or when spawned
void AMyActor::BeginPlay()
{
	Super::BeginPlay();

	Mesh_1->SetSimulatePhysics(true);
	Material = Mesh_1->GetMaterial(1);
	Dissolve_Material = UMaterialInstanceDynamic::Create(Material, this);
	FVector ImpLuseVector = {0, 0, -3000};
	Mesh_1->AddImpulse(ImpLuseVector, EName::None, true);

	FRotator meteorRotation = {0, 0, 360};
	SetActorRotation(meteorRotation);
	AddActorLocalRotation(meteorRotation);
	if (Dissolve_Material != nullptr)
	{
		//Mesh_1->SetMaterial(0,Dissolve_Material);
	}

	TArray<AActor*> OverlappingActors;
	Overlap_Area->GetOverlappingActors(OverlappingActors,UStaticMeshComponent::StaticClass());
	for(AActor* actor:OverlappingActors)
	{
		if(actor != nullptr)
		{
			OverlappingActors.AddUnique(actor);

			
		
			GEngine->AddOnScreenDebugMessage(-1,30.0,FColor::Cyan,*actor->GetActorLabel());
		}
	}
}

// Called every frame
void AMyActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}