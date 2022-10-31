#pragma once
#include "Misc/MessageDialog.h"
#include "Widgets/Notifications/SNotificationBackground.h"
#include "Framework/Notifications/NotificationManager.h"
#include "Widgets/Notifications/SNotificationList.h"


inline void Print(const FString& message, const FColor& color)
{
	if(GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1,30.0,FColor::Black,TEXT("This Works!"));
	}
}

inline void PrintLog(const FString &message)
{
	UE_LOG(LogTemp,Warning,TEXT("%s"),*message);

	
}

inline EAppReturnType::Type ShowDialog(EAppMsgType::Type m_type, const FString &message, bool b_is_warning = true)
{
	if(b_is_warning == true)
	{
		const FText MessageTitle = FText::FromString("Warning");

		return 	FMessageDialog::Open(m_type,FText::FromString(message),&MessageTitle);
		
	}
	else
	{
		return FMessageDialog::Open(m_type,FText::FromString(message));
	}
	
	
}
void ShowNotificationInfo(const FString &message)
{
	//This function adds a notification message to the screen.
	//This function needs further research.
	
	FNotificationInfo NotifyInfo(FText::FromString(message));
	NotifyInfo.bUseLargeFont = true;
	NotifyInfo.FadeOutDuration =7.5;
	FSlateNotificationManager::Get().AddNotification(NotifyInfo);
}