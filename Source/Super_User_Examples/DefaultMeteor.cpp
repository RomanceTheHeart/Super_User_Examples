// Fill out your copyright notice in the Description page of Project Settings.


#include "DefaultMeteor.h"
#include "UObject/UObjectIterator.h"
#include "EngineUtils.h"
#include "Super_Config.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/EngineTypes.h"
#include "Kismet/GameplayStatics.h"
#include "Super_Config.h"
#include "../../Plugins/Developer/RiderLink/Source/RD/thirdparty/clsocket/src/ActiveSocket.h"
#include "Engine/StaticMeshActor.h"
#include "Materials/MaterialInstanceConstant.h"
#include "SceneQueries/SceneSnappingManager.h"

// Sets default values
ADefaultMeteor::ADefaultMeteor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	CollisionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("OverlapComponent"));
	CollisionSphere->SetSphereRadius(150);
	CollisionSphere->SetCollisionEnabled(ECollisionEnabled::Type::QueryOnly);


	SetRootComponent(CollisionSphere);
	Collection = CreateDefaultSubobject<UGeometryCollection>(TEXT("Collection"));
	ComponentCollection = CreateDefaultSubobject<UGeometryCollectionComponent>(TEXT("CollectionComponent"));
	ComponentCollection->SetRestCollection(Collection);

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

	///Other Variable Intializations//
	Speed = 1;
	FVector ImpLuseVector = (CurrentLocation + (Direction) * Speed);
}

// Called when the game starts or when spawned
void ADefaultMeteor::BeginPlay()
{
	Super::BeginPlay();

	CurrentLocation = CollisionSphere->GetComponentLocation();
	CurrentLocation.Normalize();
	//PrintLog(CollisionSphere->GetName());
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
		for (TActorIterator<AActor> Itr(GetWorld()); Itr; ++Itr)
		{
			int32 counter{0};
			counter++;
			AStaticMeshActor* StaticMeshActor = Cast<AStaticMeshActor>(*Itr);
			if (StaticMeshActor)
				StaticMeshActors.Emplace(StaticMeshActor);


			for (AStaticMeshActor* actor : StaticMeshActors)
			{
				if (GEngine)
					GEngine->AddOnScreenDebugMessage(1, 300.0, FColor::Green,
					                                 (TEXT("%s"), actor->GetName()));
				if (GEngine)
					GEngine->AddOnScreenDebugMessage(1, 300.0, FColor::Green,
					                                 (TEXT("%d"), FString::FromInt(StaticMeshActors.Num())));


				FVector staticmeshlocation = actor->GetActorLocation();
				staticmeshlocation.Normalize();

				float CurrentLocationVectorSize = CurrentLocation.Size();
				float staticmeshlocationVectorSize = staticmeshlocation.Size();

				FVector RandomOffset = FVector(
					FMath::RandRange(CurrentLocationVectorSize, staticmeshlocationVectorSize),
					FMath::RandRange(CurrentLocationVectorSize, staticmeshlocationVectorSize),
					FMath::RandRange(CurrentLocationVectorSize, staticmeshlocationVectorSize));


				CollisionSphere->AddLocalOffset(FMath::Lerp(CurrentLocation, RandomOffset, Speed));
			}
		}
	}
}

// Called every frame
void ADefaultMeteor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
