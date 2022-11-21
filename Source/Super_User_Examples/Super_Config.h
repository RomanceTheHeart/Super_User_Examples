#pragma once


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