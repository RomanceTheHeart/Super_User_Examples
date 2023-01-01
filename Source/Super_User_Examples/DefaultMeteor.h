// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DestructibleInterface.h"
#include "Components/SphereComponent.h"
#include "Engine/StaticMeshActor.h"
#include "GameFramework/Actor.h"
#include "GeometryCollection/GeometryCollectionActor.h"
#include "GeometryCollection/GeometryCollectionComponent.h"
#include "GeometryCollection/GeometryCollectionObject.h"
#include "DefaultMeteor.generated.h"

UCLASS()
class SUPER_USER_EXAMPLES_API ADefaultMeteor : public AActor
{
	GENERATED_BODY()

private:
	UINT64 ImpulseVelocity{100};
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Meteor Settings", meta = (AllowPrivateAccess = "true"))
	USphereComponent* CollisionSphere;


	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Meteor Settings", meta = (AllowPrivateAccess = "true"))
	UGeometryCollection* Collection;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Meteor Settings", meta = (AllowPrivateAccess = "true"))
	UGeometryCollectionComponent* ComponentCollection; 

	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Meteor Settings", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* Mesh_1;

	//TSharedPtr<UGeometryCollection> geometry_location;

	
	UPROPERTY(VisibleAnywhere)
	FVector SpawnLocation;
	UPROPERTY()
	FVector DestructionLocation;
	//UPROPERTY(Transient)
	//mutable TArray<FString> ActorsToCollide;



	
public:
	// Sets default values for this actor's properties
	ADefaultMeteor();
	UPROPERTY()
	UMaterialInterface* Material;

	UPROPERTY()
	UMaterialInstanceDynamic* Dissolve_Material;
	FVector GetSpawnLocation() const { return SpawnLocation; }
	void SetSpawnLocation(const FVector location) { SpawnLocation = location; }
	UFUNCTION(BlueprintCallable,Category ="Meteor Settings")
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
