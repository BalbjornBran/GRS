// Copyright (c) 2025, Balbjorn Bran. All rights reserved.

#include "Reactions/GR_SimpleLog.h"


void UGR_SimpleLog::ExecuteReaction_Implementation(AActor* InstigatorActor, AActor* TargetActor)
{
	switch (LogVerbosity)
	{
	case EGRLogVerbosity::Warning:
		GR_LOG_ARGS(Warning, "%s", *LogMessage);
		break;
	case EGRLogVerbosity::Error:
		GR_LOG_ARGS(Error, "%s", *LogMessage);
		break;
	case EGRLogVerbosity::Log:
		GR_LOG_ARGS(Display, "%s", *LogMessage);
		break;
	case EGRLogVerbosity::Verbose:
		GR_LOG_ARGS(Verbose, "%s", *LogMessage);
		break;
	case EGRLogVerbosity::VeryVerbose:
		GR_LOG_ARGS(VeryVerbose, "%s", *LogMessage);
		break;
	default:
		GR_LOG_ARGS(Log, "%s", *LogMessage);
		break;
	}
}
