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

	FString ReadString = "";
	// Try reading the file
	if (!FFileHelper::LoadFileToString(ReadString, *FilePath))
	{
		bOutSuccess = false;
		OutInfoMessage = FString::Printf(TEXT("Read String From File Failed - Was not able to read file"));
		return "";
	}
	// Split the array into 
	TArray<FString> outStringArr;
	ReadString.ParseIntoArray(outStringArr, LINE_TERMINATOR, true);

	// Trim the strings before processing
	TArray<FString> newStringArr;

	for (FString String : outStringArr) {
		String.TrimStartAndEndInline();
		// TODO: We offset the characters by -20 to decode the message
		FString newString = "";
		for (int i = 0; i < String.Len(); i++) {
			newString += char(String[i] - 20);
		}
		newStringArr.Add(newString);
	}

	// Sort in Descending order
	newStringArr.Sort([](FString A, FString B) { return FCString::Atoi(*A) > FCString::Atoi(*B); });

	FString ResultString = "";
	// Construct new high score string
	for (FString str : newStringArr) {
		ResultString += str + LINE_TERMINATOR;
	}


	bOutSuccess = true;
	OutInfoMessage = FString::Printf(TEXT("Read String From File succeeded"));
	return ResultString;
}


FString UReadWriteFile::WriteStringToFile(FString FilePath, FString String, bool& bOutSuccess, FString& OutInfoMessage)
{
	// TODO: We offset the characters in the string by +20 to encode the message
	for (int i = 0; i < String.Len(); i++) {
		if (String[i] != '\n' and String[i] != '\r') {
			String[i] = String[i] + 20;
		}
	}

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

