// Fill out your copyright notice in the Description page of Project Settings.


#include "MiniProjects.h"

#include "MyActor.h"
#include "Kismet/GameplayStatics.h"


void AMiniProjects::BeginPlay()
{
	Super::BeginPlay();
	Print("Actor Spawned.", FColor::Blue);


	FTransform SpawnLocation;

	const int32 blockindex{2};
	const int32 BlockNumber{blockindex * blockindex};
	float OffSetAmount{300.0};
	float Z_OffsetAmount{0.0f};
	//float worldtime = GetGameTimeSinceCreation();
	FActorSpawnParameters SpawnParameters;

	for (int32 index{0}; index < BlockNumber * BlockNumber; index ++)
	{
		const float X_Offset{((index / BlockNumber) * OffSetAmount)};
		const float Y_Offset = {((index % BlockNumber) * OffSetAmount)};
		const float Z_Offset = {((index % BlockNumber) * Z_OffsetAmount)};
		const FVector newspawnvector = FVector(X_Offset, Y_Offset, Z_Offset);

		if (GetWorld() != nullptr)
			SpawnedActor = GetWorld()->SpawnActor<AMyActor>(AMyActor::StaticClass(), newspawnvector, FRotator(0, 0, 0),
			                                                SpawnParameters);
		if (index <= FMath::Pow(BlockNumber, 2))
		{
		
			Z_OffsetAmount += 10;
			OffSetAmount += 10;
		}
		for (int32 index_j{BlockNumber}; index_j < (BlockNumber); index_j ++)
		{
			const FVector newspawnvector_2 = FVector(X_Offset, Y_Offset, Z_Offset);
			SpawnedActor = GetWorld()->SpawnActor<AMyActor>(AMyActor::StaticClass(), newspawnvector_2,
															FRotator(0, 0, 0),
															SpawnParameters);
		}
		GetWorldTimerManager().SetTimer(DestroyTimer, this, &AMiniProjects::DestroyActor, 10);
	}
}

void AMiniProjects::DestroyActor()
{
	if (SpawnedActor != nullptr)
	{
		Print("Actor Destroyed!!", FColor::Red);
		SpawnedActor->Destroy();
	}
}
