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


	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement", meta = (AllowPrivateAccess = "true"))
	FVector CurrentLocation{FVector::ZeroVector};
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement", meta = (AllowPrivateAccess = "true"))
	FVector Direction{FVector::ZeroVector};

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Movement", meta = (AllowPrivateAccess = "true"))
	float Speed{0.0f};

	TArray<AStaticMeshActor*> StaticMeshActors;
public:
	ADefaultMeteor();
	UPROPERTY()
	UMaterialInterface* Material;

	UPROPERTY()
	UMaterialInstanceDynamic* Dissolve_Material;
	FVector GetMeteorVector() const { return Direction; }
	UFUNCTION(BlueprintCallable, Category ="Meteor Settings")
	USphereComponent* GetRoot() { return CollisionSphere; }

protected:
	virtual void BeginPlay() override;


public:
	virtual void Tick(float DeltaTime) override;
	AActor* GetActor() { return this; }
};
