// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MyPlayerController.generated.h"

/**
 * 
 */
 enum RotorVersion{
 	IV = 4,
 	V = 5,
 	VI = 6,
 	VII = 7,
 	VIII = 8
 };

UCLASS()
class CIPHER_API AMyPlayerController : public APlayerController
{
	GENERATED_BODY()
	
};
