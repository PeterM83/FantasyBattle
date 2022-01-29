// Fill out your copyright notice in the Description page of Project Settings.


#include "StructLibrary.h"

bool UStructLibrary::Equals_Profile(const FManProfile& A, const FManProfile& B)
{
	return A.ProfileName.ToString() == B.ProfileName.ToString();
}

bool UStructLibrary::Equals_Army(const FArmyStat& A, const FArmyStat& B)
{
	return A.ArmyName == B.ArmyName;
}