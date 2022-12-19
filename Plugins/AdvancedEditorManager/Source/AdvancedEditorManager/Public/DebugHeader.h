#pragma once
#include "Misc/MessageDialog.h"
#include "Widgets/Notifications/SNotificationBackground.h"
#include "Framework/Notifications/NotificationManager.h"
#include "Widgets/Notifications/SNotificationList.h"

#define Print(String,Color)if(GEngine) GEngine->AddOnScreenDebugMessage(-1,300.0,Color,String)
#define PrintLog(String) UE_LOG(LogTemp,Warning,TEXT("%s"),*String);

namespace Debug
{
	inline EAppReturnType::Type ShowDialog(EAppMsgType::Type m_type, const FString& message, bool b_is_warning = true)
	{
		if (b_is_warning == true)
		{
			const FText MessageTitle = FText::FromString("Warning");

			return FMessageDialog::Open(m_type, FText::FromString(message), &MessageTitle);
		}
		else
		{
			return FMessageDialog::Open(m_type, FText::FromString(message));
		}
	}

	void ShowNotificationInfo(const FString& message)
	{
		//This function adds a notification message to the screen.
		//This object is declared as a struct. It's constructor takes in an info structure as a parameter.

		FNotificationInfo NotifyInfo(FText::FromString(message));
		NotifyInfo.bUseLargeFont = true;
		NotifyInfo.FadeOutDuration = 7.5;
		FSlateNotificationManager::Get().AddNotification(NotifyInfo);
	}
}
