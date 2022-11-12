// Fill out your copyright notice in the Description page of Project Settings.


#include "MiniProjects.h"

#include "MyActor.h"
#include "Kismet/GameplayStatics.h"


void AMiniProjects::BeginPlay()
{
	Super::BeginPlay();
	Print("Actor Spawned.",FColor::Blue);


	FTransform SpawnLocation;

	SpawnedActor = GetWorld()->SpawnActor<AMyActor>(AMyActor::StaticClass(),SpawnLocation);

	FTimerHandle DestroyTimer;
	GetWorldTimerManager().SetTimer(DestroyTimer,this,&AMiniProjects::DestroyActor,10);

}

void AMiniProjects::DestroyActor()
{
		
	if(SpawnedActor != nullptr)
	{
		Print("Actor Destroyed!!", FColor::Red);
		SpawnedActor->Destroy();
	}
}