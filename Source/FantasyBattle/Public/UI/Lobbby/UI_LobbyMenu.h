// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
//#include "Components/BackgroundBlur.h"
#include "Interfaces/LobbyInterface.h"
#include "UI_LobbyMenu.generated.h"

class UTextBlock;
class UButton;
class UComboBoxString;
class UBackgroundBlur;

/**
 * 
 */
UCLASS()
class FANTASYBATTLE_API UUI_LobbyMenu : public UUserWidget
{
	GENERATED_BODY()

public:
		
	virtual bool Initialize() override;
	
	void SetupMenu(int32 OwnerID, FString PlayerName);

	void SetupArmyInfo(int32 MaxSize, TArray<FArmyStat> Armies);

	UFUNCTION(BlueprintImplementableEvent)
	void CreatePlayerWidget(const FString& PlayerName, const int32 PlayerID);

	void SetLobbyInterface(ILobbyInterface* Interface);

protected:

	UPROPERTY(BlueprintReadOnly)
	int32 ParentID;

	UFUNCTION(BlueprintImplementableEvent)
	void UpdateReadyState(bool newValue, int32 PlayerID);

	UPROPERTY(BlueprintReadOnly)
	int32 MaxArmySize;
	
	UPROPERTY(VisibleAnywhere, meta = (BindWidget), Category="Component")
	UButton* Ready_Btn;
	
	UPROPERTY(VisibleAnywhere, meta = (BindWidget), Category="Component")
	UComboBoxString* Armies_Combo;
	
	UPROPERTY(VisibleAnywhere, meta = (BindWidget), Category="Component")
	UTextBlock* ArmySize_Text;
	
	UPROPERTY(VisibleAnywhere, meta = (BindWidget), Category="Component")
	UTextBlock* ReadyBtn_Text;
	
	UPROPERTY(VisibleAnywhere, meta = (BindWidget), Category="Component")
	UBackgroundBlur* BG_Blur;

private:
	ILobbyInterface* LobbyInterface;

	UPROPERTY(VisibleAnywhere)
	bool bIsReady;
	
	void UpdateReadyBtnText();
	
	UFUNCTION()
	void ReadyClick();
	
	UFUNCTION()
	void ArmySelectionChanged(FString SelectedItem, ESelectInfo::Type SelectionType);
	
	
};
