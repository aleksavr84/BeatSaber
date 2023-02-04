#pragma once

UENUM(BlueprintType)
enum class EHand : uint8
{
	ECH_Left UMETA(DisplayName = "Left"),
	ECH_Right UMETA(DisplayName = "Right"),

	ECH_MAX UMETA(DisplayName = "DefalutMAX")
};

UENUM(BlueprintType)
enum class EBeatSpawnSide : uint8
{
	EBS_Left UMETA(DisplayName = "Left"),
	EBS_Right UMETA(DisplayName = "Right"),

	EBS_MAX UMETA(DisplayName = "DefalutMAX")
};

UENUM(BlueprintType)
enum class EBeatDirection : uint8
{
	EBD_Left UMETA(DisplayName = "Left"),
	EBD_Right UMETA(DisplayName = "Right"),
	EBD_Top UMETA(DisplayName = "Top"),
	EBD_Down UMETA(DisplayName = "Down"),

	EBD_MAX UMETA(DisplayName = "DefalutMAX")
};

UENUM(BlueprintType)
enum class EMovementDirection : uint8
{
	EMD_Stopped UMETA(DisplayName = "Stopped"),
	EMD_Left UMETA(DisplayName = "Left"),
	EMD_Right UMETA(DisplayName = "Right"),
	EMD_Up UMETA(DisplayName = "Up"),
	EMD_Down UMETA(DisplayName = "Down"),

	EMD_MAX UMETA(DisplayName = "DefalutMAX")
};