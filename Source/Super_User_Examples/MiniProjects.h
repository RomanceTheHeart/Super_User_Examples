// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyActor.h"
#include "GameFramework/GameModeBase.h"
#include "MiniProjects.generated.h"

/**
 *
 * 
 */

UCLASS()

class SUPER_USER_EXAMPLES_API AMiniProjects : public AGameModeBase
{
	GENERATED_BODY()

private:
	FTimerHandle DestroyTimer;
public:
	UPROPERTY()
	class AMyActor* SpawnedActor;

	UFUNCTION()
	void DestroyActor();
	
	virtual void BeginPlay() override;
};
