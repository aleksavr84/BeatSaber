#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PawnOverlay.generated.h"

UCLASS()
class BEATSABER_API UPawnOverlay : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* ScoreAmount;
};
