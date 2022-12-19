// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "Widgets/SCompoundWidget.h"
//the basics of slate widgets
// we need to pass in some macros - study the definition. 
// create a construction function.
class SAdvancedDeletionTab : public SCompoundWidget
{
	SLATE_BEGIN_ARGS(SAdvancedDeletionTab){}
	SLATE_END_ARGS()
public:
	void Construct(const FArguments Args);
};
