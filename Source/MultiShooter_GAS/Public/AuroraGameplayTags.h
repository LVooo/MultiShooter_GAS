// Copyright Weilin

#pragma once

#include "CoreMinimal.h"

/**
 * AuroraGameplayTags
 *
 * Singleton containing native Gameplay Tags
 */
struct FAuroraGameplayTags
{
public:
 static const FAuroraGameplayTags& Get() { return GameplayTags; }
 static void InitializeNativeGameplayTags();

protected:

private:
 static FAuroraGameplayTags GameplayTags;
};
