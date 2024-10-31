// Fill out your copyright notice in the Description page of Project Settings.


#include "ReadWriteFile.h"
#include "HAL/PlatformFilemanager.h"

FString UReadWriteFile::ReadStringFromFile(FString FilePath, bool& bOutSuccess, FString& OutInfoMessage)
{
	// Check if the file Exists
	if (!FPlatformFileManager::Get().GetPlatformFile().FileExists(*FilePath))
	{
		bOutSuccess = false;
		OutInfoMessage = FString::Printf(TEXT("Read String From File Failed - File doesn't exist"));
		return "";
	}

	FString ReturnString = "";
	// Try reading the file
	if (!FFileHelper::LoadFileToString(ReturnString, *FilePath))
	{
		bOutSuccess = false;
		OutInfoMessage = FString::Printf(TEXT("Read String From File Failed - Was not able to read file"));
		return "";
	}

	bOutSuccess = true;
	OutInfoMessage = FString::Printf(TEXT("Read String From File succeeded"));
	return ReturnString;
}


FString UReadWriteFile::WriteStringToFile(FString FilePath, FString String, bool& bOutSuccess, FString& OutInfoMessage)
{
	// Try writting to file
	if (!FFileHelper::SaveStringToFile(String, *FilePath))
	{
		bOutSuccess = false;
		OutInfoMessage = FString::Printf(TEXT("Write String To File Failed - Was not able to write file"));
		return "";
	}

	bOutSuccess = true;
	OutInfoMessage = FString::Printf(TEXT("Write String To File succeeded"));
	return "";
}

