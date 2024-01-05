class CfgPatches
{
	class azw_ClassicWalk
	{
		units[] = {};
		weapons[] = {};
		requiredVersion = 1;
		requiredAddons[] = {"DZ_Data","DZ_Surfaces"};
	};
};
class CfgMods
{
	class ClassicWalkScripts
	{
		dir = "azw_ClassicWalk\Scripts";
		picture = "";
		action = "";
		hideName = 1;
		hidePicture = 1;
		name = "ClassicWalk";
		credits = "JohnMcLane";
		author = "AndreZ";
		authorID = "0";
		version = "1.0";
		extra = 0;
		type = "mod";
		dependencies[] = {"World"};
		class defs
		{
			class worldScriptModule
			{
				value = "";
				files[] = {"azw_ClassicWalk/Scripts/4_World"};
			};
		};
	};
};
