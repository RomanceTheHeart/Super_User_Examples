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

	System = CreateDefaultSubobject<UFieldSystemComponent>(TEXT("Field"));
	SetRootComponent(CollisionSphere);
	Collection = CreateDefaultSubobject<UGeometryCollection>(TEXT("Collection"));
	ComponentCollection = CreateDefaultSubobject<UGeometryCollectionComponent>(TEXT("CollectionComponent"));
	ComponentCollection->SetRestCollection(Collection);
	ComponentCollection->SetCollisionResponseToChannel(ECollisionChannel::ECC_WorldDynamic,ECR_Ignore);
	ComponentCollection->SetCollisionResponseToChannel(ECollisionChannel::ECC_WorldStatic,ECR_Block);
	ComponentCollection->SetCollisionObjectType(ECollisionChannel::ECC_PhysicsBody);
	ComponentCollection->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);

	



	///Other Variable Intializations//
	Speed = .3f;
	FVector ImpLuseVector = (CurrentLocation + (Direction) * Speed);
}

// Called when the game starts or when spawned
void ADefaultMeteor::BeginPlay()
{
	Super::BeginPlay();

	CurrentLocation = CollisionSphere->GetComponentLocation();
	CurrentLocation.Normalize();
	CollisionSphere->SetSimulatePhysics(true);
	



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
			ExplodeMeteorite();
		}
	
	}
}

void ADefaultMeteor::ExplodeMeteorite()
{
	const TManagedArray<int32>& BoneMap = ComponentCollection->GetBoneMapArray();
	const TManagedArray<FString>& boneNames = ComponentCollection->GetBoneNameArray();
	
	for(FString index : boneNames)
	{
		
		//ComponentCollection->ApplyKinematicField(200000,CollisionSphere->GetComponentLocation());

		
	}
}

// Called every frame
void ADefaultMeteor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
