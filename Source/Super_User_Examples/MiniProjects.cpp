// Fill out your copyright notice in the Description page of Project Settings.


#include "MiniProjects.h"
#include "MyActor.h"
#include "Kismet/GameplayStatics.h"


void AMiniProjects::BeginPlay()
{
	Super::BeginPlay();



	FTransform SpawnLocation;

	constexpr int32 Blockindex{2};
	int32 Blockcounter{0};
	 int32 BlockNumber = {static_cast<int32>(FMath::Pow(Blockindex,2))};
	float OffSetAmount{0};
	float Z_OffsetAmount{0.0f};
	//float worldtime = GetGameTimeSinceCreation();
	FActorSpawnParameters SpawnParameters;

	float X_Offset{0};
	float Y_Offset{0};
	float Z_Offset{0};


	for (int32 index{0}; index < FMath::Pow(BlockNumber, 2); index ++)
	{
		OffSetAmount = {150};
		X_Offset = {((index / BlockNumber) * OffSetAmount)};
		Y_Offset = {((index % BlockNumber) * OffSetAmount)};
		Z_Offset = {((Blockindex % BlockNumber) * Z_OffsetAmount)};
		Z_OffsetAmount =300;
		const FVector newspawnvector = FVector(X_Offset, Y_Offset, Z_Offset);

		if (GetWorld() != nullptr)
		{
			SpawnedActor = GetWorld()->SpawnActor<AMyActor>(AMyActor::StaticClass(), newspawnvector, FRotator(0, 0, 0),
			                                                SpawnParameters);
		}
		Blockcounter++;
	}

	for (int32 index_j{Blockcounter}; index_j >= 0; index_j --)
	{
		Z_OffsetAmount = 1900;
		Z_OffsetAmount -= (Blockcounter-index_j) * 50;
		OffSetAmount += 1;
		Y_Offset = {((index_j % BlockNumber) * OffSetAmount)};
		X_Offset = {((index_j / BlockNumber) * OffSetAmount)};
		Z_Offset = {((Blockindex % BlockNumber) * Z_OffsetAmount)};

		//This Works. Just Adjust the scaler-Function to form a pyramid. 

		const FVector newspawnvector_2 = FVector(X_Offset, Y_Offset, Z_Offset);
		SpawnedActor = GetWorld()->SpawnActor<AMyActor>(AMyActor::StaticClass(), newspawnvector_2,
		                                                FRotator(0, 0, 0),
		                                                SpawnParameters);
		
	
	}
	Print("This is index_j: ", FColor::Red);
	Print(FString::FromInt(Blockcounter), FColor::Red);
	Print("Actor's Spawned.", FColor::Blue);


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
