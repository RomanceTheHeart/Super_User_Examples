// Fill out your copyright notice in the Description page of Project Settings.


#include "MiniProjects.h"

#include "MyActor.h"
#include "Kismet/GameplayStatics.h"


void AMiniProjects::BeginPlay()
{
	Super::BeginPlay();
	Print("Actor Spawned.", FColor::Blue);


	FTransform SpawnLocation;

	const int32 blockindex{8};
	const int32 BlockNumber{blockindex * blockindex};
	const float OffSetAmount{100.0};
	float Z_OffsetAmount{3.5};
	//float worldtime = GetGameTimeSinceCreation();
	FActorSpawnParameters SpawnParameters;
	for (int32 index{0}; index < BlockNumber; index ++)
	{
		const float X_Offset{((index / BlockNumber) * OffSetAmount)};
		const float Y_Offset = {((index % BlockNumber) * OffSetAmount)};
		const float Z_Offset = {((index % BlockNumber) * Z_OffsetAmount)};
		const FVector newspawnvector = FVector(X_Offset, Y_Offset, Z_Offset);
		if(BlockNumber/blockindex <= blockindex){Z_OffsetAmount = 100.0f;}
		if (GetWorld() != nullptr)
			SpawnedActor = GetWorld()->SpawnActor<AMyActor>(AMyActor::StaticClass(), newspawnvector, FRotator(0, 0, 0),
			                                                SpawnParameters);
	}


	GetWorldTimerManager().SetTimer(DestroyTimer, this, &AMiniProjects::DestroyActor, 10);
}

void AMiniProjects::DestroyActor()
{
	if (SpawnedActor != nullptr)
	{
		Print("Actor Destroyed!!", FColor::Red);
		SpawnedActor->Destroy();
	}
}
