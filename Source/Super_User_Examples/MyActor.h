// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SphereComponent.h"
#include "Engine/StaticMeshActor.h"
#include "GameFramework/Actor.h"
#include "MyActor.generated.h"

UCLASS()
class SUPER_USER_EXAMPLES_API AMyActor : public AActor
{
	GENERATED_BODY()

private:
	UPROPERTY()
	USphereComponent* CollisionSphere;
	UPROPERTY()
	UStaticMeshComponent* Mesh_1;
	UPROPERTY(VisibleAnywhere)
	FVector SpawnLocation;
	UPROPERTY()
	FVector DestructionLocation;
	UPROPERTY(Transient)
	 mutable TArray<FString> ActorsToCollide;
	UPROPERTY()
	AActor* StaticMesh = nullptr;
public:
	// Sets default values for this actor's properties
	AMyActor();
	UPROPERTY()
	UMaterialInterface* Material;

	UPROPERTY()
	UMaterialInstanceDynamic* Dissolve_Material;
	FVector GetSpawnLocation() const { return SpawnLocation; }
	void SetSpawnLocation(const FVector location){SpawnLocation = location;}


	USphereComponent* GetRoot() { return CollisionSphere; }
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	//virtual void  NotifyHit(AActor* OtherActor) override;


public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	AActor* GetActor() { return this; }
};
