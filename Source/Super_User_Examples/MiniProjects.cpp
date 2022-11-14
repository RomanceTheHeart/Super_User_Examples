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
	int32 blockcounter{0};
	constexpr int32 BlockNumber{blockindex * blockindex};
	float OffSetAmount{0};
	float Z_OffsetAmount{0.0f};
	//float worldtime = GetGameTimeSinceCreation();
	FActorSpawnParameters SpawnParameters;

	float X_Offset;
	float Y_Offset;
	float Z_Offset;


	for (int32 index{0}; index < FMath::Pow(BlockNumber, 2); index ++)
	{
		OffSetAmount = {150};
		X_Offset = {((index / BlockNumber) * OffSetAmount)};
		Y_Offset = {((index % BlockNumber) * OffSetAmount)};
		Z_Offset = {((blockindex % BlockNumber) * Z_OffsetAmount)};

		const FVector newspawnvector = FVector(X_Offset, Y_Offset, Z_Offset);

		if (GetWorld() != nullptr)
		{
			SpawnedActor = GetWorld()->SpawnActor<AMyActor>(AMyActor::StaticClass(), newspawnvector, FRotator(0, 0, 0),
			                                                SpawnParameters);
		}
		blockcounter++;
	}

	for (int32 index_j{0}; index_j <= FMath::Pow(BlockNumber, 2); index_j ++)
	{
		Z_OffsetAmount = 50;
		OffSetAmount = 140;
		X_Offset = {((index_j / BlockNumber) * OffSetAmount)};
		Y_Offset = {((index_j % BlockNumber) * OffSetAmount)};
		Z_Offset = {((blockindex % BlockNumber) * Z_OffsetAmount)};
		const FVector newspawnvector_2 = FVector(X_Offset, Y_Offset, Z_Offset);
		SpawnedActor = GetWorld()->SpawnActor<AMyActor>(AMyActor::StaticClass(), newspawnvector_2,
		                                                FRotator(0, 0, 0),
		                                                SpawnParameters);
		blockcounter++;
	}

	Print(FString::FromInt(blockcounter), FColor::Red);


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
