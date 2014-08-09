/**
 * vim: set ts=4 :
 * =============================================================================
 * SourceMod
 * Copyright (C) 2004-2008 AlliedModders LLC.  All rights reserved.
 * =============================================================================
 *
 * This program is free software; you can redistribute it and/or modify it under
 * the terms of the GNU General Public License, version 3.0, as published by the
 * Free Software Foundation.
 * 
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more
 * details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * As a special exception, AlliedModders LLC gives you permission to link the
 * code of this program (as well as its derivative works) to "Half-Life 2," the
 * "Source Engine," the "SourcePawn JIT," and any Game MODs that run on software
 * by the Valve Corporation.  You must obey the GNU General Public License in
 * all respects for all other code used.  Additionally, AlliedModders LLC grants
 * this exception to all derivative works.  AlliedModders LLC defines further
 * exceptions, found in LICENSE.txt (as of this writing, version JULY-31-2007),
 * or <http://www.sourcemod.net/license.php>.
 *
 * Version: $Id$
 */

#ifndef _INCLUDE_SOURCEMOD_PROFILETOOLMANAGER_H_
#define _INCLUDE_SOURCEMOD_PROFILETOOLMANAGER_H_

#include <IShareSys.h>


/**
 * @file IProfileToolManager.h
 * @brief Abstracts profiling tools.
 */

#define SMINTERFACE_PROFILETOOLMANAGER_NAME			"IProfileToolManager"
#define SMINTERFACE_PROFILETOOLMANAGER_VERSION		1

namespace SourceMod
{
	#define SM_PROFILE_GROUP_UNACCOUNTED	NULL			/**< Unaccounted profile group */
	#define SM_PROFILE_GROUP_SOURCEMOD		"SourceMod"		/**< SourceMod profile group */
	#define SM_PROFILE_GROUP_SOURCEPAWN		"SourcePawn"	/**< SourcePawn profile group */

	/**
	 * @brief Encapsulates a profiling tool that may be attached to SourcePawn.
	 */
	class IProfilingTool
	{
	public:
		/**
		 * @brief Return the name of the profiling tool.
		 *
		 * @return                  Profiling tool name.
		 */
		virtual const char *Name() = 0;

		/**
		 * @brief Description of the profiler.
		 *
		 * @return                  Description.
		 */
		virtual const char *Description() = 0;

		/**
		 * @brief Called to render help text.
		 *
		 * @param  render           Function to render one line of text.
		 */
		virtual void RenderHelp(void (*render)(const char *fmt, ...)) = 0;
	
		/**
		 * @brief Initiate a start command.
		 *
		 * Initiate start commands through a profiling tool, returning whether
		 * or not the command is supported. If starting, SourceMod will generate
		 * events even if it cannot signal the external profiler.
		 */
		virtual bool Start() = 0;

		/**
		 * @brief Initiate a stop command.
		 *
		 * @param render            Function to render any help messages.
		 */
		virtual void Stop(void (*render)(const char *fmt, ...)) = 0;
	
		/**
		 * @brief Returns whether or not the profiler is currently profiling.
		 *
		 * @return                  True if active, false otherwise.
		 */
		virtual bool IsActive() = 0;

		/**
		 * @brief Returns whether the profiler is attached.
		 *
		 * @return                  True if attached, false otherwise.
		 */
		virtual bool IsAttached() = 0;

		/**
		 * @brief Enters the scope of an event.
		 *
		 * LeaveScope() mus be called exactly once for each call to EnterScope().
		 *
		 * @param group             A named budget group, or NULL for the default.
		 * @param name              Event name.
		 */
		virtual void EnterScope(const char *group, const char *name) = 0;
		
		/**
		 * @brief Leave a profiling scope. This must be called exactly once for
		 * each call to EnterScope().
		 */
		virtual void LeaveScope() = 0;
	};

	/**
	 * @brief Manages profiling tools.
	 */
	class IProfileToolManager : public SMInterface
	{
	public:
		const char *GetInterfaceName()
		{
			return SMINTERFACE_PROFILETOOLMANAGER_NAME;
		}
		unsigned int GetInterfaceVersion()
		{
			return SMINTERFACE_PROFILETOOLMANAGER_VERSION;
		}

	public:
		/**
		 * @brief Registers a new profiling tool with the manager.
		 */
		virtual void RegisterTool(IProfilingTool *tool) = 0;

		/**
		 * @brief Returns whether or not a profiler is currently active.
		 */
		virtual bool IsActive() const = 0;

		/**
		 * @brief Enters the scope of an event of the active profiler, if one exists.
		 *
		 * LeaveScope() mus be called exactly once for each call to EnterScope().
		 *
		 * @param group             A named budget group, or NULL for the default.
		 * @param name              Event name.
		 */
		virtual void EnterScope(const char *group, const char *name) = 0;
		/**
		 * @brief Leave a profiling scope of the active profiler, if one exists.
		 * This must be called exactly once for each call to EnterScope().
		 */
		virtual void LeaveScope() = 0;
	};
}

#endif //_INCLUDE_SOURCEMOD_PROFILETOOLMANAGER_H_
