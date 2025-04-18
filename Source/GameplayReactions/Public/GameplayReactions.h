// Copyright (c) 2025, Balbjorn Bran. All rights reserved.

#pragma once

#include "Modules/ModuleManager.h"

class FGameplayReactionsModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};
