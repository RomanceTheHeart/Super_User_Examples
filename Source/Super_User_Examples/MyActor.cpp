// Fill out your copyright notice in the Description page of Project Settings.


#include "MyActor.h"

#include <variant>

#include "UObject/UObjectIterator.h"
#include "EngineUtils.h"
#include "Super_Config.h"
#include "Components/StaticMeshComponent.h"
#include "Elements/Interfaces/TypedElementObjectInterface.h"
#include "Engine/EngineTypes.h"
#include "Kismet/GameplayStatics.h"
#include "Super_Config.h"
#include "../../Plugins/Developer/RiderLink/Source/RD/thirdparty/clsocket/src/ActiveSocket.h"
#include "Engine/StaticMeshActor.h"
#include "Materials/MaterialInstanceConstant.h"
#include "SceneQueries/SceneSnappingManager.h"

// Sets default values
AMyActor::AMyActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	Overlap_Area = CreateDefaultSubobject<USphereComponent>(TEXT("OverlapComponent"));
	Overlap_Area->SetSphereRadius(150);
	Overlap_Area->SetRelativeLocation(FVector::ZeroVector);
	Overlap_Area->SetRelativeRotation(FRotator::ZeroRotator);

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


	//////////Get Objects Around Me //////////
	if (this != nullptr)
	{
		for (TActorIterator<AStaticMeshActor> Itr(GetWorld()); Itr; ++Itr)
		{
			const AStaticMeshActor* component = Cast<AStaticMeshActor>(*Itr);
			if (component != GetActor())

				Print(component->GetName(), FColor::Purple);
		}
	}
}

// Called every frame
void AMyActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
