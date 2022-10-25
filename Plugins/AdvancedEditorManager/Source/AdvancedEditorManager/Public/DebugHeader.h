#pragma once

void Print(const FString& message, const FColor& color)
{
	if(GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1,30.0,FColor::Black,TEXT("This Works!"));
	}
}

void PrintLog(const FString &message)
{
	UE_LOG(LogTemp,Warning,TEXT("%s"),*message);

	
}