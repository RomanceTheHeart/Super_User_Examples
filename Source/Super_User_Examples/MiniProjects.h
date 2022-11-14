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
static void Print(const FString& message, const FColor& color)
{
	if(GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1,30.0,color,message);
	}
}

static void PrintLog(const FString &message)
{
	UE_LOG(LogTemp,Warning,TEXT("%s"),*message);

	
}
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
