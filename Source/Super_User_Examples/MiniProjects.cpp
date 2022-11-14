// Fill out your copyright notice in the Description page of Project Settings.


#include "MiniProjects.h"

#include "MyActor.h"
#include "Kismet/GameplayStatics.h"


void AMiniProjects::BeginPlay()
{
	Super::BeginPlay();
	Print("Actor Spawned.", FColor::Blue);


	FTransform SpawnLocation;

	constexpr int32 blockindex{2};
	constexpr int32 BlockNumber{blockindex * blockindex};
	float OffSetAmount{100.0};
	float Z_OffsetAmount{0.0f};
	//float worldtime = GetGameTimeSinceCreation();
	FActorSpawnParameters SpawnParameters;

	 float X_Offset;
	float Y_Offset;
	const float Z_Offset = {((blockindex % BlockNumber) * Z_OffsetAmount)};


	for (int32 index{0}; index < BlockNumber * BlockNumber; index ++)
	{
		X_Offset = {((index / BlockNumber) * OffSetAmount)};
		Y_Offset = {((index % BlockNumber) * OffSetAmount)};
		
		const FVector newspawnvector = FVector(X_Offset, Y_Offset, Z_Offset);

		if (GetWorld() != nullptr)
		{
			SpawnedActor = GetWorld()->SpawnActor<AMyActor>(AMyActor::StaticClass(), newspawnvector, FRotator(0, 0, 0),
															SpawnParameters);
		}

		
	}
	
	 if  (blockindex >= BlockNumber)
	{
		for (int32 index_j{BlockNumber}; index_j < BlockNumber * blockindex; index_j ++)
		{
			Z_OffsetAmount = 100;
			OffSetAmount += .5;
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
