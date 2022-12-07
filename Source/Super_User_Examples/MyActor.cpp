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


	CollisionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("OverlapComponent"));
	CollisionSphere->SetSphereRadius(150);
	CollisionSphere->SetCollisionEnabled(ECollisionEnabled::Type::QueryOnly);


	SetRootComponent(CollisionSphere);


	Mesh_1 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RootMeshComonent"));
	auto MeshAsset = ConstructorHelpers::FObjectFinder<UStaticMesh>(
		TEXT("StaticMesh'/Game/StarterContent/Shapes/Shape_Sphere.Shape_Sphere'"));
	if (MeshAsset.Object != nullptr) { Mesh_1->SetStaticMesh(MeshAsset.Object); }
	Mesh_1->SetCollisionEnabled(ECollisionEnabled::Type::QueryAndPhysics);
	Mesh_1->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform, EName::None);
	Mesh_1->SetRelativeLocation(FVector::ZeroVector);
	Mesh_1->SetRelativeRotation(FRotator::ZeroRotator);

	static ConstructorHelpers::FObjectFinder<UMaterialInterface> asset(TEXT(
		"MaterialInstanceConstant'/Game/Material_Examples/M_MasterRockMaterial_Inst.M_MasterRockMaterial_Inst'"));
	Material = asset.Object;
	Mesh_1->SetMaterial(0, Material);

	/*geometryCollection = CreateDefaultSubobject<UGeometryCollectionComponent>(TEXT("Smash_Geometry"));
	geometryCollection->RegisterComponent();*/
}

// Called when the game starts or when spawned
void AMyActor::BeginPlay()
{
	Super::BeginPlay();


	CollisionSphere->SetSimulatePhysics(true);
	Material = Mesh_1->GetMaterial(1);
	Dissolve_Material = UMaterialInstanceDynamic::Create(Material, this);
	if (Dissolve_Material != nullptr)
	{
		//Mesh_1->SetMaterial(0,Dissolve_Material);
	}


	//////////Get Objects Around Me //////////
	if (this != nullptr)
	{
		for (TActorIterator<AStaticMeshActor> Itr(GetWorld()); Itr; ++Itr)
		{
			int32 counter{0};
			counter++;
			const AStaticMeshActor* StaticMeshActor = Cast<AStaticMeshActor>(*Itr);
			if (StaticMeshActor)
				if (StaticMeshActor != GetActor())
					if (StaticMeshActor->ActorHasTag("Floor_1"))
					{
						//Print(StaticMeshActor->GetActorLocation().ToString(),FColor::Blue);
						FVector direction = this->GetActorLocation();
						FVector ImpLuseVector = (direction - StaticMeshActor->
						                                     GetActorLocation());
						direction.Normalize();
						CollisionSphere->AddImpulse(ImpLuseVector, EName::None, true);

						FRotator plusRotation = {0, 0, 360};
						FRotator minusRotation = {0, 0, -360}; 
						SetActorRotation(plusRotation);
						AddActorLocalRotation(minusRotation);
						CollisionSphere->AddLocalOffset(FMath::Lerp(direction,
						                                            StaticMeshActor->GetActorLocation(),
						                                            .3f));
					}
		}
	}
}

// Called every frame
void AMyActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
